#include "common.h"
#include "m2c_compat.h"

extern void *D_800E3D7C;

typedef struct S_800CDE0C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    s32 unk_5C;
} S_800CDE0C_0;   /* var_a0 in func_800CDE0C */

/* Set flag 0x40000000 on every record in the circular list. */
void func_800CDE0C(void) {
    void *first_record;
    S_800CDE0C_0 *record;

    record = D_800E3D7C;
    first_record = record;
    do {
        record->unk_1C = (s32) (record->unk_1C | 0x40000000);
        record = record->unk_5C + 0x20;
    } while (record != first_record);
}
