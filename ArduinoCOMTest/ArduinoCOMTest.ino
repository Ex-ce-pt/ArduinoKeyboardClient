int counter;

const int min = 0, max = 32;

void setup() {
  Serial.begin(115200);
  counter = min;
}

void loop() {
  char str[3];
  itoa(counter, str, 10);
  Serial.print(str);
  Serial.print('\n');
  counter++;
  if (counter > max) counter = min;
  delay(1000);
}
