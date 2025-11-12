```asm 
.model small 
.stack 100h 
.data 
msg db 3  ; Declares a variable named msg, db = define byte 
msg1 db ? ; Declares another byte variable named msg1, ? means it’s uninitialized (will store some value later)

.code 
main proc
    mov ax, @data ; Loads the address of the data segment (symbol @data) into the AX register
    mov ds,ax     ; Moves the value from AX ? DS 
    
    mov ah, 2     ; Sets AH = 2
    add msg, 48   ; Adds 48 (which is 30h in hex) to the value stored in msg - ASCII 51 = '3'
    mov dl, msg   ; Loads the converted ASCII value (51 = ‘3’) into DL register
    int 21h       ; DL is used by INT 21h, function 2 to display a character   
    
    mov ah, 1     ; preparing for INT 21h function 1 — “Read a single character from keyboard”
    int 21h       ; Executes the keyboard input function.
    mov msg1, al  ; Moves the character you typed (in AL) into the variable msg1.
    
    mov ah, 2     ; Again sets up INT 21h function 2 to print a character.
    mov dl, 10    ; ASCII 10 = Line Feed (LF) — moves cursor down one line
    int 21h       ; Executes the interrupt ? moves cursor to the next line.
    mov dl, 13    ; ASCII 13 = Carriage Return (CR) — moves cursor to start of the line
    int 21h       ; Executes the interrupt ? moves the cursor to the beginning of new line
    
    mov ah, 2     ; Again prepares to print a character
    mov dl, msg1  ; Loads your typed character (stored in msg1) into DL.
    int 21h       ; Prints the character stored in msg1 — i.e., the key you typed earlier
     
    exit: 
    mov ah, 4ch   ; Sets AH = 4Ch, which is DOS function to terminate the program
    
    int 21h       ; Calls DOS interrupt 21h again
    main endp 

end main 
```

GPT Prompt: 
explain the role of decimal numbers being loaded in the register? like:
 mov ah, 2 
 mov ah, 1
 mov ah, 2     
 mov dl, 10   
 mov dl, 13
 mov ah, 2 
 mov ah, 4ch
what are other variations and what do they do?     


## 🧠 Background: Why we “load decimal numbers” into registers

In **8086 Assembly**, when you write:
```asm
mov ah, 2
```
you’re not giving AH a “random number.”  
You’re setting it to a **function code** that tells **DOS interrupt 21h** what service you want to perform.

So, the **value in AH** determines **which DOS function** is executed when you call:
```asm
int 21h
```
Think of it like this:
> `INT 21h` = DOS service center  
> `AH` = request number (what service you’re asking for)  
> Other registers (like DL, AL, etc.) = inputs or outputs for that service
## ⚙️ Common INT 21h Functions (via AH)

|AH Value|Function Name|Description|Used Registers|
|---|---|---|---|
|**1**|Read Character from Keyboard|Waits for user to press a key. The ASCII code of the key is returned in **AL**.|Output → AL|
|**2**|Display Character on Screen|Displays the character stored in **DL** on the screen.|Input → DL|
|**9**|Display String|Prints a string ending with `$` to the screen.|Input → DS:DX|
|**4Ch**|Terminate Program|Ends the program and returns control to DOS.|—|
|**0Ah**|Buffered Keyboard Input|Reads a full line of text input.|Input → DS:DX|
|**0Bh**|Check Keyboard Status|Checks if a key has been pressed (non-blocking).|Output → AL|
So:
```asm
mov ah, 1
int 21h
```
→ Reads **one character** from keyboard into `AL`.
```asm
mov ah, 2
mov dl, 'A'
int 21h
```
→ Displays **‘A’** on the screen.
```asm
mov ah, 4Ch
int 21h
```
→ Exits program.

---

## 💾 Other registers like `DL`, `AL`, etc.

Each register has a purpose when calling `int 21h`.

|Register|Role|
|---|---|
|**AH**|Chooses the DOS function (service number)|
|**AL**|Stores the character read (for input) or function result|
|**DL**|Stores the character to be printed (for output)|
|**DS:DX**|Points to the memory location of a string (for displaying strings)|

---

## 📚 Example (Your Code Explained)

```asm
mov ah, 2     ; Function 2 = Display Character
mov dl, msg   ; Character to display is stored in DL
int 21h       ; Print that character
```

### 🧱 About `mov dl, 10` and `mov dl, 13`

These are **ASCII control codes**:

|ASCII|Decimal|Hex|Meaning|
|---|---|---|---|
|**10**|10|0Ah|Line Feed (LF) — moves cursor down|
|**13**|13|0Dh|Carriage Return (CR) — moves cursor to start of line|

They are used **together** to make a “new line” in DOS output:
```asm
mov ah, 2
mov dl, 10   ; Line feed
int 21h
mov dl, 13   ; Carriage return
int 21h
```
## 🧩 Summary

| Instruction   | Purpose                                 |
| ------------- | --------------------------------------- |
| `mov ah, 1`   | Read a character from keyboard          |
| `mov ah, 2`   | Display a character on screen (uses DL) |
| `mov ah, 9`   | Display a string                        |
| `mov ah, 4Ch` | Exit program                            |
| `mov dl, 10`  | Line Feed (new line ↓)                  |
| `mov dl, 13`  | Carriage Return (move to line start ←)  |

**INT 21h cheat sheet** for the **8086 Microprocessor (DOS interrupts)** 👇

---

## 💻 **DOS Interrupt 21h Services (8086 Assembly)**

> Each function is selected by setting **AH = function number**,  
> then calling `int 21h`.  
> Other registers (like AL, DL, DX, etc.) carry data **to/from DOS**.

---

### 🧠 **Keyboard Input Functions**

|AH|Function|Description|Input|Output|Example|
|---|---|---|---|---|---|
|**01h**|Read character (with echo)|Waits for a key press and displays it on screen.|—|AL = ASCII of key|`asm mov ah,1 int 21h mov msg,al`|
|**07h**|Read character (without echo)|Reads a character without displaying it.|—|AL = ASCII of key|`asm mov ah,7 int 21h`|
|**08h**|Read character (no echo, waits)|Same as AH=7, but waits for key if none pressed.|—|AL = ASCII|`asm mov ah,8 int 21h`|
|**0Ah**|Buffered input|Reads an entire line of text into a buffer (until Enter).|DS:DX = buffer address|Buffer filled with input|—|

---

### 🖥️ **Display / Output Functions**

|AH|Function|Description|Input|Output|Example|
|---|---|---|---|---|---|
|**02h**|Display a single character|Prints the character in **DL**.|DL = ASCII code|—|`asm mov ah,2 mov dl,'A' int 21h`|
|**09h**|Display a string|Displays a string ending with `$`.|DS:DX = string address|—|`asm mov dx,offset msg mov ah,9 int 21h`|

---

### 📜 **File and Program Control**

|AH|Function|Description|Input|Output|Example|
|---|---|---|---|---|---|
|**3Ch**|Create a file|DS:DX = filename, CX = attributes|CF flag set if error|—||
|**3Dh**|Open a file|DS:DX = filename|AX = file handle|—||
|**3Eh**|Close file|BX = handle|—|—||
|**3Fh**|Read from file|BX = handle, CX = bytes, DS:DX = buffer|AX = bytes read|—||
|**40h**|Write to file|BX = handle, CX = bytes, DS:DX = buffer|AX = bytes written|—||
|**4Ch**|Exit to DOS|AL = return code (optional)|—|`asm mov ah,4Ch int 21h`||

---

### 🔢 **Miscellaneous Utilities**

|AH|Function|Description|Example|
|---|---|---|---|
|**0Bh**|Check keyboard status (non-blocking)|`asm mov ah,0Bh int 21h` — ZF=0 if key pressed||
|**19h**|Get current default drive|Returns AL = drive number (0=A, 1=B, etc.)||
|**2Ah**|Get system date|Returns date in registers (CX=year, DH=month, DL=day)||
|**2Ch**|Get system time|CH=hour, CL=min, DH=sec, DL=1/100 sec||
|**30h**|Get DOS version|AL=major, AH=minor version numbers||

---

### 🧩 **ASCII Control Characters You’ll Often Use**

|Character|Decimal|Hex|Purpose|
|---|---|---|---|
|**Carriage Return (CR)**|13|0Dh|Move cursor to start of line|
|**Line Feed (LF)**|10|0Ah|Move cursor down one line|
|**Backspace (BS)**|8|08h|Move cursor one position left|
|**Tab (HT)**|9|09h|Move cursor to next tab stop|