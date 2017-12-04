#include<iostream>
#include<stack>
#include<cstdlib>
#include<cstdio>
using namespace std;


char infix[100];
char postfix[100];
stack <char> stk;

int is_Balance(){

    int i = 0 ;
    while(infix[i] != '\0'){

        if( !((infix[i] == ' ')  || (infix[i] == '+')  || (infix[i] == '-')  || (infix[i] == '*')  || (infix[i] == '/')  || (infix[i] == '(')  || (infix[i] == ')') || (( infix[i] < '9' ) && ( infix[i] >= '0' ) ) )){
            cout << "Not a valid expression(only numbers,+,-,*,/,(,)) \n";
            break;
        }

        if( (infix[i] == '(')  || (infix[i] == ')')){
            if((infix[i] == '(') )
                stk.push(infix[i]);
            if( infix[i] == ')' ){
                if((!stk.empty()) && (stk.top() == '(')){
                    stk.pop();
                    //cout << "balanced\n";
                }
                else{
                    cout << "Not a balanced equation\n";
                    break;
                }
            }
        }
        i++;
    }
    return stk.size();
}

int to_Postfix(){
    int i = 0 ,j = 0;

    while(infix[i] != '\0'){
        if( ( infix[i] < '9' ) && ( infix[i] >= '0' ) ){
            //cout << infix[i] ;
            postfix[j++] = infix[i];
        }
        else if(( infix[i] == ')' )){
            while((!stk.empty()) && (stk.top() != '(')){
                //cout << stk.top() ;
                postfix[j++] = stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else{
            while( (!stk.empty()) && ( stk.top() >= infix[i] ) && ( stk.top() != '(') ) {
                if( !((infix[i] == '(')  || (infix[i] == ')'))){
               // cout << stk.top() ;
                postfix[j++] = stk.top();
                }
                stk.pop();
            }
            stk.push(infix[i]);
            //cout << infix[i] << endl;
        }
        i++;
    }

    while(!stk.empty()){
        //cout << stk.top();
        postfix[j++] = stk.top();
        stk.pop();
    }
    postfix[j++] = '\0';
    return 1;
}

int codeGen(){
    int i = 0;
    printf("\n\n;****************CODE STARTS*****************\nAREA myCode, CODE\n\tENTRY\n\tEXPORT __main\n\n\n__main FUNCTION\n\n");
    while(postfix[i] != '\0'){
        if( ( postfix[i] < '9' ) && ( postfix[i] >= '0' ) ){
            printf("\tMOV R0, #%c\n",postfix[i]);
            printf("\tPUSH {R0}\n");

        }
        else{
            printf("\tPOP {R0, R1}\n");
            if(postfix[i] == '+'){
                printf("\tADD R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
               // printf("\t;%d\n",i);
            }
            else if(postfix[i] == '-'){
                printf("\tSUB R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
            }
            else if(postfix[i] == '*'){
                printf("\tMUL R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
            }
            else if(postfix[i] == '/'){
                printf("\tDIV R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
            }
            else{
                printf("\t;ADD R0, R0, R1\n");
                printf("\t;PUSH {R0}\n");
                printf("\t;%d\n",i);
            }
        }
        i++;
    }
    printf("\nstop \tB stop\n\tENDFUNC\n\tEND\n;****************CODE ENDS********************\n");
    return 1;
}

int main(){
    int i = 0;
    cout << "input the expression\n";
    cin >> infix;
    cout <<"expression parsed is: "<< infix << endl;

    i = is_Balance();
    if( i == 0 ){
        cout << "It is a balanced expression\n";
    }
    else{
        exit(0);
    }
    //cout << "size of stack is: " << stk.size();

    i = to_Postfix();
    cout << "postfix form is : "<<postfix << endl;

    i = codeGen();
}
