#include <iostream>
using namespace std;
bool field[8][8];
int t=0;//time(per 5s)
bool isdead=false;
struct snake
{
    int8_t position;//position=x<<3+y
   int8_t direction;
    snake* next;
};
int8_t decodeDirection(int8_t direction){//解析direction    left:+1  right:-1    down:0    up:+2
    if(direction%2==0){
        if(direction/2%2==0)return 0;
        else return 2;
    }
    else{
        if((direction+1)/2%2==0)return -1;
        else return 1;
    }
}

snake* head=new snake;
void init_field(){//初始化活动区域
    for(int8_t row=0;row<8;row++){
        for(int8_t column=0;column<8;column++){
            field[column][row]=0;
        }
    }
}
void init_snake(){
    head->position=(4<<3)+3;//这表明它位于(4,4)
    head->direction=0;
}

void goforward(snake* temp){
    if(temp==head){
        switch (decodeDirection(head->direction))
        {
        case 1://左
            if(head->position>>3==0)isdead=1;
            else head->position-=1<<3;
            break;
        case -1://右
            if(head->position>>3==7)isdead=1;
            else head->position+=1<<3;
            break;
        case 0://下
            if(head->position-(head->position>>3<<3)==7)isdead=1;
            else head->position+=1;
            break;
        case 2://上
            if(head->position-(head->position>>3<<3)==0)isdead=1;
            else head->position-=1;
            break;
        default:
            break;
        }
    }
    if(temp->next==NULL)return;
    goforward(temp->next);
    temp->next->position=temp->position;
    temp->next->direction=temp->direction;
}

void turnLeft(){
    head->direction-=1;
}
void turnRight(){
    head->direction+=1;
}

void grow(){//body长度只与t有关
    snake* temp=head;
    for(;temp->next!=NULL;temp=temp->next){}
    switch (decodeDirection(temp->direction))
    {
    case -1://右
        if(temp->position>>3==0)isdead=1;
        else{
        snake* body=new snake;
        body->position=temp->position+(1<<3);
        body->direction=temp->direction;
        if(temp!=head)temp->next=body;
        else head->next=body;
        body->next=NULL;
        }
        break;
    case 1://左
    if(temp->position>>3==0)isdead=1;
            else{
            snake* body=new snake;
            body->position=temp->position-(1<<3);
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;}
        break;
    case 0://下
    if(temp->position-(temp->position>>3<<3)==7)isdead=1;
            else{snake* body=new snake;
            body->position=temp->position-1;
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;}
        break;
    case 2://上
        if(temp->position-(temp->position>>3<<3)==0)isdead=1;
            else{
            snake* body=new snake;
            body->position=temp->position+1;
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;
            }
        break;
    }
}

void iseatbody(snake* temp){
    if(temp==NULL)return;
    if(temp!=head&&temp!=head->next&&temp->position==head->position){
        isdead=1;
        return;
    }
    iseatbody(temp->next);
}

void display(){
    snake* temp=head;
    while(temp!=NULL){
        field[temp->position>>3][temp->position-(temp->position>>3<<3)]=1;
        temp=temp->next;
    }
    for(int8_t row=0;row<8;row++){
        for(int8_t column=0;column<8;column++){
            cout<<field[column][row]<<'\t';
        }
        cout<<'\n';
    }
}
int main(){
    init_field();
    init_snake();
    char ch;
    grow();
    
    while(!isdead){
        display();
        iseatbody(head);
        goforward(head);
        grow();
        cin.get(ch);
        if(ch=='r')turnRight();
        else if(ch=='l')turnLeft();
        system("clear");
        init_field();
        head->direction%=4;
    }
}
