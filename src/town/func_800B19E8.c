#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_800AF148_0_pre {
    u16 unk_00;
} S_800AF148_0_pre;

typedef struct S_800AF148_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xAC];
    s32 unk_D8;
} S_800AF148_0;


M2C_UNK func_8004B248();                         /* extern */
void townSendItemMenuPageEntriesToFormatter();                    /* extern */

/* Updates an object's state and sets its local and global 0x8000 flags. */
void townReleaseItemMenuListObject(s32 objectAddress) {
    void *objectFields;

    if (objectAddress != 0) {
        objectFields = objectAddress + 0x20;
        townSendItemMenuPageEntriesToFormatter(((S_800AF148_0 *)objectFields)->unk_D8, ((S_800AF148_0 *)objectFields)->unk_28);
        func_8004B248(objectAddress + 0xFC);
        ((S_800AF148_0_pre *)objectFields)[-1].unk_00 = (u16) (((S_800AF148_0_pre *)objectFields)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
