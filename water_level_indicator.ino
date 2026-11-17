
int trigPin = 9;
int echoPin = 10;
int buzzer = 8;

float tankHeight = 20.0;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.println("Water Level Indicator");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Sensor not detected");
    digitalWrite(buzzer, LOW);
    delay(1000);
    return;
  }

  float distance = duration * 0.034 / 2;

  float waterLevel = ((tankHeight - distance) / tankHeight) * 100;

  waterLevel = constrain(waterLevel, 0, 100);

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  if (waterLevel >= 90) {
    Serial.println("Tank is Full");
    digitalWrite(buzzer, HIGH);
  }
  else if (waterLevel <= 10) {
    Serial.println("Water Level is Low");
    digitalWrite(buzzer, HIGH);
  }
  else {
    Serial.println("Water Level is Normal");
    digitalWrite(buzzer, LOW);
  }

  delay(1000);
}
