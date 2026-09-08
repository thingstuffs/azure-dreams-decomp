#include "common.h"
#include "m2c_compat.h"


typedef struct S_800A7950_0 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800A7950_0;   /* arg2 in func_800A7950 */

typedef struct S_800A7950_1 {
    u8 pad_00[0x6C];
    s16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} S_800A7950_1;   /* arg0 in func_800A7950 */


extern void func_800A79C8(S_800A7950_1 *, void *, S_800A7950_0 *);
void func_800A7950(S_800A7950_1 *arg0, void *arg1, S_800A7950_0 *arg2) {
    s16 temp_v0;

    arg2->unk_1C = (s16) (((arg0->unk_90 - arg0->unk_6C) * 8) + 0x1000);
    arg2->unk_1E = (s16) (0x1000 - ((arg0->unk_90 - arg0->unk_6C) * 2));
    temp_v0 = (u16) arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if (temp_v0 < 0) {
        func_800A79C8(arg0, arg1, arg2);
    }
}
