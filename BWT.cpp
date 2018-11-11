#include <iostream>
#include<fstream>
#include<string.h>
#include<map>
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
#define N 10000
using namespace std;
char Refer[N]; // refenence 总串
char BWT[N];
map<char,int>C;
map<string,int>M; 
char SubQue[N]; // subquence 子串
char BWTMatrix[N][N];
char T[N];
string S[N];
void buildc(){ // 构造C[c] 字典序小于c的所有字符个数
    for(int i=0;i<strlen(Refer);i++){
        char c=BWT[i];
        if(c!='$'){
            if(C.find(c)==C.end()){
                int k=0;
                for(unsigned int j=0;j<strlen(Refer);j++){
                    if(BWT[j]<c&&BWT[j]!='$') k++; 
                    }
                C[c]=k;
            }
        }    
    }
}

int Occ(char a,int b){
    if(b==0){
        return 0;
    }
    else{
    int k=0;
    for(int i=0;i<b;i++){
        if(BWT[i]==a) k++;
    }
    return k;}
}
void loopMove(char *ch, int steps)
 {
    char temp[N];
    char*p;
    int n = strlen(ch) - steps;
    p = ch + n;
    memcpy(temp, p, steps);
    memcpy(temp + steps, ch, n);
    memcpy(ch, temp, strlen(ch));
 }
int compare(const void *a, const void *b)
{
return strcmp((char *)a, (char *)b);    //±»Ωœ¡Ω∏ˆ◊÷∑˚¥Æ «∑Òœ‡Õ¨∫Ø ˝
}
void FileInRefe(string file){ 
    ifstream infile;
    infile.open(file.data());
    assert(infile.is_open());
    char c;
    int i=0;
    while (!infile.eof()){
        infile>>c;
        //cout<<c;
        Refer[i]=c;
        i++;
    }
    infile.close();
    Refer[i]='$';
    Refer[i+1]='\0';
}

int SubQuesize=0;
void FileInSub(string file){
    ifstream infile;
    infile.open(file.data());
    assert(infile.is_open());
    string s;
    while(getline(infile,s)){
       // cout<<s<<endl;
        S[SubQuesize]=s;
        SubQuesize++;
    }
    infile.close()
}
void HandInRefe(){
    cout<<"please input refenence,input $ to end"<<endl;
    char c;
    int i=0;
    do{
        cin>>c;
        if(c!='\n') Refer[i]=c;
        i++;
    }while(c!='$');
    Refer[i]='\0';
}
void HandInSub(){
    cout<<"please input a subquence,input $ to end"<<endl;
    char c;
    int i=0;
    do{
        cin>>c;
        if(c!='\n') SubQue[i]=c;
        i++;
    }while(c!='$');
    SubQue[i-1]='\0'; 
}
void BWTprint(){
    /*cout<<"the matrix is:"<<endl;
    for(unsigned int i=0;i<strlen(Refer);i++){
        for(unsigned int j=0;j<strlen(Refer);j++){
            cout<<BWTMatrix[i][j];
        }
        cout<<endl;
    }*/
    cout<<"the BWT(T) is:"<<endl;
    for(unsigned int i=0;i<strlen(Refer);i++){
        BWT[i]=BWTMatrix[i][strlen(Refer)-1];
        cout<<BWTMatrix[i][strlen(Refer)-1];
    }
    cout<<endl;
    BWT[strlen(Refer)]='\0';
}
int LF(int r){
    int c=BWT[r];
    return Occ(c,r)+C[c]+1;
}
void Restore(){
    int len=strlen(Refer);
    for(int i=0;i<len;i++){
        T[i]='a';
    }
    T[len]='\0';
    int r=0;
    int p=int(strlen(Refer))-1;
    while(BWT[r]!='$'){
        T[p]=BWT[r];
        r=LF(r);
        p=p-1;
    }
    cout<<"the initial string is:"<<endl;
    for(int i=1;i<len;i++){
        cout<<T[i];
    }
    cout<<endl;
}
int LFC(int r,char c){
    return C[c]+Occ(c,r)+1;
}
void EXACTMATCH(){
    int p=strlen(SubQue)-1;
    char c=SubQue[p];
    int sp=C[c]+1;
    int num=0;
    for(unsigned int i=0;i<strlen(Refer);i++){
        if(Refer[i]==c) num++;
    }
    int ep=C[c]+num+1;
    int i=p-1;
    //cout<<sp<<" "<<ep<<endl;
    while(sp<ep&&i>=0){
        c=SubQue[i];
        sp=LFC(sp,c);
        ep=LFC(ep,c);
        i=i-1;
        //cout<<sp<<" "<<ep<<endl;
    }
    if((sp<ep)){
    cout<<"succeed!"<<endl;
    cout<<"the interval is ["<<sp<<","<<ep<<")"<<endl;
    for(int i=sp;i<ep;i++){
    string str1=BWTMatrix[i];
    cout<<"find the Referuence in "<<(strlen(Refer)-M.find(str1)->second)%(strlen(Refer))<< " of the initial Referuence"<<endl;
    }
    }
    else{
        cout<<"not found!"<<endl;
        cout<<"the latest interval is ["<<sp<<","<<ep<<")"<<endl;
        cout<<"the matching rate is :"<<(1-float((i+1))/strlen(SubQue))*100<<"%"<<endl;
    }
}
int main(){

    

    FileInRefe("/Users/summerchaser/Documents/res.txt");
    FileInSub("/Users/summerchaser/Documents/read.txt");


    int len=strlen(Refer);
    for (int i = 0; i < len; i++) {
        memcpy(BWTMatrix[i], Refer, strlen(Refer));
        loopMove(Refer, 1);
        string str=BWTMatrix[i];
        M[str]=i;
    }
    qsort(&BWTMatrix, len, N, compare);
    BWTprint();
    buildc();
    Restore();
   // HandInrefe();
    cout<<"----------------------------"<<endl;
   for(int i=0;i<SubQuesize;i++){
    //HandInSub();
    S[i].copy(SubQue, S[i].length());
    SubQue[S[i].length()] = '\0';
    EXACTMATCH();
    cout<<"----------------------------"<<endl;
   }
}

// MainMenu(){
//     char mode;
//     string adr_refe = "";//默认总串文件地址
//     string adr_sub = "";//默认子串文件地址
//     cout<<"Please choose refer input mode  (1-file from given position 2-file from other position else-hand in)"<<endl; 
//     // 选择总串输入方式 1-从默认位置读入文件 2-从给定位置读入文件 其他-手动输入
//     cin>>mode;
//     if (mode == '1'){
//         FileInRefe(adr_refe);
//     }else if (mode == '2'){
//         cout<<"please input Reference file path"<<endl;
//         cin>>adr_refe;
//         FileInRefe(adr_refe);
//     }else{        
//         HandInRefe(); 
//     }

//     cout<<"Please choose subquence input mode  (1-file from given position 2-file from other position else-hand in)"<<endl; 
//     // 选择子串输入方式 1-从默认位置读入文件 2-从给定位置读入文件 其他-手动输入
//     cin>>mode;
//     if (mode == '1'){
//         FileInSub(adr_refe);
//     }else if (mode == '2'){
//         cout<<"please input subquence file path"<<endl;
//         cin>>adr_sub;
//         FileInSub(adr_sub);
//     }else{        
//         HandInSub(); 
//     }
// }

























