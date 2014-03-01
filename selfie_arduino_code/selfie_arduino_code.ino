void setup() {
  
  pinMode(9, INPUT);
  Keyboard.begin();
}

void loop() {
  
  int grabbing = digitalRead(9);
  
  //the user is grabbing with the gloves
  if (grabbing == HIGH) { 
    Keyboard.press(' '); 
  }
  
  else {
    Keyboard.releaseAll();
  }
}
