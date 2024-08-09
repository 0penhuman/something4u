#include <iostream>
using namespace std;
bool field[8][8];
// bool snake[8][8];
int64_t t=0;
void makefield(){
    for(int row=0;row<8;row++){
        for(int conlumn=0;conlumn<8;conlumn++){
            field[conlumn][row]=0;
        }
    }
}
void born(){
    field[4][3]=1;
    field[4][4]=1;
    // snake[4][3]=1;
    // snake[4][4]=1;
    
}
void show(){
    for(int row=0;row<8;row++){
        for(int conlumn=0;conlumn<8;conlumn++){
            cout<<field[conlumn][row]<<'\t';
        }
        cout<<'\n';
    }
}
void disappear(){
    system("clear");
}
int delay(){
    for(int i=-32768;i<32767;i++){
    }
    return 1;
}
class move{
    public:
    void crawl(){
        
    }
};
void display(){
    while(1){show();
    cout<<t;
    t+=delay();
    disappear();
    delay();
    }
}
int main(){
    makefield();
    born();
    display();

}