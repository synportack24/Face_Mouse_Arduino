#include <Mouse.h>

//Serial1  = TX 0 | RX 1
//Serial = USB Native | Mouse out

bool mouseInit = false;
int commands[3];

void setup() {
    // put your setup code here, to run once:
    pinMode(2, INPUT);
    Serial1.begin(9600);

    if(digitalRead(2) == HIGH && !mouseInit){
        Mouse.begin();
        mouseInit = true;
    }
  
}

int counter = 0;
void loop() {
    if(Serial1.available() > 0) {
        int commandIndex = 0x01 & counter;
        counter++;

        int value = Serial1.read();

        if(value == '-'){
            action();
        } else 
            commands[commandIndex] = value;
    }
}

void action() {
    // Get values from buffer
    int p1 = commands[0];
    int p2 = (int8_t)commands[1];


    if(p1 != 0 && p2 != 0){
        
        // X or Y movement
        if(p1=='x'){
            MoveMouse(p2, 0);
        } else if (p1 == 'y'){
            MoveMouse(0, p2);
        
        // Right Click
        } else if (p1 == 'r'){
            if(p2 == 'c')
                MouseClick(MOUSE_RIGHT);
            else if(p2 == 'd')
                MouseDown(MOUSE_RIGHT);
            else if(p2 == 'u')
                MouseUp(MOUSE_RIGHT);
        
        // Left Click
        } else if (p1 == 'l'){
            if(p2 == 'c')
                MouseClick(MOUSE_LEFT);
            else if(p2 == 'd')
                MouseDown(MOUSE_LEFT);
            else if(p2 == 'u')
                MouseUp(MOUSE_LEFT);  
        }
    }
    commands[0] = 0;
    commands[1] = 0;
    counter = 0;
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
