#include "operation.h"


char operations[] = { '+', '-', '*', '/','^'};

int Highpriority(string equation,int &pos);

void ReduceExtremeBrackets(string &equation);

void ReduceMultiPlus(string &equation);


Operation* Operation::buildFromEquation(string equation) {

    ReduceExtremeBrackets(equation);
    ReduceMultiPlus(equation);

    int pos;

    switch (Highpriority(equation,pos)){
        case 1:
            return new Suma(equation.substr(0,pos),equation.substr(pos+1));
        case -1:
            return new Constant(equation);
        case 2:
            return new Resta(equation.substr(0,pos),equation.substr(pos+1));
        case 3:
            return new Multiplicacion(equation.substr(0,pos),equation.substr(pos+1));
        case 4:
            return new Divicion(equation.substr(0,pos),equation.substr(pos+1));
        case 5:
            return new Potencia(equation.substr(0,pos),equation.substr(pos+1));

    }



}

int Highpriority(string equation,int &pos){


    int size_op = sizeof(operations)/ sizeof(char);
    for(int i=0;i<size_op;i++){
        int c= 0;
        for(int j=0;j<equation.size();j++){
            if(equation[j]=='('){
                c++;
            }
            if(equation[j]==')'){
                c--;
            }

            if(c==0 ){
                if(equation[j]==operations[i]){
                    if(operations[i] =='-' and equation[j-1]=='*'){
                        pos = j-1;
                        return 3;
                    }
                    pos = j;
                    cout<<i+1;




                    return i+1;
                }
            }
        }
    }
    return -1;



}



void ReduceMultiPlus(string &equation){
    cout << equation<<endl;
    for(int i=0;i<equation.size();i++){
        if((equation[i]=='+' or equation[i]=='-')and(equation[i+1]=='+' or equation[i+1]=='-')){
            int c =1;
            int p;
            for(int j=i;i<equation.size();j++){

                if(equation[j]=='-'){
                    c = c*(-1);
                }
                else if(equation[j]=='+'){
                    c = c*(1);
                }
                else if((equation[j]!='-') and (equation[j]!='+')){
                    p = j;
                    break;
                }
            }

            if(c==-1){
                equation = equation.substr(0,i)+"-"+equation.substr(p);
                ReduceMultiPlus(equation);
            }
            else if(c==1){
                equation = equation.substr(0,i)+"+"+equation.substr(p);
                ReduceMultiPlus(equation);
            }

        }
    }
    cout << equation<<endl;
    return;

};




void ReduceExtremeBrackets(string &equation){

    if(equation[0]=='(' or equation[equation.size()-1]==')'){
        int c = 0;
        for(int i=0;i<equation.size();i++){
            if(equation[i]=='('){
                c++;
            }
            if(equation[i]==')'){
                c--;
            }
        }

        if(c>0){
            equation = equation.substr(1);
        }
        if(c<0){
            equation = equation.substr(0,equation.size()-1);
        }

    }

    //quitamos los parentesis extremos hasta que solo haya internos

    if(equation[0]=='('){
        int c = 0;

        for(int i=0;i<equation.size();i++){
            if(equation[i]=='('){
                c++;
            }
            if(equation[i]==')'){
                c--;
                if(c==0 ){
                    if(i == equation.size()-1){

                        equation = equation.substr(1,equation.size()-2);
                        ReduceExtremeBrackets(equation);
                        return;

                    } else{
                        return;
                    }
                }
            }
        }
    }
    return;
};
