#include "common.h"

/* Entry struct pointed to by S_80047784.unk00; only the leading u16 field is
 * accessed by this function. */
typedef struct EntryS_80047784 {
    /* 0x00 */ u16 unk00;
} EntryS_80047784;

/* Object shared with func_80047738 (its first parameter). */
typedef struct S_80047784 {
    /* 0x00 */ EntryS_80047784 *unk00;
    /* 0x04 */ u8 pad04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 pad06[0x14 - 0x06];
    /* 0x14 */ u16 unk14;
} S_80047784;

extern void func_80047738(S_80047784 *a0, s16 a1, s16 a2);
extern void func_80047694(void *arg0);

/* Re-select the current table entry via func_80047738, derive a rate byte
 * (entry's leading u16 divided by the global divisor table's first byte),
 * clear flag bits 0x6000 in unk14, store the rate, and re-run func_80047694. */
void func_80047784(S_80047784 *a0, s16 a1, s16 a2)
{
    extern u8 D_80080A84[16];

    func_80047738(a0, a1, a2);
    a0->unk05 = a0->unk00->unk00 / D_80080A84[0];
    a0->unk14 &= 0x9FFF;
    func_80047694(a0);
}
