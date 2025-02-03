#include <TaskManager.h>

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Tasks.add([] {
          PORTD ^= 1 << 3;
    })->startIntervalUsec(10000);        
    Tasks.add([] {
          PORTD ^= 1 << 5;
    })->startIntervalUsec(1000);      
    Tasks.add([] {
          PORTD ^= 1 << 6;
    })->startIntervalUsec(500);      
    Tasks.add([] {
          PORTB ^= 1 << 1;
    })->startIntervalUsec(100);   
    Tasks.add([] {
          PORTB ^= 1 << 2;
    })->startIntervalUsec(50);    
    
}

void loop() {
  Tasks.update();
}
