#include "common.h"

#include "common.h"

typedef s8 s8_local;

typedef struct S_80037030_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void ** unk_10;
} S_80037030_0;   /* arg0 in func_80037030 */

typedef struct S_80037030_1 {
    u8 pad_00[0xC];
    s32 * unk_0C;
} S_80037030_1;   /* call_arg2 in func_80037030 */



extern void func_80036D4C(s32, void *, s32 *, s16, s32, s32);
extern void func_80037090(void *, void *, void *);

void func_80037030(void *arg0, void *arg1, s32 *arg2, s16 arg3, s16 arg4, s32 arg5) {
    void *call_arg0;
    void *call_arg1;
    S_80037030_1 *call_arg2;

    func_80036D4C((s32)arg0, arg1, arg2, arg3, arg4, arg5);
    call_arg0 = (s8_local *)arg0 + 0x20;
    call_arg1 = ((S_80037030_0 *)arg0)->unk_08;
    call_arg2 = ((S_80037030_0 *)arg0)->unk_0C;
    ((S_80037030_0 *)arg0)->unk_10 = (void *)&func_80037090;
    call_arg2->unk_0C = 0;
    func_80037090(call_arg0, call_arg1, call_arg2);
}
