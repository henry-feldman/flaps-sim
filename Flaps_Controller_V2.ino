const int potentiometerPin = A0;  // Analog 0: Teensy = 23, T++ = 38
const int minPin = 2;
const int maxPin = 3;
float currentFlapPercent = 0;
int flapAngle = 0;
int previousAnalog = -100;
int flaps;
int min = 275;
int max = 485;
int span = max - min;
const float maxFlapDegrees = 40.0


void setup() {
  Serial.begin(115200);
  Serial.println("Flaps Demo");
  pinMode(potentiometerPin, INPUT);
  pinMode(minPin, INPUT);
  pinMode(maxPin, INPUT);
}

void loop() {
  //read the position of the potentiometer to calculate the absolute position of the shaft/gear
  int analog = analogRead(potentiometerPin);
  //debaounce to remove the noise
  if (analog < previousAnalog - 6 || analog > previousAnalog + 6) {
    flaps = analog / 1023.0;
    previousAnalog = analog;
    //make sure it's not calculating before min (this is hardly a completely rigid system)
    if (analog < min) {
      flapAngle = 0;
    }
    //Similar make sure we didn't flex past the max value
    if (analog > max) {
      flapAngle = 40;
    }
    //assuming we are in a valid location calculate the percentage of the maxFlapDegrees (i.e. 50% of 40 degrees is 20 degrees)
    if (min < analog < max) {
      float distance = analog - min;
      flapAngle = (distance / span) * maxFlapDegrees;
      //debugging printing
    Serial.print("Flap Angle: ");
    Serial.print(flapAngle);
    Serial.println(" degrees");
  }

  //check if the min switch was pressed and reset to current location
  if (digitalRead(minPin)) {
    min = analog;
    span = max - min;
    Serial.print("0 position reset");
  }

  //check if the max pin was pressed and reset to current location
  if (digitalRead(maxPin)) {
    max = analog;
    span = max - min;
    Serial.print("MAx position reset");
  }

}
