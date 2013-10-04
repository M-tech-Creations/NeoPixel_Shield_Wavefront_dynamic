/* 
	Editor: http://www.visualmicro.com
	        arduino debugger, visual micro +, free forum and wiki
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 101
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define __cplusplus
extern "C" void __cxa_pure_virtual() {;}

//
//
uint16_t SetElement(uint16_t row, uint16_t col);
int propagate_wavefront(int robot_x, int robot_y);
void unpropagate(int robot_x, int robot_y);
int min_surrounding_node_value(int x, int y);
void print_map(void);
void LED_Print(int x,int y,int object);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Users\Mario\Documents\Arduino\Robot_wave_led\Robot_wave_led.ino"
#include "C:\Users\Mario\Documents\Arduino\Robot_wave_led\wave.ino"
