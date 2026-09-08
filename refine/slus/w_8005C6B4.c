#include "common.h"

/* struct passed to func_8005F134: flags word, count word, an unused word,
 * then two packed 16-bit fields; the (0x40-byte) struct's remaining tail is
 * padding never touched here. Only the fields this function sets are
 * known/used. */
typedef struct S_8005C6B4 {
    s32 flags;             /* 0x0 */
    s32 count;             /* 0x4 */
    s16 f8;                /* 0x8 */
    s16 fa;                /* 0xA */
    u8  pad[0x40 - 0xC];   /* 0xC..0x3F (unused here) */
} S_8005C6B4;

extern s32 D_80073740[128];
extern void func_8005F134(void *a0);

/* Dispatches an effect request with table flags, count 3, and two scaled 7-bit values. */
s32 func_8005C6B4(s32 flag_index, s32 first_value, s32 second_value)
{
    S_8005C6B4 request;
    s32 flags;

    request.count = 3;
    flags = D_80073740[(s16)flag_index];
    request.f8 = (first_value & 0x7F) << 7;
    request.fa = (second_value & 0x7F) << 7;
    request.flags = flags;

    func_8005F134(&request);

    return 0;
}
