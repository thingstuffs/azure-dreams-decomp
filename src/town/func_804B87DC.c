#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct Struct_804B87DC_Inner {
    s32 unk_0;
    s32 unk_4;
    s32 unk_8;
} Struct_804B87DC_Inner;


/* Set the current object's inner values to 1696 and 1184. */
void func_80016FDC(void) {
    ((Struct_804B87DC_Inner *)D_80016000->unk_1C)->unk_4 = 1696;
    ((Struct_804B87DC_Inner *)D_80016000->unk_1C)->unk_8 = 1184;
}
