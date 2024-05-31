#include <stdlib.h>
#include <math.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,  16, 2);

int tab[5]={13,12,8,4,2};
int i=0;
int* t=NULL;
char c = 0;
int x = 0;
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
  analogWrite(7,0);
  lcd.init();
  lcd.backlight();
}

void loop()
{
    i = ((int)rand()/rand())%4; 
    x++;
    t = (int*) realloc(t,x*sizeof(int));
  	*(t+x-1) = i ;
  	for(i=0;i<x;i++)
    {
      Serial.print(*(t+i));
      analogWrite(tab[*(t+i)],255);
      if(*(t+i)==3){
        analogWrite(tab[4],255);
      }
      delay(1000);
      for(c=0;c<=4;c++)
      {
        analogWrite(tab[c],0);
      }
      delay(1000);
    }
    c=0;
  	Serial.println();
    
  	while(c<x)
    {
      digitalWrite(9,1);
      i = -1; 
      while(digitalRead(11))
          i = 0;
      while(digitalRead(10))
          i = 1;
      while(digitalRead(6))
          i = 2;
      while(digitalRead(5))
          i = 3;
        
       
      if(i!=-1 && *(t+(c++))!=i)
      {
        free(t);
        t = NULL;
        for(i=0;i<=4;i++)
        {
          analogWrite(tab[i],255);
        }
        delay(3000);
        for(i=0;i<=4;i++)
        {
          analogWrite(tab[i],0);
        }
        lcd.setCursor(0,0);
        lcd.print("Score:");
        c = log10(x);
        for(i=0;i<=c;i++)
        {
          lcd.setCursor(i,1);
          lcd.print('0'+((x/(int)pow(10,c-i))%10));
        }
        x=0;
        break;
      }
      else if(i!=-1)
      {
        Serial.print(i);
        digitalWrite(9,0);
      }
      delay(100);
     }
  	Serial.println();
  
}
