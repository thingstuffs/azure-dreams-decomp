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

/* Initializes a subrecord pair with shared data and the default color entry. */
void initSubRecordPair(void *record_pair, void *init_data)
{
    func_80049CF4(record_pair, init_data);
    func_800499E8((u8 *)record_pair + 0x18, init_data, &D_80080B54[0]);
}
