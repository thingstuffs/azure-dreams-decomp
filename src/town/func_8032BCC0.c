#include "common.h"

extern s32 check_callback_record_bytes(s32, s32);
extern s32 get_script_flag_mask(s32);

extern u8 D_8001C350[];
extern s32 D_8001C360;
extern u8 D_8001DCD4[];
extern u8 D_8001DDA4[];
extern u8 D_8001E1AB[];

/* Selects a byte array based on the current state and condition checks. */
u8 *select_town_byte_array(void) {
    if (get_script_flag_mask(0xD8A) != 0) {
        return D_8001E1AB;
    }
    if (D_8001C360 != 0) {
        if (check_callback_record_bytes(0xD, 7) != 0) {
            return D_8001DDA4;
        }
        return D_8001C350;
    }
    return D_8001DCD4;
}
