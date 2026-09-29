#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
} StructB;


/* Set the linked structure's two values to 1248 and 1184. */
void func_8001707C(void) {
    ((StructB *)D_80016000->unk_1C)->unk_4 = 1248;
    ((StructB *)D_80016000->unk_1C)->unk_8 = 1184;
}
