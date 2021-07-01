#include"LexicalAnalyzer.hpp"

int curPointer=0;//当前记号指针

struct AnalyzeTree{     // 语法树的结点结构
    int Token=-1; // 存记号
    string content="";// 存记号的内容，针对的是变量及常量
    struct AnalyzeTree *child=NULL,*brother=NULL; 
} *R,*P; 

int GetCurToken(){
    int token =id[curPointer];
    if(token==7||token==8)return 21;
    return token;
}

string GetCurContent(){
    return word[curPointer];
}

int match(int mark){
    if(GetCurToken()==mark){
        curPointer++;
        return 0;
    }
    else {
        cout<<"Match error on character"<<curPointer<<endl;
        return -2;//-2为匹配错误
    }
    
}

int A();int B();int C();int D();int E();int F();int G();int H();int I();int J();

int S(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 10: 
        case 20:
            cout<<"pop(S),push(A?B;)"<<endl;
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 102; 
            temp->content=GetCurContent();
            P->child = temp;
            P=q=temp; 
            if((errCode=A())<0)return errCode;
            temp = new AnalyzeTree; 
            temp->Token =10;  
            temp->content=GetCurContent();                    
            q->brother = temp;       
            q=temp; 
            cout<<"pop(?)"<<endl;
            if((errCode=match(10))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 103; 
            temp->content=GetCurContent();
            P->child = temp;
            P=q=temp;
            if((errCode=B())<0)return errCode;
            temp = new AnalyzeTree; 
            temp->Token =11;  
            temp->content=GetCurContent();                    
            q->brother = temp;       
            cout<<"pop(;)"<<endl;
            if((errCode=match(11))<10)return errCode; 
            break;
        case 9:
            cout<<"pop(S),push($)"<<endl;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
    
}

int A(){// 当栈顶非终结符为 A的时候 
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 20: 
            cout<<"pop(A),push(C;A)"<<endl;
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 104; 
            temp->content=GetCurContent();
            P->child = temp;
            P=q=temp;
            if((errCode=C())<0)return errCode;
            temp = new AnalyzeTree; 
            temp->content=GetCurContent();
            temp->Token =11;  
            temp->content=GetCurContent();                    
            q->brother = temp;       
            q = temp; 
            cout<<"pop(?)"<<endl;
            if((errCode=match(11))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 102; 
            temp->content=GetCurContent();
            q->brother = temp; 
            P=temp; 
            if((errCode=A())<0)return errCode;
            break;
        case 10:
            cout<<"pop(A)"<<endl;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;

}

int B(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 13:
        case 18:
        case 20:
        case 21:
            cout<<"pop(B),push(DE)"<<endl; 
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 105; 
            temp->content=GetCurContent();
            P->child = temp;
            P=q=temp;
            if((errCode=D())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 106; 
            temp->content=GetCurContent();
            q->brother = temp;
            P=temp; 
            if((errCode=E())<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int C(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 20: 
            cout<<"pop(C),push(变量=B)"<<endl;
            temp = new AnalyzeTree;
            temp->Token=20; 
            temp->content=GetCurContent();
            P->child = temp;
            q=temp; 
            cout<<"pop(?)"<<endl;
            if((errCode=match(20))<0)return errCode;
            temp = new AnalyzeTree; 
            temp->Token =16;     
            temp->content=GetCurContent();                 
            q->brother = temp;       
            q = temp; 
            cout<<"pop(?)"<<endl;
            if((errCode=match(16))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 103; 
            temp->content=GetCurContent();
            P=temp; 
            if((errCode=B())<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int D(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 13:
        case 18:
        case 20:
        case 21:
            cout<<"pop(D),push(FG)"<<endl; 
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 107; 
            P->child = temp;
            temp->content=GetCurContent();
            P=q=temp;
            if((errCode=F())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 108; 
            temp->content=GetCurContent();
            q->brother = temp;
            P=temp; 
            if((errCode=G())<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int E(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 12:
            cout<<"pop(E),push(+DE)"<<endl; 
            temp = new AnalyzeTree;
            temp->Token = 12;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(+)"<<endl;
            if((errCode=match(12))<0)return errCode;
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 105; 
            temp->content=GetCurContent();
            q->brother=temp;
            P=q=temp;
            if((errCode=D())<0)return errCode; 
            temp = new AnalyzeTree;
            temp->Token = 106; 
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=E())<0)return errCode;
            break;
        case 13:
            cout<<"pop(E),push(-DE)"<<endl; 
            temp = new AnalyzeTree;
            temp->Token = 13;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(-)"<<endl;
            if((errCode=match(13))<0)return errCode;
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 105;
            temp->content=GetCurContent(); 
            q->brother=temp;
            P=q=temp;
            if((errCode=D())<0)return errCode; 
            temp = new AnalyzeTree;
            temp->Token = 106; 
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=E())<0)return errCode;
            break;  
        case 11:
        case 19:
            cout<<"pop(E)"<<endl;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int F(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
            int key;
            switch (ch){
            case 0:
                cout<<"pop(F),push(sin(H))"<<endl;
                key=0;
                break;
            case 1:
                cout<<"pop(F),push(cos(H))"<<endl;
                key=1;
                break;
            case 2:
                cout<<"pop(F),push(tg(H))"<<endl;
                key=2;
                break;
            case 3:
                cout<<"pop(F),push(ctg(H))"<<endl;
                key=3;
                break;
            case 5:
                cout<<"pop(F),push(lg(H))"<<endl;
                key=5;
                break;
            case 6:
                cout<<"pop(F),push(ln(H))"<<endl;
                key=6;
                break;
            default:
                break;
            }
            temp = new AnalyzeTree;
            temp->Token = key;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            switch (ch){
            case 0:
                cout<<"pop(sin)"<<endl;
                break;
            case 1:
                cout<<"pop(cos)"<<endl;
                break;
            case 2:
                cout<<"pop(tg)"<<endl;
                break;
            case 3:
                cout<<"pop(ctg)"<<endl;
                break;
            case 5:
                cout<<"pop(lg)"<<endl;
                break;
            case 6:
                cout<<"pop(ln)"<<endl;
                break;
            default:
                break;
            }
            if((errCode=match(key))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 18;
            temp->content=GetCurContent();
            q->brother=temp;
            q = temp;
            cout<<"pop(()"<<endl;
            if((errCode=match(18))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 109;
            temp->content=GetCurContent();
            q->brother=temp;
            P = q = temp;
            if((errCode=H())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 19;
            temp->content=GetCurContent();
            q->brother=temp;
            q = temp;
            cout<<"pop())"<<endl;
            if((errCode=match(19))<0)return errCode;
            break;
        case 4:
            cout<<"pop(F),push(log(HJ)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 4;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(log)"<<endl;
            if((errCode=match(4))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 18;
            temp->content=GetCurContent();
            q->brother=temp;
            q = temp;
            cout<<"pop())"<<endl;
            if((errCode=match(18))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 109;
            temp->content=GetCurContent();
            q->brother=temp;
            P = q = temp;
            if((errCode=H())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 19;
            temp->content=GetCurContent();
            q->brother=temp;
            P=temp;
            if((errCode=J())<0)return errCode;
            break;
        case 13:
        case 18:
        case 20:
        case 21:
            cout<<"pop(F),push(HI)"<<endl; 
            temp = new AnalyzeTree;//构造语法树
            temp->Token = 109; 
            temp->content=GetCurContent();
            P->child = temp;
            temp->content=GetCurContent();
            P=q=temp;
            if((errCode=H())<0)return errCode; 
            temp = new AnalyzeTree;
            temp->Token = 110; 
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=I())<0)return errCode;
            break; 
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int G(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 11:
        case 12:
        case 13:
        case 19:
            cout<<"pop(G)"<<endl;
            break;
        case 14:
            cout<<"pop(G),push(*FG)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 14;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(*)"<<endl;
            if((errCode=match(14))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 107;
            temp->content=GetCurContent();
            q->brother=temp;
            P=q=temp;
            if((errCode=F())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 14;
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=G())<0)return errCode;
            break;
        case 15:
            cout<<"pop(G),push(/FG)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 15;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(*)"<<endl;
            if((errCode=match(15))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 107;
            temp->content=GetCurContent();
            q->brother=temp;
            P=q=temp;
            if((errCode=F())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 14;
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=G())<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
}

int H(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 20:
            cout<<"pop(H),push(变量)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 20;
            temp->content=GetCurContent();
            P->child=temp;
            cout<<"pop(变量)"<<endl;
            if((errCode=match(20))<0)return errCode;
            break;
        case 21:
            cout<<"pop(H),push(实数)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 21;
            temp->content=GetCurContent();
            P->child=temp;
            cout<<"pop(实数)"<<endl;
            if((errCode=match(21))<0)return errCode;
            break;
        case 13:
            cout<<"pop(H),push(-H)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 13;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(-)"<<endl;
            if((errCode=match(13))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 109;
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=H())<0)return errCode;
            break;
        case 18:
            cout<<"pop(H),push((B))"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 18;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(()"<<endl;
            if((errCode=match(18))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 103;
            temp->content=GetCurContent();
            q->brother=temp;
            P = q = temp;
            if((errCode=B())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 19;
            temp->content=GetCurContent();
            q->brother= temp;
            cout<<"pop()"<<endl;
            if((errCode=match(19))<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int I(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 17:
            cout<<"pop(I),push(^H)"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 17;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(^)"<<endl;
            if((errCode=match(17))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 109;
            temp->content=GetCurContent();
            q->brother=temp;
            P = temp;
            if((errCode=H())<0)return errCode;
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 19:
            cout<<"pop(I)"<<endl;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;
    }
    return errCode;
}

int J(){
    int ch=GetCurToken();
    int errCode=0;
    struct AnalyzeTree *temp,*q;
    switch (ch){
        case 22:
            cout<<"pop(J),push(,H))"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 22;
            temp->content=GetCurContent();
            P->child=temp;
            q = temp;
            cout<<"pop(^)"<<endl;
            if((errCode=match(22))<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 109;
            temp->content=GetCurContent();
            q->brother=temp;
            P = q = temp;
            if((errCode=H())<0)return errCode;
            temp = new AnalyzeTree;
            temp->Token = 19;
            temp->content=GetCurContent();
            q->brother=temp;
            cout<<"pop())"<<endl;
            if((errCode=match(19))<0)return errCode;
            break;
        case 19:
            cout<<"pop(J),push())"<<endl;
            temp = new AnalyzeTree;
            temp->Token = 19;
            temp->content=GetCurContent();
            P->child=temp;
            cout<<"pop())"<<endl;
            if((errCode=match(19))<0)return errCode;
            break;
        default:
            cout<<"Input error on character "<<curPointer<<endl;
            return -1;//-1为字符输入错误
            break;       
    }
    return errCode;
}

// int main(){
//     R = new AnalyzeTree;//初始化S语法树
//     R->Token = 101;
//     R->content="";
//     R->child = NULL;
//     R->brother = NULL; 
//     P=R; //P指向当前非终结符
//     system("chcp 65001");
//     cout<<"请将输入写在当前目录的“in.txt”中"<<endl;
//     readfile("in.txt");
//     cout<<buffer<<endl;
//     string str(buffer);
//     cout<<"当前输入字符个数:  "<<str.length()<<endl;
//     cout<<"--------词法分析--------"<<endl;
//     analyse();
//     print();
//     cout<<"------词法分析完成------"<<endl<<endl;;
//     cout<<"--------语法分析--------"<<endl;
//     cout<<"push($S)"<<endl;
//     int errCode=S();
//     if((errCode)==0){
//         cout<<"------语法分析完成------"<<endl;
//         system("pause");
//         return 0;
//     }
//     else return -1;  
// }