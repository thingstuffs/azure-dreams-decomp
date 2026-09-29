#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A9A0C();                      /* extern */
s32 func_800ADDA0(); /* extern */
M2C_UNK func_801716A4(); /* extern */

typedef struct S_80172114_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x28];
    s8 unk_9A;
} S_80172114_0;   /* held_arg0 in func_80172114 */

/* Updates object state and flags according to the state handler result. */
s32 func_80172114(void *object, M2C_UNK state_input_a, M2C_UNK state_input_b) {
    M2C_UNK saved_input_a;
    M2C_UNK saved_input_b;
    void *saved_object;
    s32 call_result;
    s32 state;

    saved_input_a = state_input_a;
    saved_input_b = state_input_b;
    saved_object = object;
    call_result = func_800ADDA0(saved_input_a, saved_input_b, saved_object, 2, 4, saved_object + 0x9C);
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state >= 0) {
        switch (state) {
        case 0:
            ((S_80172114_0 *)saved_object)->unk_9A = 0xE;
            func_800A9A0C(saved_object);
            return 0;
        case 2:
            func_801716A4(saved_object, saved_input_a, saved_input_b, saved_object);
            return 0;
        case 1:
            ((S_80172114_0 *)saved_object)->unk_71 =
                    (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
            if ((func_800A2BDC(saved_object) << 0x10) != 0) {
                ((S_80172114_0 *)saved_object)->unk_46 =
                    (u16) (((S_80172114_0 *)saved_object)->unk_46 & 0x7FFF);
                return 0;
            }
        default:
            ((S_80172114_0 *)saved_object)->unk_71 =
                    (u8) (((S_80172114_0 *)saved_object)->unk_71 & 0x7F);
            if ((dungeonStatus.flags & 8) == 0) {
                call_result = 1;
                break;
            }
            ((S_80172114_0 *)saved_object)->unk_46 =
                (u16) (((S_80172114_0 *)saved_object)->unk_46 & 0x7FFF);
            return 0;
        }
    }
    return call_result;
}
