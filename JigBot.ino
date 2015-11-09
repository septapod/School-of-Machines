//Import Servo Library
#include <Servo.h> 

//Declare servo variables
Servo servo01;
Servo servo02;
Servo servo03;

//Declare pin variables
int audioPin = A0; 
int irPin = A1;
int irVal = 0;
int counter=0;
long randomTime=0;
long previousTime = 0;

void setup() {
  //Attach Servo01 to pin ~9.
  servo01.attach(9);
  servo01.write(90);

  servo02.attach(10);
  servo02.write(90);

  servo03.attach(11);
  servo03.write(90);

  randomTime = random(5000, 10000);
  Serial.begin(9600);
}

void loop() {

  //if (millis()/2000 + randomTime>counter){ 

    Serial.print(millis());
    Serial.print(" ");
    Serial.print(previousTime);
    Serial.print(" ");
    Serial.println(randomTime);
 
  if (millis() >= (previousTime + randomTime)) {
    previousTime = millis();
    Serial.println("enter");

    counter++;
    randomTime=random(2000, 5000);

  }



  // Read the value from the sensor (audio):
  int audioValue = 0;

  //Read IR Value
  irVal = analogRead(irPin);

  /* SMOOTHING */
  ////Add together 500 sensor values
  for (int i=0; i<500; i++){

    audioValue += analogRead(audioPin); 
  } 

  ////Find the average of those values (smooths out the reading)
  audioValue = audioValue/500;

  int range = map(irVal, 500, 20, 0, 55 );




  int servoDance01 = map(audioValue, 1, 70, 90-range, 90+range);
  int servoDance02 = map(audioValue, 1, 70, 90+range, 90-range);
 



  if (audioValue <= 3) {

    servo01.write(90);
    servo02.write(90);
    servo03.write(90);

  } 
  else{
      Serial.println(counter);

    if (counter%4 == 0){ 
      Serial.println("opt 1");
      servo01.write(servoDance02);
      servo02.write(servoDance01);
      servo03.write(servoDance01);
    }
    else if (counter%3 == 0){
            Serial.println("opt 2");

      servo01.write(servoDance01);
      servo02.write(servoDance02);
      servo03.write(servoDance02);

    }
    else if (counter%2 == 0){
            Serial.println("opt 3");
      servo01.write(servoDance01);
      servo02.write(servoDance01);
      servo03.write(servoDance02);

    }
    else{
            Serial.println("opt 4");

      servo01.write(servoDance01);
      servo02.write(servoDance02);
      servo03.write(servoDance01);

    }



  }

  /* PRINT FOR DEBUGGING */
  ////Print audio values
  for (int i=0; i< audioValue/5; i++){
    //Serial.print("-");
  }

  //Serial.println(irVal);  


}






