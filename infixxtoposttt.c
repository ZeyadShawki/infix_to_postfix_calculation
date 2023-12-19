#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
   float data;
    struct node*next;
}node;

typedef struct
{
    node*top;
}stack;
 
stack*initialize()
 {
   stack*s=malloc(sizeof(stack));
   s->top=NULL;
   return s;
 }
 
node* newnode(float x)
{
  node*n=malloc(sizeof(node));
  n->data=x;
  n->next=NULL;
  return n;
}
                
void push(stack*s,float x)
{
       node*n=newnode(x);
           n->next=s->top;
           s->top=n;
     
       
}
                       
 float pop(stack*s)
{
       node*temp=s->top;
       float data=temp->data;
       s->top=temp->next;
       free(temp);
       return data;
       
}
                  
                
int isempty(stack*s)
{
       if(s->top==NULL)
           return 1;
       return 0;
}

void display(stack*s)
{
       node*temp=s->top;
       while(temp!=NULL)
       {
           printf("%f",temp->data);
           temp=temp->next;
       }
   }
       
   
float peek(stack*s)
{
    return s->top->data;
}






float evaluate(char x,float operand1,float operand2)
{
    if(x=='^')
        return pow(operand1,operand2);
    if(x=='+')
        return(operand1+operand2);
    if(x=='-')
        return(operand1-operand2);
    if(x=='/')
        return(operand1/operand2);
    if(x=='*')
        return(operand1*operand2);
}

float evaluatePostfix(char* postfix)
{
    stack *s=initialize();
    char *token;
    token = strtok(postfix," ");
    while (token !=NULL)
    {
        if (isdigit(token[0]))
            push(s,atof(token));
        else if (token[0]=='-'&&isdigit(token[1]))
            push(s,atof(token));
        else
        {
            float x=pop(s);
            float y=pop(s);
            push(s,evaluate(token[0],y,x));
        }
        token=strtok(NULL," ");
    }
    return pop(s);
}
int priority(char c)
{
    if(c=='(')
        return 3;
    if(c=='^')
        return 2;
    if(c=='*'||c=='/')
        return 1;
    else return 0;
}


char* infixtopostfix(char*infix)
{
    stack*s=initialize();
    char*postfix=malloc(strlen(infix)+1);
    postfix[0]='\0';
    char*token=strtok(infix," ");
    while(token!=NULL)
    {
        if(isdigit(token[0])|| strlen(token)>1)
        {
        strcat(postfix,token);
        strcat(postfix," ");
        }
        else if(token[0]==')')
        {
            while(!isempty(s)&&peek(s)!='(')
            {
                char c=pop(s);
                char x[3];
                x[0]=c; x[1]=' '; x[2]='\0';
                strcat(postfix,x);
                strcat(postfix," ");
            }
            pop(s);
        }
        else if(isempty(s))
            push(s,token[0]);
        else
        {
        while(!isempty(s)&&priority(peek(s))>=priority(token[0])&&peek(s)!='(')
        {
            char a=pop(s);
            char y[3];
            y[0]=a; y[1]=' '; y[2]='\0';
            strcat(postfix,y);
            strcat(postfix," ");
        }
            
        push(s,token[0]);
        }
        token=strtok(NULL," ");
    }
    while(!isempty(s))
    {
        char b=pop(s);
        char z[3];
        z[0]=b; z[1]=' '; z[2]='\0';
        strcat(postfix,z);
        strcat(postfix," ");
    }
    return postfix;
}
void replce_newline_with_space(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
   
}

int main()
    {
       char infixExpr[256] = " ";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL) 
    {
        replce_newline_with_space(infixExpr);
        char*postfix=infixtopostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    } 
        return 0;
    }