#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene/motion.h"

extern u8 D_8001798C[];
extern u8 D_80017B30[];

/* Call func_800176A0(0x12C7), then forward the inputs to func_80016C64 with D_8001798C and D_80017B30. */
void set_state_4_run_transition(s32 input_value, s32 unused, s32 extra_value) {
    set_script_flag_bit(F_casino_build);
    apply_entry_position(D_8001798C, D_80017B30, input_value, extra_value);
}
