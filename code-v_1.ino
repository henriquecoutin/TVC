#include <PID_v1.h>

#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>



MPU6050 mpu;

Servo servo;
int pos = 0;
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
}

float x = 3.00; //variável de calibração proporcional


void loop() 
{
  timer = millis();
  Vector norm = mpu.readNormalizeGyro(); //ler valores normalizados
  //calcular ângulos
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;
  
  delay((timeStep*1000) - (millis()-timer)); //esperar o timeStep
  
  input = pitch; //depende do eixo que se deseja -- verificar 
  Serial.print("Input = ");
  Serial.print(input);
  Serial.print(" Output = ");
  Serial.println(output);
  output = x*input; //aplicando proporcional
  servo.write(output); //comando atuador
  delay(15);
}
