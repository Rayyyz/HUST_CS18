int a,b32,i;    //测试int
float d,e;  //测试float
char ch;    //测试char
string str;   //测试string
int arr[5]; //测试数组
struct Test{
    int aa;
    char bb;
    string ss;

};

int f(int para){
    if(para >= 2 && para <5) return 1;
}

int main(){
    int test = 6;
    /*for*/
    for(int i= 1; i!= 5; i++){ print("ssss%c",ch); }
    /*while*/
    while(test <= 10){
        f(i);
        test++;        
    }
    /*switch*/
    switch(i){
        case 1:
            i=i%2;
            i=i*4;
            break;
        case '2':
            i = i * 2;
            break;
        default:
            break;
    }
    return ;
}