#include "operation.h"


char operations[] = { '+', '-', '*', '/','^'};

char caracters[] = {'+', '-', '*', '/','^','(',')','0','1','2','3','4','5','6','7','8','9','\n'};

int Highpriority(string equation,int &pos);

void ReduceExtremeBrackets(string &equation);

void ReduceMultiPlus(string &equation);

void SetValues(string &equation);

bool CheckVariable(string equation);

void ReplaceVariable(string &equation,char var,string real);

Operation* Operation::buildFromEquation(string equation) {


    SetValues(equation);
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

bool CheckVariable(string equation){
    int size_car = sizeof(caracters)/ sizeof(char);
    if(equation.size()==0)
        return false;

    for(int i=0;i<equation.size();i++){
        bool is= false;
        for(int j=0;j<size_car;j++){
            if(equation[i]==caracters[j]){
                is = true;
            }
        }
        if (!is){
            return true;
        }
    }
}

void SetValues(string &equation){

    map<char,string> values;

    int size_car = sizeof(caracters)/ sizeof(char);
    for(int i=0;i<equation.size();i++){
        bool is= false;
        for(int j=0;j<size_car;j++){
            if(caracters[j]==equation[i]){
                is = true;
            }
        }
        if (!is){
            values.insert(pair<char,string>(equation[i],"5"));

        }
    }
    map<char, string>::iterator itr;

    int c = 0;
    for (itr = values.begin(); itr != values.end(); ++itr) {
        string s;
        cout << "Ingrese el valor de la variable " << itr->first << ": ";
        cin >> s;
        itr->second = s;
        //values.insert(pair<char,string>(itr->first,s));
        cout << endl;
        c++;
    }
    for (itr = values.begin(); itr != values.end(); ++itr) {
        ReplaceVariable(equation,itr->first,itr->second);
    }
};

void ReplaceVariable(string &equation,char var, string real){
    for(int i =0;i<equation.size();i++){
        if(equation[i]==var){
            equation = equation.substr(0,i)+real+equation.substr(i+1);
            ReplaceVariable(equation,var,real);
        }
    }
    return;
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
                    return i+1;
                }
            }
        }
    }
    return -1;
}



void ReduceMultiPlus(string &equation){
    //cout << equation<<endl;
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

void DeleteAll(Operation* op){

    if(op->right)
        DeleteAll(op->right);
    if(op->left)
        DeleteAll(op->left);
    delete op;


}


Potencia::~Potencia() {
    DeleteAll(this);
}

Suma::~Suma() {
    DeleteAll(this);
}
Resta::~Resta() {
    DeleteAll(this);
}
Multiplicacion::~Multiplicacion() {
    DeleteAll(this);
}
Divicion::~Divicion() {
    DeleteAll(this);
}
Constant::~Constant() {
    DeleteAll(this);
}
