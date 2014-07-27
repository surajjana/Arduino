/*
  Developer : Suraj Kumar Jana
  E-mail : surajjana2@gmail.com
  
  Copyright (C) 2014  Suraj Kumar Jana

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

int cyclesPerSecond = 974;

//pins
int clockInterrupt = 0;//interrupt 0 is pin 2 on UNO
int pwnOut = 6;//pin 6

//timekeeping
int seconds = 0;
int minutes = 0;
int hours = 0;
int masterClock = 0;//number of square waves

void setup(){
  attachInterrupt(clockInterrupt,clockCounter,RISING);
  
  delay(2000);//delay time to restart if its locked
  
  Serial.begin(9600);//starting serial communication for debugging
  
  Serial.print("Writing to pin : ");
  Serial.println(pwnOut);
  analogWrite(pwnOut,127);//this starts our PWM 'clock' with a 50% duty cycle
}

void loop(){
  serialPrintTime();
  delay(1000);
}

void clockCounter(){
  masterClock++;//with each clock rise adding 1 to masterClock count
  if(masterClock == cyclesPerSecond){
    seconds++;//after one cycle add 1 to second
    masterClock = 0;//reset clock counter
    if(seconds == 60){
      minutes++;
      seconds = 0;//reset seconds counter
    
      if(minutes == 60){
        hours++;
        minutes = 0;
      }
    }
  }
  return;
}

void serialPrintTime(){
  if(hours<10){
    Serial.print("0");
  }
  Serial.print(hours);
  Serial.print(" : ");
  
  if(minutes<10){
    Serial.print("0");
  }
  Serial.print(minutes);
  Serial.print(" : ");
  
  if(seconds<10){
    Serial.print("0");
  }
  Serial.println(seconds);
}  
  
  
  


