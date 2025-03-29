#include <stdio.h>
#include <ctype.h>
#include <string.h>
// determines the data type of values

typedef enum { IDENTIFIER, NUMBER, OPERATOR, ASSIGN, PUNCTUATION, ERROR, END } tokentype;

// IDENTIFIER: Variable names like x, sum

// NUMBER: Numerical values like 10, 5

// OPERATOR: Operators like +, -, *, /

// ASSIGN: Assignment operator =

// PUNCTUATION: Symbols like ;

// ERROR: Any unrecognized character

// END: Signals the end of input

#define MAX_TOKEN_SIZE 100
#define MAX_CODE_SIZE 500
// const in c is not seen as const in compile time 
// use #define instead of const 

typedef struct {
    tokentype type;
    char value[MAX_TOKEN_SIZE];
}Asiner ;


Asiner getNextToken(const char *code ,int *pos){
    Asiner token;
    token.value[0] = '\0';


    while (code[*pos] == ' ' || code[*pos] == '\n') {(*pos)++;};
    if (code[*pos] == '\0'){
        token.type = END;
        return token;
    }
    if(isalpha(code[*pos])){
        int i = 0;
        while (isalpha(code[*pos])){
            token.value[i++] = code[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';
        token.type = IDENTIFIER;
        return token;
    }
    if(isdigit(code[*pos])){
        int i = 0;
        while (isdigit(code[*pos])){
            token.value[i++] = code[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';
        token.type = NUMBER;
        return token;
    }
    if(strchr("+*-/%%",code[*pos])){
        token.value[0] = code[*pos];
        token.value[1] = '\0';
        token.type = OPERATOR;
        (*pos)++;
        return token;
    }
    if(code[*pos] == '='){
        token.value[0] = '=';
        token.value[1] = '\0';
        token.type = ASSIGN;
        (*pos)++;
        return token;
    }
    if(code[*pos]==';'){
        token.value[0] = code[*pos];
        token.value[1] = '\0';
        token.type = PUNCTUATION;
        (*pos)++;
        return token;
    }
    token.type = ERROR;
    token.value[0] = code[*pos];
    token.value[1] = '\0';
    (*pos)++;
    return token;

};

int parseAssignment(const char *code){
    int pos = 0;
    Asiner token;

    //Step 1:  Expect IDENTIFIER (variable name)
    token = getNextToken(code,&pos);
    if(token.type !=IDENTIFIER){
        printf("Syntax Error: Expexted a variable name , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }
    
    // step2: Expect ASSIGN
    token = getNextToken(code,&pos);
    if(token.type !=ASSIGN){
        printf("Syntax Error: Expexted a variable name , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }

    // Step 3: Expect an Expression (number or number operator number)
    token = getNextToken(code,&pos);
    if(token.type !=NUMBER){
        printf("Syntax Error: Expexted a variable name , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }
    //Step 4: (optional) Check for operator and Second Number 
    token = getNextToken(code,&pos);
    if(token.type == OPERATOR){
        token = getNextToken(code,&pos);
        if (token.type != NUMBER){
            printf("Syntax Error: Expected a number after operator , but got '%s'\n",token.value);
            return 0;
        }
    } else{
        pos--; // Step back if it's not an operator
    }
    // Step 5 : Expext `;` (PUNCTUATION)
    token = getNextToken(code,&pos);
    if(token.type !=PUNCTUATION){
        printf("Syntax Error: Expexted a ';' at end of the statement , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }

    printf("Valid assignment Statement\n");
    return 1;

}



void getUserCode(char *code){
    printf("Enter your code (type 'END' on a new line to finish):\n");

    char line[100]; //Array with max line size of single line in input 
    code[0] = '\0'; // empty code at initialization

    while (1)
    {
        fgets(line,sizeof(line),stdin); // read a line from input 

        if (strncmp(line,"END",3)==0){
            break;
        } // Check END to stop taking input of code 

        strcat(code,line); // Append line to full code string

    }
    
}


void main() {
    char code[MAX_CODE_SIZE];
    getUserCode(code);
    int pos = 0;
    Asiner token;

    printf("Tokens:\n");
    while ((token = getNextToken(code, &pos)).type != END) {
        printf("Type: %d, Value: %s\n", token.type, token.value);
    }

    printf("Checking Syntax: %s\n", code);

    if (parseAssignment(code)) {  // If `1` is returned, parsing is successful
        printf("Parsing successful!\n");
    } else {  // If `0` is returned, parsing failed
        printf("Parsing failed!\n");
    }
    
}

