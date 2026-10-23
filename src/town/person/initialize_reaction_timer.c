#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
/* extern */

void func_800C9C94(Rec_func_80094268_arg0 *, s32, s32);
/* Call func_800C9C94 and store the result of scale_random_to_unsigned_halfword_limit(3) plus one. */
void initialize_reaction_timer(Rec_func_80094268_arg0 *object, s32 param_1, s32 param_2) {
    func_800C9C94(object, param_1, param_2);
    object->unk_90.as_s16 = (s16) (scale_random_to_unsigned_halfword_limit(3) + 1);
}
