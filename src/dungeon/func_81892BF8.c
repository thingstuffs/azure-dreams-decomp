#include "common.h"
#include "m2c_compat.h"

typedef struct S_81892BF8_0_pre {
    u16 unk_00;
} S_81892BF8_0_pre;   /* the 0x2 bytes before arg0 in func_81892BF8, addressed as arg0[-1] */

typedef struct S_81892BF8_0 {
    void * unk_00;
    u16 unk_04;
    s16 unk_06;
} S_81892BF8_0;   /* arg0 in func_81892BF8 */

typedef struct S_81892BF8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81892BF8_1;   /* temp_v1 in func_81892BF8 */


extern s32 D_800814A0[3];

/* Increment both counters and set completion flags when the count reaches its limit. */
void func_81892BF8(void *counterState) {
    u16 incrementedCount;
    S_81892BF8_1 *linkedCounter;

    linkedCounter = ((S_81892BF8_0 *)counterState)->unk_00;
    linkedCounter->unk_14 = (u16) (linkedCounter->unk_14 + 1);
    incrementedCount = ((S_81892BF8_0 *)counterState)->unk_04 + 1;
    ((S_81892BF8_0 *)counterState)->unk_04 = incrementedCount;
    if ((s16) incrementedCount >= ((S_81892BF8_0 *)counterState)->unk_06) {
        ((S_81892BF8_0_pre *)counterState)[-1].unk_00 = (u16) (((S_81892BF8_0_pre *)counterState)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
