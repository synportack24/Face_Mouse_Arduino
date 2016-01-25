#include <Mouse.h>

//Serial  = TX 0 | RX 1
//Serial1 = USB Native | Mouse out

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(2) == HIGH){
    Mouse.begin();
  }

  int p1 = 0;
  int p2 = 0;
  if(Serial.available() > 0){
    p1 = Serial.read();
  }
  if(Serial.available() > 0){
    p2 = Serial.read();
  }

  if(p1 != 0 && p2 != 0){
    if(p1=='x'){
      MoveMouse(p2, 0);
    } else if (p1 == 'y'){
      MoveMouse(0, p2);
    } else if (p1 == 'r'){
      if(p2 == 'c')
        MouseClick(MOUSE_RIGHT);
      else if(p2 == 'd')
        MouseDown(MOUSE_RIGHT);
      else if(p2 == 'u')
        MouseUp(MOUSE_RIGHT);
    } else if (p1 == 'l'){
      if(p2 == 'c')
        MouseClick(MOUSE_LEFT);
      else if(p2 == 'd')
        MouseDown(MOUSE_LEFT);
      else if(p2 == 'u')
        MouseUp(MOUSE_LEFT);  
    }
  }

}


void MoveMouse(int8_t x, int8_t y){
  Mouse.move(x,y);
}

void MouseClick(uint8_t MouseButton){
  Mouse.press(MouseButton);
  delay(5);
  Mouse.release(MouseButton);
}

void MouseDown(uint8_t MouseButton){
  Mouse.press(MouseButton);
}

void MouseUp(uint8_t MouseButton){
  Mouse.release(MouseButton);
}
