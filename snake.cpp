#include <iostream>
//吃苹果还没搞，苹果是闪烁的1
using namespace std;
int field[8][8];
// int t=0;//time(per 5s)
bool isdead=false;
int8_t position_of_apple;
int lengthofsnake;
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
    lengthofsnake=0;
    head->position=(4<<3)+4;//这表明它位于(4,4)
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
    for(;temp->next!=NULL;temp=temp->next){}//此时temp指向蛇尾
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
    if(temp->position>>3==7)isdead=1;
            else{
            snake* body=new snake;
            body->position=temp->position-(1<<3);
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;}
        break;
    case 0://下
    if(temp->position-(temp->position>>3<<3)==0)isdead=1;
            else{snake* body=new snake;
            body->position=temp->position-1;
            body->direction=temp->direction;
            if(temp!=head)temp->next=body;
            else head->next=body;
            body->next=NULL;}
        break;
    case 2://上
        if(temp->position-(temp->position>>3<<3)==7)isdead=1;
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
bool iseatapple(){
    if(position_of_apple!=0&&head->position==position_of_apple)return 1;
    else return 0;
}
void setapple(){
    if(rand()%2==0&&iseatapple()){
        snake* temp=head;
        int x=rand()%6+1;//保证苹果不出现在最外层
        int y=rand()%6+1;
        while(temp!=NULL){//遍历到最后一个
            if(temp->position>>3==x&&temp->position-(temp->position>>3<<3)==y)return;//该机制使得蛇越长，出现苹果的机率越低
            else temp=temp->next;
        }
        position_of_apple=(x<<3)+y;
        // field[x][y]=2;
    }
}



void iseatbody(snake* temp){
    if(temp->next==NULL){
        // if(temp->position==head->position)isdead=1;cout<<"eat body\n";
        return;
    };
    if(temp!=head&&temp!=head->next&&temp->position==head->position){
        cout<<"eat body\n";
        isdead=1;
        return;
    }
    iseatbody(temp->next);
}

void display(){
    snake* temp=head;
    field[position_of_apple>>3][position_of_apple-(position_of_apple>>3<<3)]=2;
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
    position_of_apple=(1<<3)+1;
    // field[1][1]=2;
    char ch;
    grow();
    // grow();
    // grow();
    // grow();
    display();
    while(!isdead){
        
        
        
        if(ch=='r')turnRight();
        else if(ch=='l')turnLeft();
        else goforward(head);
        system("clear");
        setapple();
        display();
        if(iseatapple()){grow();setapple();}
        cin.get(ch);
        init_field();
        head->direction%=4;
        iseatbody(head);
    }
    for(snake* temp=head;temp!=NULL;temp=temp->next){
        lengthofsnake++;
        delete temp;
    }
    cout<<"game over:";
    cout<<lengthofsnake;
    return 0;
}
