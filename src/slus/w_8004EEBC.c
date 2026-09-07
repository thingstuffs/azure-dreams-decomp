#include "common.h"

/* If arg0->unk4 is set and arg0->unk4->unk0 is nonzero, select the sub-object
 * at offset 0xF8 as "current" (0x29C) and clear the one at 0x28C; otherwise
 * select the sub-object at offset 0x80 as "current" (0x28C) and clear 0x29C.
 * If arg0->unk4 is NULL, do nothing. */
typedef struct S_8004EEBC_Inner {
    int unk0;
} S_8004EEBC_Inner;

typedef struct S_8004EEBC_Obj {
    char pad0[4];
    S_8004EEBC_Inner *unk4;
    char pad8[0x28C - 8];
    void *unk28C;
    char padC[0x29C - 0x290];
    void *unk29C;
} S_8004EEBC_Obj;

void func_8004EEBC(S_8004EEBC_Obj *a0)
{
    if (a0->unk4 != 0) {
        if (a0->unk4->unk0 != 0) {
            a0->unk28C = 0;
            a0->unk29C = (char *)a0 + 0xF8;
        } else {
            a0->unk28C = (char *)a0 + 0x80;
            a0->unk29C = 0;
        }
    }
}
