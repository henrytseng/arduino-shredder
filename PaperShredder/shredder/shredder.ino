// Button pins
const int rwdBtnPin = 10;
const int fwdBtnPin = 11;
const int autoBtnPin = 12;

// LED
const int ledPin = 13;

// Motor relay pins
const int rwdMotorPin = 3;
const int fwdMotorPin = 2;

// State
int rwdState = 0;
int fwdState = 0;
int autoState = 0;

// Run in fwd for a duration
void runFwd() {
  Serial.println("Request run forward");
  if (!rwdState && !autoState) {
    Serial.println("Run forward");
    fwdState = 1;

    // Caution
    digitalWrite(fwdMotorPin, LOW);
    delay(50);

    // Duration
    digitalWrite(fwdMotorPin, HIGH);
    delay(3000);
    digitalWrite(fwdMotorPin, LOW);
    fwdState = 0;
    Serial.println("Forward complete");
  }
}

// Run in rwd for a duration
void runRwd() {
  Serial.println("Request run rewind");
  if (!fwdState && !autoState) {
    Serial.println("Run rewind");
    rwdState = 1;

    // Caution
    digitalWrite(fwdMotorPin, LOW);
    delay(50);

    // Duration
    digitalWrite(rwdMotorPin, HIGH);
    delay(3000);
    digitalWrite(rwdMotorPin, LOW);
    rwdState = 0;
    Serial.println("Rewind complete");
  }
}

// Run in auto mode
void onAuto() {
  Serial.println("Request run auto");
  if (!fwdState && !rwdState) {
    Serial.println("Run auto");
    autoState = 1;

    // Caution
    digitalWrite(rwdMotorPin, LOW);
    delay(50);

    // Turn on light
    digitalWrite(ledPin, HIGH);
  }
}

// Stop auto mode
void offAuto() {
  Serial.println("Request stop auto");
  if (!fwdState && !rwdState) {
    Serial.println("Stop auto");

    // Turn off light
    digitalWrite(ledPin, LOW);

    autoState = 0;
  }
}

// Setup
void setup() {
  pinMode(rwdMotorPin, OUTPUT);
  pinMode(fwdMotorPin, OUTPUT);
  pinMode(rwdBtnPin, INPUT);
  pinMode(fwdBtnPin, INPUT);
  pinMode(autoBtnPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

int rwdBtn = 0;
int fwdBtn = 0;
int autoBtn = 0;

int lastRwdBtn = 0;
int lastFwdBtn = 0;
int lastAutoBtn = 0;

// Main loop
void loop() {
  // Setup button states
  lastRwdBtn = rwdBtn;
  lastFwdBtn = fwdBtn;
  lastAutoBtn = autoBtn;
  rwdBtn = digitalRead(rwdBtnPin);
  fwdBtn = digitalRead(fwdBtnPin);
  autoBtn = digitalRead(autoBtnPin);

  // Reverse
  if (lastRwdBtn != rwdBtn) {

  // Forward
  } else if (lastFwdBtn != fwdBtn) {

  // Auto
  } else if (lastAutoBtn != autoBtn) {

  }




  // compare the buttonState to its previous state
  if (autoState != lastAutoState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  // turns on the LED every four button pushes by checking the modulo of the
  // button push counter. the modulo function gives you the remainder of the
  // division of two numbers:
  if (buttonPushCounter % 2 == 0) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(motorPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(motorPin, LOW);
  }

}
