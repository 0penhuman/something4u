#include <iostream>
using namespace std;
bool field[8][8];
int t=0;//time(per 5s)
bool isdead=false;
struct snake
{
    int8_t position;//position=x<<3+y
    /*
    解析direction：
        奇数为左右，偶数为上下
        up为2的奇数倍，down为2的偶数倍
        left>0:     (left+1)/2%2=1
        left<0:     (-left+1)/2%2=0
        right>0:    (right+1)/2%2=0
        right<0:    (-right+1)/2%2=1
    */
   int8_t direction;//left:+1  right:-1,3    down:0    up:+2,-2
    snake* next;
};
snake* head=new snake;
void init_field(){//初始化活动区域
    for(int8_t row=0;row<8;row++){
        for(int8_t column=0;column<8;column++){
            field[column][row]=0;
        }
    }
}
void init_snake(){
    head->position=(4<<3);//这表明它位于(4,4)
    head->direction=0;
}
void godown(snake* temp){
    if(temp->next==NULL){//如果出现最后一个点没动，则修改这里//也许需要分类讨论
        if(head->position-(head->position>>3<<3)==7)isdead=true;
        else head->position+=1;//head->direction+0;
        return;
    };
    godown(temp->next);
    temp->next->position=temp->position;
    temp->next->direction=temp->direction;
}

void goforward(snake* temp){
    if(temp->next=NULL){
        if(head->position>>3==0&&abs(head->direction/2%2)==1)
        /*
        现在是8.12 我正在写goforward函数，我打算以godown为基础，这些if是用于判断死亡条件的
        */
    }
}

void grow(){//body长度只与t有关
    snake* temp=head;
    for(;temp->next!=NULL;temp=temp->next){}
    if(temp->direction%2==0){
        if(temp->direction/2%2==0){//表明上一个节点的运动方向向下
            if(temp->position-(temp->position>>3<<3)==7)isdead=true;
            else{snake* body=new snake;
            body->position=temp->position-1;
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;}
        }
        
        else{//表明上一个节点的运动方向向上
            if(temp->position-(temp->position>>3<<3)==0)isdead=true;
            else{
            snake* body=new snake;
            body->position=temp->position+1;
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;
            }
        }
    }

    else
    {
        if((temp->direction+1)/2%2==0){//表明上一个节点的运动方向向右
            if(temp->position>>3==0)isdead=true;
            else{
            snake* body=new snake;
            body->position=temp->position+(1<<3);
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;
            }
        }
        else{
            if(temp->position>>3==0)isdead=true;
            else{
            snake* body=new snake;
            body->position=temp->position-(1<<3);
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;
            }
        }
    }
}








void display(){
    snake* temp=head;
    while(temp!=NULL){
        field[temp->position>>3][temp->position-(temp->position>>3<<3)]=1;
        temp=temp->next;
    }
    for(int8_t row=0;row<8;row++){
        for(int8_t conlumn=0;conlumn<8;conlumn++){
            cout<<field[conlumn][row]<<'\t';
        }
        cout<<'\n';
    }
}
int main(){
    init_field();
    init_snake();
    while(!isdead){
        display();
        godown(head);
        grow();
        cin.get();
        system("clear");
        init_field();
    }
}
