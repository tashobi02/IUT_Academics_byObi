
# 🔹 **1. What is an ARRAY in 8086 Assembly?**

An array = a **block of consecutive memory cells** used to store multiple values.

Examples:

### ✔ Example-1 (byte array)

```asm
A DB 48h, 65h, 6Ch, 6Ch, 6Fh, 00h
```

These are hexadecimal values stored sequentially in memory.

### ✔ Example-2 (string array)

```asm
B DB 'Hello', 0
```

The assembler converts `'Hello'` into ASCII bytes:

| Char | ASCII Hex |
| ---- | --------- |
| H    | 48h       |
| e    | 65h       |
| l    | 6Ch       |
| l    | 6Ch       |
| o    | 6Fh       |
| null | 00h       |

So array B occupies 6 bytes.

---

# 🔹 **2. Accessing Array Elements**

You can read array elements using square brackets:

### ✔ Direct index:

```asm
MOV AL, A[3]
```

Loads 4th element into AL.

### ✔ Using index register (SI/BX/DI/BP):

```asm
MOV SI, 3
MOV AL, A[SI]
```

Registers that can index arrays:

| Type              | Registers              |
| ----------------- | ---------------------- |
| offset addressing | `SI`, `DI`, `BX`, `BP` |

---

# 🔹 **3. DUP Operator (Array Initialization)**

DUP = “duplicate”

Syntax:

```
x DUP(value)
```

### ✔ Example-1:

```asm
C DB 5 DUP(0)
```

Means:

```
DB 0, 0, 0, 0, 0
```

### ✔ Example-2:

```asm
D DB 5 DUP(1,2)
```

Means:

```
DB 1,2,1,2,1,2,1,2,1,2
```

### ✔ Example-3 for 16-bit:

```asm
E DW 10 DUP(1234h)
```

Allocates 20 bytes total (10 words)

⚠ **DW cannot define strings**, only DB can.

---

# 🔹 **4. Example Program Breakdown (Given in Manual)**

The goal of the given program is:

> Calculate sum of first N values from array A where user enters N.

### **Data Definitions:**

```asm
A db 3, 1, 2       ; array storing values
B db 00h           ; storing result
message db 'Enter the value of N:$'
```

### **How Program Works:**

#### **Step 1: Set DS segment**

```asm
mov ax, @DATA
mov ds, ax
```

#### **Step 2: Initialize pointers**

```asm
mov si, OFFSET A   ; SI points to A
mov di, OFFSET B   ; DI points to B (not really used)
```

#### **Step 3: Display message**

```asm
mov dx, OFFSET message
mov ah, 09h
int 21h
```

#### **Step 4: Take user input**

```asm
mov ah, 01h
int 21h             ; user enters ASCII '3'
mov cl, al          ; CL = '3' (ASCII 33h)
sub cl, 48          ; convert ASCII '3' -> 3
```

#### **Step 5: Summation loop**

```asm
xor al, al          ; AL = sum = 0

Loop_1:
add al, [Si]        ; add array element
inc Si              ; next element
loop Loop_1         ; repeat until CL = 0
```

#### **Step 6: Convert result to ASCII**

```asm
mov bl, al
add bl, 48          ; convert numeric to ASCII
```

#### **Step 7: Display sum**

```asm
mov ah, 02h
mov dl, bl
int 21h
```

---

## 📌 **EXAMPLE EXECUTION**

Array A:

```
A[0]=3, A[1]=1, A[2]=2
```

User enters N = `3`

Sum = `3 + 1 + 2 = 6`

Output printed: `6`

---

# 🎯 **More Examples to Understand Arrays**

---

## ⭐ **Example 1: Printing Each Array Element**

```asm
.DATA
arr DB 5,10,15,20,25
msg DB 'Array Values:',0Dh,0Ah,'$'

.CODE
mov ax, @DATA
mov ds, ax

mov dx, OFFSET msg
mov ah, 09h
int 21h

mov cx, 5         ; number of elements
mov si, OFFSET arr

print_loop:
    mov al, [si]
    add al, 48
    mov dl, al
    mov ah, 02h
    int 21h
    inc si
    loop print_loop

mov ah, 4Ch
int 21h
```

**Output:**

```
Array Values:
5 10 15 20 25
```

---

## ⭐ **Example 2: Find Maximum in Array**

```asm
.DATA
arr DB 4,1,9,2,7,6
max DB ?

.CODE
mov ax, @DATA
mov ds, ax

mov si, OFFSET arr
mov al, [si]
inc si
mov cx, 5

find_max:
    cmp al, [si]
    jae skip
    mov al, [si]
skip:
    inc si
    loop find_max

mov max, al
```

Result stored in `max = 9`

---

## ⭐ **Example 3: Count Even Numbers in Array**

```asm
.DATA
arr DB 2,5,8,11,14,3
count DB ?

.CODE
mov ax, @DATA
mov ds, ax

mov cx, 6
mov si, OFFSET arr
xor bl, bl       ; count = 0

check_even:
    mov al, [si]
    test al, 1   ; check LSB
    jnz not_even ; if odd, skip
    inc bl
not_even:
    inc si
    loop check_even

mov count, bl
```

Even numbers: 2, 8, 14 → count = 3.

---

## ⭐ **Example 4: Using DUP**

```asm
.DATA
buffer DB 10 DUP(0)   ; array of 10 zeros

.CODE
mov si, OFFSET buffer
mov cx, 10

fill_values:
    mov byte ptr [si], 5
    inc si
    loop fill_values
```

Now buffer = `{5,5,5,5,5,5,5,5,5,5}`

---

# 📌 **Key Takeaways**

| Concept          | Meaning                                      |
| ---------------- | -------------------------------------------- |
| `DB`             | define bytes (strings, chars, small ints)    |
| `DW`             | define words (16-bit)                        |
| `DUP`            | replicate values                             |
| indexing         | done using `SI`, `DI`, `BX`, `BP`            |
| ASCII conversion | `'0'` = 48 decimal, used for numeric display |
| INT 21h          | DOS input/output interrupt                   |

---

# ✅ **1. Character Arrays & Scanning Strings**

### **Example-A: Declare a character array (string)**

```asm
.data
msg db "Hello Microprocessor!",'$'
```

### **Example-B: Print a string using DOS interrupt**

```asm
.data
msg db "Hello World!$"

.code
mov dx, offset msg   ; Load address of string
mov ah, 09h          ; DOS service: print string
int 21h

mov ah, 4Ch          ; Exit to DOS
int 21h
```

---

### **Example-C: Scan (input) a string from keyboard**

```asm
.data
buffer db 20          ; Max input length
       db ?           ; Real length stored here by BIOS
       db 20 dup('$') ; Storage space

.code
mov dx, offset buffer
mov ah, 0Ah           ; DOS buffered input
int 21h               ; User types string + Enter

; Print newline after input
mov ah, 02h
mov dl, 0Dh
int 21h
mov dl, 0Ah
int 21h

; Print the typed string (skip length bytes)
mov dx, offset buffer+2
mov ah, 09h
int 21h

mov ah, 4Ch
int 21h
```

📝 **Explanation:**

* First byte = max length (20)
* Second byte = actual typed length
* Remaining bytes = actual characters

---

# ✅ **2. Handling Signed Numbers (16-bit)**

### **Signed addition**

```asm
.data
num1 dw -15
num2 dw 10

.code
mov ax, num1
add ax, num2     ; ax = -15 + 10 = -5
```

---

### **Signed subtraction**

```asm
.data
a dw -40
b dw  12

.code
mov ax, a
sub ax, b        ; ax = -40 - 12 = -52
```

---

### **Signed multiplication (IMUL)**

⚠️ `MUL` = unsigned multiply
⚠️ `IMUL` = signed multiply

```asm
.data
x dw -5
y dw  10

.code
mov ax, x
imul y           ; AX = -5 * 10 = -50
```

---

### **Signed division (IDIV)**

#### Example: `-50 / 10 = -5`

```asm
.data
num dw -50
den dw 10

.code
mov ax, num
cwd             ; extend sign into DX
idiv den        ; ax = -5
```

📝 `cwd` is important for sign extension before signed division.

---

# ⭐ **Bonus: Display Result with Sign**

To print signed number (simple method):

```asm
; AX contains signed result

cmp ax, 0
jge printValue

; If negative:
mov dl, '-'         ; print minus sign
mov ah, 02h
int 21h
neg ax              ; convert to positive for printing

printValue:
; convert AX to ASCII decimal and print (extra code needed)
```

---

