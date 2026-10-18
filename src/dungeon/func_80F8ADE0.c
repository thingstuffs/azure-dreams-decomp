#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/types3b_types.h"

   /* the 0x2 bytes before arg0 in create_cylindrical_effect, addressed as arg0[-1] */

typedef struct S_80F8ADE0_0 {
    u8 pad_00[0x48];
    u16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0xA];
    s32 unk_58;
} S_80F8ADE0_0;   /* arg0 in create_cylindrical_effect */


/* Advances a timed state sequence and sets flags when it reaches stage 15. */
void create_cylindrical_effect(void *state) {
    u16 ticks_left;
    u16 next_delay;

    if (((S_80F8ADE0_0 *)state)->unk_4C == 8) {
        ((S_80F8ADE0_0 *)state)->unk_58 = (s32) (((S_80F8ADE0_0 *)state)->unk_58 + 8);
    }
    ticks_left = ((S_80F8ADE0_0 *)state)->unk_48 - 1;
    ((S_80F8ADE0_0 *)state)->unk_48 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        next_delay = 1;
        if (((S_80F8ADE0_0 *)state)->unk_4C == 7) {
            next_delay = 0xA;
        }
        ((S_80F8ADE0_0 *)state)->unk_48 = next_delay;
        ((S_80F8ADE0_0 *)state)->unk_58 = (s32) ((((S_80F8ADE0_0 *)state)->unk_58 == 0) << 7);
        ((S_80F8ADE0_0 *)state)->unk_4C = (s16) ((u16) ((S_80F8ADE0_0 *)state)->unk_4C + 1);
    }
    if (((S_80F8ADE0_0 *)state)->unk_4C == 0xF) {
        ((ObjectStatusPrefix16 *)state)[-1].unk_00 = (u16) (((ObjectStatusPrefix16 *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
