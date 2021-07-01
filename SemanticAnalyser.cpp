#include"GrammerParser.hpp"
#include<stack>
#include<cmath>
#include <sstream>



template <class Type>  
Type stringToNum(const string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  

void visit(AnalyzeTree* pt, stack<string>& mystack){
    //cout<<mystack.size()<<endl;
    switch (pt->Token)
    {
    case 9: case 11: case 18: case 19: case 22: case 101: case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111:
        break;
    case 20: case 21:
        if(pt->content=="PI"){
            mystack.push("3.1415");
            break;
        }
        if(pt->content=="E"){
            mystack.push("2.7183");
            break;
        }
        mystack.push(pt->content);
        break;
    case 0:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = sin(x);
        mystack.push(to_string(x));
        break;  
    } 
    case 1:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = cos(x);
        mystack.push(to_string(x));
        break;  
    }
    case 2:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = tan(x);
        mystack.push(to_string(x));  
        break; 
    }   
    case 3:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = 1/tan(x);
        mystack.push(to_string(x));  
        break; 
    }
    case 4:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = log(y)/log(x);
        mystack.push(to_string(x)); 
        break;
    }
    case 5:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = log10(x);
        mystack.push(to_string(x)); 
        break;
    }
    case 6:
    {
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = log(x);
        mystack.push(to_string(x)); 
        break;
    }
    case 10:
    {
        cout<<mystack.top();
        break;
    }
    case 12:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = x + y;
        mystack.push(to_string(x));
        break;
    }
    case 13:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = x - y;
        mystack.push(to_string(x));
        break;
    }
    case 14:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = x * y;
        mystack.push(to_string(x));
        break;
    }
    case 15:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = x / y;
        mystack.push(to_string(x));
        break;
    }
    case 16:
    {
        
        string xx = mystack.top();
        mystack.pop();
        mystack.pop();
        mystack.push(xx);
        break;
    }
    case 17:
    {
        float y = stringToNum<float>(mystack.top());
        mystack.pop();
        float x = stringToNum<float>(mystack.top());
        mystack.pop();
        x = pow(x,y);
        mystack.push(to_string(x));
        break; 
    }      
    default:
        break;
    }
}

void postOder(AnalyzeTree* pt,stack<string>& mystack){
    AnalyzeTree *c;
    cout<<102<<endl;
    return;
    if(pt==NULL)return;

    postOder(c,mystack); 
    postOder(c,mystack);      
    visit(pt,mystack);         
    
    
}

int main(){
    R = new AnalyzeTree;//初始化S语法树
    R->Token = 101;
    R->content="";
    R->child = NULL;
    R->brother = NULL; 
    P=R; //P指向当前非终结符
    system("chcp 65001");
    cout<<"请将输入写在当前目录的“in.txt”中"<<endl;
    readfile("in.txt");
    cout<<buffer<<endl;
    string str(buffer);
    cout<<"当前输入字符个数:  "<<str.length()<<endl;
    cout<<"--------词法分析--------"<<endl;
    analyse();
    print();
    cout<<"------词法分析完成------"<<endl<<endl;;
    cout<<"--------语法分析--------"<<endl;
    cout<<"push($S)"<<endl;
    int errCode=S();
    if((errCode)==0){
        cout<<"------语法分析完成------"<<endl;
        
    }
    cout<<"--------语义分析--------"<<endl;
    stack<string> mystack;
    postOder(R,mystack);
    //float x = stringToNum<float>(mystack.top());
    //cout<<mystack.size()<<endl;
    cout<<"--------语义分析完成--------"<<endl;
    system("pause");
    return 0;
}