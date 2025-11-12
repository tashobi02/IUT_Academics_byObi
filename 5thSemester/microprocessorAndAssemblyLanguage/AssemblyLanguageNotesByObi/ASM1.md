```asm
.model small ; small model - one code segment and one data segment 
.stack 100h  ; reserves 256 bytes (100h = 256) - used for storing return addresses, local variables, and register values 
.code        ; marks the beginning of the code segment 

main proc    ; declares a procedure called main - like main() in c++
    mov ah, 1   ; reads a single character from the keyboard 
    int 21h     ; executes the DOS interrupt 
    mov bl, al  ; moves the first input character from AL -> BL register 
    
    mov ah, 1   ; again sets function 1 of INT 21h to read another character
    int 21h     ; reads the second character from keyboard and stores it in AL again
    mov bh, al  ; moves the second character from AL -> BH register
                ; bl = first character, bh = second character 
    mov ah, 2   ; display a single character on the screen (output)
    mov dl, bl  ; loads the first character (BL) into DL,
    int 21h     ; executes the interrupt -> displays the character in DL on the screen
    mov dl, bh  ; loads the second character (BH) into DL, preparing to print it next
    int 21h     ; displays the second character on the screen
    
exit:           ; this is just a label, used for marking the exit point of the program
    mov ah, 4ch ; terminate the program and return control to DOS
    int 21h     ; executes the interrupt ? program ends
main endp   ; marks the end of the procedure -> main
end main    ; marks the end of the program main 
```

GPT Prompt: 
.model small - what are other models? 
.stack 100h - what are other stacks? 
int 21h - is this like a data type or what? what are others? 
what is DOS? 
al, bl, ah, bh - how the register are named? can I name them in any way I want? what are other registers? are there different types?

---
## 🧩 1. `.model small` — Memory Models in Assembly

The **`.model`** directive tells the assembler how your **program’s memory** is organized — how many **segments** (code, data) you have and how big they are.

8086 uses **segmented memory** (each segment = 64 KB), so you must specify how your code and data will be separated.

|Model|Code Segment|Data Segment|Description / Usage|
|---|---|---|---|
|**tiny**|1|1|Code + data + stack all in a single segment (used for .COM programs)|
|**small**|1|1|One code and one data segment (each ≤ 64 KB) ✅ _most common for lab_|
|**medium**|Multiple|1|Multiple code segments, one data segment|
|**compact**|1|Multiple|One code segment, multiple data segments|
|**large**|Multiple|Multiple|Both multiple code and data segments (each ≤ 64 KB)|
|**huge**|Multiple|Multiple|Same as large, but can handle data > 64 KB using far pointers|

✅ So, in labs, you almost always use:

`.model small`

because your program is small (one code + one data section).

---

## 🧱 2. `.stack 100h` — Stack Segment Size

The **`.stack`** directive reserves memory for the **stack segment** — an area of memory used to store temporary data like function return addresses, local variables, and register saves.

`100h` = 256 bytes (since 1h = 1 hexadecimal).

You can change the size depending on your program needs:

|Directive|Meaning|
|---|---|
|`.stack`|Uses a default size (usually 1 KB)|
|`.stack 64`|Reserves 64 bytes|
|`.stack 100h`|Reserves 256 bytes ✅ (common default)|
|`.stack 200h`|Reserves 512 bytes|
|`.stack 400h`|Reserves 1024 bytes (1 KB)|

You can choose **any** size, but 100h (256 bytes) is standard for small programs.

---

## ⚙️ 3. `int 21h` — What It Actually Is

No, it’s **not a data type** 😊  
`int` here means **interrupt** — a way to call **system services**.
`int 21h` means **call interrupt number 21 (hexadecimal)**, which belongs to **MS-DOS**.

---

### 🖥️ What is an Interrupt?

An **interrupt** is like a **shortcut to a predefined function** provided by the system or hardware.  
When you call it, the CPU temporarily stops your program and executes the corresponding system routine.

```asm
mov ah, 1
int 21h
```

- Here, **AH = 1** selects _function 1_ of interrupt 21h — "Read a character from keyboard."

So, `int 21h` is like saying:

> “Hey DOS, please do something for me — I’ll tell you what using AH.”

### 🧮 Some Common DOS Interrupt Functions

| AH value | Function                              |
| -------- | ------------------------------------- |
| 01h      | Read character from keyboard (echoed) |
| 02h      | Display a character on screen         |
| 09h      | Display a string (`$`-terminated)     |
| 4Ch      | Exit program                          |
| 0Ah      | Buffered keyboard input               |
| 06h      | Direct console I/O                    |

So, `int 21h` is **one interrupt number**, and AH decides **which service** to perform.

---

## 🧠 4. What is **DOS**?

**DOS** stands for **Disk Operating System**.  
It’s an old operating system used before Windows — provides services for input/output, file handling, etc.

When you use:

```asm
int 21h
```

you’re calling **a DOS service**, like:

- Reading keyboard input
- Printing on screen
- Exiting the program
- Reading/writing files

So, in simple terms:

> `int 21h` = “Ask DOS to do something.”

## 🧩 5. Registers — AL, BL, AH, BH and Others

Registers are **small storage locations inside the CPU** — very fast, used for calculations, data movement, etc.

### 📦 8086 General Purpose Registers

|Register|Description|Divided Into|Use|
|---|---|---|---|
|**AX**|Accumulator|AH (high), AL (low)|Arithmetic, I/O operations|
|**BX**|Base register|BH, BL|Addressing, data storage|
|**CX**|Count register|CH, CL|Loop counters, shifts|
|**DX**|Data register|DH, DL|I/O, multiplication/division|
|**SP**|Stack Pointer|—|Points to top of stack|
|**BP**|Base Pointer|—|Access stack variables|
|**SI**|Source Index|—|Source for string operations|
|**DI**|Destination Index|—|Destination for string operations|
Each 16-bit register (like AX) can be split into two 8-bit parts:

- **AH** = upper 8 bits of AX
- **AL** = lower 8 bits of AX
Same pattern for BX, CX, DX:
AX = AH | AL
BX = BH | BL
CX = CH | CL
DX = DH | DL

### ❓Can You Rename Registers?

No ❌ — register names are **fixed by the CPU architecture**.  
You **must** use these specific names (AX, BX, etc.).  
You can use **variables** in memory with any name, but **registers are hardware-defined**.

## 🧠 6. Types of Registers (Summary)

|Type|Examples|Purpose|
|---|---|---|
|**General Purpose**|AX, BX, CX, DX|Arithmetic, data movement|
|**Segment Registers**|CS, DS, SS, ES|Define memory segments (Code, Data, Stack, Extra)|
|**Pointer/Index Registers**|SP, BP, SI, DI|Stack and string operations|
|**Flag Register**|FLAGS|Stores status bits (Zero, Carry, Sign, etc.)|
|**Instruction Pointer**|IP|Holds address of next instruction|
🧾 Example of Register Use

```asm
mov ax, 5      ; AX = 5
mov bx, 10     ; BX = 10
add ax, bx     ; AX = AX + BX = 15
```

Here:

- AX is used as accumulator.
- BX is used as a general register.
- The CPU performs operations **directly inside registers** (fastest possible).

![8086 Register Structure](https://media.geeksforgeeks.org/wp-content/uploads/20220624163841/GeneralPurposeregister-1024x1024.jpg)




