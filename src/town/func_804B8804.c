#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct Inner {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;


/* Sets the global object's inner fields to 1248 and 1184. */
void func_80017004(void) {
    Rec_D_80016000 *outer = D_80016000;
    ((Inner *)outer->unk_1C)->unk4 = 1248;
    ((Inner *)outer->unk_1C)->unk8 = 1184;
}
