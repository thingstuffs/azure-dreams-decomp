#include "common.h"

/* Resets a D_80086C00[] slot (given by arg0) to its free/default state,
 * bracketed by D_80085F98 mode-flag set/clear and calls to func_80059D1C()
 * and func_80056A08(). */
/* S_80086C00: 12-byte-stride sound-driver "sequence slot" table (8 entries),
 * indexed by the slot index arg0. Canonical layout established by sibling
 * functions (w_8005AE08.c, w_8005AE90.c, w_8005B27C.c, w_8005C5D0.c). */
typedef struct S_80086C00 {
    s16 field_0;   /* 0x0: -1 == free slot */
    s16 field_2;   /* 0x2: type/status */
    s32 field_4;   /* 0x4: data pointer / word value */
    u16 field_8;   /* 0x8 */
    u16 field_A;   /* 0xA */
} S_80086C00;

extern S_80086C00 D_80086C00[8];
extern s32 D_80085F98[4]; /* forced hi/lo access via size > 8 */

extern void func_80059D1C(void);
extern void func_80056A08(void);

void func_8005AFF4(s32 a0)
{
    s16 idx;

    D_80085F98[0] = 1;
    func_80059D1C();
    func_80056A08();
    idx = (s16)a0;

    D_80086C00[idx].field_0 = -1;
    D_80086C00[idx].field_2 = 0;
    D_80086C00[idx].field_A = 0x7F;
    D_80086C00[idx].field_8 = 0x7F;

    D_80085F98[0] = 0;
}
