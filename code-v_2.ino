
#include <PID_v1.h>

#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>

//Define Variables we'll be connecting to
double ang = -89
; //angulo desejado para o aparato: test1 = -3
double Setpoint = ang + 90, Input, Output;

//Specify the links and initial tuning parameters
double Kp=4, Ki=10, Kd=2; //test_1: 4,10,2
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


MPU6050 mpu;

Servo servo;
int pos = 90;
int input = 0; //comando de entrada - mpu
int output = 0; //comando de saída - servo

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

  Serial.println("Input, Output"); //escrevendo no monitor serial em formato para .csv após
  myPID.SetMode(AUTOMATIC);//ligar pid
}

void loop() 
{
  timer = millis();
  Vector norm = mpu.readNormalizeGyro(); //ler valores normalizados
  //calcular ângulos
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  
  delay((timeStep*1000) - (millis()-timer)); //esperar o timeStep
  
  Input = yaw; //depende do eixo que se deseja -- verificar 
  myPID.Compute();
  if(Output>=170) //limite superior de ang
  {
    Output = 170;
  }
  if(Output<=20) //limite inferior de ang
  {
    Output = 20;
  }
  
  Serial.print(Input);
  Serial.print(" ,");
  Serial.println(Output);
  
  servo.write(Output); //comando atuador
  delay(15);
}
