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
unsigned long const ISI_B = ISI_A;
unsigned long const ITI_LOW_B = ITI_LOW_A;
unsigned long const ITI_HIGH_B = ITI_HIGH_A;


int const TRIALS = 60;

int const CS_PIN = 3, CS_TONE_PIN = 8, US_PIN = 5, SWITCH_PIN = 12;



boolean const DEBUG = false;

int program_num = 1;
int trial_num = 1;


void setup() {
  
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  pinMode(CS_TONE_PIN, OUTPUT);
  pinMode(US_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);

}

void loop() {
  //int program_num = digitalRead(SWITCH_PIN);
  program(program_num);
  if (trial_num > 60) {
    while (true) {
      // endless loop
      // make reset button
      digitalWrite(CS_PIN, HIGH);
    }
  } else {
    trial_num++;
  }
}

void program(int program_num) {
  if (!program_num) {
    trace_cc();
  } else {
    delay_cc();
  }
}

void wait_rand(unsigned long low, unsigned long high) {
  unsigned long startTime = millis();  
  while ((millis() - startTime) <= random(low, high)) {
    // wait
  }
}

void wait(unsigned long width) {
  unsigned long startTime = millis();  
  while ((millis() - startTime) <= width) {
    // wait
  }
}

void pulse(int pin, unsigned long width) {
  digitalWrite(pin, HIGH);
  unsigned long startTime = millis();
  while ((millis() - startTime) <= width) {
    // wait
  }
  digitalWrite(pin, LOW);
}

void pulse_tone(int pin, unsigned int freq, unsigned long duration) {
  tone(pin, freq, duration);
}


// 1st program
void trace_cc() {
  wait_rand(ITI_LOW_A, ITI_HIGH_A);
  pulse(CS_PIN, CS_WIDTH_A);
  wait(ISI_A);
  pulse(US_PIN, US_WIDTH_A);
  //pulse_tone(CS_TONE_PIN, CS_TONE_A, CS_WIDTH_A);
}

// 2nd program
void delay_cc() {
  wait_rand(ITI_LOW_B, ITI_HIGH_B);
  digitalWrite(CS_PIN, HIGH);
  wait(CS_WIDTH_B + ISI_B - US_WIDTH_B);
  pulse(US_PIN, US_WIDTH_B);
  digitalWrite(CS_PIN, LOW);
}

