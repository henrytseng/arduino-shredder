// IR
const int irRxPin = A5;

// Button pins
const int rwdBtnPin = 10;
const int fwdBtnPin = 11;

// LED
const int powerLedPin = 9;
const int tempLedPin = 8;

// Motor pins
const int rwdMotorPin = 3;
const int fwdMotorPin = 2;

// State
int irState = 0;
int rwdRunState = 0;
int fwdRunState = 0;
int autoRunState = 0;
int autoEnabled = 0;

// Click state
int rwdBtnDown = 0;
int fwdBtnDown = 0;

// Run in fwd for a duration
void runFwd() {
  Serial.println("Request run forward");
  if (!rwdRunState && !autoRunState) {
    Serial.println("Run forward");
    fwdRunState = 1;

    // Duration
    digitalWrite(fwdMotorPin, HIGH);
    delay(3000);
    digitalWrite(fwdMotorPin, LOW);
    fwdRunState = 0;
    Serial.println("Forward complete");
  } else {
    Serial.println("Unable to run forward");
  }
}

// Run in rwd for a duration
void runRwd() {
  Serial.println("Request run rewind");
  if (!fwdRunState && !autoRunState) {
    Serial.println("Run rewind");
    rwdRunState = 1;

    // Duration
    delay(1000);
    digitalWrite(rwdMotorPin, HIGH);
    delay(3000);
    digitalWrite(rwdMotorPin, LOW);
    delay(1000);
    rwdRunState = 0;
    Serial.println("Rewind complete");
  } else {
    Serial.println("Unable to run rewind");
  }
}

// Run in auto mode
void enableAuto() {
  if (autoEnabled == 0) {
    Serial.println("Request on auto");
    if (!fwdRunState && !rwdRunState) {
      Serial.println("Run auto");
      autoEnabled = 1;

      // Turn on light
      digitalWrite(powerLedPin, HIGH);
    } else {
      Serial.println("Unable to run auto");
    }
  }
}

// Stop auto mode
void disableAuto() {
  if (autoEnabled == 1) {
    Serial.println("Auto off");
    digitalWrite(powerLedPin, LOW);
    autoEnabled = 0;
  }
}

// Run in fwd for a duration
void autoStartFwd() {
  Serial.println("Request auto forward");
  if (autoEnabled && !rwdRunState && !fwdRunState) {
    Serial.println("Auto forward");

    // Duration
    autoRunState = 1;
    digitalWrite(fwdMotorPin, HIGH);
    delay(3000);
  } else {
    Serial.println("Unable to auto forward");
  }
}

// Stop auto
void autoStopFwd() {
  if(autoRunState == 1) {
    digitalWrite(fwdMotorPin, LOW);
    autoRunState = 0;
    Serial.println("Auto forward complete");
  }
}

// Setup
void setup() {
  pinMode(rwdBtnPin, INPUT);
  pinMode(fwdBtnPin, INPUT);
  pinMode(irRxPin, INPUT);
  pinMode(powerLedPin, OUTPUT);
  pinMode(tempLedPin, OUTPUT);
  pinMode(rwdMotorPin, OUTPUT);
  pinMode(fwdMotorPin, OUTPUT);

  Serial.begin(115200);
  enableAuto();
}

// Main loop
void loop() {
  int lastIrState = irState;
  irState = min(1000, analogRead(irRxPin)) > 500 ? 1 : 0;
  rwdBtnDown = digitalRead(rwdBtnPin);
  fwdBtnDown = digitalRead(fwdBtnPin);

  // Available
  if (autoRunState == 0) {

    // Rewind
    if (rwdBtnDown == 1) {
      disableAuto();
      runRwd();
      enableAuto();

    // Forward
    } else if (fwdBtnDown == 1) {
      disableAuto();
      runFwd();
      enableAuto();
    }
  }

  // Auto
  if (autoEnabled == 1) {
    if (irState != lastIrState) {
      Serial.print("irState: ");
      Serial.println(irState);
    }

    if (irState == 1) {
      autoStartFwd();
    } else {
      autoStopFwd();
    }
  }

  delay(10);
}
