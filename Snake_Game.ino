#include <LiquidCrystal.h>


#define joystick_x        A0
#define joystick_y        A1
#define joystick_switch   A2
#define JOYSTICK_RELEASED              0
#define JOYSTICK_UP_                   1
#define JOYSTICK_DOWN_                 2
#define JOYSTICK_LEFT_                 3
#define JOYSTICK_RIGHT_                4
#define rs                12
#define en                11
#define d4                5
#define d5                4
#define d6                3
#define d7                2
#define rows              2
#define columns           16
#define pixels_rows       8
#define pixels_col        5
#define initial_snake_len 3
#define       Max_Snake_length             25


LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
unsigned long time, timeNow; //long numbers to store 4Byte.
int gameSpeed; //variable to set game speed
boolean skip, gameOver, gameStarted; // boolean variables to determine game situation
int olddir; //variable to determine old direction of snake.
byte key=0; // value to check movement of joystick
byte oldkey=0; //value to check old movement of joystick

byte Field[8*rows*16]; //array 1D size 1280 ,byte variable 


struct partdef  //struct to  set a way to group several related variables into one place
{
  int row,column,dir;  //members of partdef struct
  struct partdef *next; //nested struct pointer next.(??)
}; 
typedef partdef part;  //initiate part datatype for struct partdef so we dont need to declare struct every time.

part *head, *tail;   // make 2 pointers variable to struct part.
int collected;       //variable to count collected food(??)
unsigned int pc,pr;  //pc,pr are positive only.
//----------------------------------------------------
// display on the screen
void drawMatrix() 
{
  //levelz variable 3D to set the lvl difficulty and ditermine matrix.
  boolean levelz[4][16] = {
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
};

  byte myChar[8]; //1D array 0-7 indexses
  boolean special; //special boolean variable
  int cc=0;  //variable int probably counter
  
  if (!gameOver)
  {
  ChangeDot(pr, pc, true);//making the food????
  
  for(int r=0;r<rows;r++)
  {    
    for(int c=0;c<16;c++)
    {
      special = false;
      for(int i=0;i<8;i++)
      {
        byte b=B00000;

        if ((Field[16 * (r*8+i) + (c*5+0)/5] & (1 << ((c*5+0) % 5))) >> ((c*5+0) % 5)) {b+=B10000; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+1)/5] & (1 << ((c*5+1) % 5))) >> ((c*5+1) % 5)) {b+=B01000; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+2)/5] & (1 << ((c*5+2) % 5))) >> ((c*5+2) % 5)) {b+=B00100; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+3)/5] & (1 << ((c*5+3) % 5))) >> ((c*5+3) % 5)) {b+=B00010; special = true;}
        if ((Field[16 * (r*8+i) + (c*5+4)/5] & (1 << ((c*5+4) % 5))) >> ((c*5+4) % 5)) {b+=B00001; special = true;}        
 
        myChar[i] = b;

      }
      if (special) 
      {
        lcd.createChar(cc, myChar);
        lcd.setCursor(c,r);
        lcd.write(byte(cc));
  cc++;
      }
      else 
      {
        lcd.setCursor(c,r);
        if (levelz[r][c]) lcd.write(255);
        else lcd.write(128);
      }
    }
  } 
  }
}

//----------------------------------------------------
void freeList()
{
  part *p,*q; //2 pointers to struct part def
  p = tail;   //assign pointer tail to pointer p.
  while (p!=NULL) //while there is datat in p it means there is tail.
  {
    q = p;//
    p = p->next;  //access structure member p 
    free(q);  //free memory from pointer q.
  }
  head = tail = NULL;
}
//--------------------------------------------------
void gameOverFunction()//preety simple
{
  delay(1000);
  lcd.clear();
  freeList(); //data structure used in dynamic memory allocation connection unallocated regions of memory together in a linked list.
  lcd.setCursor(3,0);
  lcd.print("Game Over!");
  lcd.setCursor(4,1);
  lcd.print("Score: ");
  lcd.print(collected);
  delay(15000);
}
//--------------------------------------------------
void growSnake()  
{
  part *p; //set pointer in structure partdef
  p = (part*)malloc(sizeof(part)); //setting memory place.
  p->row = tail->row;
  p->column = tail->column;
  p->dir = tail->dir;
  p->next = tail;
  tail = p;
}
//--------------------------------------------------
// a new dot on the screen
void newPoint()
{
  //again choosing the specific lvl.
  boolean levelz[4][16] = {
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
  };

part *p;
p = tail;
boolean newp = true;
while (newp)
{
    pr = random(8*rows);
    pc = random(80);
    newp = false;
    if (levelz[pr / 8][pc / 5]) newp=true;
    while (p->next != NULL && !newp) 
    {
      if (p->row == pr && p->column == pc) newp = true;
      p = p->next;
    }
}
  
  if (collected < Max_Snake_length && gameStarted) growSnake();
}
//------------------------------------------------------
void moveHead()
{
  boolean levelz[4][16] = {
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false},
{false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false}
  };
switch(head->dir) // 1 step in direction
  {
    case 0: head->row--; break;
    case 1: head->row++; break;
    case 2: head->column++; break;
    case 3: head->column--; break;
    default : break;
  }
  if (head->column >= 80) head->column = 0;
  if (head->column < 0) head->column = 79;
  if (head->row >= (8*rows)) head->row = 0;
  if (head->row < 0) head->row = (8*rows - 1);
  
  if (levelz[head->row / 8][head->column / 5]) gameOver = true; // wall collision check
  
  part *p;
  p = tail;
  while (p != head && !gameOver) // self collision 
  {
    if (p->row == head->row && p->column == head->column) gameOver = true;
    p = p->next;
  }
  if (gameOver)
    gameOverFunction();
  else
  {
  ChangeDot(head->row, head->column, true);
  
  if (head->row == pr && head->column == pc) // point pickup check
  {
    collected++;
    if (gameSpeed < 25) gameSpeed+=3;
    newPoint();
  }
  }
}
//------------------------------------------------
// funny move
void moveAll()
{
  part *p;
  p = tail;

  ChangeDot(p->row, p->column, false);
  
  while (p->next != NULL) 
  {
    p->row = p->next->row;
    p->column = p->next->column;
    p->dir = p->next->dir;
    p = p->next;
  }
  moveHead();
}
//------------------------------------------------
//create snake
void createSnake(int n) // n = size of snake
{
  for (unsigned int i=0;i<(8*rows*16);i++)
    Field[i] = 0;
    
  part *p, *q;
  tail = (part*)malloc(sizeof(part));
  tail->row = 7;
  tail->column = 39 + n/2;
  tail->dir = 3;
  q = tail;
  
  ChangeDot(tail->row, tail->column, true);
  
  for (int i = 0; i < n-1; i++) // build snake from tail to head
  {
    p = (part*)malloc(sizeof(part));
    p->row = q->row;
    p->column = q->column - 1; //initial snake id placed horizoltally
    
    ChangeDot(p->row, p->column, true);
    
    p->dir = q->dir;
    q->next = p;
    q = p;
  }
  if (n>1)
  {
    p->next = NULL;
    head  = p;
  }
  else 
  {
    tail->next = NULL;
    head = tail;
  }
}

void startF()
{
  byte mySnake[8][8] = 
{
{ B00000,
  B00000,
  B00011,
  B00110,
  B01100,
  B11000,
  B00000,
},
{ B00000,
  B11000,
  B11110,
  B00011,
  B00001,
  B00000,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
},
{ B00000,
  B00000,
  B00011,
  B01111,
  B11000,
  B00000,
  B00000,
},
{ B00000,
  B11100,
  B11111,
  B00001,
  B00000,
  B00000,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B11000,
  B01101,
  B00111,
  B00000,
},
{ B00000,
  B00000,
  B01110,
  B11011,
  B11111,
  B01110,
  B00000,
},
{ B00000,
  B00000,
  B00000,
  B01000,
  B10000,
  B01000,
  B00000,
}
};
  
  gameOver = false;
  gameStarted = false;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Game On!");
  for(int i=0;i<8;i++)
  {
    lcd.createChar(i,mySnake[i]);
    lcd.setCursor(i+4,1);
    lcd.write(byte(i));
  }
  delay(15000);
  
  collected = 0;
  gameSpeed = 8;
  createSnake(3);
  time = 0;
}
//----------------------------------
void setup() {
  digitalWrite(joystick_switch,HIGH);
  lcd.begin(16,rows);
  startF();
}
//----------------------------------
void loop()
{
  if (!gameOver && !gameStarted) 
// if the game does not start
  {
   key = ScanJoyStick(); 
// check the joystick
   if (key != oldkey)    
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0)
       {
         olddir = head->dir;
       }
     }
   }

   else if (digitalRead(joystick_switch))
// if the joystick button is pressed, the beginning of the game
   {
     lcd.clear();
     newPoint();
     gameStarted = true;
    }
   else 
// otherwise continue the display the announcment.
    {
      lcd.setCursor(14,0);
      lcd.print("Lets play!");
    }
  }
  
  else if (!gameOver && gameStarted)
// if there is a game
  {
   skip = false;
   
   key = ScanJoyStick(); // check the joystick
   if (key != oldkey)   
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0)
       {
         
// select the direction of movement of the snake depending on the position of the joystick
         olddir = head->dir;
         if (key==JOYSTICK_RIGHT_ && head->dir!=3) head->dir = 2;
         else if (key==JOYSTICK_UP_    && head->dir!=1) head->dir = 0;
         else if (key==JOYSTICK_DOWN_  && head->dir!=0) head->dir = 1;
         else if (key==JOYSTICK_LEFT_  && head->dir!=2) head->dir = 3;
         
         if (olddir != head->dir)
         {
           skip = true;
           delay(1000/gameSpeed);
           moveAll();
           drawMatrix();
         }
       }
     }
   }
   if (!skip)
   {
     timeNow = millis();
     if (timeNow - time > 1000 / gameSpeed)
     {
       moveAll();
       drawMatrix();
       time = millis();
     }
   }
  }
  
  if(gameOver) // if the game is over
  {
   key = ScanJoyStick();// check the joystick
   if (key != oldkey)   
   {
     delay(50);  
     key = ScanJoyStick();
     if (key != oldkey)    
     {   
       oldkey = key;
       if (key > 0)// start the game when you move the joystick in any direction
       {
          startF();
       }
     }
   }
   
  }
}
//-----------------------------------
// check the joystick
byte ScanJoyStick()
{
  byte Direction = JOYSTICK_RELEASED;
  unsigned int X_Val = analogRead(joystick_x);
  unsigned int Y_Val = analogRead(joystick_y);
  
  if ((Y_Val >= 900) && (X_Val >= 400))
  {
    Direction = JOYSTICK_DOWN_;
  }
  else if ((Y_Val <= 400) && (X_Val >= 400))
  {
    Direction = JOYSTICK_UP_;
  }
  else if ((Y_Val >= 400) && (X_Val >= 900))
   {
    Direction = JOYSTICK_RIGHT_;
   }
  else if ((Y_Val >= 400) && (X_Val <= 400))
  {
    Direction = JOYSTICK_LEFT_;
  }
  
  return Direction;
}
//-----------------------------------------------------
// making changes to matrix of points on eran
void ChangeDot(unsigned int RowVal, unsigned int ColVal, boolean NewVal)
{
  Field[16 * RowVal + ColVal/5] &= ~(1 << (ColVal % 5));

  if (NewVal)
    Field[16 * RowVal + ColVal/5] |= 1 << (ColVal % 5);
} 
