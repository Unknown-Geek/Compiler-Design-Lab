# C String & Character Functions Cheat Sheet

A complete, exam-friendly reference for all string and character manipulation functions used across the Compiler Design Lab (`CD_Lab`).

---

## 1. Quick Reference Table

| Function | Header | Syntax | Return Value | Exam Use Case in CD Lab |
| :--- | :---: | :--- | :--- | :--- |
| **`strcpy`** | `<string.h>` | `strcpy(dest, src)` | `char *dest` | Copy whole string until `\0` |
| **`strncpy`** | `<string.h>` | `strncpy(dest, src, n)` | `char *dest` | Slice/extract substring of length `n` |
| **`strcmp`** | `<string.h>` | `strcmp(s1, s2)` | `0` if equal, `<0` if `s1<s2`, `>0` if `s1>s2` | Compare token to keyword (e.g. `"exit"`, `"int"`) |
| **`strchr`** | `<string.h>` | `strchr(str, ch)` | Pointer to first `ch` or `NULL` | Check if transition label has `'e'` (epsilon) |
| **`strlen`** | `<string.h>` | `strlen(str)` | `size_t` (number of chars) | Get string length excluding `\0` |
| **`strcat`** | `<string.h>` | `strcat(dest, src)` | `char *dest` | Append string to end of another |
| **`isdigit`** | `<ctype.h>` | `isdigit(ch)` | Non-zero (true) / `0` (false) | Check if char is `'0'`–`'9'` |
| **`isalpha`** | `<ctype.h>` | `isalpha(ch)` | Non-zero (true) / `0` (false) | Check if char is `'a'`–`'z'` or `'A'`–`'Z'` |
| **`isalnum`** | `<ctype.h>` | `isalnum(ch)` | Non-zero (true) / `0` (false) | Check if char is letter or digit |
| **`isupper`** | `<ctype.h>` | `isupper(ch)` | Non-zero (true) / `0` (false) | Distinguish Non-Terminals (`A`-`Z`) from Terminals |
| **`atoi`** | `<stdlib.h>` | `atoi(str)` | `int` value | Convert number string `"125"` $\to$ `125` |

---

## 2. `<string.h>` String Functions

### 1. `strcpy(dest, src)`
Copies the entire string from `src` to `dest`, stopping only when it hits the null terminator `\0`.
```c
char op1[20];
strcpy(op1, stmt + 2); // Copies everything from index 2 to end of stmt
```
> [!WARNING]
> `dest` must have enough allocated space to hold `strlen(src) + 1` characters.

---

### 2. `strncpy(dest, src, n)`
Copies at most `n` characters from `src` into `dest`.
```c
len1 = opPos - 2;
strncpy(op1, stmt + 2, len1);
op1[len1] = '\0'; // ⚠️ CRITICAL: strncpy does NOT append '\0' automatically!
```
> [!IMPORTANT]
> If `src` has `n` or more characters, `strncpy` **will not add a null terminator**. You **must manually add** `dest[n] = '\0'`.

---

### 3. `strcmp(s1, s2)`
Compares two strings lexicographically character by character.
```c
if (strcmp(id, "int") == 0) {
    printf("Keyword: %s\n", id);
}

if (strcmp(icode[i], "exit") == 0) {
    break; // End of 3AC statements
}
```
> [!CAUTION]
> Remember: `strcmp` returns **`0` when strings match**!
> - `strcmp(a, b) == 0` $\implies$ Equal
> - `strcmp(a, b) != 0` $\implies$ Not equal

---

### 4. `strchr(str, ch)`
Searches for the first occurrence of character `ch` inside string `str`.
```c
// Check if transition contains 'e' (epsilon)
if (strchr(trans[current][next], 'e') != NULL) {
    // Found epsilon transition!
}
```
- **Found:** Returns pointer to that character (`!= NULL`).
- **Not found:** Returns `NULL`.

---

### 5. `strlen(str)`
Calculates the number of characters before the terminating null character `\0`.
```c
int len = strlen("hello"); // len = 5
```

---

## 3. `<ctype.h>` Character Classification Functions

All `<ctype.h>` functions take an `int` (or `char`) and return non-zero (true) or `0` (false).

### 1. `isdigit(ch)`
Checks if a character is a decimal digit (`'0'` through `'9'`).
```c
if (isdigit(token[0])) {
    return atoi(token); // Operand is a constant number!
}
```

### 2. `isalpha(ch)`
Checks if a character is an alphabetic letter (`'a'`–`'z'` or `'A'`–`'Z'`).
```c
if (isalpha(ch) || ch == '_') {
    // Start of an identifier
}
```

### 3. `isalnum(ch)`
Checks if a character is alphanumeric (`'a'`–`'z'`, `'A'`–`'Z'`, or `'0'`–`'9'`).
```c
while (isalnum(ch) || ch == '_') {
    // Continue reading identifier
}
```

### 4. `isupper(ch)`
Checks if a character is uppercase (`'A'` through `'Z'`).
Used in parsing grammars to distinguish **Non-Terminals** from **Terminals**:
```c
if (isupper(c)) {
    // Non-Terminal (e.g. 'E', 'T', 'F') -> Find First & Follow
} else {
    // Terminal (e.g. '+', '*', 'i') -> Directly part of First set
}
```

---

## 4. `<stdlib.h>` String-to-Number Functions

### `atoi(str)`
Converts an ASCII digit string into an integer (`int`).
```c
int val = atoi("42");     // val = 42
int num = atoi(yytext);   // In LEX/YACC: convert matched token to int
```
- Stops parsing at the first non-digit character (e.g. `atoi("42abc")` returns `42`).
- Returns `0` if string cannot be converted.

---

## 5. C Pointer Arithmetic for String Slicing (Lab Exam Shortcuts)

In C, strings are pointers (`char *`). You can skip substrings without calling extra functions:

### 1. Slicing with `str + offset`
```text
stmt:  ['a', '=', '1', '0', '+', 'b', '\0']
Index:   0    1    2    3    4    5    6
```
- `stmt` $\implies$ points to `"a=10+b"`
- `stmt + 2` $\implies$ points to `"10+b"` (skips `a=`)
- `stmt + opPos + 1` $\implies$ points to `"b"` (skips past `+`)

### 2. Slicing by inserting temporary `\0`
```c
char opr = stmt[opPos];
stmt[opPos] = '\0';    // Temporarily cut string after op1

strcpy(op1, stmt + 2); // Now strcpy naturally stops at opPos!
stmt[opPos] = opr;     // Restore original character
```
