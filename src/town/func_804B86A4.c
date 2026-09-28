#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;

typedef struct {
    char pad[0x1C];
    StructB *unk1C;
} StructA;


/* Set the referenced object's unk4 and unk8 fields to 800 and 736. */
void func_80016EA4(void) {
    ((StructA *)D_80016000)->unk1C->unk4 = 800;
    ((StructA *)D_80016000)->unk1C->unk8 = 736;
}
