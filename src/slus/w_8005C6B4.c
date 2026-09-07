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

/* summary: builds a local effect-request struct with flags looked up from
 * D_80073740[(s16)a0], a fixed count of 3, and two 7-bit values (a1,a2)
 * each shifted left 7 and packed as halfwords at offsets 0x8/0xA of the
 * (0x40-byte) struct, then dispatches it via func_8005F134. Always returns 0. */
s32 func_8005C6B4(s32 a0, s32 a1, s32 a2)
{
    S_8005C6B4 st;
    s32 flags;

    st.count = 3;
    flags = D_80073740[(s16)a0];
    st.f8 = (a1 & 0x7F) << 7;
    st.fa = (a2 & 0x7F) << 7;
    st.flags = flags;

    func_8005F134(&st);

    return 0;
}
