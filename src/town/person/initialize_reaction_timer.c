#include "common.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
/* extern */

typedef struct S_800C9D80_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C9D80_0;   /* arg0 in initialize_reaction_timer */
void func_800C9C94(S_800C9D80_0 *, s32, s32);
/* Call func_800C9C94 and store the result of scale_random_to_unsigned_halfword_limit(3) plus one. */
void initialize_reaction_timer(S_800C9D80_0 *object, s32 param_1, s32 param_2) {
    func_800C9C94(object, param_1, param_2);
    object->unk_90 = (s16) (scale_random_to_unsigned_halfword_limit(3) + 1);
}
