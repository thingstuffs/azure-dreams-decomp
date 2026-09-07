#include "common.h"

typedef struct EntryS_80047738 {
    /* 0x0 */ u16 unk00;
    /* 0x2 */ u16 pad02;
    /* 0x4 */ s32 unk04;
} EntryS_80047738; /* size 0x8 */

typedef struct S_80047738 {
    /* 0x00 */ EntryS_80047738 *unk00;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 pad05[3];
    /* 0x08 */ s32 unk08;
    /* 0x0C */ u8 pad0C[0x14 - 0x0C];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 pad16[0x28 - 0x16];
    /* 0x28 */ EntryS_80047738 ****unk28;
} S_80047738;

/* Selects table entry [a1][a2] via a quadruply-indirected table pointer,
 * caches the entry pointer + its second word into a0, records the index,
 * and clears flag bit 0x40 on a0. */
void func_80047738(S_80047738 *a0, s16 a1, s16 a2)
{
    EntryS_80047738 **p = **a0->unk28;
    EntryS_80047738 *e = p[a1] + a2;

    a0->unk00 = e;
    a0->unk08 = e->unk04;
    a0->unk04 = (u8)a2;
    a0->unk14 &= 0xFFBF;
}
