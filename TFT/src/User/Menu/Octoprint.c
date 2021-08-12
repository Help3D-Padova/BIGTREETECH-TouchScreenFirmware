#include "Octoprint.h"
#include "includes.h"

#ifdef BUZZER_PIN // Speaker
  #define BUZZER_KEY_INDEX KEY_ICON_3
#endif


void menuOctoprint(void)
{
  LISTITEMS sounditems = {
  // title
  LABEL_OCTOPRINT,
  // icon                 ItemType      Item Title        item value text(only for custom value)
  {
    {CHARICON_TOGGLE_ON, LIST_TOGGLE,  LABEL_DISABLE_NOTY,LABEL_BACKGROUND},
    {CHARICON_TOGGLE_ON, LIST_TOGGLE,  LABEL_ALERT_SOUND,  LABEL_BACKGROUND},
    {CHARICON_TOGGLE_ON, LIST_TOGGLE,  LABEL_TOAST_SOUND,  LABEL_BACKGROUND},
    {CHARICON_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {CHARICON_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {CHARICON_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {CHARICON_BACKGROUND, LIST_LABEL,  LABEL_BACKGROUND,   LABEL_BACKGROUND},
    {CHARICON_BACK,       LIST_LABEL,  LABEL_BACKGROUND,   LABEL_BACKGROUND},}
  };

  sounditems.items[0].icon = (infoSettings.ack_notification == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;
  sounditems.items[1].icon = (infoSettings.alertSound == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;
  sounditems.items[2].icon = (infoSettings.toastSound == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;

  KEY_VALUES key_num = KEY_IDLE;
  SETTINGS now = infoSettings;

  menuDrawListPage(&sounditems);

  while (infoMenu.menu[infoMenu.cur] == menuOctoprint)
  {
    key_num = menuKeyGetValue();
    switch(key_num)
    {
    
    case KEY_ICON_0:
      infoSettings.ack_notification = (infoSettings.ack_notification + 1) % 2;
      sounditems.items[key_num].icon = (infoSettings.ack_notification == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;
      menuDrawListItem(&sounditems.items[key_num], key_num);
      break;  

    case KEY_ICON_1:
      infoSettings.alertSound = (infoSettings.alertSound + 1) % 2;
      sounditems.items[key_num].icon = (infoSettings.alertSound == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;
      menuDrawListItem(&sounditems.items[key_num], key_num);
      break;

    case KEY_ICON_2:
      infoSettings.toastSound = (infoSettings.toastSound + 1) % 2;
      sounditems.items[key_num].icon = (infoSettings.toastSound == 1) ? CHARICON_TOGGLE_ON : CHARICON_TOGGLE_OFF;
      menuDrawListItem(&sounditems.items[key_num], key_num);
      break;

    case KEY_ICON_7:
      infoMenu.cur--;
      break;

    default:
      break;
    }
    loopProcess();
  }

  if (memcmp(&now, &infoSettings, sizeof(SETTINGS)))
  {
    storePara();
  }
} //menuOctoprint

