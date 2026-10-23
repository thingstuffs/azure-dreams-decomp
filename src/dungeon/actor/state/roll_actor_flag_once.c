#include "common.h"
typedef struct S_800ADD20_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x80];
    u16 unk_98;
} S_800ADD20_0;   /* arg0 in roll_actor_flag_once */


extern s32 generate_random_value(void);
/* Once per object, set flag 0x100 if the computed low 16 bits are divisible by divisor. */
void roll_actor_flag_once(S_800ADD20_0 *object, s32 divisor, s32 unused_2, s32 unused_3) {
    s32 state_flags;
    u16 result_flags;

    state_flags = object->unk_14;
    if (!(state_flags & 0x8000)) {
        object->unk_14 = (s32) (state_flags | 0x8000);
        if (((s32) (generate_random_value() & 0xFFFF) % divisor) != 0) {
            result_flags = object->unk_98;
            result_flags = (u16) (result_flags & 0xFEFF);
        } else {
            result_flags = object->unk_98;
            result_flags = (u16) (result_flags | 0x100);
        }
        object->unk_98 = result_flags;
    }
}
