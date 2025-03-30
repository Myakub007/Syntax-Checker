# Features Added

## changed the tokeizer to support decimal numbers
### how it works 
when checking a number it also checks 
for a decimal point and only allows one decimal point by using if 
statement.
```
while (isdigit(code[*pos])|| (code[*pos] == '.' && !hasDecimal)){
    if (code[*pos] == '.'){
        hasDecimal = 1; //Ensure only one decimal point
    }
    token.value[i++] = code[*pos];
    (*pos)++;
}
```

## Added a Symbol table to store values of variables 
```
// Adding symbol table for variable support in statements
typedef struct
{
    char name[MAX_TOKEN_SIZE]; // variable name
    double value; //Variable value
}Bag;

Bag inventory[100]; // Store up to 100 variables
int itemCount = 0;


```
### How it works
we first edit the parseAssignment() to store the variable name if 
an identifier is found

then at the end of the function we store the variable name in inventory obj
along with its value after it is evaluated 

## Added a function to evaluate assignment expressions before storing the value 

```
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


```

### how this function works
it first checks that after a number an operator is present or not
** if present check for another number
** if absent give error

if both are present evaluated the expression and return the value

** function is called in parseAssignment() After Assignment operator is found