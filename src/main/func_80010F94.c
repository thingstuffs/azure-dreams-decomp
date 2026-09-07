#include "common.h"

typedef struct S_80023F94_0 {
    s32 unk_00;
    s32 unk_04;
} S_80023F94_0;   /* arg0 in func_80023F94 */

void func_80023F94(S_80023F94_0 *arg0, s32 arg1, s32 arg2) {
    arg0->unk_00 = arg2;
    arg0->unk_04 = arg1;
}
