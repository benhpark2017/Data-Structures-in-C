/**Solutions to Chapter 3, Section 4, numbered exercises 2, 3, 4, and 5 of
 * Horowitz's Fundamentals of Data Structures in C.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum {lparen, rparen, plus, minus,
              times, divide, mod, logical_and,
              logical_or, left_shift, right_shift,
              equal, not_equal, less, greater,
              less_equal, greater_equal, eos, operand,
             } precedence;

int stack[MAX_STACK_SIZE]; //global stack for input math expression
char expr[MAX_EXPR_SIZE];

//in-stack precedence (Use the precedence chart)
//left parenthesis, right parenthesis, plus, minus, times, divide, mod, eos, operand
const int isp[] = { 0,19,12,12,13,13,13,5,4,11,11,9,9,10,10,10,10,0 };

//incoming precedence (Use the precedence chart)
//left parenthesis, right parenthesis, plus, minus, times, divide, mod, eos, operand
const int icp[] = { 20,19,12,12,13,13,13,5,4,11,11,9,9,10,10,10,10,0 };

//Function prototypes
int evaluatePostfix(void);
void addToStack(int *top, int item);
int deleteFromStack(int *top);
void infixToPostfix(void);
void setToken(precedence token, char **str);
precedence getToken(char *symbol, int *n);

//Driver code
int main(){
    printf("Please enter an infix expression, e.g. 3*9/2+3\n");
    printf("followed by Enter key: \n");
    scanf("%s", expr);
    infixToPostfix();

    printf("\nResult: %d \n", evaluatePostfix());
    return 0;
}

/**The function evaluates a postfix expression expr, maintained as a global variable.
 * '\0' is at the end of the expression. The stack and top of the stack are global
 * variables. The function getToken is used to return the token type and the
 * character symbol. The operands are assumed to be single character digits.
 */
int evaluatePostfix() {
    precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    int top = -1;
    token = getToken(&symbol, &n);
    while (token != eos){
        if (token == operand)
            addToStack(&top, symbol - '0'); //insert into stack
        else {
            //remove two operands, perform operation, and return result
            //into the stack
            op2 = deleteFromStack(&top);
            op1 = deleteFromStack(&top);
            switch (token){
                case plus: addToStack(&top, op1 + op2); break;
                case minus: addToStack(&top, op1 - op2); break;
                case times: addToStack(&top, op1 * op2); break;
                case divide: addToStack(&top, op1 / op2); break;
                case mod: addToStack(&top, op1 % op2); break;
                case logical_and: addToStack(&top, op1 && op2); break;
                case logical_or: addToStack(&top, op1 || op2); break;
                case left_shift: addToStack(&top, op1 << op2); break;
                case right_shift: addToStack(&top, op1 >> op2); break;
                case equal: addToStack(&top, op1 == op2); break;
                case not_equal: addToStack(&top, op1 != op2); break;
                case less: addToStack(&top, op1 < op2); break;
                case greater: addToStack(&top, op1 > op2); break;
                case less_equal: addToStack(&top, op1 <= op2); break;
                case greater_equal: addToStack(&top, op1 >= op2); break;
                default: break;
            } //end switch
        } //end else
        token = getToken(&symbol, &n);
    }
    return deleteFromStack(&top); //return result
}

/**The function gets the next token. The variable symbol is the character
 * representation, which is returned, the token is represented by its
 * enumerated value, which is returned in the function name. */
precedence getToken(char *symbol, int *n){
    *symbol = expr[(*n)++];
    switch (*symbol){
        case '(': return lparen;
        case ')': return rparen;
        case '+': return plus;
        case '-': return minus;
        case '/': return divide;
        case '*': return times;
        case '%': return mod;
        case '&': if ( expr[*n] == '&' ) {
                      ++*(n); return logical_and; // logical and 연산자 반환
                  }
                  return eos;
        case '|': if ( expr[*n] == '|' ) {
                      ++*(n); return logical_or; // logical and 연산자 반환
                  }
                  return eos;
        case '<': if (expr[*n] == '<') { 
                      ++(*n); return left_shift;
                  } else if (expr[*n] == '=') { // If = follows <
                      ++(*n);
                      return less_equal; // Return the less than or equal operator
                  }
                  return less; // Otherwise, return less than operator
        case '>': if (expr[*n] == '>') { // If > is followed by another >
                      ++(*n);
                      return right_shift; // Return the right shift operator
                  } else if (expr[*n] == '=') { // If = follows >
                      ++(*n);
                      return greater_equal; // Return the greater than or equal operator
                  }
                  return greater; // Otherwise, return greater than operator
        case '=': if (expr[*n] == '=') { // = 뒤에 문자가 = 일경우
                      ++*(n); return equal; // logical equal 연산자 반환
                  }
                  return eos;
        case '!': if (expr[*n] =='=' ) {
                      ++*(n); return not_equal; // logical not equal 연산자 반환}
                  }
                  return eos; // 그렇지 않다면 eos 반환
        case '\0': return eos;
        default : return operand;
        //no need to check error, since the default is set to operand
    }
}

/**Function that converts an infix expression into postfix expression.
 * The function outputs the postfix expression. The expression string,
 * the stack, and top are global variables.
 */
void infixToPostfix(void){
    char symbol;
    char expr_post[MAX_EXPR_SIZE] = {0,};
    char *str = expr_post;
    precedence token;
    int n = 0;
    int top = 0; //place eos on stack
    stack[0] = eos;

    //algorithm to convert infix into postfix
    //repeat until token reaches eos (end of string)
    for (token = getToken(&symbol, &n); token != eos;
         token = getToken(&symbol, &n)){
        if (token == operand){
            *str++ = symbol;
        }
        //If token is a right parenthesis
        else if (token == rparen){
            while (stack[top] != lparen) //unstack until left parenthesis is reached
                setToken(deleteFromStack(&top), &str);
            deleteFromStack(&top);
        } else {
            //remove and print symbols whose isp is greater than or equal to the
            //current token's icp
            while (isp[stack[top]] >= icp[token])
                setToken(deleteFromStack(&top), &str);
            addToStack(&top, token);
        }
    }
    while ( (token = deleteFromStack(&top)) != eos)
        setToken(token, &str);
    printf("\n");

    printf("Postfix expression: %s \n", expr_post);
    strcpy(expr, expr_post);
}

void setToken(precedence token, char **str){
    switch(token){
        case plus: *(*str)++ = '+'; return;
        case minus: *(*str)++ = '-'; return;
        case divide: *(*str)++ = '/'; return;
        case times: *(*str)++ = '*'; return;
        case mod: *(*str)++ = '%'; return;
        case logical_and: *(*str)++ = '&'; *(*str)++ = '&'; return;
        case logical_or: *(*str)++ = '|'; *(*str)++ = '|'; return;
        case left_shift: *(*str)++ = '<'; *(*str)++ = '<'; return;
        case right_shift: *(*str)++ = '>'; *(*str)++ = '>'; return;
        case equal: *(*str)++ = '='; *(*str)++ = '='; return;
        case not_equal: *(*str)++ = '!'; *(*str)++ = '='; return;
        case less: *(*str)++ = '<'; return;
        case greater: *(*str)++ = '>'; return;
        case less_equal: *(*str)++ = '<'; *(*str)++ = '='; return;
        case greater_equal: *(*str)++ = '>'; *(*str)++ = '='; return;
        case eos: return;
        default: return; //operand
    }
}


void addToStack(int* top, int item){
    if ((*top) == MAX_STACK_SIZE){
        fprintf(stderr, "The stack is full.\n");
        exit(1);
    }
    stack[++(*top)] = item;
}


int deleteFromStack(int *top){
    if ((*top) == -1) return eos;
    return stack[(*top)--];
}

//END OF PROGRAM


