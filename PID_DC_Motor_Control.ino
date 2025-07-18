// --- Define Pins ---
#define ENCODER1_A 2
#define ENCODER1_B 3
#define ENCODER2_A 4
#define ENCODER2_B 5

#define MOTOR1_IN1 6
#define MOTOR1_IN2 7
#define MOTOR1_PWM 10

#define MOTOR2_IN1 8
#define MOTOR2_IN2 9
#define MOTOR2_PWM 11

#define BTN_SETPOINT_INC 12
#define BTN_SETPOINT_DEC 13

#define LED_TARGET_REACHED  A2  // Optional: indicator LED

// --- Globals ---
volatile long encoder1_count = 0, encoder2_count = 0;
long setpoint1 = 1000, setpoint2 = 1000; // Target encoder counts
float Kp = 2.0, Ki = 0.5, Kd = 0.1;

// --- PID Variables ---
float integral1 = 0, prev_err1 = 0;
float integral2 = 0, prev_err2 = 0;
unsigned long prevTime = 0;
const float dt = 0.05;  // 50ms cycle time (same as loop interval)

const float integral_limit = 500;
const int deadband = 5; // Error threshold for considering setpoint reached

// --- Button Debounce ---
unsigned long lastButtonPressInc = 0;
unsigned long lastButtonPressDec = 0;
const unsigned long debounceDelay = 200; // ms

// --- Encoder ISRs ---
void encoder1ISR() {
  if (digitalRead(ENCODER1_B) == HIGH) encoder1_count++;
  else encoder1_count--;
}

void encoder2ISR() {
  if (digitalRead(ENCODER2_B) == HIGH) encoder2_count++;
  else encoder2_count--;
}

// --- Setup ---
void setup() {
  Serial.begin(115200);
  pinMode(ENCODER1_A, INPUT_PULLUP); pinMode(ENCODER1_B, INPUT_PULLUP);
  pinMode(ENCODER2_A, INPUT_PULLUP); pinMode(ENCODER2_B, INPUT_PULLUP);
  pinMode(MOTOR1_IN1, OUTPUT); pinMode(MOTOR1_IN2, OUTPUT); pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT); pinMode(MOTOR2_IN2, OUTPUT); pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(BTN_SETPOINT_INC, INPUT_PULLUP); pinMode(BTN_SETPOINT_DEC, INPUT_PULLUP);

  // Optional: LED to indicate "both motors at target"
  pinMode(LED_TARGET_REACHED, OUTPUT);
  digitalWrite(LED_TARGET_REACHED, LOW);

  attachInterrupt(digitalPinToInterrupt(ENCODER1_A), encoder1ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER2_A), encoder2ISR, RISING);

  Serial.println("Dual DC Motor PID Position Control");
}

// --- Utility: Set Motor ---
void setMotor(int pwmPin, int in1, int in2, int speed) {
  // Soft stop logic: if speed == 0, fully disable H-bridge outputs
  if (speed > 0) {
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    analogWrite(pwmPin, min(speed,255));
  } else if (speed < 0) {
    digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    analogWrite(pwmPin, min(-speed,255));
  } else {
    digitalWrite(in1, LOW); digitalWrite(in2, LOW);
    analogWrite(pwmPin, 0);
  }
}

// --- Main Control Loop ---
void loop() {
  unsigned long currentTime = millis();
  if (currentTime - prevTime >= dt * 1000) {
    prevTime = currentTime;

    // --- BUTTON HANDLING (non-blocking debounce) ---
    if (digitalRead(BTN_SETPOINT_INC) == LOW && 
        currentTime - lastButtonPressInc > debounceDelay) {
      setpoint1 += 100; setpoint2 += 100;
      lastButtonPressInc = currentTime;
    }
    if (digitalRead(BTN_SETPOINT_DEC) == LOW &&
        currentTime - lastButtonPressDec > debounceDelay) {
      setpoint1 -= 100; setpoint2 -= 100;
      lastButtonPressDec = currentTime;
    }

    // --- SERIAL SETPOINT INPUT ---
    if (Serial.available()) {
      String cmd = Serial.readStringUntil('\n');
      if (cmd.startsWith("S")) { // Format: S1000,1000
        int idx = cmd.indexOf(',');
        if(idx > 1) { // valid input check
          setpoint1 = cmd.substring(1, idx).toInt();
          setpoint2 = cmd.substring(idx+1).toInt();
        }
      }
    }

    // --- PID for Motor 1 ---
    float err1 = setpoint1 - encoder1_count;
    integral1 += err1 * dt;
    integral1 = constrain(integral1, -integral_limit, integral_limit);
    float deriv1 = (err1 - prev_err1) / dt;
    int pid_out1 = Kp*err1 + Ki*integral1 + Kd*deriv1;
    prev_err1 = err1;
    if (abs(err1) < deadband) pid_out1 = 0;

    // --- PID for Motor 2 ---
    float err2 = setpoint2 - encoder2_count;
    integral2 += err2 * dt;
    integral2 = constrain(integral2, -integral_limit, integral_limit);
    float deriv2 = (err2 - prev_err2) / dt;
    int pid_out2 = Kp*err2 + Ki*integral2 + Kd*deriv2;
    prev_err2 = err2;
    if (abs(err2) < deadband) pid_out2 = 0;

    // --- Command Motors ---
    setMotor(MOTOR1_PWM, MOTOR1_IN1, MOTOR1_IN2, pid_out1);
    setMotor(MOTOR2_PWM, MOTOR2_IN1, MOTOR2_IN2, pid_out2);

    // --- Target Reached Indicator / Soft Stop ---
    bool bothAtTarget = (abs(err1) < deadband && abs(err2) < deadband);
    digitalWrite(LED_TARGET_REACHED, bothAtTarget ? HIGH : LOW);
    static bool wasAtTarget = false;
    if (bothAtTarget && !wasAtTarget) {
      Serial.println("Both motors at target position!");
      wasAtTarget = true;
    } else if (!bothAtTarget) {
      wasAtTarget = false;
    }

    // --- Output to Serial Monitor ---
    Serial.print("Enc1: "); Serial.print(encoder1_count);
    Serial.print(" Set1: "); Serial.print(setpoint1);
    Serial.print(" Err1: "); Serial.print(err1);
    Serial.print(" | Enc2: "); Serial.print(encoder2_count);
    Serial.print(" Set2: "); Serial.print(setpoint2);
    Serial.print(" Err2: "); Serial.print(err2);
    Serial.print(" | At Target: "); Serial.println(bothAtTarget ? "YES" : "NO");
  }
}
