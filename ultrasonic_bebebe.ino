#include "IRremote.h"
int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'


/******************************************************************************
----------------本例程仅供学习使用，未经作者允许，不得用于其他用途。-----------
------------------------版权所有，仿冒必究！-----------------------------------
----------------1.开发环境:Arduino IDE-----------------------------------------
----------------2.测试使用开发板型号：Arduino Leonardo or Arduino UNO R3-------
----------------3.单片机使用晶振：16M------------------------------------------
----------------4.淘宝网址：Ilovemcu.taobao.com--------------------------------
----------------------------epic-mcu.taobao.com--------------------------------
----------------5.作者：神秘藏宝室---------------------------------------------
******************************************************************************/
#define TrigPin 2
#define EchoPin 3
int spk=13; //　定義揚聲器為數位接腳13
int DETECT_DISTANCE = 30;
float Value_cm;
bool b_bebebe = true;
int MODE_BEBE = 1; 
void be()
{
   digitalWrite(spk, 1);
   delay(20);
   digitalWrite(spk, 0);
}

void bebebe(float sound_distance)
{    
  Serial.print((int)Value_cm);
  Serial.println("cm");
  if(sound_distance > DETECT_DISTANCE)
  {
    digitalWrite(spk, 0);
    return;
  }
  else
  {
    if(MODE_BEBE % 2 == 1)
    {
        digitalWrite(spk, 1);
        if(sound_distance > 10)
        {// BE BE BE...
          delay(5 * (int)sound_distance);
          digitalWrite(spk, 0);
        }
    }
    else
    {//BE~~~~~~~~~~
      digitalWrite(spk, 1);
    }
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(spk, OUTPUT);
  
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
}
void loop()
{
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  Value_cm = float( pulseIn(EchoPin, HIGH) * 17 )/1000; //将回波时间换算成cm
  //读取一个引脚的脉冲（HIGH或LOW）。例如，如果value是HIGH，pulseIn()会等待引脚变为HIGH，开始计时，再等待引脚变为LOW并停止计时。
  //返回脉冲的长度，单位微秒。如果在指定的时间内无脉冲函数返回。
  //此函数的计时功能由经验决定，长时间的脉冲计时可能会出错。计时范围从10微秒至3分钟。（1秒=1000毫秒=1000000微秒）
  //接收到的高电平的时间（us）* 340m/s / 2 = 接收到高电平的时间（us） * 17000 cm / 1000000 us = 接收到高电平的时间 * 17 / 1000  (cm)

  if(b_bebebe)
  {
    bebebe(Value_cm);
  }    
  delay(100);  
  
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}

void translateIR() // takes action based on IR code received
// describing Remote IR codes 
{
;
  Serial.println(results.value, HEX);
  
  if(results.value == 0x530ACF)
  {
    DETECT_DISTANCE += 10;    
    be();
  }
  
  if(results.value == 0x510AEF)
  {
    DETECT_DISTANCE -= 10;    
    be();
  }
  
  if(results.value == 0x511AEE)
  {
    b_bebebe=true;    
    MODE_BEBE++;
    
    be();
  }
  
  if(results.value == 0x500AFF)
  {
    b_bebebe=false;    
    be();
  }  
/*
  switch(results.value)

  {

  case 0xFF629D: Serial.println(" FORWARD"); break;
  case 0xFF22DD: Serial.println(" LEFT");    break;
  case 0xFF02FD: Serial.println(" -OK-");    break;
  case 0xFFC23D: Serial.println(" RIGHT");   break;
  case 0xFFA857: Serial.println(" REVERSE"); break;
  case 0xFF6897: Serial.println(" 1");    break;
  case 0xFF9867: Serial.println(" 2");    break;
  case 0xFFB04F: Serial.println(" 3");    break;
  case 0xFF30CF: Serial.println(" 4");    break;
  case 0xFF18E7: Serial.println(" 5");    break;
  case 0xFF7A85: Serial.println(" 6");    break;
  case 0xFF10EF: Serial.println(" 7");    break;
  case 0xFF38C7: Serial.println(" 8");    break;
  case 0xFF5AA5: Serial.println(" 9");    break;
  case 0xFF42BD: Serial.println(" *");    break;
  case 0xFF4AB5: Serial.println(" 0");    break;
  case 0xFF52AD: Serial.println(" #");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default:      
   //Serial.println(results.value, HEX);
     Serial.println(" other");
  }// End Case
  */
  delay(50); // Do not get immediate repeat
} //END transl
