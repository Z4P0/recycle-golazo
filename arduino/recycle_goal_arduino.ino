/*
  Recycling Goal
  
  place the device in any box/container and make it interactive
  it plays sound whenever you score a goal
*/


const int motionSensor = A0;
long distance;
long distance1;
const int vibrationSensor = A1;


// audio stuff
const int speaker = 8;
const int pingNote = 262;
const int pingDuration = 4;









void setup()
{
  Serial.begin(9600);
  
  // set pinModes
  pinMode(motionSensor, INPUT);
  Serial.println("========================================");
  Serial.println("RECYCLE GOAL");
  Serial.println("========================================");
  
  ping();
  for(int i = 0; i < 20; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" sensor ready");
  delay(50);
  calibrate();
  ping();
}



void calibrate()
{
  /* 2 second calibration where we set the distance */
  int delayTime = 100;
  long previousValue = 0;
  
  for(int i = 0; i < 8; i++) {

    long reading = analogRead(motionSensor)/2;
    
    if (reading == previousValue) distance = reading;
    if (reading > distance) distance = reading;
    
    previousValue = reading;
    delay(delayTime);
  }
}

void ping()
{
  int noteDuration = 1000/pingDuration;

  tone(speaker, pingNote, noteDuration);
  delay(noteDuration * 1.30); // to distinguish the notes, set a minimum time between them.

  noTone(speaker); // stop the tone playing:  
}












void loop()
{
  int reading = analogRead(motionSensor)/2;

  if (reading < distance || reading > distance) {
    Serial.println("GOAL");
    ping();
    calibrate();
  }

  delay(150); 
}


















// convenience functions
// ===================================
void turnOn(int led) {digitalWrite(led, HIGH);}
void turnOff(int led) {digitalWrite(led, LOW);}
