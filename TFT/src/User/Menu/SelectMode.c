#include "SelectMode.h"
#include "includes.h"

typedef enum
{
  MKEY_0 = 0,
  MKEY_1,
  MKEY_IDLE = IDLE_TOUCH,
} MKEY_VALUES;

<<<<<<< HEAD
=======
const GUI_RECT rect_of_mode[MODE_COUNT] = {
  // 2 select icon
  {1 * SPACE_SELEX + 0 * ICON_WIDTH, SPACE_SELEY, 1 * SPACE_SELEX + 1 * ICON_WIDTH, SPACE_SELEY + ICON_HEIGHT},
  {3 * SPACE_SELEX + 1 * ICON_WIDTH, SPACE_SELEY, 3 * SPACE_SELEX + 2 * ICON_WIDTH, SPACE_SELEY + ICON_HEIGHT},
};

const uint8_t icon_mode [MODE_COUNT] = {
  ICON_MARLIN_MODE,
  ICON_TOUCH_MODE,
};

void drawModeIcon(void)
{
  for (uint8_t i = 0; i < MODE_COUNT; i++)
  {
    ICON_ReadDisplay(rect_of_mode[i].x0, rect_of_mode[i].y0, icon_mode[i]);
  }

  const GUI_RECT mode_title_rect[MODE_COUNT] = {
    {0,           rect_of_mode[0].y1 + BYTE_HEIGHT / 2, text_startx, rect_of_mode[0].y1 + BYTE_HEIGHT / 2 + BYTE_HEIGHT},
    {text_startx, rect_of_mode[0].y1 + BYTE_HEIGHT / 2, LCD_WIDTH,   rect_of_mode[0].y1 + BYTE_HEIGHT / 2 + BYTE_HEIGHT},
  };

  GUI_RestoreColorDefault();
  GUI_DispStringInPrect(&mode_title_rect[0],(uint8_t *)"Marlin Mode");
  GUI_DispStringInPrect(&mode_title_rect[1],(uint8_t *)"Touch Mode");
}
>>>>>>> master

// open mode switching menu
void menuMode(void)
{
  // 1 title, ITEM_PER_PAGE items(icon+label)
  MENUITEMS mainPageItems = {
    // title
    LABEL_MAINMENU,
    // icon                         label
    {{ICON_LEVELING,                LABEL_BED_LEVELING},
     {ICON_EXTRUDE,                 LABEL_EXTRUDE},
     {ICON_EEPROM_SAVE,             LABEL_EEPROM_SETTINGS},
     {ICON_OCTOPRINT,               LABEL_OCTOPRINT},
     {ICON_DISABLE_STEPPERS,        LABEL_DISABLE_STEPPERS},
     {ICON_CONNECTION_SETTINGS,     LABEL_CONNECTION_SETTINGS},
     {ICON_BACKGROUND,              LABEL_BACKGROUND},
     {ICON_BACK,                    LABEL_BACK},}
  };

  KEY_VALUES key_num = KEY_IDLE;

  if (infoSettings.status_screen != 1)
  {
    mainPageItems.items[7].icon = ICON_PRINT;
    mainPageItems.items[7].label.index = LABEL_PRINT;
  }

  menuDrawPage(&mainPageItems);

  while (infoMenu.menu[infoMenu.cur] == menuMode)
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        infoMenu.menu[++infoMenu.cur] = menuBedLeveling;
        break;

      case KEY_ICON_1:
        infoMenu.menu[++infoMenu.cur] = menuExtrude;
        break;

      case KEY_ICON_2:
        infoMenu.menu[++infoMenu.cur] = menuEepromSettings;
        break;    

      case KEY_ICON_3:
        OPEN_MENU(menuConnectionSettings);
        break; 

      case KEY_ICON_4:
        storeCmd("M84\n");
        break;  

      case KEY_ICON_5:
        infoMenu.menu[++infoMenu.cur] = menuConnectionSettings;
        break;

      case KEY_ICON_7:
        if (infoSettings.status_screen != 1)
          infoMenu.menu[++infoMenu.cur] = menuPrint;
        else
          infoMenu.cur--;
        break;  

      default:
        break;
    }

    loopProcess();
  }
}

