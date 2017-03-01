#include <CapacitiveSensor.h>


const int sendPin = 4,pinCount=8;
CapacitiveSensor cs[pinCount];

unsigned long csSum;

void setup() {
  Serial.begin(9600);
  
  csSum = 0;
  for(int i=0;i<pinCount;++i)
  {
    cs[i] = CapacitiveSensor(sendPin,sendPin+i+1);
  }
}

void loop() {
  CSread(&cs[0], 0);
  CSread(&cs[1], 1);
  CSread(&cs[2], 2);
}

void CSread(CapacitiveSensor* cs,const int index) {
    long value = cs->capacitiveSensor(80); //a: Sensor resolution is set to 80
  if (value > 100) { //b: Arbitrary number
    csSum += value;
    //Serial.println(value); 
    if (csSum >= 3800) //c: This value is the threshold, a High value means it takes longer to trigger
    {
      Serial.print("Button: ");
      Serial.println(index);
      if (csSum > 0) { csSum = 0; } //Reset
      cs->reset_CS_AutoCal(); //Stops readings
    }
  } else {
    csSum = 0; //Timeout caused by bad readings
  }
}
