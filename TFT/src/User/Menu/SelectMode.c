#include "SelectMode.h"
#include "includes.h"

typedef enum
{
  MKEY_0 = 0,
  MKEY_1,
  MKEY_IDLE = IDLE_TOUCH,
} MKEY_VALUES;


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
     {ICON_NULL,                    LABEL_NULL},
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

