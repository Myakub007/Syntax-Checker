#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// determines the data type of values

typedef enum { IDENTIFIER, KEYWORD, NUMBER, OPERATOR, ASSIGN, PUNCTUATION, ERROR, END } tokentype;

// IDENTIFIER: Variable names like x, sum

// KEYWORD : Predefined variable names

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

#define KEYWORD_COUNT 6

typedef struct {
    tokentype type;
    char value[MAX_TOKEN_SIZE];
}Asiner ;

//storing datatypes checker
typedef struct {
    double value;
    char type[MAX_TOKEN_SIZE]; // Stores "int" or "float"
} EvalResult; 


// Adding symbol table for variable support in statements
typedef struct
{
    char name[MAX_TOKEN_SIZE]; // variable name
    double value; //Variable value
    char type[MAX_TOKEN_SIZE]; // datatype
}Bag;

Bag inventory[100]; // Store up to 100 variables
int itemCount = 0;

const char *keywords[KEYWORD_COUNT] = {"int","float","if","while","return","else"};


int isKeyword(const char *str){
    for (int i = 0; i < KEYWORD_COUNT; i++){
        if(strcmp(str,keywords[i] == 0))
            return 1; // its a keyword
    }
    return 0; // not a keyword
}
// function divide the given code into tokens for
// understanding the code given and identify the datatypes
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
        while (isalnum(code[*pos])){
            token.value[i++] = code[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';

        //check for keyword
        if(isKeyword(token.value)){
            token.type = KEYWORD;
        }else{
            token.type = IDENTIFIER;
        }
        return token;
    }
    if(isdigit(code[*pos])){
        int i = 0;
        // Adding Decimal support
        int hasDecimal = 0; // check for decimal or not 0 false 1 true

        while (isdigit(code[*pos])|| (code[*pos] == '.' && !hasDecimal)){
            if (code[*pos] == '.'){
                hasDecimal = 1; //Ensure only one decimal point
            }
            token.value[i++] = code[*pos];
            (*pos)++;
        }
        token.value[i] = '\0';
        token.type = NUMBER;
        return token;
    }
    if(strchr("+*-/",code[*pos])){
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
    if(code[*pos] == '(' || code[*pos] == ')') {
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



// function for evaluating assignment statements
EvalResult evalExp(const char *code,int *pos){
    Asiner token; 
    EvalResult result;
    // Step 3: Expect an Expression (number or number operator number)
    token = getNextToken(code,pos);
    if (token.type == PUNCTUATION && strcmp(token.value, "(") == 0) {
        result = evalExp(code, pos); // Evaluate inside parentheses
    
        token = getNextToken(code, pos);
        if (token.type != PUNCTUATION || strcmp(token.value, ")") != 0) {
            printf("Syntax Error: Expected ')' but got '%s'\n", token.value);
            result.value = 0;
            strcpy(result.type, "error");
            return result;
        }
    }
    

    else if (token.type == NUMBER){
        result.value == atof(token.value);
        strcpy(result.type,(strchr(token.value,'.')?"float":"int"));
    }else if (token.type == IDENTIFIER){
        int found = 0;
        for (int i=0;i<itemCount;i++){
            if(strcmp(inventory[i].name,token.value)==0){
                result.value = inventory[i].value;
                strcpy(result.type,inventory[i].type);
                found=1;
                break;
            }
        }
        if(!found){
            printf("Error: Undefined variable '%s' \n",token.value);
            result.value = 0;
            strcpy(result.type,"unknown");
        }
    } else{
        printf("Syntax Error: Expected a number or variable , but got '%s'\n",token.value);
        result.value = 0;
        strcpy(result.type,"error");
    }

    // if(token.type !=NUMBER){
    //     printf("Syntax Error: Expexted a number , but got '%s' \n",token.value);
    //     return 0; // break cannot be used in if statements
    // }
    
    // convert string to float and store it
    // double value = atof(token.value);
    
    // //Step 4: (optional) Check for operator and Second Number 
    token = getNextToken(code,pos);
    if (token.type == OPERATOR){
        EvalResult right = evalExp(code,pos); // Recursively evaluate right hand expression
        
        // next
        if(strcmp(result.type,"int")==0&& strcmp(right.type,"float")==0){
            strcpy(result.type,"float"); //implicit conversion to float

        }else if (strcmp(result.type,"float")==0 && strcmp(right.type,"int")==0)
        {strcpy(result.type,"float");}
        if (strcmp(token.value,"+") == 0) result.value += right.value;
        if (strcmp(token.value,"-") == 0) result.value -= right.value;
        if (strcmp(token.value,"*") == 0) result.value *= right.value;
        if (strcmp(token.value,"/") == 0) 
        {if (right.value != 0){result.value /= right.value;}
        else{printf("Error : Division by ZERO");}}
    }else{
        (*pos)--;
    }
    return result;

    // token = getNextToken(code,pos);
    // if(token.type == OPERATOR){
    //     token = getNextToken(code,pos);
    //     if (token.type != NUMBER){
    //         printf("Syntax Error: Expected a number after operator , but got '%s'\n",token.value);
    //         return 0;
    //     }
    // } else{
    //     // pos--; // Step back if it's not an operator
    //     // chnged to *pos as it is a pointer
    //     (*pos)--;
        
    // }

//     while(1){
//         token = getNextToken(code,pos);
//         if(token.type == OPERATOR){
//             (*pos)--; // Step back if not an operator
//             break;
//         } 
//         char op = token.value[0];
//         token = getNextToken(code,pos);
//         if(token.type != NUMBER){
//             printf("Syntax Error : Expected a number after operator, but got '%s'\n",token.value);
//             return value;
//         }

//         double num = atof(token.value);
//         switch (op)
//         {
//         case '+':
//             value+=num;
//             break;
//         case '-':
//             value-=num;
//             break;
//         case '*':
//             value*=num;
//             break;
//             case '/':
//             if (num == 0){
//                 printf("Error: Division by Zero\n");
//                 return value;
//             }
//             value /= num;
//             break;
            
//         case '%':
//             value=(int)value % (int)num;//convert both numbers to integer before evaluating
//             break;
//         }
//     }
// return value;
}

// function to verify correct arrangement or syntax 
// for single assignment statements
// addded the pos pointer to allow tracking of position
//  across multiple statements

int parseAssignment(const char *code,int *pos){
    Asiner token;

    token = getNextToken(code,pos);
    char varType[MAX_TOKEN_SIZE] = "unknown";//Default type

    int isDeclaring =0;
    if (token.type == KEYWORD){
        isDeclaring = 1;
        strcpy(varType,token.value);//storing data type
        token = getNextToken(code,pos);//next
    }
    //Step 1:  Expect IDENTIFIER (variable name)
    // changed &pos -> pos because pos is a pointer while
    // &pos is an integer value so original value will not be modified

    if(token.type !=IDENTIFIER){
        printf("Syntax Error: Expexted a variable name , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }
    //Store name of variable
    char varName[MAX_TOKEN_SIZE];
    strcpy(varName,token.value);
    
    // step2: Expect ASSIGN
    token = getNextToken(code,pos);
    if(token.type !=ASSIGN){
        printf("Syntax Error: Expexted a '=' after variable name , but got '%s' \n",token.value);
        // return 0; // break cannot be used in if statements

        // removing the return value causes the parser to keep parsesing
        // even when '=' is missing
    }

    EvalResult result = evalExp(code,pos);

    // if (strcmp(varType, "int") == 0 && (value != (int)value)) {
    //     printf("Type Error: Cannot assign non-integer value %lf to an 'int' variable '%s'\n", value, varName);
    //     return 0;
    // }
    if (strcmp(varType, "int") == 0 && strcmp(result.type,"float") == 0) {
        printf("Type Error: Cannot assign non-integer value %lf to an 'int' variable '%s'\n", value, varName);
        return 0;
    }

    // Step 5 : Expext `;` (PUNCTUATION)
    token = getNextToken(code,pos);
    if(token.type !=PUNCTUATION){
        printf("Syntax Error: Expexted a ';' at end of the statement , but got '%s' \n",token.value);
        // return 0; // break cannot be used in if statements
        // removed the return statement to continue parsing
    }

    printf("Valid assignment Statement\n");
    strcpy(inventory[itemCount].name,varName);
    inventory[itemCount].value = result.value; //Converts string to float
    strcpy(inventory[itemCount].type,varType);
    itemCount++;// increment stored value count
    printf("Stored: (%s) %s = %lf\n",varType,varName,result.value);
    return 1;

}




// adding a function to parse multiple statements in a single line.
void parseMultiState(const char *code){
    int pos = 0;
    Asiner token;
    while(1){
        // Skip empty spaces
        while(code[pos] == ' ' || code[pos] == '\n') {
            pos++;
        }
        if (code[pos] == '\0'){
            break;//END of input
        }
        //Try to parse an ssignment stement
        // &pos -> modifyies the original value instead of a copy
        if (!parseAssignment(code, &pos)){
            printf("Error : Skipping to next statement...\n");

            // skip to next semicolon or end of input for recovery
            while (code[pos]!= ';' && code[pos] != '\0')
            {
                pos++;
            }

            // if semicolon was found, skip it
            if (code[pos] == ';'){pos++;}
            
        }
    }
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
// print the variables currently stored in parser
void printSymbolTable() {
    printf("\nSymbol Table:\n");
    printf("| Type   | Name   | Value  |\n");
    for (int i = 0; i < itemCount; i++) {
        printf("| %-6s | %-8s | %-6lf |\n",inventory[i].type, inventory[i].name, inventory[i].value);
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

    // if (parseAssigment(code)) {  // If `1` is returned, parsing is successful
    //     printf("Parsing successful!\n");
    // } else {  // If `0` is returned, parsing failed
    //     printf("Parsing failed!\n");
    // }
    // Above code is for single statement in a line
    
    printf("\n Parsing your code:\n%s\n\n",code);
    parseMultiState(code);

    printSymbolTable();
    printf("done");

}
