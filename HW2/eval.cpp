//
//  eval.cpp
//  HW2
//
//  Created by Kratik Agrawal on 1/28/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;


bool evalPostfix(string& postfix, const bool values[], bool& tempResult);

int precedence(char ch){
    switch (ch){
        case '!':
            return 20;
        case '&':
            return 10;
        case '|':
            return 0;
        default:
            return -1;
    }
}

string removeSpaces(string infix){
    string noSpaces = "";
    for(int i = 0; i < infix.size(); i++){
        if(infix.at(i) != ' ')
            noSpaces += infix.at(i);
    }
    return noSpaces;
}

int evaluate(string infix, const bool values[], string& postfix, bool& result){
    infix = removeSpaces(infix);
    postfix = "";
    stack<char> operators;
    stack<char> paren;
    for(int i = 0; i < infix.size();i++){
        char c = infix.at(i);
        switch (c){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if(i != 0 && infix.at(i-1) == ')') return 1; //number can't follow )
                if(i != 0 && (isdigit(infix.at(i-1)) || infix.at(i-1) == ')')) return 1; //number can't follow a number
                if(i != infix.size()-1 && (infix.at(i+1) == '(' || infix.at(i+1) == '!')) return 1; //number can't be followed by ( or ! )
                postfix+= c;
                break;
            case ' ':
                break;
            
            case '(':
                if(i == infix.size()-1) return 1; //can't end with open paranthesis
                if(i != infix.size()-1 && infix.at(i+1) == ')') return 1;
                operators.push(c);
                paren.push(c);
                break;
            case ')':
                if(i == 0) return 1;
                while(operators.top() != '('){
                    postfix+= operators.top();
                    operators.pop();
                    
                }
                operators.pop();
            
                if(paren.empty()) return 1;
                else paren.pop();
                
                break;
            
            case '&':
            case '|':
                if(i != 0 && (infix.at(i-1) == '&' || infix.at(i-1) == '!' || infix.at(i-1) == '|')) return 1;
            case '!':
                if(i == infix.size()-1 || i == 0) return 1; //can't end with operators
                while(!operators.empty() && operators.top() != '(' && precedence(c) <= precedence(operators.top())){
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(c);
                break;
            default:
                return 1;
        }
    }
    
    if(!paren.empty()) return 1; // if there are more open ( than )
     
    while(!operators.empty()){
        postfix += operators.top();
        operators.pop();
    }
    //cout << postfix << endl << endl;
    bool tempResult;
    if(evalPostfix(postfix, values, tempResult))
        result = tempResult;
    else
        return 1;
//    if(result == true)
//        cout << "true" << endl << endl;
//    else
//        cout << "false" << endl << endl;

    
    return 0;
}

bool evalPostfix(string& postfix, const bool values[], bool& tempResult){
    stack<bool> operands;
    for(int i = 0; i < postfix.size();i++){
        char c = postfix.at(i);
        if(c == '&' || c == '|' ){
            if(operands.size() < 2)
                return false;
            bool o2 = operands.top();
            operands.pop();
            bool o1 = operands.top();
            operands.pop();
            if(c == '&')
                operands.push(o1 && o2);
            if(c == '|')
                operands.push(o1 || o2);
        } else if(c == '!'){
            bool operandTemp = operands.top();
            if(operands.empty())
                return false;
            operands.pop();
            operands.push(!operandTemp);
        } else{
            operands.push(values[c-'0']);
        }
    }
    if(operands.size() != 1)
        return false;
    tempResult = operands.top();
    return true;
    
}

//
//int main()
//{
//    bool ba[10] = {
//        //  0      1      2      3      4      5      6      7      8      9
//        true,  true,  true,  false, false, false, true,  false, true,  false
//    };
//
//
//    string pf;
//    bool answer;
//
//
//
//
//
////    evaluate("(3)", ba, pf, answer);
////    evaluate("2&(3)", ba, pf, answer);
////    evaluate("0 & !9", ba, pf, answer);
////    evaluate("!(7|8)", ba, pf, answer);
////    evaluate("!7|8", ba, pf, answer);
////    evaluate("6|4&5", ba, pf, answer);
////    evaluate("1&!(9|1&1|9) | !!!(9&1&9)", ba, pf, answer);
//
//
//    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
//    assert(evaluate("8|", ba, pf, answer) == 1);
//    assert(evaluate(" &6", ba, pf, answer) == 1);
//    assert(evaluate("4 5", ba, pf, answer) == 1);
//    assert(evaluate("01", ba, pf, answer) == 1);
//    assert(evaluate("()", ba, pf, answer) == 1);
//    assert(evaluate("()4", ba, pf, answer) == 1);
//    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
//    assert(evaluate("2(&8)", ba, pf, answer) == 1);
//    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
//    assert(evaluate("x+5", ba, pf, answer) == 1);
//    assert(evaluate("", ba, pf, answer) == 1);
//    assert(evaluate("2|3|4", ba, pf, answer) == 0
//           &&  pf == "23|4|"  &&  answer);
//    assert(evaluate("2|(3|4)", ba, pf, answer) == 0
//           &&  pf == "234||"  &&  answer);
//    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
//           &&  pf == "43!03&&|"  &&  !answer);
//    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
//    ba[2] = false;
//    ba[9] = true;
//    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
//    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
//
//
//    assert(evaluate("8||2", ba, pf, answer) == 1);
//    assert(evaluate("82|2", ba, pf, answer) == 1);
//    assert(evaluate("8|&2", ba, pf, answer) == 1);
//    assert(evaluate("8|(2)", ba, pf, answer) == 0 && pf == "82|" && answer);
//    assert(evaluate("8|         5", ba, pf, answer) == 0 && pf == "85|" && answer);
//    assert(evaluate("(8) | (9)", ba, pf, answer) == 0);
//
//    cout << "Passed all tests" << endl;
//}
//
