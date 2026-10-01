# Lex / Flex Cheat Sheet

## File Structure

```
%{
  /* C code: includes, globals */
%}

/* Definitions */

%%

/* Rules: pattern   action */

%%

/* C code: main(), yywrap() */
```

---

## Regex Symbols — Outside `[...]`

| Symbol | Meaning | Example |
|--------|---------|---------|
| `.` | Any char (except newline) | `a.b` → `axb`, `a1b` |
| `*` | 0 or more | `a*` → `""`, `a`, `aaa` |
| `+` | 1 or more | `a+` → `a`, `aaa` |
| `?` | 0 or 1 (optional) | `colou?r` → `color`, `colour` |
| `\|` | OR | `cat\|dog` |
| `(...)` | Group | `(ab)+` → `ab`, `abab` |
| `\` | Escape next char | `\.` = literal `.` |
| `^` | Start of line | `^int` |
| `$` | End of line | `;\n$` |
| `x/y` | Match `x` only if followed by `y` | `0/1` |
| `x{n}` | Exactly n of x | `a{3}` → `aaa` |
| `x{n,m}` | Between n and m of x | `a{2,4}` |

---

## Regex Symbols — Inside `[...]`

| Symbol | Meaning | Example |
|--------|---------|---------|
| `^` | NOT (only at start) | `[^0-9]` = not a digit |
| `-` | Range | `[a-z]`, `[0-9]`, `[A-Z]` |
| `\` | Escape | `[\[\]]` = literal `[` or `]` |
| anything else | Literal | `[abc]` = `a`, `b`, or `c` |

> **`^` has two meanings:**
> - Inside `[^...]` → **NOT**
> - Outside `[...]` → **start of line**

---

## Named Definitions

```lex
DIGIT   [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIGIT})*
```

Use with `{NAME}` in rules:

```lex
%%
{DIGIT}+  { printf("NUMBER: %s\n", yytext); }
{ID}      { printf("IDENT:  %s\n", yytext); }
```

---

## `yy` Variables

| Variable | Type | What it holds |
|----------|------|---------------|
| `yytext` | `char *` | The matched text — e.g., `[0-9]+` on `42` gives `yytext = "42"` |
| `yyleng` | `int` | Length of `yytext` — e.g., for `42`, `yyleng = 2` |
| `yylineno` | `int` | Current line number (requires `%option yylineno`) |
| `yyin` | `FILE *` | Input source — default `stdin`; set to read from a file |
| `yyout` | `FILE *` | Output destination — default `stdout`; used by `ECHO` |

```c
/* Read from a file instead of stdin */
yyin = fopen("input.c", "r");
yylex();
```

---

## `yy` Functions

| Function | What it does |
|----------|-------------|
| `yylex()` | Starts/continues the scanner — call from `main()` |
| `yywrap()` | Called at EOF — return `1` to stop, `0` to continue |
| `ECHO` | Prints `yytext` to `yyout` — same as `fprintf(yyout, "%s", yytext)` |
| `yyless(n)` | Push back all but first `n` chars of `yytext` into input |
| `yymore()` | Append next match onto `yytext` instead of replacing it |
| `unput(c)` | Push a single character `c` back into input |
| `input()` | Read next character manually from input |
| `BEGIN(state)` | Switch to a start condition, e.g., `BEGIN(COMMENT)` |

---

## `yywrap()` explained

Called automatically when scanner hits **EOF**:
- Return `1` → **stop** scanning
- Return `0` → **continue** (set `yyin` to a new file first)

```c
int yywrap() { return 1; }   /* always stop — standard lab usage */
```

---

## Common Patterns (Copy-Paste)

```lex
[a-zA-Z_][a-zA-Z0-9_]*          /* identifier */
[0-9]+                           /* integer */
[0-9]+\.[0-9]+                   /* float */
\"([^\"\\]|\\.)*\"               /* string literal */
\/\/[^\n]*                       /* single-line comment */
\/\*([^*]|\*[^/])*\*\/           /* multi-line comment */
[ \t\n\r]+                       /* whitespace (skip) */
[{}();,\[\]]                     /* special symbols */
==|!=|<=|>=|\+\+|--|[+\-*/%=<>]  /* operators */
```

---

## Rule Priority

1. **Longest match wins** — `int` beats `in` for input `int`
2. **First rule wins** — if same length, whichever rule appears first

> Put **keywords before identifiers** so `int` isn't matched as an identifier.

---

## Compile & Run

```bash
lex program.l          # generates lex.yy.c
gcc lex.yy.c -ll
./a.out
```
