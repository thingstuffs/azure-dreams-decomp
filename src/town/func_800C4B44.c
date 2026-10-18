#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"


/* Initialize D_800D4740 with selector 6 and run the follow-up setup. */
void initialize_resource_selector_six(void) {
    Control_CD(6, &D_800D4740, 0);
    drain_cd_command_queue();
}
