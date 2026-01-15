```asm 
m db 'Awawa Kawawa Wawawa$'  
.code
main proc
    ; 1 -> single key input 
    ; 2 -> single caracter output 
    ; 9 -> character string 
    
    mov ax, @data ; Load the segment address of the program's data segment 
    mov ds, ax    ; ds register will access the data 
    
    mov ah, 9     ; Putting DOS Function 9 into ah register
    lea dx, m     ; lea -> load effective address of label m into dx 
    int 21h       ; interrupts and print characters starting at ds:dx until it finds the $
                  ; prints "Awawa Kawawa Wawawa"
    mov ah, 1     ; DOS Function 1 which takes a single character input  
    int 21h       ; Calls the function and waits for input 
    mov bl, al    ; Copy the character code from al into the lower 8 bits of BX (register BL) so                        the program can use it later.
                  ; Now bl holds the ASCII code of the user’s key. 
    
    mov ah, 2     ; ah = 02h (DOS function 2: display single character from DL) 
    mov dl, bl    ; Again copies the input into dl
    int 21h       ; Prints saved character 
    
    exit: 
    mov ah, 4ch 
    
    int 21h 
    main endp 

end main
         
```

GPT Prompt: 

Explain how this data movement works? Why we need to copy it into another register? 
mov ds, ax
mov bl, al
mov dl, bl

## ⚙️ 8086 Architecture Reminder

8086 has several **16-bit general-purpose registers**:  
`AX`, `BX`, `CX`, `DX`, `SI`, `DI`, `BP`, `SP`

Each 16-bit register can be split into **two 8-bit halves**:

| 16-bit | High 8-bit | Low 8-bit |
| ------ | ---------- | --------- |
| AX     | AH         | AL        |
| BX     | BH         | BL        |
| CX     | CH         | CL        |
| DX     | DH         | DL        |

So:

- `AH` and `AL` are **two separate 8-bit parts** of AX
- You can move data between them like small boxes
- DOS functions use these small boxes (like `AH`, `AL`, `DL`) for different purposes
---

## 🧩 Now Let’s Decode Each Movement

### 🔹 1. `mov ds, ax`

**Purpose:**  
Initialize the **data segment register** (`DS`) so the program can access your variables in `.data`.

**Explanation:**

- In 8086, **data addresses** come from _two parts_: **segment register** + **offset**.
- When you define variables like `m db 'text$'`, they live inside the _data segment_ of your program.
- `@data` gives the **segment base address** of your data area.
- You can’t directly set `DS` with an immediate value (`mov ds, @data` is _illegal_), so you must first:
```asm
mov ax, @data
mov ds, ax
```
- That’s why you copy it through `AX`.  
    → Now `DS` correctly points to your `.data` variables, so instructions like `lea dx, m` work properly.

**Analogy:**  
You first write down the street address on a piece of paper (`AX`), then you tell your GPS to use that street as its current map (`DS`).

### 🔹 2. `mov bl, al`

**Purpose:**  
To **store** the character you read from the keyboard (in `AL`) into another register (`BL`) so you can reuse it later.

**Explanation:**

- When you use DOS function 1 (`mov ah, 1` + `int 21h`), the typed character’s **ASCII code** is returned in `AL`.
- You want to use that character later to print it, but:
    - DOS function 2 (to print) uses **DL**, not AL.
    - You also might call other interrupts that overwrite AL or AH.
- So you save the value safely:
```asm
mov bl, al
```
- → Copies the character from `AL` → `BL`.
**Analogy:**  
Think of `AL` as the **input tray** and `BL` as a **temporary storage box**.  
Before you do something else that could overwrite `AL`, you move the data to `BL` for safekeeping.

### 🔹 3. `mov dl, bl`

**Purpose:**  
To **move** the stored character into `DL`, which is the **required input register** for DOS Function 2 (print character).

**Explanation:**

- DOS interrupt 21h function 2:
```asm
mov ah, 2
mov dl, <character>
int 21h
```
expects the character to display to be in `DL`.
- You previously stored the input key in `BL`, so you now move it there:
```asm
mov dl, bl
```

- → Copies your saved character from `BL` → `DL`

Then `int 21h` prints the ASCII character in DL.

**Analogy:**  
You took your key (`AL`), put it in a box for safekeeping (`BL`), and when ready to use it, you place it in the machine input slot (`DL`).

## 🔁 The Flow of Data

Here’s how data travels step-by-step through registers in your program:

```
Keyboard key → AL  (via INT 21h / Function 1)
AL → BL             (save for later use)
BL → DL             (prepare for printing)
DL → Screen         (via INT 21h / Function 2)
```


|**Instruction**|**Source**|**Destination**|**Meaning**|**Why it’s Needed**|
|---|---|---|---|---|
|`mov ds, ax`|AX → DS|Sets **data segment base address**|The `@data` segment address is first loaded into AX, then moved to DS so that all `.data` variables (like `m`) can be accessed correctly.|The CPU separates **code** and **data** memory segments; DS must point to the data segment before any variable can be used.|
|`mov bl, al`|AL → BL|Save input character|After reading a character from the keyboard (stored in AL), it’s copied to BL for safekeeping.|Because the **next interrupts (INT 21h)** will overwrite AL, so storing it in BL prevents data loss.|
|`mov dl, bl`|BL → DL|Prepare character for display|The character saved in BL is moved into DL so DOS function 2 (display character) can output it.|DOS interrupt **INT 21h / AH=2** expects the character to print inside DL, so we must move it there.|


GPT Prompt: 
lea dx, m explain this line in more details

### 🔹 **Meaning of Each Part**

- `lea` → **Load Effective Address**
- `dx` → **Destination Register**
- `m` → **Memory Label (the variable or string defined in `.data`)**

So this instruction means:

> “Load the **memory address** (not the data itself) of variable `m` into register `DX`.”


### 🔹 **What’s Happening**

When you write something like:

```asm
m db 'Awawa Kawawa Wawawa$'
```

the assembler places that string somewhere in **memory** (inside the _data segment_).  
That memory location gets a **label** `m` — so `m` really stands for a _memory address_, not the actual text.

Now when you call:

```asm
mov dx, m
```

this would actually _move the value stored at `m`_ (the first character, `'A'`, i.e. ASCII 65) into `dx`.  
That’s **not** what we want.

But when we call:

```asm
lea dx, m
```

`lea` (Load Effective Address) means:

> “Get me the _address_ of `m`, not the content.”

So `DX` will hold the **address (pointer)** of the string in memory.

---

### 🔹 **Why DOS Function 9 Needs It**

When you do:

```asm
mov ah, 9
int 21h
```

DOS expects the **address of the string** to be in the `DX` register.  
It will start printing from the memory address stored in `DS:DX`, one character at a time,  
until it finds a `$` (which marks the end of the string).

So, this part:

```asm
lea dx, m
int 21h
```

basically tells DOS:

> “Go to the memory location labeled `m` and print all characters until you hit a `$`.”

---

### 🔹 **Summary Table**

|Part|Meaning|Purpose|
|---|---|---|
|`lea`|Load Effective Address|Loads the _address_ of memory operand|
|`dx`|Destination Register|Holds the address of the string|
|`m`|Label of string|Start of text `"Awawa Kawawa Wawawa$"`|
|Result|`DX = address of m`|Allows `int 21h` (function 9) to print the string|

---

### 🔹 **Analogy**

Think of it like this:

- `mov dx, m` → “Go get what’s inside the mailbox named _m_.”
- `lea dx, m` → “Write down the **address** of the mailbox named _m_.”
For `int 21h` function 9, we need the **address**, not the **letter inside**.