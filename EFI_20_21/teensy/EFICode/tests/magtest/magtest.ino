#include "Constants.h"
//
char str[500];

void setup() {
  Serial.begin(115200);
  while(!Serial);
  
  // GPIO tests
  pinMode(GPIO_0 , INPUT);
  pinMode(GPIO_1 , INPUT);
  pinMode(GPIO_2 , INPUT);
  pinMode(GPIO_3 , INPUT);
  pinMode(GPIO_4 , INPUT);
  pinMode(GPIO_5 , INPUT);
  pinMode(GPIO_6 , INPUT);
  pinMode(GPIO_7 , INPUT);
  pinMode(GPIO_8 , INPUT);
  pinMode(GPIO_9 , INPUT);
  pinMode(GPIO_10, INPUT);
  pinMode(GPIO_11, INPUT);

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
  sprintf(str, "GPIO: %01i%01i%01i%01i%01i%01i%01i%01i%01i%01i%01i%01i \n DIP: %01i%01i%01i%01i \n BTN: %01i \n",
  digitalRead(GPIO_0 ),
  digitalRead(GPIO_1 ),
  digitalRead(GPIO_2 ),
  digitalRead(GPIO_3 ),
  digitalRead(GPIO_4 ),
  digitalRead(GPIO_5 ),
  digitalRead(GPIO_6 ),
  digitalRead(GPIO_7 ),
  digitalRead(GPIO_8 ),
  digitalRead(GPIO_9 ),
  digitalRead(GPIO_10),
  digitalRead(GPIO_11),
  digitalRead(DIP_1),
  digitalRead(DIP_2),
  digitalRead(DIP_3),
  (analogRead(DIP_4) > 100),
  digitalRead(PBTN ));

  //digitalWrite(BUZZ_Pin, HIGH);
  //digitalWrite(INJ_Pin, HIGH);

  delay(1);

  //digitalWrite(GPIO_0 , LOW); // TO TEST INJ PIN

  //digitalWrite(BUZZ_Pin, LOW);

  delay(2);

  Serial.print(str);
}
