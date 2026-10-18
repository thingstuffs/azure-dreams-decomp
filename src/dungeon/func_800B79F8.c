#include "modules/dungeon_cd_control.h"

/* Passes D_800DF3E4 to Control_CD with selector 6 and a zero final argument. */
void submit_control_command_six(void) {
    Control_CD(6, &D_800DF3E4, 0);
}
