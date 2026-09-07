#include "common.h"

extern s32 D_00003F50[];
extern s32 D_00003FCC[];
extern s32 D_000045F8[];

extern s32 func_80003544(s32 arg0);
extern s32 func_800036D8(s32 arg0, s32 arg1);

s32 func_808B81FC(void) {
    s32 index;
    s32 held;

    index = D_00003F50[0];
    held = D_00003FCC[index * 8];
    func_800036D8(index, 3);
    func_80003544(3);
    return held + D_000045F8[0];
}

/* MECHANISM: Named overlay globals force the retail hi/lo address forms.
   The table is word-indexed by index*8, emitting the byte stride sll 5.
   Holding the table value across both calls naturally allocates only s0. */
