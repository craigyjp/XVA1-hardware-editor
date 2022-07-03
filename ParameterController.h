//
// Created by André Mathlener on 08/04/2021.
//

#ifndef XVA1USERINTERFACE_PARAMETERCONTROLLER_H
#define XVA1USERINTERFACE_PARAMETERCONTROLLER_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h> 
#include <SPI.h>
#include <ST7735_t3.h> // Hardware-specific library
#include <ST7789_t3.h> // Hardware-specific library
#include <st7735_t3_font_Arial.h>
#include "Synthesizer.h"
#include "Multiplexer.h"
#include "Section.h"
#include "LEDButton.h"
#include "SectionFactory.h"

#define TFT_GREY 0x5AEB
#define MY_ORANGE 0xFBA0
// Default color definitions
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

class ParameterController {
private:
    Synthesizer *synthesizer;
    Multiplexer *multiplexer;
    ST7789_t3 *tft;
    Adafruit_SSD1306 *display;
    LEDButton *upButton;
    LEDButton *downButton;

    const int LINE_HEIGHT = 25;

    Section section = SectionFactory().createDefaultSection();
    int parameterIndices[16];

    int currentPageNumber = 0;
    int currentSubSectionNumber = 0;
    Section subSection = Section("empty");

    bool shouldShowEnvelopes = false;
    const uint16_t envelopeColors[3] = { TFT_BLUE, TFT_MAGENTA, TFT_YELLOW };
//    TaskHandle_t displayEnvelopesTaskHandle = nullptr;

    void clearParameters();

    void setActivePage(int pageNumber);

    void setActiveSubSection(int pageNumber);

    void displayActivePage();

    void displayParameters();

    void handleParameterChange(int index, bool clockwise, int speed);

    void displayTwinParameters(int index1, int index2, int displayNumber);

    void displayTwinParameters(string title1, string value1, string title2, string value2, int displayNumber);

    void drawCenteredText(string buf, int x, int y);

    string getDisplayValue(int parameterIndex);

    Section *getSubSection();

    void displaySubSections();
    void displaySubSections(bool paintItBlack);

    void clearCurrentSubsection();

    void displayCurrentSubsection();

    void clearEnvelopes();

    void displayEnvelopes();

    void displayEnvelope(const Envelope &envelope, uint16_t color);

    static void displayEnvelopesTask(void *parameter);

public:
    ParameterController(Synthesizer *synthesizer, Multiplexer *multiplexer, ST7789_t3 *tft, Adafruit_SSD1306 *display,
                        LEDButton *upButton, LEDButton *downButton);

    void setSection(int sectionNumber);
    void setSection(int sectionNumber, bool showSubSections);

    void setDefaultSection();

    bool rotaryEncoderChanged(int id, bool clockwise, int speed);

    bool rotaryEncoderButtonChanged(int id, bool released);

    void upButtonTapped();

    void downButtonTapped();

    void clearScreen();

    Section createSection(int sectionNumber);

    string to_string(int value);
};


#endif //XVA1USERINTERFACE_PARAMETERCONTROLLER_H
