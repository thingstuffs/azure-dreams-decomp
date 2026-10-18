#include "modules/dungeon_ovl_18d0850.h"

s32 dispatch_effect_state_handler(void *state_ptr, void *second_ptr, void *third_ptr)
{
    switch (((ovl_18d0850_818B15F4_Func818B15F4Arg *)state_ptr)->state) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    default:
        break;
    case 4:
        build_a_trigonometric_table_processes_up_eight_height_offset_segments(state_ptr, second_ptr, third_ptr);
        break;
    case 5:
        build_a_circular_lookup_table_submit_eight_phase_shifted_entries(state_ptr, second_ptr, third_ptr);
        break;
    case 6:
        fade_effect_sprite_to_black(state_ptr, second_ptr, third_ptr);
        break;
    }
    return 0;
}
