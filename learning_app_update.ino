#define SOUND_SENSOR_PIN 5
#define BUZZER_PIN 2

#define RX_PIN 3 // Define RX pin of HC-05 (not used for ESP32)
#define TX_PIN 1 // Define TX pin of HC-05 (not used for ESP32)

HardwareSerial bluetoothSerial(2); // For ESP32, use Serial2 (GPIO 16: RX, GPIO 17: TX)

void setup() {
  Serial.begin(115200);
  bluetoothSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN); // Initialize hardware serial with custom pins
  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(SOUND_SENSOR_PIN) == HIGH) {
    Serial.println("Sound Detected!");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);

    Serial.println("Enter first number:");
    int num1 = readNumberFromSerial();
    Serial.println(num1);

    Serial.println("Enter second number:");
    int num2 = readNumberFromSerial();
    Serial.println(num2);

    int sum = num1 + num2;

    Serial.print("Sum: ");
    Serial.println(sum);

    // Print numbers and sum over Bluetooth
    bluetoothSerial.print("First number: ");
    bluetoothSerial.print(num1);
    bluetoothSerial.print(", Second number: ");
    bluetoothSerial.print(num2);
    bluetoothSerial.print(", Sum: ");
    bluetoothSerial.println(sum);

    digitalWrite(BUZZER_PIN, LOW);
  }
  else {
    Serial.println("Sound not Detected!");
    delay(2000);
  }
  delay(100);
}

int readNumberFromSerial() {
  while (!Serial.available());
  String input = Serial.readStringUntil('\n');
  return input.toInt();
}
