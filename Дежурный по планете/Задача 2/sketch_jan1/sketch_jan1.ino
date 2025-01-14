// C++ code
//
const int photoResistor1 = A0; // Аналоговый вход для первого фоторезистора
const int photoResistor2 = A1; // Аналоговый вход для второго фоторезистора

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value1 = analogRead(photoResistor1);
  int value2 = analogRead(photoResistor2);

  // Отправляем значения на светодиоды
  Serial.print("setBrightINT;1;");
  Serial.print(value1);
  Serial.print("#");
  delay(500);

 // Serial.println();

  Serial.print("setBrightINT;2;");
  Serial.print(value2);
  Serial.print("#");
  delay(500);

 // Serial.println();

  // Проверяем условия для запуска анимаций
  if (value1 < 900 || value2 < 900) {
    Serial.print("launchAnimation;separately;5000#");
  } else if (value1 > 900 && value2 > 900) {
    Serial.print("launchAnimation;together;3000#");
  }
 // Serial.println();

  delay(100); // Частота опроса 10Hz
}

