#include "ser.h"
#include "reg.h"

void setup () {
  pinMode(31, OUTPUT);
  digitalWrite(31, 1);

  Serial.begin(115200);
  while(!Serial);
  Serial.println("test");

  // reg.h tests

  // test _RB_GET
  {
    char t = 0xfa;
    int temp = 0;
    for(int i = 0; i < 8; i++)
      temp += _RB_GET(&t, i) * (1 << i);
    if(temp == t)
      Serial.println("Pass 1");
    else
      Serial.println("Fail 1");
  }

  // test _RB_SET
  {
    int cnt = 0;
    for(int i = 1; i < 8; i++) {
      char t = 1;
      _RB_SET(&t, i);
      if(t == ((1 << i) + 1))
        cnt++;
    }
    if(cnt == 7)
      Serial.println("Pass 2");
    else
      Serial.println("Fail 2");
  }

  // test _RB_CLR
  {
    int cnt = 0;
    char t;
    for(int i = 0; i < 8; i++) {
      t = 0xff;
      _RB_CLR(&t, i);
      if((t ^ (1 << i)) == 0xff)
        cnt++;
    }
    if(cnt == 8)
      Serial.println("Pass 3");
    else
      Serial.println("Fail 3");
  }
  
  // test _RW_SET
  // test _RW_GET

  Serial.println("ser initialized");
}

uint32_t test1 = 0;
uint32_t test2 = 0;
void loop () {
  test2 = ser_test();
  Serial.print(" txlevel2: ");
  Serial.print(test2);
  Serial.print(" Sending at: ");
  Serial.println(millis());
  delay(500);
  ser_write("hi\n", 1);
  test1 = ser_test();
  //ser_write("hi", 0);
  Serial.print("txlevel1: ");
  Serial.print(test1);
  delay(500);
}
