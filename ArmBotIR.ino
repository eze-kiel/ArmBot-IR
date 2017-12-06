#include <IRremote.h>
#include <Servo.h>

Servo servo1;
//Servo servo2;

signed short positionServo = 90;
signed short valeurTel;

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  servo1.attach(3);
  servo1.write(81);
  //servo2.attach(6);
  //servo2.write(90);

  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.begin(9600);

  irrecv.enableIRIn();

  Serial.println("**NEC protocol**\nready to detect");
  digitalWrite(2, HIGH);
}
void loop() {
  delay(800);
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    valeurTel = results.value;
    //do{

    switch (results.value)
    {
      //LEFT
      case 1386468383:
        Serial.println("left");
        positionServo = positionServo + 10;
        servo1.write(positionServo);
        break;
      case 16720605:
        Serial.println("left");
        positionServo = positionServo + 10;
        servo1.write(positionServo);
        break;

      //RIGHT
      case 553536955:
        Serial.println("right");
        positionServo = positionServo - 10;
        servo1.write(positionServo);
        break;
      case 16761405:
        Serial.println("right");
        positionServo = positionServo - 10;
        servo1.write(positionServo);
        break;

      //INIT
      case 3622325019:
        Serial.println("reset position");
        servo1.write(81);
        positionServo = 81;
        break;
      case 16712445:
        Serial.println("reset position");
        servo1.write(81);
        positionServo = 81;
        break;

    }
    //}while(valeur == 4294967295);

    if (positionServo > 85 || positionServo < 78)
    {
      digitalWrite(4, HIGH);
      digitalWrite(2, LOW);

    }
    else
    {
      digitalWrite(2, HIGH);
      digitalWrite(4, LOW);
    }

    irrecv.resume();
  }
}
