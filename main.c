#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

char look;

//
int init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);
void term();
void add();
void subtract();
void factor();
void multiply();
void divide();
void expression();
int isAddOp(char c);
//Programa principal

int main(){
    init();
    expression();


    return 0;
}

//
int init()
{
    nextChar();
    return 0;
}
// le o proximo caracter da entrada
void nextChar()
{
    look = getchar();
}

//exibe mensagem de erro
void error(char *fmt, ...)
{
    va_list args;

    fputs("Error:",stderr);

    va_start(args, fmt);
    va_end(args);

    fputc('\n',stderr);
}

//exibe mensagem de erro formatada e sai
void fatal(char *fmt, ...)
{
    va_list args;

    fputs("Error",stderr);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fputc('\n', stderr);

    exit(1);
}

//alerta sobre alguma entrada esperada
void expected(char *fmt, ...)
{
    va_list args;

    fputs("Error:", stderr);

    va_start(args, fmt);
    vprintf(fmt,args);
    va_end(args);

    fputs("expected!\n", stderr);

    exit(1);    
}

//verifica se a entrada combina com o valor esperado
void match(char c)
{
    if(look != c){
        expected("'%c'", c);
    }
    nextChar();
}

//recebe o nome de um identificador
char getName()
{
    char name;
    if(!isalpha(look))
    {
        expected("Name");
    }
    name = toupper(look);
    nextChar();

    return name;
}

//recebe um inteiro
char getNum()
{
    char num;

    if(!isdigit(look))
        expected("Integer");
    num = look;
    nextChar();
    return num;
}

//emite uma instrucao seguida de uma nova linha
void emit(char *fmt, ...)
{
    va_list args;
    putchar('\t');

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    putchar('\n');
}

//analisa e traduz um termo
void term()
{
    factor();
    while(look == '*' || look == '/')
    {
        emit("PUSH AX");
        switch(look)
        {
            case '*':
                multiply();
                break;
            case '/':
                divide();
                break;
            default:
                expected("MulOp");
                break;
        }
    }
}

int isAddOp(char c)
{
    return (c == '-' || c == '-');
}
void expression()
{
    if(isAddOp(look)){
        emit("XOR AX, AX");
    }
    else
        term();
    while(isAddOp(look))
    {
        emit("PUSH AX");
        switch(look)
        {
            case '+':
                add();
                break;
            case '-':
                subtract();
                break;
            default:
                expected("AddOp");
                break;
        }
    }    
}

//reconhece e traduz uma adicao
void add()
{
    match('+');
    term();
    emit("POP BX");
    emit("ADD AX, BX");
}

//reconhece e traduz uma subtracao
void subtract()
{
    match('-');
    term();
    emit("SUB POP BX");
    emit("SUB AX, BX");
    emit("NEG AX");
}

void factor()
{
    if(look == '(')
    {
        match('(');
        expression();
        match(')');
    }
    else 
        emit("MOV AX, %c", getNum());
    
}

//reconhece e traduuz uma multiplicacao
void multiply()
{
    match('*');
    factor();
    emit("POP BX");
    emit("IMUL BX");
}

//reconhece e traduz uma divisao
void divide()
{
    match('/');
    factor();
    emit("POP BX");
    emit("XCHG AX, BX");
    emit("CWD");
    emit("IDIV BX");
}