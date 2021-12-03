#include "UnifiedMove.h"
#include "includes.h"

#if DELTA_PROBE_TYPE != 0  // if Delta printer
  void deltaCalibration(void)
  {
    mustStoreCmd("G33\n");
  }
#endif

void menuUnifiedMove(void)
{
  MENUITEMS UnifiedMoveItems = {
    // title
    LABEL_UNIFIEDMOVE,
    // icon                          label
    {
      {ICON_HOME,                    LABEL_HOME},
      {ICON_MOVE,                    LABEL_MOVE},
      {ICON_DISABLE_STEPPERS,        LABEL_DISABLE_STEPPERS},
      {ICON_BABYSTEP,                LABEL_BABYSTEP},
<<<<<<< HEAD
      {ICON_BACKGROUND,              LABEL_BACKGROUND},
      {ICON_BACKGROUND,              LABEL_BACKGROUND},
=======
      #if DELTA_PROBE_TYPE == 0  // if not Delta printer
        {ICON_MANUAL_LEVEL,            LABEL_LEVELING},
      #else
        {ICON_DELTA_CALIBRATE,         LABEL_CALIBRATION},
      #endif
>>>>>>> master
      {ICON_BACKGROUND,              LABEL_BACKGROUND},
      {ICON_BACK,                    LABEL_BACK},
    }
  };

  KEY_VALUES key_num = KEY_IDLE;


  menuDrawPage(&UnifiedMoveItems);

  while (MENU_IS(menuUnifiedMove))
  {
    key_num = menuKeyGetValue();
    switch (key_num)
    {
      case KEY_ICON_0:
        OPEN_MENU(menuHome);
        break;

      case KEY_ICON_1:
        OPEN_MENU(menuMove);
        break;

      case KEY_ICON_2:
         storeCmd("M84\n");
        break;

      case KEY_ICON_3:
       infoMenu.menu[++infoMenu.cur] = menuBabystep;
        break;

      case KEY_ICON_7:
        CLOSE_MENU();
        break;

      default:
        break;
    }

    loopProcess();
  }
}
