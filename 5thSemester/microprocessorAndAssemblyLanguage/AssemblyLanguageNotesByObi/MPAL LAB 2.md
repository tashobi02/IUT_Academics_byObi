
# 🧩 **SECTION 1: The INT Instruction**

### **What is INT?**

`INT` stands for **software interrupt**.

It calls a specific system routine (like calling library functions in high-level languages).

Format:

```
INT interrupt_number
```

Examples:

* `INT 10h` → BIOS video services
* `INT 21h` → DOS services
* `INT 16h` → Keyboard BIOS services

---

# 🧩 **SECTION 2: INT 21h — DOS Functions**

`INT 21h` gives access to **DOS services**, like:

✔ keyboard input
✔ screen output
✔ string output
✔ file operations (not used here)

Which service runs depends on **AH**.

---

# 🧩 **SECTION 3: INT 21h — Function Details**

We study these 3 functions:

| Function | AH value   | Purpose                 |
| -------- | ---------- | ----------------------- |
| **1**    | `AH = 01h` | Single-key input        |
| **2**    | `AH = 02h` | Single-character output |
| **9**    | `AH = 09h` | Display string          |

---

## ✔ **FUNCTION 1: Keyboard Input**

To read a single character:

```asm
MOV AH, 01h
INT 21h
```

After execution:

* `AL` contains ASCII code if a **printable** character was pressed
* `AL = 0` for **special keys** (like arrow keys)

Example:

```asm
MOV AH, 1
INT 21h     ; returns ASCII in AL
```

---

## ✔ **FUNCTION 2: Character Output**

To display a single ASCII character:

Inputs:

* `AH = 02h`
* `DL = ASCII` code of character

Example:

```asm
MOV AH, 2
MOV DL, '?'   ; print '?'
INT 21h
```

After printing:

* Cursor automatically moves forward

### 📝 **Control Characters with Function 2**

Characters inside DL with special effects:

| ASCII in DL | Name | Effect                               |
| ----------- | ---- | ------------------------------------ |
| `0Ah`       | LF   | Line feed (new line)                 |
| `0Dh`       | CR   | Carriage return (move to line start) |

To perform a new line in DOS:

```asm
MOV DL, 0Dh   ; CR
INT 21h
MOV DL, 0Ah   ; LF
INT 21h
```

---

# 🧩 **SECTION 4: Conditional Control Instructions**

These are **conditional jumps** based on CPU flags.

Most conditions are tested using:

```asm
CMP destination, source
```

`CMP` performs:

```
destination - source
```

without saving result — only changes **flags**.

---

## ✔ **Common Jump Conditions**

| Condition    | Instruction | Means                    |
| ------------ | ----------- | ------------------------ |
| `ZF = 1`     | `JZ`        | Jump if zero             |
| `ZF = 0`     | `JNZ`       | Jump if not zero         |
| `>` signed   | `JG`        | Jump if greater          |
| `>=` signed  | `JGE`       | Jump if greater or equal |
| `<` signed   | `JL`        | Jump if less             |
| `<=` signed  | `JLE`       | Jump if less or equal    |
| `< unsigned` | `JB`        | Jump if below            |
| `CF = 1`     | `JC`        | Jump if carry            |

---

# 🧩 **SECTION 5: Example Program Explanation**

Given example:

```asm
ORG 0100h
MAIN PROC
; display prompt
MOV AH, 2
MOV DL, '?'
INT 21h
; input a character
MOV AH, 1
INT 21h
MOV BL, AL
; go to a new line with carriage return
MOV AH, 2
MOV DL, 0DH
INT 21h
MOV DL, 0AH
INT 21h
; display character
MOV DL, BL
INT 21h
; return to DOS
MOV AH, 4CH
INT 21H
MAIN ENDP
END MAIN
RET
```

### 🔍 Let’s break it:

1. **ORG 0100h**

   * Required for `.COM` programs

2. **Display prompt (`?`)**

   ```asm
   MOV AH, 2
   MOV DL, '?'
   INT 21h
   ```

3. **Read keyboard input**

   ```asm
   MOV AH, 1
   INT 21h
   MOV BL, AL   ; store typed key in BL
   ```

4. **Print newline**

   ```asm
   MOV AH, 2
   MOV DL, 0Dh  ; carriage return
   INT 21h
   MOV DL, 0Ah  ; line feed
   INT 21h
   ```

5. **Print typed character**

   ```asm
   MOV DL, BL
   INT 21h
   ```

6. **Exit program**

   ```asm
   MOV AH, 4Ch
   INT 21h
   ```

---

# 🧩 **SECTION 6: Second Code Explained**

Given code:

```asm
org 100h
START: mov cl, 03h
LABEL_JNZ: dec cl
jnz LABEL_JNZ
mov bl, 04h
mov al, 04h
LABEL_JZ: dec al
dec bl
xor bl, al
jz LABEL_JZ
mov bl, 02h
mov al, 06h
LABEL_JG: dec al
cmp al, bl
jg LABEL_JG
mov bl, 06h
mov al, 00h
LABEL_JL: inc al
cmp al, bl
jl LABEL_JL
ret
```

We’ll decode it **block by block**.

---

### 🧱 **BLOCK 1: Using JNZ**

```asm
mov cl, 03h
LABEL_JNZ: dec cl
jnz LABEL_JNZ
```

* Load `CL = 3`
* `dec cl` ⇒ decreases until zero
* `jnz` loops until **CL == 0**

So loop runs:

```
CL: 3 → 2 → 1 → 0 (stop)
```

---

### 🧱 **BLOCK 2: Using XOR + JZ**

```asm
mov bl, 04h
mov al, 04h
LABEL_JZ: dec al
dec bl
xor bl, al
jz LABEL_JZ
```

Execution state table:

| AL   | BL   | XOR (BL⊕AL) | ZF?  |                    |
| ---- | ---- | ----------- | ---- | ------------------ |
| 4→3  | 4→3  | 3⊕3=0       | ZF=1 |                    |
| 3→2  | 3→2  | 2⊕2=0       | ZF=1 |                    |
| 2→1  | 2→1  | 1⊕1=0       | ZF=1 |                    |
| 1→0  | 1→0  | 0⊕0=0       | ZF=1 |                    |
| 0→-1 | 0→-1 | FF⊕FF=0     | ZF=1 | (wraps, continues) |

Loop ends when XOR ≠ 0 (when registers mismatch)

---

### 🧱 **BLOCK 3: Using JG (signed)**

```asm
mov bl, 02h
mov al, 06h
LABEL_JG: dec al
cmp al, bl
jg LABEL_JG
```

Meaning:

* Start `AL=6`, `BL=2`
* Decrement AL until `AL > BL` is false

Trace:

```
AL=6: cmp 6 vs 2 → JG true
AL=5: cmp 5 vs 2 → JG true
AL=4: cmp 4 vs 2 → JG true
AL=3: cmp 3 vs 2 → JG true
AL=2: cmp 2 vs 2 → JG false (stop)
```

---

### 🧱 **BLOCK 4: Using JL (signed)**

```asm
mov bl, 06h
mov al, 00h
LABEL_JL: inc al
cmp al, bl
jl LABEL_JL
```

Meaning:

* Start `AL = 0`, `BL = 6`
* Loop while `AL < BL`

Trace:

```
AL increases: 0,1,2,3,4,5
At AL=6 → cmp 6 vs 6 → JL false → stop
```

---

# 🧩 **Final Summary**

### ✔ **You learned:**

* `INT` calls system routines
* `INT 21h` performs DOS services
* `AH` selects the service
* Function 01h → keyboard input
* Function 02h → character output
* Conditional jumps:

  * `JZ`, `JNZ`, `JG`, `JL`, etc.
* `CMP` sets flags for jumps
* Looping using jump conditions

---

