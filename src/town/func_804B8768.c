#include "common.h"
#include "shared/record_ptrs.h"

typedef struct StructB {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;

typedef struct StructA {
    u8 pad[0x1C];
    StructB *unk1C;
} StructA;


/* Set the referenced structure's two values to 1248 and 992. */
void func_80016F68(void) {
    ((StructA *)D_80016000)->unk1C->unk4 = 1248;
    ((StructA *)D_80016000)->unk1C->unk8 = 992;
}
