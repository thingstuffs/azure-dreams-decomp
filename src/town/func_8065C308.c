#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern s32 D_800183C8;
extern s32 D_800183D0;


/* Call the context callback with the two global values. */
void func_8065C308(void) {
    D_80016000->unk_20->callback_04C(D_800183C8, D_800183D0);
}
