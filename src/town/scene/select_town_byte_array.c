#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern s32 check_callback_record_bytes(s32, s32);

extern u8 D_8001C350[];
extern s32 scene_response_enabled;
extern u8 scene_event_buffer[];
extern u8 D_8001DDA4[];
extern u8 D_8001E1AB[];

/* Selects a byte array based on the current state and condition checks. */
u8 *select_town_byte_array(void) {
    if (get_script_flag_mask(Ftt_pad89) != 0) {
        return D_8001E1AB;
    }
    if (scene_response_enabled != 0) {
        if (check_callback_record_bytes(0xD, 7) != 0) {
            return D_8001DDA4;
        }
        return D_8001C350;
    }
    return scene_event_buffer;
}
