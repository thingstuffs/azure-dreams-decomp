#include "common.h"
#include "m2c_compat.h"

s32 scaleRandomToUnsignedHalfwordLimit();                         /* extern */
/* extern */

typedef struct S_800C9D80_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800C9D80_0;   /* arg0 in townInitializeReactionTimer */


M2C_UNK func_800C9C94(S_800C9D80_0 *, s32, s32);
/* Call func_800C9C94 and store the result of scaleRandomToUnsignedHalfwordLimit(3) plus one. */
void townInitializeReactionTimer(S_800C9D80_0 *object, s32 param_1, s32 param_2) {
    func_800C9C94(object, param_1, param_2);
    object->unk_90 = (s16) (scaleRandomToUnsignedHalfwordLimit(3) + 1);
}
