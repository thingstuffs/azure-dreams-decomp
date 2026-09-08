#include "common.h"

/* Guards on a0's byte field at offset 0x9B == 0xFF: if so, marks bit 0x8000
 * on a0's 16-bit flags word located 2 bytes before the parameter itself,
 * and marks bit 0x8000 on the global 32-bit flags word D_800814A0 (same
 * global/sibling shape as func_800510DC/func_8004B298/func_8004F52C).
 * Afterward unconditionally forwards a2 to func_800478B8. Matches at
 * gcc 2.7.2 -O2 -G0: a plain `extern int D_800814A0;` scalar with
 * small-data disabled forces lui/%hi + lw|sw/%lo addressing. */

typedef struct {
    u8 pad[0x9B + 1];
} S_800D2200_a0;

extern int D_800814A0; /* global 32-bit "used"/flags word */
extern void func_800478B8(void *arg0);

/* Marks the record and global flags for a sentinel byte, then processes the target. */
void func_800D7960(S_800D2200_a0 *record, s32 unused, void *target)
{
    if (record->pad[0x9B] == 0xFF) {
        *(u16 *)((u8 *)record - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    func_800478B8(target);
}
