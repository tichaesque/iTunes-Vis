int grabbing = 0;

void setup() {
  
  pinMode(13, INPUT);
  Keyboard.begin();
  
}

void loop() {
  
  int grabbing = digitalRead(13);
  
  //the user is grabbing with the gloves
  if (grabbing == HIGH) { 
    Keyboard.write('a');
  }
}
