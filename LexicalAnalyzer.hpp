#include<iostream>
#include<string>
#include<fstream>
using namespace std;

string keyword[] = {"sin","cos","tg","ctg","log","lg","ln","PI","E"};//定义关键字
char buffer[1000];//字符缓存
int id[100];//记号流缓存
string word[100];//单词缓存
int num = 0;//已识别单词个数

//判断是否是关键字,并返回相应序号（非记号)
int isKey(string& c){
    for(int i=0;i<sizeof(keyword)/sizeof(keyword[0]);i++){
        if(c==keyword[i]){
            return i;
        }
    }
    return -1;
}
//判断是否是单个数字
bool isNumber(char& c){
    if('0'<=c&&c<='9'){
        return true;
    }
    else{
        return false;
    }
}

//判断是否是字符
bool isChar(char& c){
    if('a'<=c&&c<='z'||'A'<=c&&c<='Z'||c=='_'){
        return true;
    }
    else{
        return false;
    }
    
}

//判断是否是操作符，并返回相应记号，否则返回-1
int isOperator(char& c){
    switch (c){
    case '?': return 10;
    case ';': return 11;
    case '+': return 12;
    case '-': return 13;
    case '*': return 14;
    case '/': return 15;
    case '=': return 16;
    case '^': return 17;
    case '(': return 18;
    case ')': return 19;
    case ',': return 22;
    default:  return -1;
    }
}

//判断是否是分隔符
bool isBlank(char& c){
    switch (c)
    {
    case ' ':
    case '\n':
    case '\t': return true; 
    default: return false;
    }
}

//从文件中读取字符并存入缓存
void readfile(string filename){
    ifstream fin(filename);
    int i = 0;
    if (!fin)//检测文件输入是否正常
    {
        cout << "文件不能打开" << endl;
    }
    else{
        try{
            while (fin >> buffer[i]){i++;}
        }
        catch(exception e){
            cout << "loading error" << endl;
            return;
        }
        cout <<"Successfully load code"<< endl;
    }
    fin.close();
    return;
}


string getWord(int& sp,int& ep){
    char s [ep-sp+1];
    for(int i=0;sp<=ep;i++){
        s[i]=buffer[sp++];
    }
    ep++;
    string str(s);
    return str;
}

void addWord(string s,int t){
    int i = isKey(s);
    if(i>=0){
        s = keyword[i];
        t=i;
    }
    word[num] = s;
    id[num] = t;
    num++;
    return;
}

//识别分析函数
void analyse(){
    int starP = 0;
    int endP = 0;
    int curState = 0;//当前状态
    //int curId = NULL;//当前单词记号
    char curChar;//当前字符
    int t;
    while(true){
        switch (curState){
        case 0://初始状态
            curChar=buffer[endP];
            if(curChar=='$'){
                addWord("$",9);
                return;
            }
            t=isOperator(curChar);
            if(t>0){
                string s;s = curChar;
                addWord(s,t);
                curState=0;
                break;
            }
            if(curChar=='0'){
                curState=2;
                endP++;
                continue;                    
            }
            if(isChar(curChar)){
                curState=1;
                endP++;
                continue;
            }
            if(isNumber(curChar)){
                curState=3;
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" << endl;//输入的不是本语言支持的字符
                return;
            }
            
        case 1://识别标识符
            curChar=buffer[endP];
            if(curChar=='$'){
                string s = getWord(starP,--endP);
                addWord(s,20);
                addWord("$",9);
                return;
            }
            t = isOperator(curChar);
            if(t>0){
                string s = getWord(starP,--endP);
                addWord(s,20);
                s = curChar;
                addWord(s,t);
                curState=0;               
                break;
            }
            if(isChar(curChar)||isNumber(curChar)){
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" <<endl;
                return;
            }
            
        case 2:
            curChar=buffer[endP];
            if(curChar=='$'){
                string s = getWord(starP,--endP);
                addWord(s,21);
                addWord("$",9);
                return;
            }
            t = isOperator(curChar);
            if(t>0){
                string s = getWord(starP,--endP);
                addWord(s,20);
                s = curChar;
                addWord(s,t);                
                curState=0;
                break;
            }
            if(curChar=='.'){
                curState=4;
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" <<endl;
                return;
            }
        case 3:
            curChar=buffer[endP];
            if(curChar=='$'){
                string s = getWord(starP,--endP);
                addWord(s,21);
                addWord("$",9);
                return;
            }
            t = isOperator(curChar);
            if(t>0){
                string s = getWord(starP,--endP);
                addWord(s,20);
                s = curChar;
                addWord(s,t);
                curState=0;
                break;
            }
            if(isNumber(curChar)){
                endP++;
                continue;
            }
            if(curChar=='.'){
                curState = 4;
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" <<endl;
                return;
            }

        case 4:
            curChar=buffer[endP];
            if(curChar=='$'){
                cout << "error identifier when finished"<<endl;
            }
            t = isOperator(curChar);
            if(t>0){
                string s = getWord(starP,--endP);
                addWord(s,20);
                s = curChar;
                addWord(s,t);
                curState=0;
                break;
            }
            if(curChar=='0'){
                endP++;
                continue;
            }
            if(isNumber(curChar)){
                curState = 5;
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" <<endl;
                return;
            }
        case 5:
            curChar=buffer[endP];
            if(curChar=='$'){
                string s = getWord(starP,--endP);
                addWord(s,21);
                addWord("$",9);
                return;
            }
            t = isOperator(curChar);
            if(t>0){
                string s = getWord(starP,--endP);
                addWord(s,20);
                s = curChar;
                addWord(s,t);
                curState=0;
                break;
            }
            if(curChar=='0'){
                curState = 4;
                endP++;
                continue;
            }
            if(isNumber(curChar)){
                endP++;
                continue;
            }
            else{
                cout << "not allowed identifier" <<endl;
                return;
            }
        default:
            cout << "state error"<<endl;
        }
        if(curState==0){
            starP=++endP; //得到一个单词后，重置单词边界指针  
        }
    }
}

//打印记号流
void print(){
    int i;
    for(i=0;id[i]!=9;i++){
        cout<<'<'<<i+1<<','<<word[i]<<','<<id[i]<<'>'<<endl;
    }
    cout<<"当前输入单词数："<<i<<endl;
}

//输出记号流
// void dump(){
//     ofstream mycout("out.txt");
//     for(int i=0;id[i]!=9;i++){
//         mycout<<id[i]<<endl;
//     }
//     mycout.close();
//     return;
    
// }

//主函数
// int main(){
//     system("chcp 65001");
//     cout<<"请将输入写在当前目录的“in.txt”中"<<endl;
//     readfile("in.txt");
//     cout<<buffer<<endl;
//     string str(buffer);
//     cout<<"当前输入字符个数:  "<<str.length()<<endl;
//     analyse();
//     print();
//     // dump();
//     system("pause");
//     return 0;
// }