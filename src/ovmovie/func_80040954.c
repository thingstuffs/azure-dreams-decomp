#include "modules/ovmovie_game.h"

/* Start operation 0x15 and wait for the 0x1C0 completion check. */
void func_80177154(void *playback_state) {
    Control_CD(0x15, func_80061350(), 0);
    drain_cd_command_queue();
    do {

    } while (func_80063424(0x1C0) == 0);
}
