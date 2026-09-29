#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;


/* Set the inner object's unk4 and unk8 fields to 1248 and 1184. */
void func_80016EF4(void) {
    ((Inner *)D_80016000->unk_1C)->unk4 = 1248;
    ((Inner *)D_80016000->unk_1C)->unk8 = 1184;
}
