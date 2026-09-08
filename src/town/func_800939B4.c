#include "common.h"


extern void func_80091000(void);
extern void func_80093D48(void *, void *, s32);
extern void func_80093E98(void *, void *, s32);
extern u8 D_80083160[];


typedef struct S_80091114_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80091114_0;   /* state in func_80091114 */

typedef struct S_80091114_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_80091114_1;   /* arg1 in func_80091114 */

void func_80091114(s32 *arg0, S_80091114_1 *arg1, s32 arg2) {
    register s32 saved_arg2 ASM_REG("$19") = arg2;   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 previous;
    register u8 *state = D_80083160;

    previous = *arg0;
    func_80091000();

    if (previous == *arg0) {
        if (!(((S_80091114_0 *)state)->unk_08 & 0x20)) {
            func_80093D48(arg0, arg1, saved_arg2);
            return;
        }

        if ((arg1->unk_0C == 0) &&
            (arg1->unk_10 == 0)) {
            func_80093E98(arg0, arg1, saved_arg2);
        }
    }
}
