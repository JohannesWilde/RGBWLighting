
//// NeoPixel test program showing use of the WHITE channel for RGBW
//// pixels only (won't look correct on regular RGB NeoPixel strips).

//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
// #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
//#endif

//#include "NeoPixelPatterns.hpp"
//#include "RelaisDriver.hpp"

//// Which pin on the Arduino is connected to the NeoPixels?
//// On a Trinket or Gemma we suggest changing this to 1:
//#define LED_PIN     27

//// How many NeoPixels are attached to the Arduino?
//#define LED_COUNT  10

//// NeoPixel brightness, 0 (min) to 255 (max)
//#define BRIGHTNESS 50

//// Declare our NeoPixel strip object:
//static Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
//// Argument 1 = Number of pixels in NeoPixel strip
//// Argument 2 = Arduino pin number (most are valid)
//// Argument 3 = Pixel type flags, add together as needed:
////   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
////   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
////   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
////   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
////   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//void setup() {
//  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
//  // Any other board, you can remove this part (but no harm leaving it):
//#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
//  clock_prescale_set(clock_div_1);
//#endif
//  // END of Trinket-specific code.

//  Driver::RelaisDriver<25, Driver::RelaisStateOn> powerRelais(Driver::RelaisStateOff);

//  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
//  strip.show();            // Turn OFF all pixels ASAP
//  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)

//  unsigned long const relaisTogglePeriod = 5000;
//  unsigned long const startTime = millis();

//  unsigned long latestRelaisToggleTime = startTime - relaisTogglePeriod;
//  powerRelais.turnOn();
//  while (true)
//  {
//      unsigned long const curTime = millis();
//      unsigned long deltaTime = (curTime - startTime);

//      if ((curTime - latestRelaisToggleTime) >= relaisTogglePeriod)
//      {
//          powerRelais.toggle();
//          latestRelaisToggleTime = curTime;
//      }

//      double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
//      NeoPixelPatterns::updateStrip<LED_COUNT, NeoPixelPatterns::brightnessFunctionMountain>(strip, Adafruit_NeoPixel::Color(0, 0, 0, 255), deltaTimeDouble);

//  }
//}

//void loop()
//{
//    /* intentionally empty */
//}

#include <Arduino.h>

void fail();
void startup();
void centertitle(const char *s);
void centerprint(const char *s, int y);
void drawCrossHair(int x, int y, uint16_t color);
void report();
void calibrate(int x, int y, int i, String msg);
void readCoordinates();


// TouchScreen_Calibr_native for MCUFRIEND UNO Display Shields
// adapted by David Prentice
// for Adafruit's <TouchScreen.h> Resistive Touch Screen Library
// from Henning Karlsen's original UTouch_Calibration program.
// Many Thanks.

#define PORTRAIT  0
#define LANDSCAPE 1
#define USE_XPT2046   0
#define USE_LOCAL_KBV 0

#define TOUCH_ORIENTATION  PORTRAIT

#if defined(USB_PID) && USB_PID == 0x804E // Arduino M0 Native
#define Serial SerialUSB
#endif

#define SWAP(x, y) { int t = x; x = y; y = t; }

#define TITLE "TouchScreen.h GFX Calibration"
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

// MCUFRIEND UNO shield shares pins with the TFT.
#if defined(ESP32)
int XP = 27, YP = 4, XM = 15, YM = 14;  //most common configuration
#else
//int XP = 6, YP = A1, XM = A2, YM = 7;  //most common configuration
//int XP = 7, YP = A2, XM = A1, YM = 6;  //next common configuration
int XP=8,XM=A2,YP=A3,YM=9; //320x480 ID=0x9486
const int TS_LEFT=126,TS_RT=912,TS_TOP=957,TS_BOT=89;
//int XP=PB7,XM=PA6,YP=PA7,YM=PB6; //BLUEPILL must have Analog for YP, XM
#endif
#if USE_LOCAL_KBV
#include "TouchScreen_kbv.h"         //my hacked version
#define TouchScreen TouchScreen_kbv
#define TSPoint     TSPoint_kbv
#else
#include <TouchScreen.h>         //Adafruit Library
#endif
TouchScreen ts(XP, YP, XM, YM, 300);   //re-initialised after diagnose
TSPoint tp;                            //global point

void readResistiveTouch(void)
{
    tp = ts.getPoint();
    pinMode(YP, OUTPUT);      //restore shared pins
    pinMode(XM, OUTPUT);
    //digitalWrite(YP, HIGH);  //because TFT control pins
    //digitalWrite(XM, HIGH);
    //    Serial.println("tp.x=" + String(tp.x) + ", tp.y=" + String(tp.y) + ", tp.z =" + String(tp.z));
}

uint16_t readID(void) {
    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9486;
    return ID;
}
#define TFT_BEGIN()  tft.begin(ID)

#define WHITE 0xFFFF
#define RED   0xF800
#define BLUE  0x001F
#define GREEN 0x07E0
#define BLACK 0x0000

//#define GRAY  0x2408        //un-highlighted cross-hair
#define GRAY      BLUE     //idle cross-hair colour
#define GRAY_DONE RED      //finished cross-hair

bool ISPRESSED(void)
{
    // .kbv this was too sensitive !!
    // now touch has to be stable for 50ms
    int count = 0;
    bool state, oldstate;
    while (count < 10) {
        readResistiveTouch();
        state = tp.z > 200;     //ADJUST THIS VALUE TO SUIT YOUR SCREEN e.g. 20 ... 250
        if (state == oldstate) count++;
        else count = 0;
        oldstate = state;
        delay(5);
    }
    return oldstate;
}

uint32_t cx, cy, cz;
uint32_t rx[8], ry[8];
int32_t clx, crx, cty, cby;
float px, py;
int dispx, dispy, text_y_center, swapxy;
uint32_t calx, caly, cals;

char *Aval(int pin)
{
    static char buf[2][10], cnt;
    cnt = !cnt;
#if defined(ESP32)
    sprintf(buf[cnt], "%d", pin);
#else
    sprintf(buf[cnt], "A%d", pin - A0);
#endif
    return buf[cnt];
}

void showpins(int A, int D, int value, const char *msg)
{
    char buf[40];
    sprintf(buf, "%s (%s, D%d) = %d", msg, Aval(A), D, value);
    Serial.println(buf);
}

void bofe(char *buf)
{
    tft.println(buf);
    Serial.println(buf);
}

#if USE_XPT2046 == 0
bool diagnose_pins()
{
    uint8_t i, j, Apins[2], Dpins[2], found = 0;
    uint16_t value, Values[2];

    Serial.println(F("Making all control and bus pins INPUT_PULLUP"));
    Serial.println(F("Typical 30k Analog pullup with corresponding pin"));
    Serial.println(F("would read low when digital is written LOW"));
    Serial.println(F("e.g. reads ~25 for 300R X direction"));
    Serial.println(F("e.g. reads ~30 for 500R Y direction"));
    Serial.println(F(""));

    for (i = A0; i < A5; i++) pinMode(i, INPUT_PULLUP);
    for (i = 2; i < 10; i++) pinMode(i, INPUT_PULLUP);
    for (i = A0; i < A4; i++) {
        pinMode(i, INPUT_PULLUP);
        for (j = 5; j < 10; j++) {
            pinMode(j, OUTPUT);
            digitalWrite(j, LOW);
            value = analogRead(i);               // ignore first reading
            value = analogRead(i);
            if (value < 100 && value > 0) {
                showpins(i, j, value, "Testing :");
                if (found < 2) {
                    Apins[found] = i;
                    Dpins[found] = j;
                    Values[found] = value;
                }
                found++;
            }
            pinMode(j, INPUT_PULLUP);
        }
        pinMode(i, INPUT_PULLUP);
    }
    if (found == 2) {
        int idx = Values[0] < Values[1];
        /*
                Serial.println(F("Diagnosing as:-"));
                for (i = 0; i < 2; i++) {
                    showpins(Apins[i], Dpins[i], Values[i],
                             (Values[i] < Values[!i]) ? "XM,XP: " : "YP,YM: ");
                }
        */
        XM = Apins[!idx]; XP = Dpins[!idx]; YP = Apins[idx]; YM = Dpins[idx];
        ts = TouchScreen(XP, YP, XM, YM, 300);    //re-initialise with pins
        return true;                              //success
    }
    if (found == 0) Serial.println(F("MISSING TOUCHSCREEN"));
    //else Serial.println(F("BROKEN TOUCHSCREEN"));
    return false;
}
#endif

#define pinTftBacklight 44

void setup()
{
    pinMode(pinTftBacklight, OUTPUT);
    analogWrite(pinTftBacklight, 255);
    char buf[40];
    uint16_t ID = readID();
    TFT_BEGIN();
    tft.fillScreen(TFT_NAVY);
    tft.println("Waiting for Serial");
    delay(1000);
    Serial.begin(9600);
    while (!Serial);
    tft.fillScreen(TFT_BLUE);
    Serial.println(TITLE);
    bool ret = true;
#if USE_XPT2046 || defined(__arm__) || defined(ESP32)
    Serial.println(F("Not possible to diagnose Touch pins on ARM or ESP32"));
#else
    ret = diagnose_pins();  //destroys TFT pin modes
    TFT_BEGIN();            //start again
#endif
    tft.setRotation(TOUCH_ORIENTATION);
    dispx = tft.width();
    dispy = tft.height();
    text_y_center = (dispy / 2) - 6;
    sprintf(buf, "ID = 0x%04x", ID);
    Serial.println(buf);
    if (ret == false) {
        centerprint("BROKEN TOUCHSCREEN", text_y_center);
        fail();
    }
}

void loop()
{
    startup();

    int x, y, cnt, idx = 0;
    tft.fillScreen(BLACK);
    for (x = 10, cnt = 0; x < dispx; x += (dispx - 20) / 2) {
        for (y = 10; y < dispy; y += (dispy - 20) / 2) {
            if (++cnt != 5) drawCrossHair(x, y, GRAY);
        }
    }
    centerprint("***********", text_y_center - 12);
    centerprint("***********", text_y_center + 12);
    for (x = 10, cnt = 0; x < dispx; x += (dispx - 20) / 2) {
        for (y = 10; y < dispy; y += (dispy - 20) / 2) {
            if (++cnt != 5) calibrate(x, y, idx++, " X, Y, Pressure"); // F(" X, Y, Pressure"));
        }
    }

    cals = (long(dispx - 1) << 12) + (dispy - 1);
    swapxy = rx[2] - rx[0];
    //else swapxy = ry[2] - ry[0];
    swapxy = (swapxy < -400 || swapxy > 400);
    if (swapxy != 0) {
        clx = (ry[0] + ry[1] + ry[2]); //rotate 90
        crx = (ry[5] + ry[6] + ry[7]);
        cty = (rx[0] + rx[3] + rx[5]);
        cby = (rx[2] + rx[4] + rx[7]);
    } else {
        clx = (rx[0] + rx[1] + rx[2]); //regular
        crx = (rx[5] + rx[6] + rx[7]);
        cty = (ry[0] + ry[3] + ry[5]);
        cby = (ry[2] + ry[4] + ry[7]);
    }
    clx /= 3;
    crx /= 3;
    cty /= 3;
    cby /= 3;
    px = float(crx - clx) / (dispx - 20);
    py = float(cby - cty) / (dispy - 20);
    //  px = 0;
    clx -= px * 10;
    crx += px * 10;
    cty -= py * 10;
    cby += py * 10;

    calx = (long(clx) << 14) + long(crx);
    caly = (long(cty) << 14) + long(cby);
    if (swapxy)
        cals |= (1L << 31);

    report();          // report results
    while (true) {}    // tread water
}

void readCoordinates()
{
    int iter = 5000;
    int failcount = 0;
    int cnt = 0;
    uint32_t tx = 0;
    uint32_t ty = 0;
    uint32_t tz = 0;
    bool OK = false;

    while (OK == false)
    {
        centerprint("*  PRESS  *", text_y_center);
        while (ISPRESSED() == false) {}
        centerprint("*  HOLD!  *", text_y_center);
        cnt = 0;
        iter = 400;
        do
        {
            readResistiveTouch();
            if (tp.z > 200)  //.kbv
            {
                tx += tp.x;
                ty += tp.y;
                tz += tp.z;
                cnt++;
            }
            else
                failcount++;
        } while ((cnt < iter) && (failcount < 10000));
        if (cnt >= iter)
        {
            OK = true;
        }
        else
        {
            tx = 0;
            ty = 0;
            tz = 0;
            cnt = 0;
        }
        if (failcount >= 10000)
            fail();
    }

    cx = tx / iter;
    cy = ty / iter;
    cz = tz / iter;
}

void calibrate(int x, int y, int i, String msg)
{
    drawCrossHair(x, y, WHITE);
    readCoordinates();
    centerprint("* RELEASE *", text_y_center);
    drawCrossHair(x, y, GRAY_DONE);
    rx[i] = cx;
    ry[i] = cy;
    char buf[40];
    sprintf(buf, "\r\ncx=%ld cy=%ld cz=%ld %s", cx, cy, cz, msg.c_str());
    Serial.print(buf);
    while (ISPRESSED() == true) {}
}

void report()
{
    uint16_t TS_LEFT, TS_RT, TS_TOP, TS_BOT, TS_WID, TS_HT, TS_SWAP;
    int16_t tmp;
    char buf[60];
    centertitle(TITLE);

    tft.println(F("To use the new calibration"));
    tft.println(F("settings you must map the values"));
    tft.println(F("from Point p = ts.getPoint() e.g. "));
    tft.println(F("x = map(p.x, LEFT, RT, 0, tft.width());"));
    tft.println(F("y = map(p.y, TOP, BOT, 0, tft.height());"));
    tft.println(F("swap p.x and p.y if diff ORIENTATION"));

    //.kbv show human values
    TS_LEFT = (calx >> 14) & 0x3FFF;
    TS_RT   = (calx >>  0) & 0x3FFF;
    TS_TOP  = (caly >> 14) & 0x3FFF;
    TS_BOT  = (caly >>  0) & 0x3FFF;
    TS_WID  = ((cals >> 12) & 0x0FFF) + 1;
    TS_HT   = ((cals >>  0) & 0x0FFF) + 1;
    TS_SWAP = (cals >> 31);
    if (TOUCH_ORIENTATION == LANDSCAPE) { //always show PORTRAIT first
        tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;
        tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;
    }
    sprintf(buf, "\n\n*** COPY-PASTE from Serial Terminal:");
    bofe(buf);
    bool ts_landscape = (TOUCH_ORIENTATION == LANDSCAPE) ^ swapxy;
#if (USE_XPT2046)
    sprintf(buf, "const int TS_LANDSCAPE=%d; //%s", ts_landscape, TITLE);
    bofe(buf);
#else
    if (ts_landscape) {
        SWAP(XM, YP);
        SWAP(XP, YM);
        SWAP(TS_LEFT, TS_RT);
        SWAP(TS_TOP, TS_BOT);
    }
    sprintf(buf, "const int XP=%d,XM=%s,YP=%s,YM=%d; //%dx%d ID=0x%04X",
            XP, Aval(XM), Aval(YP), YM, TS_WID, TS_HT, readID());
    Serial.println(buf);
    sprintf(buf, "\nTouch Pin Wiring XP=%d XM=%s YP=%s YM=%d",
            XP, Aval(XM), Aval(YP), YM);
    tft.println(buf);
#endif
    sprintf(buf, "const int TS_LEFT=%d,TS_RT=%d,TS_TOP=%d,TS_BOT=%d;",
            TS_LEFT, TS_RT, TS_TOP, TS_BOT);
    Serial.println(buf);

#if !defined(ARDUINO_AVR_LEONARDO)
    for (int orient = 0; orient < 2; orient++) {
        sprintf(buf, "\n%s CALIBRATION     %d x %d",
                orient ? "LANDSCAPE" : "PORTRAIT ", TS_WID, TS_HT);
        bofe(buf);
        sprintf(buf, "x = map(p.%s, LEFT=%d, RT=%d, 0, %d)",
                orient ? "y" : "x", TS_LEFT, TS_RT, TS_WID);
        bofe(buf);
        sprintf(buf, "y = map(p.%s, TOP=%d, BOT=%d, 0, %d)",
                orient ? "x" : "y", TS_TOP, TS_BOT, TS_HT);
        bofe(buf);
        tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;
        tmp = TS_WID, TS_WID = TS_HT, TS_HT = tmp;
    }

    int16_t x_range = TS_LEFT - TS_RT, y_range = TS_TOP - TS_BOT;
    if (abs(x_range) > 500 && abs(y_range) > 650) //LANDSCAPE
        return;
    sprintf(buf, "\n*** UNUSUAL CALIBRATION RANGES %d %d", x_range, y_range);
    bofe(buf);
#endif
}

void drawCrossHair(int x, int y, uint16_t color)
{
    tft.drawRect(x - 10, y - 10, 20, 20, color);
    tft.drawLine(x - 5, y, x + 5, y, color);
    tft.drawLine(x, y - 5, x, y + 5, color);
}

void centerprint(const char *s, int y)
{
    int len = strlen(s) * 6;
    tft.setTextColor(WHITE, RED);
    tft.setCursor((dispx - len) / 2, y);
    tft.print(s);
}

void centertitle(const char *s)
{
    tft.fillScreen(BLACK);
    tft.fillRect(0, 0, dispx, 14, RED);
    tft.fillRect(0, 14, dispx, 1, WHITE);
    centerprint(s, 1);
    tft.setCursor(0, 30);
    tft.setTextColor(WHITE, BLACK);
}

void startup()
{
    centertitle(TITLE);

    tft.println(F("#define NUMSAMPLES 3 in Library\n"));
    tft.println(F("Use a stylus or something"));
    tft.println(F("similar to touch as close"));
    tft.println(F("to the center of the WHITE"));
    tft.println(F("crosshair.  Keep holding"));
    tft.println(F("until crosshair turns RED."));
    tft.println(F("Repeat for all crosshairs.\n"));
    tft.println(F("Report can be pasted from Serial\n"));
    tft.println(F("Touch screen to continue"));

    while (ISPRESSED() == false) {}
    while (ISPRESSED() == true) {}
    //    waitForTouch();
}

void fail()
{
    centertitle("Touch Calibration FAILED");

    tft.println(F("Unable to read the position"));
    tft.println(F("of the press. This is a"));
    tft.println(F("hardware issue and can not"));
    tft.println(F("be corrected in software."));
    tft.println(F("check XP, XM pins with a multimeter"));
    tft.println(F("check YP, YM pins with a multimeter"));
    tft.println(F("should be about 300 ohms"));

    while (true) {};
}








//// UTFT_Demo_480x320
//// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
//// web: http://www.RinkyDinkElectronics.com/
////
//// This program is a demo of how to use most of the functions
//// of the library with a supported display modules.
////
//// This demo was made for modules with a screen resolution
//// of 480x320 pixels.
////
//// This program requires the UTFT library.
////

////################################################
//// GLUE class that implements the UTFT API
//// replace UTFT include and constructor statements
//// remove UTFT font declaration e.g. SmallFont
////################################################

//#include <UTFTGLUE.h>              //use GLUE class and constructor
//UTFTGLUE myGLCD(0,A2,A1,A3,A4,A0); //all dummy args

//// Declare which fonts we will be using
////extern uint8_t SmallFont[];      //GLUE defines as GFXFont ref

//// Set the pins to the correct ones for your development shield
//// ------------------------------------------------------------
//// Arduino Uno / 2009:
//// -------------------
//// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
//// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
////
//// Arduino Mega:
//// -------------------
//// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
//// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
////
//// Remember to change the model parameter to suit your display module!
////UTFT myGLCD(CTE32HR,38,39,40,41);

//void setup()
//{
//  randomSeed(analogRead(0));

//// Setup the LCD
//  myGLCD.InitLCD();
//  myGLCD.setFont(SmallFont);
//}

//void loop()
//{
//  int buf[478];
//  int x, x2;
//  int y, y2;
//  int r;

//// Clear the screen and draw the frame
//  myGLCD.clrScr();

//  myGLCD.setColor(255, 0, 0);
//  myGLCD.fillRect(0, 0, 479, 13);
//  myGLCD.setColor(64, 64, 64);
//  myGLCD.fillRect(0, 306, 479, 319);
//  myGLCD.setColor(255, 255, 255);
//  myGLCD.setBackColor(255, 0, 0);
//  myGLCD.print("* Universal Color TFT Display Library *", CENTER, 1);
//  myGLCD.setBackColor(64, 64, 64);
//  myGLCD.setColor(255,255,0);
//  myGLCD.print("<http://www.RinkyDinkElectronics.com/>", CENTER, 307);

//  myGLCD.setColor(0, 0, 255);
//  myGLCD.drawRect(0, 14, 479, 305);

//// Draw crosshairs
//  myGLCD.setColor(0, 0, 255);
//  myGLCD.setBackColor(0, 0, 0);
//  myGLCD.drawLine(239, 15, 239, 304);
//  myGLCD.drawLine(1, 159, 478, 159);
//  for (int i=9; i<470; i+=10)
//    myGLCD.drawLine(i, 157, i, 161);
//  for (int i=19; i<220; i+=10)
//    myGLCD.drawLine(237, i, 241, i);

//// Draw sin-, cos- and tan-lines
//  myGLCD.setColor(0,255,255);
//  myGLCD.print("Sin", 5, 15);
//  for (int i=1; i<478; i++)
//  {
//    myGLCD.drawPixel(i,159+(sin(((i*1.13)*3.14)/180)*95));
//  }

//  myGLCD.setColor(255,0,0);
//  myGLCD.print("Cos", 5, 27);
//  for (int i=1; i<478; i++)
//  {
//    myGLCD.drawPixel(i,159+(cos(((i*1.13)*3.14)/180)*95));
//  }

//  myGLCD.setColor(255,255,0);
//  myGLCD.print("Tan", 5, 39);
//  for (int i=1; i<478; i++)
//  {
//    myGLCD.drawPixel(i,159+(tan(((i*1.13)*3.14)/180)));
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);
//  myGLCD.setColor(0, 0, 255);
//  myGLCD.setBackColor(0, 0, 0);
//  myGLCD.drawLine(239, 15, 239, 304);
//  myGLCD.drawLine(1, 159, 478, 159);

//// Draw a moving sinewave
//  x=1;
//  for (int i=1; i<(478*15); i++)
//  {
//    x++;
//    if (x==479)
//      x=1;
//    if (i>479)
//    {
//      if ((x==239)||(buf[x-1]==159))
//        myGLCD.setColor(0,0,255);
//      else
//        myGLCD.setColor(0,0,0);
//      myGLCD.drawPixel(x,buf[x-1]);
//    }
//    myGLCD.setColor(0,255,255);
//    y=159+(sin(((i*0.7)*3.14)/180)*(90-(i / 100)));
//    myGLCD.drawPixel(x,y);
//    buf[x-1]=y;
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some filled rectangles
//  for (int i=1; i<6; i++)
//  {
//    switch (i)
//    {
//      case 1:
//        myGLCD.setColor(255,0,255);
//        break;
//      case 2:
//        myGLCD.setColor(255,0,0);
//        break;
//      case 3:
//        myGLCD.setColor(0,255,0);
//        break;
//      case 4:
//        myGLCD.setColor(0,0,255);
//        break;
//      case 5:
//        myGLCD.setColor(255,255,0);
//        break;
//    }
//    myGLCD.fillRect(150+(i*20), 70+(i*20), 210+(i*20), 130+(i*20));
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some filled, rounded rectangles
//  for (int i=1; i<6; i++)
//  {
//    switch (i)
//    {
//      case 1:
//        myGLCD.setColor(255,0,255);
//        break;
//      case 2:
//        myGLCD.setColor(255,0,0);
//        break;
//      case 3:
//        myGLCD.setColor(0,255,0);
//        break;
//      case 4:
//        myGLCD.setColor(0,0,255);
//        break;
//      case 5:
//        myGLCD.setColor(255,255,0);
//        break;
//    }
//    myGLCD.fillRoundRect(270-(i*20), 70+(i*20), 330-(i*20), 130+(i*20));
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some filled circles
//  for (int i=1; i<6; i++)
//  {
//    switch (i)
//    {
//      case 1:
//        myGLCD.setColor(255,0,255);
//        break;
//      case 2:
//        myGLCD.setColor(255,0,0);
//        break;
//      case 3:
//        myGLCD.setColor(0,255,0);
//        break;
//      case 4:
//        myGLCD.setColor(0,0,255);
//        break;
//      case 5:
//        myGLCD.setColor(255,255,0);
//        break;
//    }
//    myGLCD.fillCircle(180+(i*20),100+(i*20), 30);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some lines in a pattern
//  myGLCD.setColor (255,0,0);
//  for (int i=15; i<304; i+=5)
//  {
//    myGLCD.drawLine(1, i, (i*1.6)-10, 304);
//  }
//  myGLCD.setColor (255,0,0);
//  for (int i=304; i>15; i-=5)
//  {
//    myGLCD.drawLine(478, i, (i*1.6)-11, 15);
//  }
//  myGLCD.setColor (0,255,255);
//  for (int i=304; i>15; i-=5)
//  {
//    myGLCD.drawLine(1, i, 491-(i*1.6), 15);
//  }
//  myGLCD.setColor (0,255,255);
//  for (int i=15; i<304; i+=5)
//  {
//    myGLCD.drawLine(478, i, 490-(i*1.6), 304);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some random circles
//  for (int i=0; i<100; i++)
//  {
//    myGLCD.setColor(random(255), random(255), random(255));
//    x=32+random(416);
//    y=45+random(226);
//    r=random(30);
//    myGLCD.drawCircle(x, y, r);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some random rectangles
//  for (int i=0; i<100; i++)
//  {
//    myGLCD.setColor(random(255), random(255), random(255));
//    x=2+random(476);
//    y=16+random(289);
//    x2=2+random(476);
//    y2=16+random(289);
//    myGLCD.drawRect(x, y, x2, y2);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//// Draw some random rounded rectangles
//  for (int i=0; i<100; i++)
//  {
//    myGLCD.setColor(random(255), random(255), random(255));
//    x=2+random(476);
//    y=16+random(289);
//    x2=2+random(476);
//    y2=16+random(289);
//    myGLCD.drawRoundRect(x, y, x2, y2);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//  for (int i=0; i<100; i++)
//  {
//    myGLCD.setColor(random(255), random(255), random(255));
//    x=2+random(476);
//    y=16+random(289);
//    x2=2+random(476);
//    y2=16+random(289);
//    myGLCD.drawLine(x, y, x2, y2);
//  }

//  delay(2000);

//  myGLCD.setColor(0,0,0);
//  myGLCD.fillRect(1,15,478,304);

//  for (int i=0; i<10000; i++)
//  {
//    myGLCD.setColor(random(255), random(255), random(255));
//    myGLCD.drawPixel(2+random(476), 16+random(289));
//  }

//  delay(2000);

//  myGLCD.fillScr(0, 0, 255);
//  myGLCD.setColor(255, 0, 0);
//  myGLCD.fillRoundRect(160, 70, 319, 169);

//  myGLCD.setColor(255, 255, 255);
//  myGLCD.setBackColor(255, 0, 0);
//  myGLCD.print("That's it!", CENTER, 93);
//  myGLCD.print("Restarting in a", CENTER, 119);
//  myGLCD.print("few seconds...", CENTER, 132);

//  myGLCD.setColor(0, 255, 0);
//  myGLCD.setBackColor(0, 0, 255);
//  myGLCD.print("Runtime: (msecs)", CENTER, 290);
//  myGLCD.printNumI(millis(), CENTER, 305);

//  delay (10000);
//}
