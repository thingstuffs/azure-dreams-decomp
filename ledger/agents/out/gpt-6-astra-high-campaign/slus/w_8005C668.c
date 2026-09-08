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

/* Sends a type-3 request with indexed flags and two s16 parameters, then returns zero. */
s32 func_8005C668(s16 flags_index, s16 first_value, s16 second_value)
{
    S_8005C668 request;

    request.unk4 = 3;
    request.unk0 = *(&D_80073740[flags_index]);
    request.unk8 = first_value;
    request.unkA = second_value;
    func_8005F134(&request);
    return 0;
}
