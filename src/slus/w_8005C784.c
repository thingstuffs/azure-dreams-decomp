#include "common.h"

/* Looks up D_80073740[idx] as a flags value, builds a request struct with
 * unk0=flags, unk4=0, calls func_8005FA34 which fills unk8/unkA (s16
 * outputs), then rescales each output (>>7) into the caller's out-pointers.
 * Always returns 0. */
/* Request/response struct passed to func_8005FA34: caller pre-fills unk0
 * (flags from D_80073740[idx]) and zeroes unk4; callee writes back two
 * s16 outputs at unk8/unkA which the caller rescales (>>7) into *a1/*a2. */
typedef struct S_8005C784 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    u8 pad[0x40 - 0xC];
} S_8005C784;

extern s32 D_80073740[];
extern void func_8005FA34(S_8005C784 *a0);

s32 func_8005C784(s16 a0, s16 *a1, s16 *a2)
{
    S_8005C784 sp10;

    sp10.unk4 = 0;
    sp10.unk0 = D_80073740[a0];
    func_8005FA34(&sp10);
    *a1 = sp10.unk8 >> 7;
    *a2 = sp10.unkA >> 7;
    return 0;
}
