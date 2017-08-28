#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<string.h>
#include<time.h>

int i,j;
int score=0;  //score.
int missed=0; //alphabets or digits missed.
int levelChoice=0;  //selection of level.
int wrongKey=0; //wrong key counter.
int speed=0;  //selection of speed.
int choice=0;  //user choice
int t=100; //for time
int delayTime=0; //time used for delay.
int missedNum[100]; //for numbers  missed.

char startNewGame[]="\n\t\n\n\t\t\t\tStart New Game  \n\n\nSelect Game Level \n\n1. Capital Alphabet Level (A-Z)\n2. Small Alphabet Level (a-z)\n3. Digits Level (0-9)\n\nYour Choice is -------------->  ";
char selectLevel[]="\n\n\nSelect Speed Level\n\n1. Speed Level One\n2. Speed Level Two\n3. Speed Level Three\nYour Choice is -------------->   ";



//void insertNode(int, int, int);
//void deleteNode(int data);
//void Developer();
//void startingScreen();
//int search(int data);
//int randX();
//void printChar();
//void capitalAlphabet();
//void digits();

void levelSelection();
void gameLost();
void keyPressed();
void winningScreen();

struct node
{
    int data;
    int x;
    int y;
    struct node *next;
}*first,*last,*temp;

//starting screen
void startingScreen()
{
    clrscr();
    choice=0;
    printf("\n\n\n\n\t\t\tTyping Tutor Game\n\n\n(1) To Start Game\n(2) Help\n(3) About Developer\n(4) Exit Game\n\nEnter your option -------> ");
    scanf("%d",&choice);
    if(choice==1)
    {
        levelSelection();
    }
    if(choice==2)
    {
        //helpScreen();
    }
    if(choice==3)
    {
        //about_developer();
    }
     else if(choice==4)
     {
        exit(0);
     }
     else
     startingScreen();
}

//select level
void levelSelection()
{
    choice=0;
    for(i=0;startNewGame[i]!='\0';i++)
    {
        printf("%c",startNewGame[i]);
        delay(10);
    }
    scanf("%d",&levelChoice);
    for(j=0;selectLevel[j]!='\0';j++)
    {
        printf("%c",selectLevel[j]);
        delay(10);
    }
    scanf("%d",&speed);
    if(levelChoice>=1 && levelChoice<=3 && speed>=1 && speed<=3)
    {
        if(speed==1)
        {
            delayTime=1000;
        }
        else if(speed==2)
        {
            delayTime=500;
        }
        else if(speed==3)
        {
            delayTime=300;
        }
        keyPressed();
    }
    else
    {
        levelSelection();
    }
}

//create new node
struct node *createNode()
{
    struct node *n;
    n=(struct node *)malloc(sizeof(struct node));
    return(n);
};

//inserting node
void insertNode(int data, int x, int y)
{
    if(first==NULL)
    {
        first=createNode();
        first->data=data;
        first->x=x;
        first->y=y;
        first->next=NULL;
        last=first;
    }
    else
    {
       while(last->next!=NULL)
       {
           last=last->next;
       }
       temp=createNode();
       temp->data=data;
       temp->x=x;
       temp->y=y;
       temp->next=NULL;
       last->next=temp;
       last=temp;

    }
}

// Deleting Node
void deleteNode(int data)
{

    temp=last=first;
    while(last)
    {
        if(last->data==data)
        {
            if(last==first)
            {
                first=first->next;
                last=NULL;
                last=first;
            }
            else if(last->next!=NULL)
            {
                temp->next=last->next;
                last=NULL;
                last=temp->next;
            }
            else
            {
                temp->next=NULL;
                last=NULL;
                last=temp;
            }
        }
        temp=last;
        last=last->next;

    }
}

//generate random x-axis between 1-80
int randX()
{
    int x=0;
    x=(rand()%80)+1;
    return x;
}

/*
void gotoxy(int x,int y)
{

}*/

//print characters and numbers
void printChar()
{
    clrscr();
    last=first;
    while(last->next)
    {
        gotoxy(last->x,last->y++);
        printf("%c",last->data);
        if(last->y<=20)
        {
            last=last->next;
        }
        else
        {

            missedNum[missed++]=last->data ; //string missed and missed counter.
            deleteNode(last->data);
            printChar();
        }
    }
    gotoxy(last->x,last->y++);
    printf("%c\n",last->data);
    gotoxy(1,20);
    printf("______________________________________________________________________________");
    gotoxy(1,22);
    printf("Score : %d",score);
    gotoxy(27,22);
    printf("Time Left : %d ",t--);
    gotoxy(60,22);
    printf("Digits Missed : %d",missed);
    gotoxy(1,24);
    printf("Characters Missed : ");
    for (i=0;i<missed;i++)
    {
        printf("%c ",missedNum[i]);
    }
    gotoxy(60,24);
    printf("Wrong Key Hits : %d",wrongKey);
}

//Generates random Capital Alphabets between 65-90 i.e. (A-Z)
void capitalAlphabet()
{
    int randNum=0;
    randNum=65+(rand()%(int)(90-65+1));
    insertNode(randNum,randX(),0);
    printChar();
}

//Generates random small alphabets between 65-90 i.e. (a-z)
void smallAlphabet()
{
    int randNum=0;
    randNum=97+(rand()%(int)(122-97+1));
    insertNode(randNum,randX(),0);
    printChar();
}

//Generates random number between 48-57 i.e (0-9)
void digits()
{
     int randNum = 0;
     randNum=48+(rand()%(int)(57-48+1));
     insertNode(randNum,randX(),0);
     printChar();
}

void keyPressed()
{
    int key=0;
    do
    {
        if(kbhit())
        {
            char k=getch();
            key=k;
            if(search(key)==1)
            {
                score++;
                deleteNode(key);
            }
            else
            {
                wrongKey++;
            }
        }
        if(levelChoice==1)
        {
            capitalAlphabet();
        }
        else if(levelChoice==2)
        {
            smallAlphabet();
        }
        else if(levelChoice==3)
        {
            digits();
        }
        delay(delayTime);
    }while(key != 27 && missed+wrongKey<10 && t>0); //escape key.
    if(missed+wrongKey>=10)
    {
        gameLost();
    }
    if (t<=0)
    {
        winningScreen();
    }
}

//
int search(int data)
{
    int s=0;
    last=first;
    while(last)
    {
        if(last->data==data)
        {
            s=1;
            return s;
        }
        last=last->next;
    }
    return s;
}

//
void gameLost()
{
    char k;
    int key;
    clrscr();
    do
    {
        k = getch();
        key = k;
        delay(100);
        printf("\n\n\t\t\t\tSummary");
        delay(100);
        printf("\n\n\t\t\tYou Have Lost the Game");
        delay(100);
        printf("\n\n\t\t\tScore : %d",score);
        delay(100);
        printf("\n\n\t\t\tNumber of Wrong Keys Hit : %d",wrongKey);
        delay(100);
        printf("\n\n\t\t\tNumber of Characters Missed : %d",missed);
        printf("\n\n\t\t\tCharacters Missed : ");
        for(i=0;i<missed;i++)
        {
            printf("%c  ",missedNum[i]);
            delay(100);
        }
        delay(1000);
        printf("\n\n\t\t\tBetter Luck Next Time");
        delay(1000);
	printf("\n\n\tYou should try again to increase your score.");
	delay(1000);
	printf("\n\nYou will be redirected to Menu after 2 Second ........... Please Wait");
	delay(2000);
	startingScreen();
	/*if(key == 37) //space key ascii.
	{
	    startingScreen();
	}*/
    }while(key!=27);//esc key
    //exit(0);
}

//
void winningScreen()
{
    clrscr();
    delay(100);
    printf("\n\t\t\t\tCongratulations :) ");
    delay(100);
    printf("\n\n\t\t\tYou Have Won the Game !!!!");
    delay(100);
    printf("\n\n\n\tNumber of Wrong key Hits : %d ",wrongKey);
    delay(100);
    printf("\n\tNumber of Character Missed : %d ",missed);
    delay(100);
    printf("\n\n\tCharacters Missed : ");
    for(i=0;i<missed;i++)
    {
	printf("%c ",missedNum[i]);
	delay(100);
    }
    delay(100);
    printf("\n\n\n\tTry Again to Increase your Score.");
    delay(100);
    printf("\n\n\n\t\t\tYou will be redirected to Menu after 2 Seconds.");
    delay(2000);
    //while(!kbhit())
    //{
	startingScreen();
    //}
    //sleep(3);
    //exit(0);
}


void typingTutor()
{
     char text[]="\
000000 00  00 00000   0000 00    00  0000\n\r\
  00    0000  00   00  00  0000  00 00\n\r\
  00     00   00000    00  00 00 00 00 00\n\r\
  00     00   00       00  00  0000 00  00\n\r\
  00     00   00      0000 00    00  0000\n\r\
\n\r\
000000 00  00  000000 000000 00000\n\r\
  00   00  00    00   00     00   00\n\r\
  00   00  00    00   0000   00000\n\r\
  00   00  00    00   00     00   00  \n\r\
  00   000000    00   000000 00    00\
\n";


    //textmode(C4350);
	//textbackground(0);
	//_setcursortype(_NOCURSOR);
	window(15,5,80,25);
	for(i=0;i<16;i++)
	{
		textcolor(i);
		clrscr();
		cprintf(text);
		delay(500);
	}

}
void main()
{
    clrscr();
    //typingTutor();
    clrscr();
    srand(time(NULL));
    startingScreen();
    getch();
}


