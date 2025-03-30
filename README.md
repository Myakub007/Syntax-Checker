# Tokenizer and Syntax Validator

## Overview

This project is a simple tokenizer and syntax validator for assignment statements written in C-like syntax. It takes user input code, tokenizes it, and verifies whether the syntax is valid for an assignment statement.

## Features

- Tokenizes input code into different token types: IDENTIFIER, NUMBER, OPERATOR, ASSIGN, PUNCTUATION, ERROR, END.
- Parses and validates assignment statements.
- Provides meaningful syntax error messages.
- Reads user input until 'END' is entered.

## Token Types

| Token Type  | Description                                  |
| ----------- | -------------------------------------------- |
| IDENTIFIER  | Variable names like `x`, `sum`               |
| NUMBER      | Numerical values like `10`, `5`              |
| OPERATOR    | Arithmetic operators like `+`, `-`, `*`, `/` |
| ASSIGN      | Assignment operator `=`                      |
| PUNCTUATION | End of statement symbol `;`                  |
| ERROR       | Any unrecognized character                   |
| END         | Signals the end of input                     |

## How It Works

1. The user enters a line of code.
2. The program tokenizes the input and displays the tokens.
3. The parser checks if the input follows the expected assignment syntax.
4. If the syntax is correct, it prints `Parsing successful!`, otherwise, it outputs an appropriate error message.

## Compilation and Execution

### Compiling the Program
Use a C compiler such as GCC to compile the program:
```sh
gcc tokenizer.c -o tokenizer
```

### Running the Program
After compilation, execute the program:
```sh
./tokenizer
```

### Input Instructions
1. Enter an assignment statement (e.g., `x = 5 + 3;`).
2. Type `END` on a new line to stop input.
3. The program will tokenize the input and validate the syntax.

## Example Input & Output

**Input:**

```
x = 10 + 5;
END
```

**Output:**

```
Tokens:
Type: 0, Value: x
Type: 3, Value: =
Type: 1, Value: 10
Type: 2, Value: +
Type: 1, Value: 5
Type: 4, Value: ;
Checking Syntax: x = 10 + 5;
Valid assignment Statement
Parsing successful!
```

## Notes

- The program only handles single assignment statements.
- It does not support complex expressions or multiple statements.
- The code uses `typedef enum` for defining token types.

## Future Enhancements

- Extend support for floating-point numbers.
- Handle multiple statements.
- Improve operator handling (e.g., parentheses support).
- Enhance error messages for better debugging.

## Author

This project was developed as a simple tokenizer and parser demonstration in C.

