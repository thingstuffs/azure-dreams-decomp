#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Processes IDs 0xFB7 and 0xFB8, then returns zero. */
s32 clear_hospital_first_visit_flags(void) {
    clear_script_flag_bit(F_hos_first_cheriru);
    clear_script_flag_bit(F_hos_first_hush);
    return 0;
}
