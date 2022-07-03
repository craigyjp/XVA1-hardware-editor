

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <ST7735_t3.h> // Hardware-specific library
#include <ST7789_t3.h> // Hardware-specific library
#include <st7735_t3_font_Arial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include "SynthParameter.h"
#include "Button.h"
#include "Hardware.h"
#include <MIDI.h>
#include <ShiftRegister74HC595.h>

#define TFT_GREY 0x5AEB
#define MY_ORANGE 0xFBA0
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */

#define SAVE_LED 0
#define SHIFT_LED 1
#define MENU_LED 2
#define ESCAPE_LED 3

// Variable to indicate that an interrupt has occurred
boolean awokeByInterrupt = false;

unsigned long lastTransition[9];
int prevPatchNumber;
int activeShortcut = 0;
bool saveMode = false;

bool shiftButtonPushed = false;
bool mainRotaryButtonPushed = false;

/* function prototypes */

void handleMainEncoder(bool clockwise, int speed);

void initOLEDDisplays();

void pollAllMCPs();

//void IRAM_ATTR interruptCallback();
void interruptCallback();

void displayPatchInfo();

void displayPatchInfo(bool paintItBlack);

void initButtons();

void clearShortcut();

void clearMainScreen();

void initMainScreen();

void initRotaryEncoders();

void rtrim(std::string &s, char c);

void readMainRotaryButton();

void readMainRotaryEncoder();

void handleInterrupt();

void attachInterrupts();

void detachInterrupts();

int getEncoderSpeed(int id);

ShiftRegister74HC595<4> srpanel(28, 29, 30);

void setup() {
  Serial.begin(115200);

  //while the serial stream is not open, do nothing:
  //    while (!Serial);

  Serial.println("\n");
  Serial.println("===================");
  Serial.println("XVA1 User Interface");
  Serial.println("===================\n");

  //MIDI 5 Pin DIN
  MIDI1.begin();
  MIDI1.setHandleProgramChange(myProgramChange);
  Serial.println("MIDI1 In DIN Listening");

  mcp1.begin(0);
  mcp2.begin(1);
  mcp3.begin(2);
  mcp4.begin(3);
  mcp5.begin(4);

  synthesizer.begin();

  initMainScreen();
  clearMainScreen();

  initRotaryEncoders();
  initOLEDDisplays();
  initButtons();

  attachInterrupts();

  synthesizer.selectPatch(1);
  parameterController.setDefaultSection();
  displayPatchInfo();

}

void loop() {
  pollAllMCPs();

  if (awokeByInterrupt) {
    handleInterrupt();
  }
  MIDI1.read();
}

void myProgramChange(byte channel, byte value) {
  synthesizer.selectPatch(value + 1);
  parameterController.setDefaultSection();
  parameterController.clearScreen();
  clearShortcut();
  displayPatchInfo();
}

/**
   The interrupt callback will just signal that an interrupt has occurred.
   All work will be done from the main loop, to avoid watchdog errors
*/


void interruptCallback() {
  awokeByInterrupt = true;
}

void readMainRotaryEncoder() {
  unsigned char result = mainRotaryEncoder.process();
  if (result) {
    int speed = getEncoderSpeed(0);

    bool clockwise = result == DIR_CW;
    if (activeShortcut != 0) {
      bool consumed = parameterController.rotaryEncoderChanged(0, clockwise, 1);
      if (!consumed) {
        handleMainEncoder(clockwise, speed);
      }
    } else {
      handleMainEncoder(clockwise, speed);
    }
  }
}

void rotaryEncoderChanged(bool clockwise, int id) {
  int speed = getEncoderSpeed(id);

  Serial.println("Encoder " + String(id) + ": "
                 + (clockwise ? String("clockwise") : String("counter-clock-wise")) + ", Speed: " + String(speed));

  parameterController.rotaryEncoderChanged(id, clockwise, speed);
}

int getEncoderSpeed(int id) {
  unsigned long now = millis();
  unsigned long revolutionTime = now - lastTransition[id];

  int speed = 1;
  if (revolutionTime < 50) {
    speed = 10;
  } else if (revolutionTime < 125) {
    speed = 5;
  } else if (revolutionTime < 250) {
    speed = 2;
  }

  lastTransition[id] = now;
  return speed;
}

void initRotaryEncoders() {
  for (auto &rotaryEncoder : rotaryEncoders) {
    rotaryEncoder.init();
  }

  mainRotaryEncoder.begin(true);
}

void initMainScreen() {
  tft.init(240, 240);
  tft.setRotation(3);  // 0 & 2 Portrait. 1 & 3 landscape;

}

void initOLEDDisplays() {
  for (int d = 0; d < 8; d++) {
    multiplexer.selectChannel(d);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.setTextWrap(false);
    display.clearDisplay();
    display.display();
  }
}

void initButtons() {
  for (auto &button : allButtons) {
    button->begin();
  }

  pinMode(MAIN_ROTARY_BTN_PIN, INPUT_PULLUP);
}

void handleInterrupt() {
  // Disable interrupts while handling them
  detachInterrupts();

  readMainRotaryButton();
  readMainRotaryEncoder();

  // Enable interrupts again
  awokeByInterrupt = false;
  attachInterrupts();
}

void attachInterrupts() {
  attachInterrupt(MAIN_ROTARY_BTN_PIN, interruptCallback, CHANGE);
  attachInterrupt(MAIN_ROTARY_ENCODER_PIN_A, interruptCallback, CHANGE);
  attachInterrupt(MAIN_ROTARY_ENCODER_PIN_B, interruptCallback, CHANGE);
}

void detachInterrupts() {
  detachInterrupt(MAIN_ROTARY_BTN_PIN);
  detachInterrupt(MAIN_ROTARY_ENCODER_PIN_A);
  detachInterrupt(MAIN_ROTARY_ENCODER_PIN_B);
}

void handleMainEncoder(bool clockwise, int speed) {
  int currentPatchNumber = synthesizer.getPatchNumber();
  int oldValue = currentPatchNumber;

  if (clockwise) {
    if (currentPatchNumber < 128) {
      currentPatchNumber += speed;
      if (currentPatchNumber > 128) {
        currentPatchNumber = 128;
      }
    }
  } else {
    if (currentPatchNumber > 1) {
      currentPatchNumber -= speed;
      if (currentPatchNumber < 1) {
        currentPatchNumber = 1;
      }
    }
  }

  Serial.print("Selecting patch: ");
  Serial.println(currentPatchNumber);
  if (!saveMode)
  {
    Serial.print("Loading the patch: ");
    Serial.println(currentPatchNumber);
    if (currentPatchNumber != oldValue) {
      synthesizer.selectPatch(currentPatchNumber);
      clearShortcut();
      parameterController.setDefaultSection();
      displayPatchInfo();
    }
  }
  if (saveMode)
  {
    Serial.print("Scroll through patches: ");
    Serial.println(currentPatchNumber);
    if (currentPatchNumber != oldValue) {
      synthesizer.changePatch(currentPatchNumber);
      //clearShortcut();
      //parameterController.setDefaultSection();
      displayPatchInfo();
    }
  }

}

void displayPatchInfo() {
  displayPatchInfo(false);
}

void rtrim(std::string &s, char c) {

  if (s.empty())
    return;

  std::string::iterator p;
  for (p = s.end(); p != s.begin() && *--p == c;);

  if (*p != c)
    p++;

  s.erase(p, s.end());
}

void displayPatchInfo(bool paintItBlack) {
  int currentPatchNumber = synthesizer.getPatchNumber();

  tft.setTextColor(paintItBlack ? MY_ORANGE : TFT_BLACK);

  tft.setTextSize(2);
  tft.setTextDatum(1);
  tft.drawString("XVA1 Synthesizer", 119, 4);
  tft.setTextColor((paintItBlack) ? TFT_BLACK : TFT_WHITE);
  tft.drawString("Patch", 119, 40);
  if (!paintItBlack) {
    tft.setTextColor(MY_ORANGE, TFT_BLACK);
  }

  tft.setTextSize(5);
  tft.setTextColor(TFT_BLACK);
  tft.drawNumber(prevPatchNumber, 119, 67);
  tft.setTextColor(MY_ORANGE, TFT_BLACK);
  tft.drawNumber(currentPatchNumber, 119, 67);
  prevPatchNumber = currentPatchNumber;


  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.setTextSize(1);
  tft.fillRect(0, 114, 240, 26, TFT_BLACK);
  if (!paintItBlack) {
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
  }
  string name = synthesizer.getPatchName();
  rtrim(name, ' ');
  tft.setTextSize(2);
  tft.setTextDatum(1);
  tft.drawString(name.c_str(), 119, 120);
  tft.setTextDatum(0);
  tft.setTextSize(1);
}

void clearMainScreen() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.fillRect(0, 0, 240, 26, MY_ORANGE);
}

void pollAllMCPs() {
  // Read all MCPs and feed the input to each encoder and shortcut button.
  // This is more efficient than reading one pin state at a time
  for (auto &mcp : allMCPs) {
    uint16_t gpioAB = mcp->readGPIOAB();

    for (auto &rotaryEncoder : rotaryEncoders) {
      // Only feed this in the encoder if this is coming from the correct MCP
      if (rotaryEncoder.getMCP() == mcp) {
        rotaryEncoder.feedInput(gpioAB);
      }
    }

    for (auto &button : allButtons) {
      if (button->getMcp() == mcp) {
        button->feedInput(gpioAB);
      }
    }
  }
}

void shortcutButtonChanged(Button *btn, bool released) {
  Serial.print("Shortcut-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  if (!released) {
    if (activeShortcut > 0) {
      parameterController.clearScreen();
    }

    activeShortcut = (shiftButtonPushed && btn->id <= 4) ? btn->id + 8 : btn->id;

    Serial.print("Active Shortcut: ");
    Serial.println(activeShortcut);
    for (auto &shortcutButton : shortcutButtons) {
      shortcutButton->setLED(shortcutButton->id == btn->id);
    }

    displayPatchInfo(true);

    parameterController.setSection(activeShortcut);
  }
}

void mainButtonChanged(Button *btn, bool released) {
  Serial.print("Main-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  switch (btn->id) {
    case SHIFT_BUTTON:
      shiftButtonPushed = !released;
      break;
    case SAVE_BUTTON:
      if (!released) {
        saveMode = !saveMode;
        if (saveMode)
        {
          if (activeShortcut > 0)
          {
            parameterController.clearScreen();
            clearShortcut();
            displayPatchInfo();
          }
          srpanel.set(SAVE_LED, HIGH);
          tft.setTextSize(2);
          tft.setTextDatum(2);
          tft.fillRect(0, 160, 240, 26, TFT_VIOLET);
          tft.setTextColor(TFT_WHITE);
          tft.drawString(" Select Location", 120, 164);
          parameterController.setDefaultSection();
        }
        if (!saveMode)
        {
          tft.setTextSize(2);
          tft.setTextDatum(1);
          tft.fillRect(0, 160, 240, 26, TFT_RED);
          tft.setTextColor(TFT_WHITE);
          tft.drawString("Writing Patch", 119, 164);
          int currentPatchNumber = synthesizer.getPatchNumber();
          synthesizer.savePatchData(currentPatchNumber);
          delay(1000);
          tft.fillRect(0, 160, 240, 26, TFT_BLACK);
          srpanel.set(SAVE_LED, LOW);
        }
      }
      break;
    case ESC_BUTTON:
      if (!released) {
        if (activeShortcut > 0) {
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
        }
        if (saveMode)
        {
          saveMode = !saveMode;
          tft.fillRect(0, 160, 240, 26, TFT_BLACK);
          parameterController.clearScreen();
          clearShortcut();
          displayPatchInfo();
          srpanel.set(SAVE_LED, LOW);
        }

        parameterController.setDefaultSection();
      }
  }
}

void clearShortcut() {
  activeShortcut = 0;
  for (auto &shortcutButton : shortcutButtons) {
    shortcutButton->setLED(false);
  }
}

void readMainRotaryButton() {
  bool mainRotaryButtonState = (digitalRead(MAIN_ROTARY_BTN_PIN) == LOW);
  if (mainRotaryButtonState != mainRotaryButtonPushed) {
    mainRotaryButtonPushed = mainRotaryButtonState;
    mainRotaryButtonChanged(!mainRotaryButtonPushed);
  }
}

void rotaryButtonChanged(Button *btn, bool released) {
  Serial.print("Rotary-button #");
  Serial.print(btn->id);
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");
}

void upOrDownButtonChanged(Button *btn, bool released) {
  Serial.print((btn->id == UP_BUTTON) ? "Up" : "Down");
  Serial.print("-button");
  Serial.print(" ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

  if (!released) {
    if (btn->id == UP_BUTTON) {
      parameterController.upButtonTapped();
    } else {
      parameterController.downButtonTapped();
    }
  }
}

void mainRotaryButtonChanged(bool released) {
  Serial.print("MAIN-Rotary-button ");
  Serial.println((released) ? "RELEASED" : "PRESSED");

}
