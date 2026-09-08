#include "common.h"
#include "m2c_compat.h"

typedef struct S_800DCA88_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800DCA88_0;   /* arg0 in func_800DCA88 */

typedef struct S_800DCA88_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_800DCA88_1;   /* ((S_800DCA88_0 *)arg0)->unk_04 in func_800DCA88 */





/* Set the attached object position according to the alternate-position flag. */
void func_800DCA88(S_800DCA88_0 *object, s32 alternate_position) {
    if (alternate_position != 0) {
        ((S_800DCA88_1 *)(object->unk_04))->unk_08 = -0x8C;
    } else {
        ((S_800DCA88_1 *)(object->unk_04))->unk_08 = -0x22;
    }
    ((S_800DCA88_1 *)(object->unk_04))->unk_0A = -0x52;
    ((S_800DCA88_1 *)(object->unk_04))->unk_0C = 0x200;
}
