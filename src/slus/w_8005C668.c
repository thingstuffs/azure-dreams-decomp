#include "common.h"

/* Request struct passed to func_8005F134 (an ~0x40-byte object; here only
 * flags word (offset 0), type/count word (offset 4), and two s16 params
 * (offsets 8/0xA) are initialized -- the rest is left as stack garbage). */
typedef struct S_8005C668 {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    u8 pad[0x40 - 0xC];
} S_8005C668;

extern s32 D_80073740[];
extern void func_8005F134(void *a0);

/* Builds a partially-filled request struct (flags=D_80073740[a0], type=3,
 * two raw s16 params) and forwards it to func_8005F134; always returns 0. */
s32 func_8005C668(s16 a0, s16 a1, s16 a2)
{
    S_8005C668 sp10;

    sp10.unk4 = 3;
    sp10.unk0 = *(&D_80073740[a0]);
    sp10.unk8 = a1;
    sp10.unkA = a2;
    func_8005F134(&sp10);
    return 0;
}
