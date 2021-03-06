// 1st program parameters (trace)
unsigned long const CS_WIDTH_A = 50;
unsigned long const CS_TONE_A = 5000;
unsigned long const US_WIDTH_A = 20;
unsigned long const ISI_A = 250;
unsigned long const ITI_LOW_A = 15000;
unsigned long const ITI_HIGH_A = 30000;

// 2nd program parameters (delay)
unsigned long const CS_WIDTH_B = CS_WIDTH_A;
unsigned long const CS_TONE_B = CS_TONE_A;
unsigned long const US_WIDTH_B = US_WIDTH_A;
unsigned long const ISI_B = ISI_A + CS_WIDTH_A;
unsigned long const ITI_LOW_B = ITI_LOW_A;
unsigned long const ITI_HIGH_B = ITI_HIGH_A;


int const TRIALS = 60;

int const CS_PIN = 3, CS_TONE_PIN = 8, US_PIN = 5, SWITCH_PIN = 6, START_PIN = 4;

// CS_TONE_PIN send only square wave. Button on the device may blink in "wrong" time.
// CS_TONE_PIN can be changed to regular pulse.



boolean const DEBUG = false;

int program_num = 0;
int trial_num = 1;
int started = 0;


void setup() {
  
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CS_TONE_PIN, OUTPUT);
  pinMode(US_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(START_PIN, INPUT_PULLUP);

}

void loop() {
  while (true && !started) {
    digitalWrite(CS_PIN, LOW);
    digitalWrite(US_PIN, LOW);
    digitalWrite(CS_TONE_PIN, LOW);
    if (!digitalRead(START_PIN)) {
        started = !started;
        break;
      }
  }
  int program_num = !digitalRead(SWITCH_PIN);
  // Serial.println("Trial number: " + String(trial_num) + ", " + String(millis()));
  program(program_num);
  if (trial_num > 60) {
    while (true) {
      // endless loop
      // make reset button
      digitalWrite(CS_PIN, HIGH);
      if (!digitalRead(START_PIN)) {
        started = !started;
        trial_num = 1;
        break;
      }
    }
  } else {
    trial_num++;
  }
}

void program(int program_num) {
  if (!program_num) {
    // Serial.println("Trace trial start, " + String(millis()));
    trace_cc();
  } else {
    // Serial.println("Delay trial start, " +String(millis()));
    delay_cc();
  }
}

void wait_rand(String name, unsigned long low, unsigned long high) {
  wait(name, random(low, high));
}

void print_time(String name, unsigned long start, unsigned long end) {
  // Serial.println(name + ", " + String(start) + ", " + String(end));
}

void wait(String name, unsigned long width) {
  unsigned long startTime = millis();  
  while ((millis() - startTime) <= width) {
    // wait
  }
  print_time(name, startTime, millis());
}

void pulse(String name, int pin, unsigned long width) {
  digitalWrite(pin, HIGH);
  wait(name, width);
  digitalWrite(pin, LOW);
}

void pulse_tone(String name, int pin, unsigned int freq, unsigned long duration) {
  unsigned long startTime = millis();  
  tone(pin, freq, duration);
  print_time(name, startTime, millis());
}


// 1st program
void trace_cc() {
  wait_rand("ITI_A", ITI_LOW_A, ITI_HIGH_A);
  pulse("CS_A", CS_PIN, CS_WIDTH_A);
  wait("ISI_A", ISI_A);
  pulse("US_A", US_PIN, US_WIDTH_A);
}

// 2st program
void delay_cc() {
  wait_rand("ITI_B", ITI_LOW_B, ITI_HIGH_B);
  digitalWrite(CS_PIN, HIGH);
  wait("ISI_B", ISI_B);
  pulse("US_B", US_PIN, US_WIDTH_B);
  digitalWrite(CS_PIN, LOW);
}

