#include "Constants.h"

char str[500];

void setup() {
  Serial.begin(115200);
  while(!Serial);
  
  // GPIO tests
//  pinMode(GPIO_0 , INPUT);
//  pinMode(GPIO_1 , INPUT);
//  pinMode(GPIO_2 , INPUT);
//  pinMode(GPIO_3 , INPUT);
//  pinMode(GPIO_4 , INPUT);
//  pinMode(GPIO_5 , INPUT);
//  pinMode(GPIO_6 , INPUT);
//  pinMode(GPIO_7 , INPUT);
//  pinMode(GPIO_8 , INPUT);
//  pinMode(GPIO_9 , INPUT);
//  pinMode(GPIO_10, INPUT);
//  pinMode(GPIO_11, INPUT);
  pinMode(GPIO_0 , OUTPUT);
  pinMode(GPIO_1 , OUTPUT);
  pinMode(GPIO_2 , OUTPUT);
  pinMode(GPIO_3 , OUTPUT);
  pinMode(GPIO_4 , OUTPUT);
  pinMode(GPIO_5 , OUTPUT);
  pinMode(GPIO_6 , OUTPUT);
  pinMode(GPIO_7 , OUTPUT);
  pinMode(GPIO_8 , OUTPUT);
  pinMode(GPIO_9 , OUTPUT);
  pinMode(GPIO_10, OUTPUT);
  pinMode(GPIO_11, OUTPUT);

  // Peripheral Inputs
  pinMode(DIP_1, INPUT);
  pinMode(DIP_2, INPUT);
  pinMode(DIP_3, INPUT);
  pinMode(DIP_4, INPUT);
  pinMode(PBTN , INPUT);

  // Peripheral Outputs
  pinMode(INJ_Pin , OUTPUT);
  pinMode(BUZZ_Pin, OUTPUT);
  pinMode(LED_1   , OUTPUT);

  digitalWrite(LED_1, HIGH);
}

void loop() {
//  sprintf(str, "GPIO: %01i%01i%01i%01i%01i%01i%01i%01i%01i%01i%01i%01i \n DIP: %01i%01i%01i%01i \n BTN: %01i \n",
//  digitalRead(GPIO_0 ),
//  digitalRead(GPIO_1 ),
//  digitalRead(GPIO_2 ),
//  digitalRead(GPIO_3 ),
//  digitalRead(GPIO_4 ),
//  digitalRead(GPIO_5 ),
//  digitalRead(GPIO_6 ),
//  digitalRead(GPIO_7 ),
//  digitalRead(GPIO_8 ),
//  digitalRead(GPIO_9 ),
//  digitalRead(GPIO_10),
//  digitalRead(GPIO_11),
//  digitalRead(DIP_1),
//  digitalRead(DIP_2),
//  digitalRead(DIP_3),
//  (analogRead(DIP_4) > 100),
//  digitalRead(PBTN ));

  digitalWrite(GPIO_0 , HIGH);
  digitalWrite(GPIO_1 , HIGH);
  digitalWrite(GPIO_2 , HIGH);
  digitalWrite(GPIO_3 , HIGH);
  digitalWrite(GPIO_4 , HIGH);
  digitalWrite(GPIO_5 , HIGH);
  digitalWrite(GPIO_6 , HIGH);
  digitalWrite(GPIO_7 , HIGH);
  digitalWrite(GPIO_8 , HIGH);
  digitalWrite(GPIO_9 , HIGH);
  digitalWrite(GPIO_10, HIGH);
  digitalWrite(GPIO_11, HIGH);

  //digitalWrite(BUZZ_Pin, HIGH);
  digitalWrite(INJ_Pin, HIGH);

  delay(1);

  //digitalWrite(GPIO_0 , LOW); // TO TEST INJ PIN
  digitalWrite(GPIO_1 , LOW);
  digitalWrite(GPIO_2 , LOW);
  digitalWrite(GPIO_3 , LOW);
  digitalWrite(GPIO_4 , LOW);
  digitalWrite(GPIO_5 , LOW);
  digitalWrite(GPIO_6 , LOW);
  digitalWrite(GPIO_7 , LOW);
  digitalWrite(GPIO_8 , LOW);
  digitalWrite(GPIO_9 , LOW);
  digitalWrite(GPIO_10, LOW);
  digitalWrite(GPIO_11, LOW);

  //digitalWrite(BUZZ_Pin, LOW);
  digitalWrite(INJ_Pin, LOW);

  delay(2);

  Serial.print(str);
}
