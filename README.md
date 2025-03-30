# Tokenizer and Syntax Validator

## Overview

This project is a simple tokenizer and syntax validator for assignment statements written in C-like syntax. It takes user input code, tokenizes it, and verifies whether the syntax is valid for multiple assignment statements.

## Features

- Tokenizes input code into different token types: IDENTIFIER, NUMBER, OPERATOR, ASSIGN, PUNCTUATION, ERROR, END.
- Parses and validates multiple assignment statements.
- Provides meaningful syntax error messages and skips erroneous statements.
- Supports user input until 'END' is entered.
- Implements basic error recovery by skipping to the next valid statement.

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

1. The user enters multiple assignment statements.
2. The program tokenizes the input and displays the tokens.
3. The parser checks if the input follows the expected assignment syntax.
4. If the syntax is correct, it prints `Valid assignment statement`, otherwise, it outputs an appropriate error message and skips to the next statement.

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
1. Enter multiple assignment statements (e.g., `x = 5 + 3;`).
2. Type `END` on a new line to stop input.
3. The program will tokenize the input and validate the syntax for each statement.

## Example Input & Output

**Input:**
```
x = 10 + 5;
y = 3 *;
z = 7;
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
Type: 0, Value: y
Type: 3, Value: =
Type: 1, Value: 3
Type: 2, Value: *
Type: 4, Value: ;
Type: 0, Value: z
Type: 3, Value: =
Type: 1, Value: 7
Type: 4, Value: ;

Checking Syntax:
x = 10 + 5;
y = 3 *;
z = 7;

Valid assignment Statement
Syntax Error: Expected a number after operator, but got ''
Error: Skipping to next statement...
Valid assignment Statement
Parsing completed!
```

## Notes

- The program supports multiple assignment statements.
- Basic error recovery is implemented to allow parsing to continue after an error.
- Operators must be followed by valid numbers.
- `;` is required at the end of each statement.

## Future Enhancements

- Extend support for floating-point numbers.
- Handle expressions with parentheses.
- Implement operator precedence parsing.
- Improve error recovery mechanisms.
- Add support for variable lookup and evaluation.

## Author

This project was developed as a simple tokenizer and parser demonstration in C.

