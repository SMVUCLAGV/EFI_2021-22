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

  ser_init();
  Serial.println("ser initialized");
}

void loop () {
  //Serial.print(ser_test());
}
