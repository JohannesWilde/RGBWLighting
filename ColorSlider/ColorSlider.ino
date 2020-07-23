//<App !Start!>
// FILE: [ColorSlider.ino]
// Created by GUIslice Builder version: [0.14.b004]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "ColorSlider_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* m_pBoxLedColor    = NULL;
gslc_tsElemRef* m_pButtonBacklightDecrease= NULL;
gslc_tsElemRef* m_pButtonBacklightIncrease= NULL;
gslc_tsElemRef* m_pButtonLedBrightnessDecrease= NULL;
gslc_tsElemRef* m_pButtonLedBrightnessIncrease= NULL;
gslc_tsElemRef* m_pCheckBacklight = NULL;
gslc_tsElemRef* m_pCheckLedBrightness= NULL;
gslc_tsElemRef* m_pCheckPower     = NULL;
gslc_tsElemRef* m_pCheckRelais    = NULL;
gslc_tsElemRef* m_pSliderBacklight= NULL;
gslc_tsElemRef* m_pSliderLedBlue  = NULL;
gslc_tsElemRef* m_pSliderLedBrightness= NULL;
gslc_tsElemRef* m_pSliderLedGreen = NULL;
gslc_tsElemRef* m_pSliderLedRed   = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_BTN_BACKLIGHT_DECREASE:
        break;
      case E_BTN_LED_BRIGHTNESS_DECREASE:
        break;
      case E_BTN_BACKLIGHT_INCREASE:
        break;
      case E_BTN_LED_BRIGHTNESS_INCREASE:
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
// Checkbox / radio callbacks
// - Creating a callback function is optional, but doing so enables you to
//   detect changes in the state of the elements.
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);
  if (pElemRef == NULL) {
    return false;
  }
  
  boolean bChecked = gslc_ElemXCheckboxGetState(pGui,pElemRef);

  // Determine which element issued the callback
  switch (pElem->nId) {
//<Checkbox Enums !Start!>
    case E_CHECK_POWER:
      break;
    case E_CHECK_RELAIS:
      break;
    case E_CHECK_BACKLIGHT:
      break;
    case E_CHECK_LED_BRIGHTNESS:
      break;

//<Checkbox Enums !End!>
    default:
      break;
  } // switch
  return true;
}
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_SLIDER_LED_RED:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pSliderLedRed);
      break;
    case E_SLIDER_LED_GREEN:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pSliderLedGreen);
      break;
    case E_SLIDER_LED_BLUE:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pSliderLedBlue);
      break;

    case E_SLIDER_LED_BRIGHTNESS:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pSliderLedBrightness);
      break;
    case E_SLIDER_BACKLIGHT:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pSliderBacklight);
      break;
//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(9600);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}

