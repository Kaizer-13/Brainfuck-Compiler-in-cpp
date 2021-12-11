#include<bits/stdc++.h>
#include <getopt.h>
using namespace std;


map<int,int> mp;
vector<char>code;
const int lim=30000;
unsigned char memo[lim];
int i;
void handle(int x, int y)
{
    if(y<x) return;
    for(int p=x;p<=y;p++)
    {
        if(code[p]=='>') i=(i+1)%lim;
        if(code[p]=='<') i=(i-1+lim)%lim;
        if(code[p]=='+') memo[i]++;
        if(code[p]=='-') memo[i]--;
        if(code[p]==','){
            unsigned char z;
            scanf("%c",&z);
            memo[i]+=z;
        }
        if(code[p]=='.') printf("%c",memo[i]);
        if(code[p]=='['){
            int w=mp[p];
            while(memo[i]) handle(p+1,w-1);
            p=w;
        }
    }
}


int main(int argc, char** argv){

    int stream;
    char *name;
    if(argc==1){
        printf("ERROR: INVALID COMMAND FORMAT\n");
        return 0;
    }
    
    while((stream = getopt(argc, argv, ":bf:")) != -1){
        switch (stream){
            case 'b':
            case 'f':
                name=optarg;
                break;
            default:
                printf("ERROR: NO BRAINFUCK FILE FOUND\n");
                return 0;
        }
    }

    
    int len=strlen(name);
    if(len<3||!((name[len-3]=='.'&&name[len-2]=='b'&&name[len-1]=='f')||(name[len-2]=='.'&&name[len-1]=='b'))){
        printf("ERROR: INVALID FILE FORMAT\n");
        return 0;
    }
    FILE *fp=freopen(name,"r",stdin);
    if(fp==NULL){
        printf("ERROR: FILE \"%s\" DOES NOT EXIST\n",name);
        return 0;
    }

    vector<int> last;
    char curr;
    int success=1;

    while(fscanf(fp,"%c",&curr)!=EOF){
        if(curr=='<'||curr=='>'||curr=='+'||curr=='-'||curr==','||curr=='.'||curr=='['||curr==']') {
            code.push_back(curr);
            if(curr=='[') {
                last.push_back(code.size()-1);
            }
            if(curr==']'){
                if(last.size()){
                    mp[last.back()]=code.size()-1;
                    last.pop_back();
                }
                else{
                    success=0;
                    break;
                }
            }
        }
    }
    fclose(fp);
    if(!success){
        cout<<"ERROR: SYNTAX FAULT\n";
        return 0;
    }
    handle(0,code.size()-1);
}