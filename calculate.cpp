#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstring>
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

struct Variable {
    string type;
    string name;
    string value;
};

vector <Variable> Variables;
vector <Variable> ans;
//前處理
// , -> ", "
// ; -> end of string
string replace(string str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if(str[i] == ';'){
            break;
        }
        if (str[i] == ',' && str[i - 1] != ' ') {
            result += " ";
        }
        if (str[i] == ',' && i + 1 < str.size() && str[i + 1] != ' ') {
            result += ", ";
        } else {
            result += str[i];
        }
    }
    return result;
}

float StringToFlaot(char n){
    for(Variable v : ans){
        if(v.name[0] == n){
           return stof(v.value);
        }
    }
}

const vector<string> split(const string& str, const string& pattern) {
    vector<string> result;
    string::size_type begin, end;

    end = str.find(pattern);
    begin = 0;

    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end-begin)); 
        }    
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }

    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;        
}
void preProcessing(string str){
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ' ){
            result += "";
        } else {
            result += str[i];
        }
    }
    string delimiter = "=";
    vector<string> ret = split(str, delimiter);
   
    bool answer = calculate(ret[1]);
    operate2();
    if(Operator.size() != 0 || answer != true){
        cout<<"Error "<<endl;
    }else{
        for(int i =0; i < ans.size(); i++){
            if(ans[i].name[0] == ret[0][0]){
                if(ans[i].type == "int"){
                    ans.at(i).value = to_string((int)Value.top());
                }else if(ans[i].type == "float"){
                    float val = roundf(Value.top() * 1000.0) / 1000.0;
                    stringstream ss;
                    ss << fixed << setprecision(3) << val;
                    ans.at(i).value = ss.str();
                }

                Value = stack<float>();
                Operator = stack<char>();
                debt = stack<char>();
                break;
            }
        }
    }

}

string replaceEqual(string str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if(str[i] == ';'){
            break;
        }
        if (str[i] == '=' && str[i - 1] != ' ') {
            result += " ";
        }
        if (str[i] == '=' && i + 1 < str.size() && str[i + 1] != ' ') {
            result += "= ";
        } else {
            result += str[i];
        }
    }
    return result;
}




void function2(string line){
    istringstream iss(line);
    string s;
    while(iss >> s){
        if(s == "int" || s == "float"){
            string type = s;
            while (iss >> s ) {
                if(s != ","){
                    string vValue = "0.000";
                    if(s == "int"){
                        vValue = "0";
                    }
                    Variable v = {type,s,"0.000"};
                    ans.push_back(v);
                }
                
            }
        }else{
            preProcessing(line);
            break;
        }
    }
}


//計算模式二之情境
void calculate2(string inputfile, string outputfile){
    ifstream file(inputfile);
    ofstream out; // 建立輸出串流物件
    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
    }
    string line;

    while (getline(file, line)) {
        line = replace(line);
        line = replaceEqual(line);
        function2(line);
    }
    string a="(",b="(";
     for(int i=0;i<ans.size();i++){
        a += ans[i].name + ", ";
        b += ans[i].value + ", ";
    }
    a = a.substr(0, a.size() - 2) + ")";
    b = b.substr(0, b.size() - 2) + ")";
    cout << a << "=" << b;
    
    
    out.open(outputfile); // 開啟即將被寫入資料的檔案
    if(out.fail()){ //確認是否開啟成功
        cout << "input file opening failed...";
        exit(1);
    }
    
    out << a << "=" << b; // 將兩個字串寫入

    file.close();
}

//判斷answer == integer
bool integer(float k)
{
    if( k == (int) k) return true;
    return false;
}


// 計算模式一之情境
bool calculate(string s){
    bool isempty = true;           // 判斷正負數
    int  i=0;
    try{
        while(i<s.length()){
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
                        }else if (s[i+1] == ' ') {
                            Value.push(StringToFlaot(c));
                            break;
                        }
                    case 'c':
                        if(s.substr(i, 3) == "cos"){
                            Operator.push('2');
                        }else if(s.substr(i, 3) == "cot"){
                            Operator.push('4');
                        }else if(s.substr(i, 3) == "csc"){
                            Operator.push('6');
                        }else if (s[i+1] == ' ') {
                            Value.push(StringToFlaot(c));
                            break;
                        }
                    
                    case 's':
                        if(s.substr(i, 3) == "sin"){
                            Operator.push('1');
                        }else if(s.substr(i, 3) == "sec"){
                            Operator.push('5');
                        }else if (s[i+1] == ' ') {
                            Value.push(StringToFlaot(c));
                            break;
                        }
                        
                    case 'l':
                        if(s.substr(i, 3) == "log"){
                            Operator.push('l');
                        }else if (s[i+1] == ' ') {
                            Value.push(StringToFlaot(c));
                            break;
                        }
                       
                    case 'e':
                        if(s.substr(i, 3) == "exp"){
                            Operator.push('e');
                        }else if (s[i+1] == ' ') {
                            Value.push(StringToFlaot(c));
                            break;
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
                        if(int(c)>= 97 && int(c)<=122){
                            Value.push(StringToFlaot(c));
                            break;
                        }
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

    Value.push(value);
    return i;
}

//multiplication
float multipy(float num1, float num2){
    num1 = num1 * num2;
    return num1;
}

float add(float num1, float num2){
    num1 = num1 + num2;
    return num1;
}


float sub(float num1, float num2){
    num1 = num2 - num1;
    return num1;
}

float div(float num1, float num2){
    num1 = num2 / num1;
    return num1;
}

float power(float num1, float num2){
    num1 = pow(num2, num1);
    return num1;
}

float MathFunction(char c, float num1){
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
    return num1;
}

void operate2(){
    while(Operator.size() != 0){
        char opr = Operator.top();

        if(isdigit(int(opr)) || opr == 'e' || opr =='l'){
                float num1 = Value.top();
                Value.pop();
                Value.push(MathFunction(opr, num1));
                Operator.pop();
        }else{
            if(Value.size() == 1){
                break;
            }
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



int main(){
    string choose;
    cout<<"Choose your mode:";
    getline(cin,choose);
    string s;
    if(choose == "direct"){
        getline(cin,s);
        // 移除字符串中的空格
        // s.erase(remove_if(s.begin(), s.end(), [](unsigned char x){return isspace(x);}), s.end());
        bool answer = calculate(s);
        operate2();
        if(Operator.size() != 0 || answer != true){
            cout<<"Error "<<endl;
        }else{
            if(!integer(answer)){
                 cout<<"Answer is ";
                cout<< setprecision(0) << Value.top()<< endl;
            }else{
                // printf("Answer is %.4f", Value.top());
                cout<<"Answer is ";
                cout<< setprecision(4) << Value.top()<< endl;
            }
        }
    }else if(choose == "file"){
        cout<<"Input file name:";
        getline(cin,s);

        string outputfile;
        cout<<"Output file name:";
        getline(cin,outputfile);
        calculate2(s, outputfile);

    }
    return 0;
}
