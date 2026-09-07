#include "common.h"

typedef struct S_800981D4_0 {
    u8 pad_00[0x6];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800981D4_0;   /* arg1 in func_800981D4 */



extern s32 func_8009822C(void);
extern s32 func_80098DC0(void);

s32 func_800981D4(s32 arg0, S_800981D4_0 *arg1)
{
    s16 current;
    u16 raw;
    s32 result;

    current = arg1->unk_06.s;
    raw = arg1->unk_06.u;
    if (current < 0x300) {
        current = raw + 4;
        arg1->unk_06.s = current;
        if (current < 0x300) {
            result = 0x300;
        } else {
            return func_8009822C();
        }
    } else {
        current = raw - 4;
        arg1->unk_06.s = current;
        if (current < 0x301) {
            result = 0x300;
            arg1->unk_06.s = result;
            result = func_80098DC0();
        } else {
            result = 0x300;
        }
    }
    return result;
}
