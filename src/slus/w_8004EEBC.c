#include "common.h"

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

/* Selects one of two embedded subobjects according to the linked state, when present. */
void func_8004EEBC(S_8004EEBC_Obj *object)
{
    if (object->unk4 != 0) {
        if (object->unk4->unk0 != 0) {
            object->unk28C = 0;
            object->unk29C = (char *)object + 0xF8;
        } else {
            object->unk28C = (char *)object + 0x80;
            object->unk29C = 0;
        }
    }
}
