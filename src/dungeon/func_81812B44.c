#include "common.h"
#include "m2c_compat.h"

typedef struct S_80027B44_0 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80027B44_0;   /* arg0 in func_80027B44 */

typedef struct S_80027B44_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80027B44_1;   /* ((S_80027B44_0 *)arg0)->unk_04 in func_80027B44 */

typedef struct S_80027B44_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80027B44_2;   /* ((S_80027B44_1 *)(((S_80027B44_0 *)arg0)->unk_04))->unk_04 in func_80027B44 */
/* Store the ratio scaled by 144 in the object's nested 16-bit field. */
void func_80027B44(S_80027B44_0 *object, s32 numerator, s32 denominator) {
    ((S_80027B44_2 *)(((S_80027B44_1 *)(object->unk_04))->unk_04))->unk_0A = (s16) ((s32) (numerator * 0x90) / denominator);
}
