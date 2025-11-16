String cmd = "";
bool loggedIn = false;
struct Schedule {
  char device;
  bool action;
  unsigned long triggerTime;
  bool active;
};
Schedule tasks[4];
int getPin(char d) {
  switch (d) {
    case 'A': return 2;
    case 'B': return 3;
    case 'C': return 4;
    case 'D': return 5;
    default: return -1;
  }
}
void setup() {
  Serial.begin(9600);
  for (int p = 2; p <= 5; p++) {
    pinMode(p, OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    tasks[i].active = false;
  }
  Serial.println("Home Automation System Ready!");
  Serial.println("Login using: LOGIN XXXX (where XXXX is default password)");
}
void loop() {
  checkSchedules();
  if (Serial.available()) {
    cmd = Serial.readStringUntil('\n');
    cmd.trim();
    cmd.toUpperCase();
    processCommand(cmd);
  }
}
void processCommand(String s) {
  if (!loggedIn) {
    if (s.startsWith("LOGIN ")) {
      String pwd = s.substring(6);
      if (pwd == "1234") {
        loggedIn = true;
        Serial.println("Login Successful!");
        Serial.println("Available commands: ON X (where X=A/B/C/D, e.g., ON A, ON B), OFF X (similar to ON command), STATUS (to check ON/OFF status of the appliances/LEDs), SCHEDULE A ON AFTER X (where X is time in seconds, e.g., 'SCHEDULE A ON AFTER 5' turns A ON after 5seconds");
      } else {
        Serial.println("Wrong Password!");
      }
    } else {
      Serial.println("Please login first using: LOGIN XXXX");
    }
    return;
  }
  if (s == "STATUS") {
    printStatus();
    return;
  }
  if (s.startsWith("ON ") || s.startsWith("OFF ")) {
    handleOnOff(s);
    return;
  }
  if (s.startsWith("SCHEDULE ")) {
    handleSchedule(s);
    return;
  }
  Serial.println("Invalid Command!");
}
void handleOnOff(String s) {
  String action = s.substring(0, s.indexOf(' '));
  char device = s.charAt(s.length() - 1);
  int pin = getPin(device);
  if (pin == -1) {
    Serial.println("Invalid device! Use A/B/C/D");
    return;
  }
  if (action == "ON") {
    digitalWrite(pin, HIGH);
    Serial.print(device); Serial.println(" turned ON.");
  } else {
    digitalWrite(pin, LOW);
    Serial.print(device); Serial.println(" turned OFF.");
  }
}
void printStatus() {
  Serial.println("---- DEVICE STATUS ----");
  printDeviceStatus('A');
  printDeviceStatus('B');
  printDeviceStatus('C');
  printDeviceStatus('D');
}
void printDeviceStatus(char d) {
  int p = getPin(d);
  String state = digitalRead(p) ? "ON" : "OFF";
  Serial.print(d);
  Serial.print(": ");
  Serial.println(state);
}
void handleSchedule(String s) {
  int pos1 = s.indexOf(' ', 9);
  char device = s.charAt(9);
  int pin = getPin(device);
  if (pin == -1) {
    Serial.println("Invalid device for scheduling!");
    return;
  }
  int actionStart = pos1 + 1;
  int actionEnd = s.indexOf(' ', actionStart);
  String action = s.substring(actionStart, actionEnd);
  int afterIndex = s.indexOf("AFTER ");
  if (afterIndex == -1) {
    Serial.println("Invalid schedule format!");
    return;
  }
  int delaySec = s.substring(afterIndex + 6).toInt(); 
  if (delaySec <= 0) {
    Serial.println("Invalid time!");
    return;
  }
  for (int i = 0; i < 4; i++) {
    if (!tasks[i].active) {
      tasks[i].device = device;
      tasks[i].action = (action == "ON");
      tasks[i].triggerTime = millis() + delaySec * 1000UL;
      tasks[i].active = true;
      Serial.print("Scheduled ");
      Serial.print(device);
      Serial.print(" to turn ");
      Serial.print(action);
      Serial.print(" after ");
      Serial.print(delaySec);
      Serial.println(" seconds.");
      return;
    }
  }
  Serial.println("No free schedule slots!");
}
void checkSchedules() {
  unsigned long now = millis();
  for (int i = 0; i < 4; i++) {
    if (tasks[i].active && now >= tasks[i].triggerTime) {
      int pin = getPin(tasks[i].device);
      digitalWrite(pin, tasks[i].action ? HIGH : LOW);
      Serial.print("SCHEDULE EXECUTED: ");
      Serial.print(tasks[i].device);
      Serial.print(" turned ");
      Serial.println(tasks[i].action ? "ON" : "OFF");
      tasks[i].active = false;
    }
  }
}
