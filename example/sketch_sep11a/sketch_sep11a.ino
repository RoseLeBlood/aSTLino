#define LED 13
#define DLY 1000

int dly = DLY;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  delay(100);
  
  
}

void loop() {
  if(Serial.available()) {
    dly = Serial.parseInt()
  }
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(dly);
  digitalWrite(LED, LOW);
  delay(dly);
}
