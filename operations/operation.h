#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <iterator>


using namespace std;

class Operation {
    protected:
        string equation;

    public:
        Operation* left;
        Operation* right;

        static Operation* buildFromEquation(string equation);

        inline string name() { return equation; }

        virtual float operate() = 0;
};


class Suma: public Operation{
public:
    Suma(string left_equation, string right_equation){
        left = Operation::buildFromEquation(left_equation);
        right = Operation::buildFromEquation(right_equation);
    }
    float operate(){
        return left->operate() + right ->operate();
    }
    ~Suma();
};

class Resta: public Operation{
public:
    Resta(string left_equation, string right_equation){
        left = Operation::buildFromEquation(left_equation);
        right = Operation::buildFromEquation(right_equation);
    }
    float operate(){
        return left->operate() - right->operate();
    }
    ~Resta();
};


class Multiplicacion: public Operation{
public:
    Multiplicacion(string left_equation, string right_equation){
        left = Operation::buildFromEquation(left_equation);
        right = Operation::buildFromEquation(right_equation);
    }
    float operate(){
        return left->operate() * right ->operate();
    }
    ~Multiplicacion();
};

class  Divicion: public Operation{
public:
    Divicion(string left_equation, string right_equation){
        left = Operation::buildFromEquation(left_equation);
        right = Operation::buildFromEquation(right_equation);
    }
    float operate(){
        return left->operate()/right ->operate();
    }
    ~Divicion();
};

class Potencia: public Operation{
public:
    Potencia(string left_equation, string right_equation){
        left = Operation::buildFromEquation(left_equation);
        right = Operation::buildFromEquation(right_equation);
    }
    float operate(){
        return pow(left->operate() , right ->operate());
    }
    ~Potencia();
};





class Constant: public Operation{
public:
    Constant(string equation_){
        equation = equation_;
        left = nullptr;
        right = nullptr;
    }

    float operate(){
        return strtof(equation.c_str(),0);
    }
    ~Constant();
};

class Variable: public Operation{

    Variable(string equation_){
        equation = equation_;
        left = nullptr;
        right = nullptr;
    }
    ~Variable();


};

#endif