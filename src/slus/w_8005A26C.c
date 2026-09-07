#include "common.h"

/* D_80086A40[16]: slot table, 0x1C-byte stride (see sibling funcs
 * func_8005AC68/func_80057A50/func_8005A428/func_8005B470). This function
 * only touches the marker (0x00) and three trailing bytes (0x19/0x1A/0x1B),
 * likely default volume/pan values. */
typedef struct {
    /* 0x00 */ s16 marker;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 pad14[5];
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
} S_80086A40; /* size 0x1C (28) */

/* D_800869C0[16]: 8-byte-stride table immediately preceding D_80086A40
 * (0x800869C0 + 16*8 == 0x80086A40). Not referenced by any other matched
 * function yet. */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
} S_800869C0; /* size 0x8 */

/* D_80086C00: sound-slot table, 12-byte stride (canonical layout from
 * func_8005AE08/func_8005AE90/func_8005B2C8/func_8005B27C/func_8005C5D0).
 * This init function walks 16 entries (0x80086A40 + 16*0x1C == 0x80086C00,
 * and 0x80086C00 + 16*0xC == 0x80086CC0), touching field_0/field_2/field_8/
 * field_A but not field_4. */
typedef struct {
    /* 0x00 */ s16 field_0;
    /* 0x02 */ s16 field_2;
    /* 0x04 */ s32 field_4;
    /* 0x08 */ u16 field_8;
    /* 0x0A */ u16 field_A;
} S_80086C00; /* size 0xC (12) */

extern S_80086A40 D_80086A40[16];
extern S_800869C0 D_800869C0[16];
extern S_80086C00 D_80086C00[16];
extern s32 D_80086D4C[3]; /* forced hi/lo via size > 8 */

/* Re-initializes the D_80086A40/D_800869C0/D_80086C00 slot tables to their
 * default/free state, then resets a counter global. */
void func_8005A26C(void)
{
    s32 i;
    S_80086A40 *p;
    S_800869C0 *q;
    S_80086C00 *r;
    s16 c_marker;
    u8 c_vol;
    u8 c_pan;
    s16 c_free;
    u16 c_val;

    i = 0;
    c_marker = -1;
    c_vol = 0x7F;
    c_pan = 0x40;
    p = D_80086A40;
    do {
        p->marker = c_marker;
        p->unk19 = c_vol;
        p->unk1A = c_vol;
        p->unk1B = c_pan;
        i++;
        p++;
    } while (i < 16);

    i = 0;
    c_free = -1;
    c_val = 0x7F;
    q = D_800869C0;
    r = D_80086C00;
    do {
        r->field_0 = c_free;
        r->field_2 = 0;
        r->field_A = c_val;
        r->field_8 = c_val;
        q->unk04 = 0;
        q->unk00 = 0;
        q++;
        i++;
        r++;
    } while (i < 16);

    D_80086D4C[0] = 0x1000;
}
