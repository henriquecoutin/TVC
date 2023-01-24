
#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

Servo servo;
int pos = 90;


//variáveis de tempo
unsigned long timer = 0;
float timeStep = 0.01;

//variáveis do giroscópio
float pitch = 0;
float roll = 0;
float yaw = 0;


void setup() 
{
  Serial.begin(115200);
  servo.attach(9); //servo conectado ao pino 9
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) //validar se o sensor está conectado
  {
    Serial.println("Não encontramos um MPU válido.");
    delay(500);
  }

  mpu.calibrateGyro(); //calibra o giroscópio em (0,0,0)
  mpu.setThreshold(3); //setar sensibilidade
  
  Serial.println("servo, angulo"); //escrevendo no monitor serial em formato para .csv após
  servo.write(pos);
}

void loop() 
{

  //yaw é o que se salva... 

  for(pos=20; pos<=170; pos++)
  {
    timer = millis();
    Vector norm = mpu.readNormalizeGyro(); //ler valores normalizados
    //calcular ângulos
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
    
    delay((timeStep*1000) - (millis()-timer)); //esperar o timeStep
    
    servo.write(pos);
    delay(150);
    Serial.print(pos);
    Serial.print(" ,");
    Serial.println(yaw);
  }
  for(pos=170; pos>=20; pos--)
  {
    timer = millis();
    Vector norm = mpu.readNormalizeGyro(); //ler valores normalizados
    //calcular ângulos
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
    
    delay((timeStep*1000) - (millis()-timer)); //esperar o timeStep
    
    servo.write(pos);
    delay(150);
    Serial.print(pos);
    Serial.print(" ,");
    Serial.println(yaw);
  }
}
