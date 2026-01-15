
---

# 🔹 **1. STRING DISPLAY INSTRUCTIONS**

8086 does **not** have a direct "print string" instruction from the CPU itself.

Instead, printing is done through **DOS Interrupts**, especially:

```
INT 21h → DOS functions
```

For printing a string, we use:

```
AH = 09h  (Function 9: Display String)
```

---

## 📌 **HOW DOES FUNCTION 9 PRINT A STRING?**

Function 9 expects:

* **DS:DX** = starting address of the string
* The string must end with a **'$'** character

So a valid string must be defined like:

```asm
.DATA
test_string DB 'My first string', 0Dh, 0Ah, '$'
```

### 🔍 Explanation:

* **0Dh = Carriage Return (CR)** → moves cursor to the beginning of line
* **0Ah = Line Feed (LF)** → moves cursor to next line
* **'$'** → string terminator for DOS printing

---

## ✔️ **DISPLAYING THE STRING**

Use:

```asm
MOV AH, 9
LEA DX, test_string ; or MOV DX, OFFSET test_string
INT 21h
```

### What happens here?

| Instruction         | Purpose                            |
| ------------------- | ---------------------------------- |
| MOV AH, 9           | Select DOS function 9              |
| LEA DX, test_string | Load address of the string into DX |
| INT 21h             | Display until '$' is found         |

---

# 📌 **Example 1: Printing Two Strings**

```asm
.DATA
msg1 DB 'Hello, World!', '$'
msg2 DB 0Dh,0Ah, 'Assembly is fun!', '$'

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    MOV AH, 9
    LEA DX, msg1
    INT 21h

    MOV AH, 9
    LEA DX, msg2
    INT 21h

    MOV AH, 4Ch
    INT 21h
MAIN ENDP
END MAIN
```

---

# 🔹 **2. LOOP INSTRUCTION**

The `LOOP` instruction is useful for **count-controlled repetition**.

### ✔ **How LOOP works:**

1. **Decrements CX**
2. If **CX ≠ 0 → jumps to label**
3. If **CX = 0 → continues to next instruction**

Syntax:

```
LOOP label
```

So:

```asm
MOV CX, 5
top:
    ; do something
    LOOP top
```

Will repeat **5 times**.

---

# 📌 **Example from the manual: Display 50 '*' characters**

```asm
org 100h

.DATA
.CODE
MAIN PROC
    mov ax, @DATA
    mov ds, ax

    xor cx, cx   ; CX = 0
    mov cx, 50   ; CX = 50

    mov ah, 2
    mov dl, '*'

top:
    int 21h      ; print '*'
    loop top     ; CX--, repeat until CX=0

    mov ah, 4Ch  ; exit
    int 21h
MAIN ENDP
END MAIN
```

### 🧠 Key Points:

* `mov cx, 50` → set loop count
* `loop top` → decrements CX & jumps until CX = 0

---

# 🎯 **More LOOP Examples**

---

## ✔ **Example 2: Display digits 0–9**

```asm
org 100h
mov cx, 10
mov ah, 2
mov dl, '0'

print_digits:
    int 21h    ; print current digit
    inc dl     ; next character
    loop print_digits
ret
```

**Output:**

```
0123456789
```

---

## ✔ **Example 3: Sum first 10 natural numbers**

(1 + 2 + ... + 10 = 55)

```asm
org 100h
mov cx, 10
xor ax, ax     ; AX = sum = 0
mov bx, 1

sum_loop:
    add ax, bx
    inc bx
    loop sum_loop

; Now AX = 55
ret
```

---

## ✔ **Example 4: Print Table of 5**

```asm
org 100h
mov cx, 10
mov bx, 5
mov ax, 5
mov ah, 2
mov dl, 0Dh
int 21h
mov dl, 0Ah
int 21h

table_loop:
    ; AX has current multiple
    ; convert AX to ASCII & print (not shown here)
    add ax, bx
    loop table_loop
ret
```

(Printing numbers properly requires conversion routine.)

---

org 100h

.DATA
.CODE
MAIN PROC
    mov ax, @DATA
    mov ds, ax

    xor cx, cx   ; CX = 0
    mov cx, 50   ; CX = 50

    mov ah, 2
    mov dl, '*'

top:
    int 21h      ; print '*'
    loop top     ; CX--, repeat until CX=0

    mov ah, 4Ch  ; exit
    int 21h
MAIN ENDP
END MAIN# 🔹 **Difference Between LOOP and Jumps**

| Instruction  | Behavior                          |
| ------------ | --------------------------------- |
| `LOOP label` | Decrements CX, jumps if != 0      |
| `JMP label`  | Unconditional jump                |
| `JZ`/`JNZ`   | Conditional jumps using Zero Flag |
| `JC`/`JNC`   | Conditional on Carry flag         |
| `JG`/`JL`    | Conditional on comparisons        |

So `LOOP` is best for simple **counter-based** loops.

---

# 🧠 **Summary**

| Feature          | Purpose                      |
| ---------------- | ---------------------------- |
| `INT 21h AH=09h` | Print string ending with `$` |
| `LEA DX, string` | Load string address          |
| `LOOP label`     | Repeat CX times              |
| `CX register`    | Loop counter                 |

---

# ✅ **1. PRINTING NUMBERS (DECIMAL & HEX)**

## ⭐ **(A) Printing Numbers in HEX**

Hex printing is easy because each nibble (4 bits) directly maps to a hex digit.

### **Example: Print AX in HEX**

```asm
; === Print AX as HEX ===
print_hex proc
    push ax
    push bx
    push cx
    push dx

    mov cx, 4           ; 4 hex digits for 16-bit AX
next_digit:
    rol ax, 4           ; rotate left 4 bits
    mov bl, al
    and bl, 0Fh         ; isolate 1 hex digit

    cmp bl, 9
    jbe digit_is_num
    add bl, 37h         ; A-F skip 10 characters (55 decimal)
    jmp output_digit
digit_is_num:
    add bl, 30h         ; '0' to '9'

output_digit:
    mov dl, bl
    mov ah, 02h
    int 21h
    loop next_digit

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_hex endp
```

**Example use:**

```asm
mov ax, 0ABCDh
call print_hex
```

**Output:**

```
ABCD
```

---

## ⭐ **(B) Printing Numbers in DECIMAL**

Decimal printing needs division by 10 repeatedly.

### **Example: Print AX as UNSIGNED DECIMAL**

```asm
print_dec proc
    push ax
    push bx
    push cx
    push dx

    xor cx, cx          ; digit count = 0

convert_loop:
    xor dx, dx
    mov bx, 10
    div bx              ; AX / 10 → AX=quotient, DX=remainder
    push dx             ; save remainder
    inc cx              ; count digits
    cmp ax, 0
    jne convert_loop    ; repeat until AX = 0

print_loop:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    loop print_loop

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_dec endp
```

**Example use:**

```asm
mov ax, 1234
call print_dec
```

**Output:**

```
1234
```

---

# ✅ **2. LOOP WITH ARRAYS**

The `LOOP` instruction is perfect for scanning or summing arrays.

## ⭐ **Example: Sum 5 bytes from array**

```asm
.data
arr db 10, 20, 30, 40, 50
sum dw ?

.code
mov ax, @data
mov ds, ax

mov cx, 5
mov si, offset arr
xor ax, ax

sum_loop:
    add al, [si]
    inc si
    loop sum_loop

mov sum, ax
```

Afterwards:

```
sum = 150 (0x96)
```

---

## ⭐ **Example: Print characters from an array**

```asm
.data
msg db 'HELLO', '$'

.code
mov ax, @data
mov ds, ax

mov si, offset msg
mov cx, 5
mov ah, 02h

print_loop:
    mov dl, [si]
    int 21h
    inc si
    loop print_loop
```

Output:

```
HELLO
```

---

# ✅ **3. LOOP with CONDITIONAL JUMPS**

You can combine `LOOP` + `CMP` + conditional jump for logic.

---

## ⭐ **Example: Count values > 10 in array**

```asm
.data
arr db 5, 12, 7, 25, 3, 19
count db ?

.code
mov ax, @data
mov ds, ax

mov cx, 6           ; number of elements
mov si, offset arr
xor bl, bl          ; bl = count = 0

check_loop:
    mov al, [si]
    cmp al, 10
    jle not_greater
    inc bl
not_greater:
    inc si
    loop check_loop

mov count, bl
```

After execution:

```
count = 3   ; values > 10 are 12, 25, 19
```

---

## ⭐ **Example: Loop until array element = 0**

```asm
.data
arr db 4, 3, 2, 1, 0, 9, 9, 9

.code
mov si, offset arr

search_zero:
    mov al, [si]
    cmp al, 0
    je found_zero
    inc si
    jmp search_zero

found_zero:
; SI now points to first zero
```

---

# 🎉 **SUMMARY TABLE**

| Concept                        | Usage                             |
| ------------------------------ | --------------------------------- |
| `call print_hex`               | Print AX in hex                   |
| `call print_dec`               | Print AX in decimal               |
| `LOOP label`                   | Counter-based loops using CX      |
| Arrays + LOOP                  | Summation, counting, scanning     |
| Conditional jumps              | Filtering, searching, comparisons |

---

