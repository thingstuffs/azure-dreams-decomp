#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;


/* Set the referenced object's unk4 and unk8 fields to 800 and 736. */
void func_80016EA4(void) {
    ((StructB *)D_80016000->unk_1C)->unk4 = 800;
    ((StructB *)D_80016000->unk_1C)->unk8 = 736;
}
