const int TRIG_PIN = 12;
const int ECHO_PIN = 13;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  pinMode(3 , OUTPUT);
  
}

void loop()
{
   long duration, distanceCm, distanceIn;
   if (Serial.available() > 0) {
        char command = Serial.read();

        // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);
        duration = pulseIn(ECHO_PIN,HIGH);

        // convert the time into a distance
        distanceCm = duration / 29.1 / 2 ;
        distanceIn = duration / 74 / 2;

        if (distanceCm <= 0){
          Serial.println("Out of range");
        }
        
        if (distanceCm < 200){
          digitalWrite(3 , HIGH);
          delay(1000);

        }
        
        else{
          digitalWrite(3 , LOW);
        }
        if (command == '1'){
          digitalWrite(3 , HIGH);
          delay(1000);
        }
        if( command == '0'){
          digitalWrite(3 , LOW);
        }
        
        //delay(100);
   }
}