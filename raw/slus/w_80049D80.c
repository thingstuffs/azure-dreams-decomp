#include "common.h"

/* CVECTOR-style color entry: r,g,b + a 4th (pad/code) byte.
   Declared as an array so its total size > 8, forcing %hi/%lo access
   (the maspsx delay-store patch requires this); array length is provisional. */
typedef struct S_80080B54 {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} S_80080B54;

extern S_80080B54 D_80080B54[3];

extern void *func_80049CF4(void *a0, void *a1);
extern void func_800499E8(void *a0, void *a1, void *a2);

void initSubRecordPair(void *a0, void *a1)
{
    func_80049CF4(a0, a1);
    func_800499E8((u8 *)a0 + 0x18, a1, &D_80080B54[0]);
}
