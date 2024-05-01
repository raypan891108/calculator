#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

vector <Variable> Variables;

//資料前處理
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

struct Variable {
    string type;
    string name;
    string value;
};

void function2(string line){
    istringstream iss(line);
    string s;
    while(iss >> s){
        if(s == "int" || s == "float"){
            string type = s;
            while (iss >> s ) {
                cout<<type<<":"<<s<<endl;
                if(s != ";"){
                    Variable v = {type,s,""};
                    Variables.push_back(v);
                }
                
            }
        }else{
            
        }
    }
}


int main(){
    ifstream file("Q1.txt");

    if (!file.is_open()) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    string line;
    int lineNumber = 1;

    while (getline(file, line)) {
        cout << "Line " << lineNumber << ": " << replace(line) << endl;
        function2(replace(line));
        ++lineNumber;
    }

    file.close();

    return 0;
}
