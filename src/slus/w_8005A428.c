#include "common.h"

/* Runs the shared per-frame update (func_80056C30), conditionally runs
 * func_8005863C when the D_80086D4C[0] counter is in (0, 4), then walks the
 * first 8 entries of the D_80086A40 slot table, calling func_8005A1D0 on the
 * unk10 field of every entry whose unk00 slot-marker is non-negative, and
 * finally re-initializes the slot table via func_8005A26C. */
/* Slot-table element (see sibling func_80057A50 for the confirmed 0x1C-byte
 * stride layout of D_80086A40). Only the fields this function touches are
 * named; the rest is padding. */
typedef struct {
    /* 0x00 */ s16 unk00;      /* slot-marker; negative == unused */
    /* 0x02 */ u8 pad02[0xE];
    /* 0x10 */ s32 unk10;      /* value passed to func_8005A1D0 */
    /* 0x14 */ u8 pad14[0x8];
} S_8005A428_D80086A40; /* size 0x1C (28) */

extern int D_80086D4C[3]; /* forced hi/lo via size > 8 */
extern S_8005A428_D80086A40 D_80086A40[16];

extern void func_80056C30(void);
extern void func_8005863C(void);
extern void func_8005A1D0(s32 arg0);
extern void func_8005A26C(void);

void func_8005A428(void)
{
    s32 i;
    S_8005A428_D80086A40 *p;

    func_80056C30();

    if (D_80086D4C[0] > 0)
    {
        if (D_80086D4C[0] < 4)
        {
            func_8005863C();
        }
    }
    i = 0;

    p = D_80086A40;
    for (; i < 8; i++, p++)
    {
        if (p->unk00 >= 0)
        {
            func_8005A1D0(p->unk10);
        }
    }

    func_8005A26C();
}
