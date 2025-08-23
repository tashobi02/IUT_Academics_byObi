#!/bin/bash

usage() {
    echo "Usage: $0 -path <path_to_task_directory>"
    exit 1
}

while [[ $# -gt 0 ]]; do
    case "$1" in
        -path)
            shift
            if [[ -z "$1" ]]; then
                echo "$0: error: missing argument for '-path'"
                usage
            fi
            TASK_PATH="$1"
            shift
            ;;
        -*)
            echo "$0: error: unrecognized option '$1'"
            usage
            ;;
        *)
            echo "$0: error: unexpected argument '$1'"
            usage
            ;;
    esac
done

if [[ -z "$TASK_PATH" ]]; then
    echo "$0: error: missing required option '-path'"
    usage
fi

GREEN='\e[32m'
RED='\e[31m'
BOLDGREEN='\e[1;32m'
BOLDRED='\e[1;31m'
RESET='\e[0m'

TIME_LIMIT=$(grep 'time_limit' "$TASK_PATH"/limits.yaml | awk '{print $2}')
MEMORY_LIMIT=$(grep 'memory_limit' "$TASK_PATH"/limits.yaml | awk '{print $2}')

declare -A verdict_priority=(
    ["COMPILATION ERROR"]=4
    ["RUNTIME ERROR"]=3
    ["TIME/MEMORY LIMIT EXCEEDED"]=2
    ["WRONG ANSWER"]=1
    ["ACCEPTED"]=0
)

declare -a final_results

clean_file() {
    sed -e 's/[[:space:]]\+/ /g' \
        -e 's/^ *//' \
        -e 's/ *$//' \
        -e '/^$/d' "$1" \
    | awk '{print} END{if (NR > 0) print ""}' > "$2"
}

judgeCPP() {
    local source_file="$1"
    local name=$(basename "$source_file" .cpp)
    local executable="./${name}_cpp.bin"

    g++ -std=c++17 "$source_file" -o "$executable" 2> "${name}_cpp.compile.log"
    if [ $? -ne 0 ]; then
        echo "$name.cpp: COMPILATION ERROR"
        final_results+=("$name.cpp: ${BOLDRED}COMPILATION ERROR${RESET}")
        return
    fi

    runExecutable "$name.cpp" "$executable"
    rm -f "$executable" "${name}_cpp.compile.log"
}

judgeC() {
    local source_file="$1"
    local name=$(basename "$source_file" .c)
    local executable="./${name}_c.bin"

    gcc -std=c11 "$source_file" -o "$executable" 2> "${name}_c.compile.log"
    if [ $? -ne 0 ]; then
        echo "$name.c: COMPILATION ERROR"
        final_results+=("$name.c: ${BOLDRED}COMPILATION ERROR${RESET}")
        return
    fi

    runExecutable "$name.c" "$executable"
    rm -f "$executable" "${name}_c.compile.log"
}

judgePY() {
    local source_file="$1"
    local name=$(basename "$source_file" .py)
    runExecutable "$name.py" "python3 \"$source_file\""
}

judgeJava() {
    local source_file="$1"
    local orig_name=$(basename "$source_file")
    local name_without_ext="${orig_name%.java}"
    local temp_source="Main.java"

    if ! grep -q "public[[:space:]]\+class[[:space:]]\+Main" "$source_file"; then
        echo "$orig_name: COMPILATION ERROR (Main class not found)"
        final_results+=("$orig_name: ${BOLDRED}COMPILATION ERROR${RESET}")
        return
    fi

    cp "$source_file" "$temp_source"
    javac "$temp_source" 2> "${name_without_ext}_java.compile.log"
    if [ $? -ne 0 ]; then
        echo "$orig_name: COMPILATION ERROR"
        final_results+=("$orig_name: ${BOLDRED}COMPILATION ERROR${RESET}")
        rm -f "$temp_source"
        return
    fi

    runExecutable "$orig_name" "java Main"
    rm -f Main.class "$temp_source" "${name_without_ext}_java.compile.log"
}

runExecutable() {
    local name="$1"
    local command="$2"

    echo "Judging $name..."
    highest_verdict="ACCEPTED"

    mapfile -t inputs < <(find "$TASK_PATH"/input -type f -name "input*.txt" | sort -V)

    for in_file in "${inputs[@]}"; do
        case_id=$(basename "$in_file" .txt | sed 's/input//')
        printf -v padded_case_id "%02d" "$case_id"

        ans_file="$TASK_PATH"/answer/answer${case_id}.txt
        output_file="output_file.txt"
        input_with_sentinel="input_with_sentinel.txt"

        cp "$in_file" "$input_with_sentinel"
        echo -e "\n$RANDOM" >> "$input_with_sentinel"

        full_command="ulimit -v $((MEMORY_LIMIT * 1024)); $command < \"$input_with_sentinel\" > \"$output_file\""

        /usr/bin/timeout --preserve-status -s SIGKILL "${TIME_LIMIT}s" \
            /usr/bin/time -f "TIME=%e MEM=%M" -o usage.log \
            bash -c "$full_command" 2>/dev/null

        status=$?
        read time_s mem_kb < <(awk -F '[ =]' '{print $2, $4}' usage.log 2>/dev/null)
        rm -f usage.log

        time_ms=$(echo "($time_s * 1000 + 0.5)/1" | bc)
        mem_mb=$(echo "($mem_kb / 1024 + 0.5)/1" | bc)

        if [ $status -eq 124 ] || [ $status -eq 137 ]; then
            test_verdict="TIME/MEMORY LIMIT EXCEEDED"
        elif [ $status -ne 0 ]; then
            test_verdict="RUNTIME ERROR"
        else
            clean_file "$ans_file" ans_clean.txt
            clean_file "$output_file" output_clean.txt

            if ! diff -q output_clean.txt ans_clean.txt > /dev/null; then
                test_verdict="WRONG ANSWER"
            else
                test_verdict="ACCEPTED"
            fi

            rm -f output_clean.txt ans_clean.txt
        fi

        if [ "$test_verdict" = "ACCEPTED" ]; then
            echo -e "Test $padded_case_id: ${GREEN}ACCEPTED${RESET} [${time_ms}ms, ${mem_mb}MB]"
        else
            echo -e "Test $padded_case_id: ${RED}$test_verdict${RESET}"
        fi

        if [ ${verdict_priority[$test_verdict]} -gt ${verdict_priority[$highest_verdict]} ]; then
            highest_verdict="$test_verdict"
        fi
    done

    echo

    if [ "$highest_verdict" = "ACCEPTED" ]; then
        final_results+=("$name: ${BOLDGREEN}$highest_verdict${RESET}")
    else
        final_results+=("$name: ${BOLDRED}$highest_verdict${RESET}")
    fi

    rm -f "$input_with_sentinel" "$output_file"
}

mapfile -t source_files < <(find "$TASK_PATH"/submission -type f \( -name "*.cpp" -o -name "*.c" -o -name "*.py" -o -name "*.java" \) | sort)

for source_file in "${source_files[@]}"; do
    case "$source_file" in
        *.cpp)  judgeCPP "$source_file" ;;
        *.c)    judgeC "$source_file" ;;
        *.py)   judgePY "$source_file" ;;
        *.java) judgeJava "$source_file" ;;
    esac
done

echo
echo "================== FINAL VERDICTS =================="
for result in "${final_results[@]}"; do
    echo -e "$result"
done
echo
