#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct StructB {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} StructB;


/* Set the referenced structure's two values to 1248 and 992. */
void func_80016F68(void) {
    ((StructB *)D_80016000->unk_1C)->unk4 = 1248;
    ((StructB *)D_80016000->unk_1C)->unk8 = 992;
}
