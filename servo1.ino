#include <Servo.h>
#include <Wire.h>

Servo servo;
int pos = 0;

void setup()
{
  Serial.begin(115200);
  servo.attach(9);
  pos = 20;
  servo.write(pos);
  delay(1000);
}

void loop() 
{
  /*
  for(pos=30; pos<=150; pos++)
  {
    servo.write(pos);
    delay(15);
  }
  for(pos=150; pos>=30; pos--)
  {
    servo.write(pos);
    delay(15);
    
  }
  */
}
