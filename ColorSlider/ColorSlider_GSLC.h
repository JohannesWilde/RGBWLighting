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
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XCheckbox.h"
#include "elem/XSlider.h"
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
      ,E_CHECK_BACKLIGHT,E_CHECK_LED_BRIGHTNESS,E_CHECK_POWER
      ,E_CHECK_RELAIS,E_DRAW_LINE1,E_ELEM_BOX1,E_ELEM_TEXT8
      ,E_LABEL_BACKLIGHT,E_LABEL_BRIGHTNESS,E_LABEL_LED_BLUE
      ,E_LABEL_LED_GREEN,E_LABEL_LED_RED,E_LABEL_POWER,E_LABEL_RELAIS
      ,E_LBL_TITLE,E_SLIDER_BACKLIGHT,E_SLIDER_LED_BLUE
      ,E_SLIDER_LED_BRIGHTNESS,E_SLIDER_LED_GREEN,E_SLIDER_LED_RED};
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
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asProject1Elem[MAX_ELEM_PROJECT_OPTIONS_RAM];
gslc_tsElemRef                  m_asProject1ElemRef[MAX_ELEM_PROJECT_OPTIONS];
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsXSlider                  m_sXSlider1;
gslc_tsXSlider                  m_sXSlider2;
gslc_tsXSlider                  m_sXSlider3;
gslc_tsXCheckbox                m_asXCheck1;
gslc_tsXCheckbox                m_asXCheck2;
gslc_tsXCheckbox                m_asXCheck3;
gslc_tsXCheckbox                m_asXCheck4;
gslc_tsXSlider                  m_sXSlider4;
gslc_tsXSlider                  m_sXSlider5;

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
extern gslc_tsElemRef* m_pSliderBacklight;
extern gslc_tsElemRef* m_pSliderLedBlue;
extern gslc_tsElemRef* m_pSliderLedBrightness;
extern gslc_tsElemRef* m_pSliderLedGreen;
extern gslc_tsElemRef* m_pSliderLedRed;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

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
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN_TXT15,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN_TXT5,GSLC_FONTREF_PTR,NULL,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_GRAY_LT2);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
   
  // Create E_ELEM_BOX1 box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_ELEM_BOX1,E_PG_MAIN,(gslc_tsRect){10,40,460,270});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_LT2,GSLC_COL_GRAY_LT2);
  
  // Create E_LBL_TITLE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LBL_TITLE,E_PG_MAIN,(gslc_tsRect){22,5,306,26},
    (char*)"Lightning Control",0,E_BUILTIN_TXT15);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);
   
  // Create E_BOX_LED_COLOR box
  pElemRef = gslc_ElemCreateBox(&m_gui,E_BOX_LED_COLOR,E_PG_MAIN,(gslc_tsRect){20,190,130,100});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,((gslc_tsColor){255,128,0}),GSLC_COL_WHITE);
  m_pBoxLedColor = pElemRef;
  
  // Create E_LABEL_LED_RED text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_LED_RED,E_PG_MAIN,(gslc_tsRect){160,200,26,12},
    (char*)"Red:",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // Create slider E_SLIDER_LED_RED 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SLIDER_LED_RED,E_PG_MAIN,&m_sXSlider1,
          (gslc_tsRect){200,195,256,20},0,255,255,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,GSLC_COL_RED,10,5,GSLC_COL_RED);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pSliderLedRed = pElemRef;
  
  // Create E_LABEL_LED_GREEN text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_LED_GREEN,E_PG_MAIN,(gslc_tsRect){160,230,38,12},
    (char*)"Green:",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // Create slider E_SLIDER_LED_GREEN 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SLIDER_LED_GREEN,E_PG_MAIN,&m_sXSlider2,
          (gslc_tsRect){200,225,256,20},0,255,128,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,GSLC_COL_GREEN,10,5,GSLC_COL_GREEN);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pSliderLedGreen = pElemRef;
  
  // Create E_LABEL_LED_BLUE text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_LED_BLUE,E_PG_MAIN,(gslc_tsRect){160,260,32,12},
    (char*)"Blue:",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // Create slider E_SLIDER_LED_BLUE 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SLIDER_LED_BLUE,E_PG_MAIN,&m_sXSlider3,
          (gslc_tsRect){200,255,256,20},0,255,0,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,true,GSLC_COL_BLUE,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pSliderLedBlue = pElemRef;
  
  // Create E_ELEM_TEXT8 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT8,E_PG_MAIN,(gslc_tsRect){430,20,30,10},
    (char*)"v 0.1",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY,GSLC_COL_GRAY_LT2,GSLC_COL_BLACK);

  // Create E_DRAW_LINE1 line 
  pElemRef = gslc_ElemCreateLine(&m_gui,E_DRAW_LINE1,E_PG_MAIN,20,140,460,140);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_WHITE,GSLC_COL_WHITE);
  
  // Create E_LABEL_BACKLIGHT text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_BACKLIGHT,E_PG_MAIN,(gslc_tsRect){20,55,54,10},
    (char*)"Backlight",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  
  // Create E_LABEL_POWER text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_POWER,E_PG_MAIN,(gslc_tsRect){20,85,30,10},
    (char*)"Power",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  
  // Create E_LABEL_RELAIS text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_RELAIS,E_PG_MAIN,(gslc_tsRect){20,115,36,10},
    (char*)"Relais",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  
  // Create E_LABEL_BRIGHTNESS text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_LABEL_BRIGHTNESS,E_PG_MAIN,(gslc_tsRect){20,160,60,10},
    (char*)"Brightness",0,E_BUILTIN_TXT5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
   
  // create checkbox E_CHECK_POWER
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_CHECK_POWER,E_PG_MAIN,&m_asXCheck1,
    (gslc_tsRect){110,80,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_GRAY_DK3,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pCheckPower = pElemRef;
   
  // create checkbox E_CHECK_RELAIS
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_CHECK_RELAIS,E_PG_MAIN,&m_asXCheck2,
    (gslc_tsRect){110,110,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_GRAY_DK3,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pCheckRelais = pElemRef;
  
  // create E_BTN_BACKLIGHT_DECREASE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_BTN_BACKLIGHT_DECREASE,E_PG_MAIN,
    (gslc_tsRect){145,50,20,20},(char*)"<",0,E_BUILTIN_TXT5,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_YELLOW,GSLC_COL_GRAY_LT1);
  m_pButtonBacklightDecrease = pElemRef;
  
  // create E_BTN_LED_BRIGHTNESS_DECREASE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_BTN_LED_BRIGHTNESS_DECREASE,E_PG_MAIN,
    (gslc_tsRect){145,155,20,20},(char*)"<",0,E_BUILTIN_TXT5,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_YELLOW,GSLC_COL_GRAY_LT1);
  m_pButtonLedBrightnessDecrease = pElemRef;
   
  // create checkbox E_CHECK_BACKLIGHT
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_CHECK_BACKLIGHT,E_PG_MAIN,&m_asXCheck3,
    (gslc_tsRect){110,50,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_GRAY_DK3,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pCheckBacklight = pElemRef;
   
  // create checkbox E_CHECK_LED_BRIGHTNESS
  pElemRef = gslc_ElemXCheckboxCreate(&m_gui,E_CHECK_LED_BRIGHTNESS,E_PG_MAIN,&m_asXCheck4,
    (gslc_tsRect){110,155,20,20},false,GSLCX_CHECKBOX_STYLE_X,GSLC_COL_GRAY_DK3,false);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_GRAY_DK3,GSLC_COL_GRAY_LT2,GSLC_COL_YELLOW);
  gslc_ElemXCheckboxSetStateFunc(&m_gui, pElemRef, &CbCheckbox);
  m_pCheckLedBrightness = pElemRef;
  
  // create E_BTN_BACKLIGHT_INCREASE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_BTN_BACKLIGHT_INCREASE,E_PG_MAIN,
    (gslc_tsRect){441,50,20,20},(char*)">",0,E_BUILTIN_TXT5,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_YELLOW,GSLC_COL_GRAY_LT1);
  m_pButtonBacklightIncrease = pElemRef;
  
  // create E_BTN_LED_BRIGHTNESS_INCREASE button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_BTN_LED_BRIGHTNESS_INCREASE,E_PG_MAIN,
    (gslc_tsRect){441,155,20,20},(char*)">",0,E_BUILTIN_TXT5,&CbBtnCommon);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLACK,GSLC_COL_YELLOW,GSLC_COL_GRAY_LT1);
  m_pButtonLedBrightnessIncrease = pElemRef;

  // Create slider E_SLIDER_LED_BRIGHTNESS 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SLIDER_LED_BRIGHTNESS,E_PG_MAIN,&m_sXSlider4,
          (gslc_tsRect){175,155,256,20},0,255,127,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLACK,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pSliderLedBrightness = pElemRef;

  // Create slider E_SLIDER_BACKLIGHT 
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_SLIDER_BACKLIGHT,E_PG_MAIN,&m_sXSlider5,
          (gslc_tsRect){175,50,256,20},0,255,127,5,false);
  gslc_ElemXSliderSetStyle(&m_gui,pElemRef,false,GSLC_COL_BLACK,10,5,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pSliderBacklight = pElemRef;
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
