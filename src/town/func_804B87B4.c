#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct Inner {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;


/* Set the current inner object's unk4 and unk8 values to 1696 and 864. */
void func_80016FB4(void) {
    ((Inner *)D_80016000->unk_1C)->unk4 = 1696;
    ((Inner *)D_80016000->unk_1C)->unk8 = 864;
}
