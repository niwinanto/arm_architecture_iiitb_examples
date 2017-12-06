#include<iostream>
#include<stack>
#include<cstdlib>
#include<cstdio>
using namespace std;


char infix[100];
char postfix[100];
stack <char> stk;

int is_Balance(){

    int i = 0, j = 0 ;
    char temp[100];
//printf("ssss--%d\n",infix[1]);
#if 1
    while(infix[i] != '\0'){
        if(infix[i] != 0x20){
            infix[j++] = infix[i];
        }
        i++;
    }
    infix[j++] = '\0';
#endif
#if 1
    i = 0; j = 0;
    if(infix[i] == '-'){
        temp[j++] = '0';
        temp[j++] = infix[i];
        i++;
    }
    while(infix[i] != '\0'){
        if(infix[i] == '-' ){
            if( (infix[i-1] == '+')  || (infix[i-1] == '-')  || (infix[i-1] == '*')  || (infix[i-1] == '/')  || (infix[i-1] == '(') ){
                temp[j++] = '0';
            }
        }
        temp[j++] = infix[i];
        i++;
    }
    temp[j++] = '\0';

    i = 0; j = 0;
    while(temp[i] != '\0'){
        infix[i] = temp[i];
        i++;
    }
    infix[i] = temp[i];
#endif
    i = 0;
    while(infix[i] != '\0'){

        if( !((infix[i] == 0x20)  || (infix[i] == '+')  || (infix[i] == '-')  || (infix[i] == '*')  || (infix[i] == '/')  || (infix[i] == '(')  || (infix[i] == ')') || (( infix[i] < '9' ) && ( infix[i] >= '0' ) ) )){
            cout << ";Not a valid expression(only numbers,+,-,*,/,(,)) \n";
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
                    cout << ";Not a balanced equation\n";
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
            i++;
            while( ( infix[i] < '9' ) && ( infix[i] >= '0' ) ){
                postfix[j++] = infix[i];
                i++;
            }
            postfix[j++] = ',';
            i--;
        }
        else if(( infix[i] == ')' )){
            while((!stk.empty()) && (stk.top() != '(')){
                //cout << stk.top() ;
                postfix[j++] = stk.top();
                postfix[j++] = ',';
                stk.pop();
            }
            stk.pop();
        }
        else{
            while( (!stk.empty()) && ( stk.top() <= infix[i] ) && ( stk.top() != '(') ) {
                if( !((infix[i] == '(')  || (infix[i] == ')'))){
               // cout << stk.top() ;
                postfix[j++] = stk.top();
                postfix[j++] = ',';
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
        postfix[j++] = ',';
        stk.pop();
    }
    postfix[j++] = '\0';
    return 1;
}

int codeGen(){
    int i = 0;
    int val = 0;
    printf("\n\n;****************CODE STARTS*****************\n\tAREA myCode, CODE\n\t\tENTRY\n\t\tEXPORT __main\n\n\n__main FUNCTION\n\n");
    while(postfix[i] != '\0'){
        if( ( postfix[i] < '9' ) && ( postfix[i] >= '0' ) ){
            val = 0;
            while(postfix[i] != ','){
                val = (val*10)+(postfix[i]-'0');
                i++;
            }
            printf("\tMOV R0, #%d\n",val);
            printf("\tPUSH {R0}\n");

        }
        else if(postfix[i] == ','){
            //
        }
        else{
            printf("\n\tPOP {R1, R0}\n");
            if(postfix[i] == '+'){
                printf(";Addition operation\n");
                printf("\tADD R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
               // printf("\t;%d\n",i);
            }
            else if(postfix[i] == '-'){
                printf(";Substraction operation\n");
                printf("\tSUB R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
            }
            else if(postfix[i] == '*'){
                printf(";Multiplication operation\n");
                printf("\tMUL R0, R0, R1\n");
                printf("\tPUSH {R0}\n");
            }
            else if(postfix[i] == '/'){
                printf(";Division operation\n");
                printf("\tCMP R1, #0\n\tBEQ stop\n");
                printf("\tUDIV R0, R0, R1\n");
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
    cout << ";input the expression\n";
    //cin >> infix;
    scanf("%[^\n]s",infix);
    cout <<";expression parsed is: "<< infix << endl;

    i = is_Balance();
    if( i == 0 ){
        cout << ";It is a balanced expression\n";
    }
    else{
        exit(0);
    }
    //cout << "size of stack is: " << stk.size();

    i = to_Postfix();
    cout << ";postfix form is : "<<postfix << endl;

    i = codeGen();
}
