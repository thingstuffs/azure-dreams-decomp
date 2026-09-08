#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AF148_0_pre {
    u16 unk_00;
} S_800AF148_0_pre;   /* the 0x2 bytes before temp_s0 in func_800AF148, addressed as temp_s0[-1] */

typedef struct S_800AF148_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AF148_0;   /* temp_s0 in func_800AF148 */


M2C_UNK func_8004B248();                         /* extern */
M2C_UNK func_800AF0E0();                    /* extern */
extern s32 D_800814A0[];

/* Updates an object's state and sets its local and global 0x8000 flags. */
void func_800AF148(s32 objectAddress) {
    void *objectFields;

    if (objectAddress != 0) {
        objectFields = objectAddress + 0x20;
        func_800AF0E0(((S_800AF148_0 *)objectFields)->unk_D8, ((S_800AF148_0 *)objectFields)->unk_28);
        func_8004B248(objectAddress + 0xFC);
        ((S_800AF148_0_pre *)objectFields)[-1].unk_00 = (u16) (((S_800AF148_0_pre *)objectFields)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32) (D_800814A0[0] | 0x8000);
    }
}
