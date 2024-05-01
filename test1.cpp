#include <iostream>
#include <stack>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;



stack<char> Operator;
stack<float> Value;
stack<char>  debt;

bool calculate(string s); // Function declaration
void operate(); // Function declaration
void operate2();
void operate3(int n); // Function declaration
int SearchValue(int i, string s, char opr); // Function declaration

float MathFunction(char c, float num1); //
float power(float num1, float num2);
float div(float num1, float num2);
float multipy(float num1, float num2);
float sub(float num1, float num2);
float add(float num1, float num2);

bool integer(float k);

int main(){
    string choose;
    cout<<"Choose your mode:";
    getline(cin,choose);
    if(choose == "direct"){
        string s;
        getline(cin,s);
        // 移除字符串中的空格
        s.erase(remove_if(s.begin(), s.end(), [](unsigned char x){return isspace(x);}), s.end());
        bool answer = calculate(s);
        operate2();
        if(Operator.size() != 0 || answer != true){
            cout<<"Error "<<endl;
        }else{
            if(!integer(answer)){
                printf("Answer is %.0f", Value.top());
            }else{
                printf("Answer is %.4f", Value.top());
            }
        }
    }else if(choose == "file"){

    }
    return 0;
}

//判斷answer == integer
bool integer(float k)
{
    cout<<k<<endl;
    if( k == (int) k) return true;
    return false;
}


// 計算模式一之情境
bool calculate(string s){
    bool isempty = true;           // 判斷正負數
    int  i=0;
    try{
        while(i<s.length()){
            // cout<<i<<endl;
            //error check
            if(i == -1){
                return false;
            }
            char c = s[i];
            // Value
            if(isdigit(int(c))){
               i = SearchValue(i, s, '+') - 1;
               isempty = false;
            }else{
                //Operator Switch
                switch (c){
                    case 't':
                        if(s.substr(i, 3) == "tan"){
                            Operator.push('3');
                        }
                        i+=2;
                        break;
                    case 'c':
                        if(s.substr(i, 3) == "cos"){
                            Operator.push('2');
                        }else if(s.substr(i, 3) == "cot"){
                            Operator.push('4');
                        }else if(s.substr(i, 3) == "csc"){
                            Operator.push('6');
                        }
                        i+=2;
                        break;
                    case 's':
                        if(s.substr(i, 3) == "sin"){
                            Operator.push('1');
                        }else if(s.substr(i, 3) == "sec"){
                            Operator.push('5');
                        }
                        i+=2;
                        break;
                    case 'l':
                        if(s.substr(i, 3) == "log"){
                            Operator.push('l');
                        }else{
                            return false;
                        }
                        i+=2;
                        break;
                    case 'e':
                        if(s.substr(i, 3) == "exp"){
                            Operator.push('e');
                        }else{
                            return false;
                        }
                        i+=2;
                        break;
                    case '-':
                        //判斷負數
                        if(isempty == true){
                            i = SearchValue(i+1, s, '-') - 1;
                            isempty = false;
                            break;
                        }
                    case '+':
                        //  todo 加一個判斷
                        operate3(3);
                        Operator.push(c);
                        break;
                    case '/':
                    case '*':
                        //  todo 加一個判斷
                        operate3(2);
                    case '^':
                        Operator.push(c);
                        break;
                    case '.':
                        break;
                    case '(':
                        Operator.push(c);
                        isempty = true;
                        break;
                    case ')':
                        operate();
                        break;
                    default:
                        break;
                }
                
            }
            i++;
        }
    }catch( exception& e ){
        cout << "Error: " << e.what() << endl;
    }
    return true;
}
// MathFunction > (*, /, ^) > (+, -)
void operate3(int n){
    while(Operator.size() > 0){
        cout<<"Operator3:"<<n <<"  "<<Operator.top()<<endl;
        char oper = Operator.top();
        if(n == 2 || n == 3){
            if(oper == 'e' || oper == 'l' || isdigit(int(oper))){
                float value = Value.top();
                value = MathFunction(oper, value);
                Value.pop();
                Operator.pop();
                Value.push(value);
                continue;
            }else if(oper == '*'){
                float num1 = Value.top();
                Value.pop();
                float num2 = Value.top();
                Value.pop();
                Value.push(multipy(num1, num2));
                Operator.pop();
                continue;
            }else if(oper == '/'){
                float num1 = Value.top();
                Value.pop();
                float num2 = Value.top();
                Value.pop();
                Value.push(div(num1, num2));
                Operator.pop();    
                continue; 
            }else if(oper == '^'){
                float num1 = Value.top();
                Value.pop();
                float num2 = Value.top();
                Value.pop();
                Value.push(power(num1, num2));
                Operator.pop();  
                continue;   
            }else if(n == 2){
                break;
            }
        }
        if (n == 3){
            if(oper == '-'){
                float num1 = Value.top();
                Value.pop();
                float num2 = Value.top();
                Value.pop();
                Value.push(sub(num1, num2));
                Operator.pop();   
                continue;  
            }else{
                break;
            }
        }

    }
}

int SearchValue(int i, string s, char opr){
    cout<<"SearchValue"<< endl;
    bool tmp = true;
    float value = 0;
    int decimal = 1;
    while(i<s.length() && (isdigit(int(s[i])) || s[i]=='.')){
        if(s[i]=='.'){
            tmp = false;
        }else{
            if(tmp == true){
                value = value * 10 + (s[i] - '0');
            }else{
                value = value + (s[i] - '0') * pow(0.1, (decimal++));
            }
        }
        i++;
    }
    if(opr == '-'){
        value = value * -1;
    }
    cout<<value<<endl;
    Value.push(value);
    return i;
}

//multiplication
float multipy(float num1, float num2){
    cout<< num1 << " * " << num2 << "=";
    num1 = num1 * num2;
    cout<<num1<<endl;
    return num1;
}

float add(float num1, float num2){
    cout<< num1<<" + "<<num2<<"=";
    num1 = num1 + num2;
    cout<<num1<<endl;
    return num1;
}


float sub(float num1, float num2){
    cout<< num2<<" - "<<num1<<"=";
    num1 = num2 - num1;
    cout<<num1<<endl;
    return num1;
}

float div(float num1, float num2){
    cout<< num2<<" / "<<num1<<"=";
    num1 = num2 / num1;
    cout<<num1<<endl;
    return num1;
}

float power(float num1, float num2){
    cout<< num2<<" ^ "<<num1<<"=";
    num1 = pow(num2, num1);
    cout<<num1<<endl;
    return num1;
}

float MathFunction(char c, float num1){
    cout<< c<<"=";
    switch (c){
        case '1':
            num1 = sin(num1 * M_PI / 180);
            break;
        case '2':
            num1 = (num1 == 90)?0:cos(num1 * M_PI / 180);
            break;
        case '3':
            num1 = tan(num1 * M_PI / 180);
            break;
        case '6':
            num1 = asin(num1);
            break;
        case '5':
            num1 = acos(num1);
            break;
        case '4':
            num1 = atan(num1);
            break;
        case 'e':
            num1 = exp(num1);
            break;
        case 'l':
            num1 = log10(num1);
            break;
        default:
            break;
    }
    cout<<num1<<endl;
    return num1;
}

void operate2(){
    cout<<"operate2"<<endl;
    while(Operator.size() != 0){
        char opr = Operator.top();
        cout<<opr<<endl;

        if(isdigit(int(opr)) || opr == 'e' || opr =='l'){
                float num1 = Value.top();
                Value.pop();
                Value.push(MathFunction(opr, num1));
                Operator.pop();
        }else{
            if(Value.size() == 1){
                break;
            }
            // cout<<opr<<endl;
            float num1 = Value.top();
            Value.pop();
            float num2 = Value.top();
            Value.pop();
            switch (opr){
                case '+':
                    Value.push(add(num1, num2));
                    break;
                case '-':
                    Value.push(sub(num1, num2));
                    break;
                case '*':
                    Value.push(multipy(num1, num2));
                    break;
                case '/':
                    Value.push(div(num1, num2));
                    break;
                case '^':
                    Value.push(power(num1, num2));
                    break;
                default:
                    break;
            }
            Operator.pop();
        }
    }
}

void operate(){
    cout<<"Operating"<<endl;
    char opr = Operator.top();
    Operator.pop();
    while(opr != '(' ){
        if(isdigit(int(opr)) || opr == 'e' || opr =='l'){
            float num1 = Value.top();
            Value.pop();
            Value.push(MathFunction(opr, num1));
        }else{
            float num1 = Value.top();
            Value.pop();
            float num2 = Value.top();
            Value.pop();
            switch (opr){
                case '+':
                    Value.push(add(num1, num2));
                    break;
                case '-':
                    Value.push(sub(num1, num2));
                    break;
                case '*':
                    Value.push(multipy(num1, num2));
                    break;
                case '/':
                    Value.push(div(num1, num2));
                    break;
                case '^':
                    Value.push(pow(num1, num2));
                    break;
                default:
                    break;
            }
        }
        if(Operator.size()!= 0){
            opr = Operator.top();
            Operator.pop();
        }
    }
}
