int ledPins[3] = {11, 9, 10}; // Array for LED pins
int rgb[3];                  // Array to store RGB values

void setup() {
  Serial.begin(115200);      // Start serial communication
  for (int i = 0; i < 3; i++) {
    pinMode(ledPins[i], OUTPUT); // Set each LED pin as output
  }
}

void setColor(int R, int G, int B) {
  analogWrite(ledPins[0], R);    // Set red LED brightness
  analogWrite(ledPins[1], G);    // Set green LED brightness
  analogWrite(ledPins[2], B);     // Set blue LED brightness
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Read input until newline
    if (splitRGB(input)) { // Validate and set the RGB color
      setColor(rgb[0], rgb[1], rgb[2]);
      Serial.print("Set color to - Red: "); 
      Serial.print(rgb[0]);
      Serial.print(", Green: "); 
      Serial.print(rgb[1]);
      Serial.print(", Blue: "); 
      Serial.println(rgb[2]); // Print the RGB values
    } else {
      Serial.println("Error: Enter three numbers (0-255) separated by commas.");
      setColor(0, 0, 0);
    }
  }
}

bool splitRGB(String input) {
  int i = 0;
  char buffer[32]; // Create a buffer to hold the string (make sure it's large enough)
  input.toCharArray(buffer, sizeof(buffer)); // Convert String to char array
  
  // Use strtok to tokenize the input string
  char* token = strtok(buffer, ",");
  while (token && i < 3) {
    int value = atoi(token); // Convert token to integer
    if (value < 0 || value > 255) return false; // Validate value
    rgb[i++] = value; // Store value in array
    token = strtok(NULL, ","); // Get the next token
  }
  return (i == 3); //Return true if exactly 3 values were parsed
}
