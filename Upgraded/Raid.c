#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
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

// Adding symbol table for variable support in statements
typedef struct
{
    char name[MAX_TOKEN_SIZE]; // variable name
    double value; //Variable value
}Bag;

Bag inventory[100]; // Store up to 100 variables
int itemCount = 0;



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
    if(strchr("+*-/%",code[*pos])){
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



// function for evaluating assignment statements
double evalExp(const char *code,int *pos){
    Asiner token; 
    // Step 3: Expect an Expression (number or number operator number)
    token = getNextToken(code,pos);
    if(token.type !=NUMBER){
        printf("Syntax Error: Expexted a number , but got '%s' \n",token.value);
        return 0; // break cannot be used in if statements
    }
    
    // convert string to float and store it
    double value = atof(token.value);
    
    // //Step 4: (optional) Check for operator and Second Number 
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

    while(1){
        token = getNextToken(code,pos);
        if(token.type != OPERATOR){
            (*pos)--; // Step back if not an operator
            break;
        } 
        char op = token.value[0];
        token = getNextToken(code,pos);
        if(token.type != NUMBER){
            printf("Syntax Error : Expected a number after operator, but got '%s'\n",token.value);
            return value;
        }

        double num = atof(token.value);
        switch (op)
        {
        case '+':
            value+=num;
            break;
        case '-':
            value-=num;
            break;
        case '*':
            value*=num;
            break;
            case '/':
            if (num == 0){
                printf("Error: Division by Zero\n");
                return value;
            }
            value /= num;
            break;
            
        case '%':
            value=(int)value % (int)num;//convert both numbers to integer before evaluating
            break;
        }
    }
return value;
}

// function to verify correct arrangement or syntax 
// for single assignment statements
// addded the pos pointer to allow tracking of position
//  across multiple statements

int parseAssignment(const char *code,int *pos){
    Asiner token;

    //Step 1:  Expect IDENTIFIER (variable name)
    // changed &pos -> pos because pos is a pointer while
    // &pos is an integer value so original value will not be modified

    token = getNextToken(code,pos);
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

    double value = evalExp(code,pos);
    // Step 5 : Expext `;` (PUNCTUATION)

    
    token = getNextToken(code,pos);
    if(token.type !=PUNCTUATION){
        printf("Syntax Error: Expexted a ';' at end of the statement , but got '%s' \n",token.value);
        // return 0; // break cannot be used in if statements
        // removed the return statement to continue parsing
    }

    printf("Valid assignment Statement\n");
    strcpy(inventory[itemCount].name,varName);
    inventory[itemCount].value = value; //Converts string to float
    itemCount++;// increment stored value count
    printf("Stored: %s = %lf\n",varName,value);
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
    for (int i = 0; i < itemCount; i++) {
        printf("%s = %lf\n", inventory[i].name, inventory[i].value);
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
