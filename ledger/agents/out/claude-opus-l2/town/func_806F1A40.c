#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"

typedef struct S_806F1A40_1 {
    u8 pad_00[0x334];
    s32 (*unk_334)(M2C_UNK);
} S_806F1A40_1;

M2C_UNK func_80017744();
M2C_UNK func_800177BC();
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80017A00;
extern M2C_UNK *D_80017A98;

/* Ask the scene object for its mode and raise the matching 0xBE9 event, then arm the next handler. */
void func_806F1A40(void) {
    if (((S_806F1A40_1 *)(D_80016000->unk_20))->unk_334(0) != 5) {
        func_80017744(0xBE9);
    } else {
        func_800177BC(0xBE9);
    }
    D_80017A98 = &D_80017A00;
}
