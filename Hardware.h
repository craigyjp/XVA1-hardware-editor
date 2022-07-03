//
// Created by André Mathlener on 05/04/2021.
//

#include <SPI.h>
#include <ST7735_t3.h> // Hardware-specific library
#include <ST7789_t3.h> // Hardware-specific library
#include <st7735_t3_font_Arial.h>
#include <MIDI.h>

#ifndef XVA1USERINTERFACE_HARDWARE_H
#define XVA1USERINTERFACE_HARDWARE_H

#include "Rotary.h"
#include "RotaryEncOverMCP.h"
#include "Button.h"
#include "Multiplexer.h"
#include "Synthesizer.h"
#include "ParameterController.h"

#define MAIN_ROTARY_BUTTON  0
#define MENU_BUTTON         1
#define SAVE_BUTTON         2
#define ESC_BUTTON          3
#define SHIFT_BUTTON        4

#define UP_BUTTON           1
#define DOWN_BUTTON         2

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     (-1) // Reset pin # (or -1 if sharing Arduino reset pin)

#define MAIN_ROTARY_ENCODER_PIN_A 5
#define MAIN_ROTARY_ENCODER_PIN_B 4
#define MAIN_ROTARY_BTN_PIN 6


//MIDI 5 Pin DIN
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
//MIDI 5 Pin DIN
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI2);
//MIDI 5 Pin DIN
MIDI_CREATE_INSTANCE(HardwareSerial, Serial4, MIDI3);

// Pins for MCP23017
#define GPA0 0
#define GPA1 1
#define GPA2 2
#define GPA3 3
#define GPA4 4
#define GPA5 5
#define GPA6 6
#define GPA7 7
#define GPB0 8
#define GPB1 9
#define GPB2 10
#define GPB3 11
#define GPB4 12
#define GPB5 13
#define GPB6 14
#define GPB7 15

/* Function prototypes */

void mainRotaryButtonChanged(bool released);

void mainButtonChanged(Button *btn, bool released);

void shortcutButtonChanged(Button *btn, bool released);

void rotaryButtonChanged(Button *btn, bool released);

void upOrDownButtonChanged(Button *btn, bool released);

void rotaryEncoderChanged(bool clockwise, int id);

// TCA9548A Multiplexer
Multiplexer multiplexer = Multiplexer(0x70);

// I2C MCP23017 GPIO expanders
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;

//Array of pointers of all MCPs
Adafruit_MCP23017 *allMCPs[] = {&mcp1, &mcp2, &mcp3, &mcp4, &mcp5};


// OLED display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

  #define TFT_CS         2
  #define TFT_RST        8 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         3
  #define TFT_MOSI      11  //a12
  #define TFT_SCK       13  //a13
  
ST7789_t3 tft = ST7789_t3(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCK, TFT_RST);


Rotary mainRotaryEncoder = Rotary(MAIN_ROTARY_ENCODER_PIN_A, MAIN_ROTARY_ENCODER_PIN_B);

/* Array of all rotary encoders and their pins */
RotaryEncOverMCP rotaryEncoders[] = {
        RotaryEncOverMCP(&mcp1, GPA1, GPA0, &rotaryEncoderChanged, 1),
        RotaryEncOverMCP(&mcp1, GPA4, GPA3, &rotaryEncoderChanged, 2),
        RotaryEncOverMCP(&mcp1, GPB1, GPB0, &rotaryEncoderChanged, 3),
        RotaryEncOverMCP(&mcp1, GPB4, GPB5, &rotaryEncoderChanged, 4),
        RotaryEncOverMCP(&mcp2, GPA1, GPA0, &rotaryEncoderChanged, 5),
        RotaryEncOverMCP(&mcp2, GPA4, GPA3, &rotaryEncoderChanged, 6),
        RotaryEncOverMCP(&mcp2, GPB1, GPB0, &rotaryEncoderChanged, 7),
        RotaryEncOverMCP(&mcp2, GPB4, GPB3, &rotaryEncoderChanged, 8),
        RotaryEncOverMCP(&mcp4, GPA1, GPA0, &rotaryEncoderChanged, 9),
        RotaryEncOverMCP(&mcp4, GPA4, GPA3, &rotaryEncoderChanged, 10),
        RotaryEncOverMCP(&mcp4, GPB1, GPB0, &rotaryEncoderChanged, 11),
        RotaryEncOverMCP(&mcp4, GPB4, GPB3, &rotaryEncoderChanged, 12),
        RotaryEncOverMCP(&mcp5, GPA1, GPA0, &rotaryEncoderChanged, 13),
        RotaryEncOverMCP(&mcp5, GPA4, GPA3, &rotaryEncoderChanged, 14),
        RotaryEncOverMCP(&mcp5, GPB1, GPB0, &rotaryEncoderChanged, 15),
        RotaryEncOverMCP(&mcp5, GPB4, GPB3, &rotaryEncoderChanged, 16)
};

Button menuButton = Button(&mcp3, GPB4, MENU_BUTTON, &mainButtonChanged);
Button saveButton = Button(&mcp3, GPB5, SAVE_BUTTON, &mainButtonChanged);
Button escButton = Button(&mcp3, GPB3, ESC_BUTTON, &mainButtonChanged);
Button shiftButton = Button(&mcp3, GPB2, SHIFT_BUTTON, &mainButtonChanged);

Button *mainButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
};

LEDButton shortcutButton1 = LEDButton(&mcp1, GPA6, GPA7, 1, &shortcutButtonChanged);
LEDButton shortcutButton2 = LEDButton(&mcp1, GPB6, GPB7, 2, &shortcutButtonChanged);
LEDButton shortcutButton3 = LEDButton(&mcp2, GPA6, GPA7, 3, &shortcutButtonChanged);
LEDButton shortcutButton4 = LEDButton(&mcp2, GPB6, GPB7, 4, &shortcutButtonChanged);
LEDButton shortcutButton5 = LEDButton(&mcp4, GPA6, GPA7, 5, &shortcutButtonChanged);
LEDButton shortcutButton6 = LEDButton(&mcp4, GPB6, GPB7, 6, &shortcutButtonChanged);
LEDButton shortcutButton7 = LEDButton(&mcp5, GPA6, GPA7, 7, &shortcutButtonChanged);
LEDButton shortcutButton8 = LEDButton(&mcp5, GPB6, GPB7, 8, &shortcutButtonChanged);
LEDButton shortcutButton9 = LEDButton(&mcp3, GPA0, GPA1, 9, &shortcutButtonChanged);
LEDButton shortcutButton10 = LEDButton(&mcp3, GPA2, GPA3, 10, &shortcutButtonChanged);
LEDButton shortcutButton11 = LEDButton(&mcp3, GPA4, GPA5, 11, &shortcutButtonChanged);
//LEDButton saveButton1 = LEDButton(&mcp3, GPB5, GPB6, SAVE_BUTTON, &shortcutButtonChanged);

LEDButton *shortcutButtons[] = {
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8,
        &shortcutButton9, &shortcutButton10, &shortcutButton11
};

Button rotaryButton1 = Button(&mcp1, GPA2, 1, &rotaryButtonChanged);
Button rotaryButton2 = Button(&mcp1, GPA5, 2, &rotaryButtonChanged);
Button rotaryButton3 = Button(&mcp1, GPB2, 3, &rotaryButtonChanged);
Button rotaryButton4 = Button(&mcp1, GPB3, 4, &rotaryButtonChanged);
Button rotaryButton5 = Button(&mcp2, GPA2, 5, &rotaryButtonChanged);
Button rotaryButton6 = Button(&mcp2, GPA5, 6, &rotaryButtonChanged);
Button rotaryButton7 = Button(&mcp2, GPB2, 7, &rotaryButtonChanged);
Button rotaryButton8 = Button(&mcp2, GPB5, 8, &rotaryButtonChanged);
Button rotaryButton9 = Button(&mcp4, GPA2, 9, &rotaryButtonChanged);
Button rotaryButton10 = Button(&mcp4, GPA5, 10, &rotaryButtonChanged);
Button rotaryButton11 = Button(&mcp4, GPB2, 11, &rotaryButtonChanged);
Button rotaryButton12 = Button(&mcp4, GPB5, 12, &rotaryButtonChanged);
Button rotaryButton13 = Button(&mcp5, GPA2, 13, &rotaryButtonChanged);
Button rotaryButton14 = Button(&mcp5, GPA5, 14, &rotaryButtonChanged);
Button rotaryButton15 = Button(&mcp5, GPB2, 15, &rotaryButtonChanged);
Button rotaryButton16 = Button(&mcp5, GPB5, 16, &rotaryButtonChanged);

LEDButton upButton = LEDButton(&mcp3, GPB0, GPB1, 1, &upOrDownButtonChanged);
LEDButton downButton = LEDButton(&mcp3, GPA6, GPA7, 2, &upOrDownButtonChanged);

Button *allButtons[] = {
        &menuButton, &saveButton, &escButton, &shiftButton,
        &shortcutButton1, &shortcutButton2, &shortcutButton3, &shortcutButton4,
        &shortcutButton5, &shortcutButton6, &shortcutButton7, &shortcutButton8,
        &shortcutButton9, &shortcutButton10, &shortcutButton11,
        &rotaryButton1, &rotaryButton2, &rotaryButton3, &rotaryButton4,
        &rotaryButton5, &rotaryButton6, &rotaryButton7, &rotaryButton8,
        &rotaryButton9, &rotaryButton10, &rotaryButton11, &rotaryButton12,
        &rotaryButton13, &rotaryButton14, &rotaryButton15, &rotaryButton16,
        &upButton, &downButton
};


Synthesizer synthesizer;
ParameterController parameterController = ParameterController(&synthesizer, &multiplexer, &tft, &display, &upButton, &downButton);

#endif //XVA1USERINTERFACE_HARDWARE_H
