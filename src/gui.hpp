//<File !Start!>
// FILE: [ColorSlider_GSLC.h]
// Created by GUIslice Builder version: [0.14.b004]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include <GUIslice.h>
#include <GUIslice_drv.h>

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include <elem/XCheckbox.h>
#include <elem/XProgress.h>
#include <elem/XSlider.h>
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PROJECT_OPTIONS,E_PG_MAIN};
enum {E_BOX_LED_COLOR,E_BTN_BACKLIGHT_DECREASE,E_BTN_BACKLIGHT_INCREASE
      ,E_BTN_LED_BRIGHTNESS_DECREASE,E_BTN_LED_BRIGHTNESS_INCREASE
      ,E_CHECK_BACKLIGHT,E_CHECK_POWER,E_CHECK_RELAIS,E_DRAW_LINE1
      ,E_ELEM_BOX1,E_ELEM_CHECK4,E_ELEM_TEXT8,E_LABEL_BACKLIGHT
      ,E_LABEL_BRIGHTNESS,E_LABEL_LED_BLUE,E_LABEL_LED_GREEN
      ,E_LABEL_LED_RED,E_LABEL_POWER,E_LABEL_RELAIS,E_LBL_TITLE
      ,E_PROGRESS_BACKLIGHT,E_PROGRESS_LED_BRIGHTNESS,E_SLIDER_LED_BLUE
      ,E_SLIDER_LED_GREEN,E_SLIDER_LED_RED};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN_TXT15,E_BUILTIN_TXT5,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                2

#define MAX_ELEM_PROJECT_OPTIONS 0 // # Elems total on page
#define MAX_ELEM_PROJECT_OPTIONS_RAM MAX_ELEM_PROJECT_OPTIONS // # Elems in RAM

#define MAX_ELEM_PG_MAIN 25 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
extern gslc_tsGui                      m_gui;
extern gslc_tsDriver                   m_drv;
extern gslc_tsFont                     m_asFont[MAX_FONT];
extern gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
extern gslc_tsElem                     m_asProject1Elem[MAX_ELEM_PROJECT_OPTIONS_RAM];
extern gslc_tsElemRef                  m_asProject1ElemRef[MAX_ELEM_PROJECT_OPTIONS];
extern gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
extern gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
extern gslc_tsXSlider                  m_sXSlider1;
extern gslc_tsXSlider                  m_sXSlider2;
extern gslc_tsXSlider                  m_sXSlider3;
extern gslc_tsXCheckbox                m_asXCheck1;
extern gslc_tsXCheckbox                m_asXCheck2;
extern gslc_tsXProgress                m_sXBarGauge1;
extern gslc_tsXProgress                m_sXBarGauge3;
extern gslc_tsXCheckbox                m_asXCheck3;
extern gslc_tsXCheckbox                m_asXCheck4;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* m_pBoxLedColor;
extern gslc_tsElemRef* m_pButtonBacklightDecrease;
extern gslc_tsElemRef* m_pButtonBacklightIncrease;
extern gslc_tsElemRef* m_pButtonLedBrightnessDecrease;
extern gslc_tsElemRef* m_pButtonLedBrightnessIncrease;
extern gslc_tsElemRef* m_pCheckBacklight;
extern gslc_tsElemRef* m_pCheckLedBrightness;
extern gslc_tsElemRef* m_pCheckPower;
extern gslc_tsElemRef* m_pCheckRelais;
extern gslc_tsElemRef* m_pProgressBacklight;
extern gslc_tsElemRef* m_pProgressLedBrightness;
extern gslc_tsElemRef* m_pSliderLedBlue;
extern gslc_tsElemRef* m_pSliderLedGreen;
extern gslc_tsElemRef* m_pSliderLedRed;
//<Extern_References !End!>

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen();

#endif // end _GUISLICE_GEN_H
