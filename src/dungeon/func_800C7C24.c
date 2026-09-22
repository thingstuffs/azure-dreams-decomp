#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80099844();
extern void func_800A6508(void);
extern M2C_UNK func_800C5BBC();
extern s32 func_800C8844();
extern M2C_UNK func_800DC1B8();
extern s32 D_800DCF1C;
extern M2C_UNK D_800E1C14;
extern u8 D_800E3D40;


typedef struct S_800CD384_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD384_0_pre;   /* the 0x14 bytes before object in func_800CD384, addressed as object[-1] */


typedef struct S_800CD384_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD384_1;   /* entry in func_800CD384 */

/* Run the 8-slot request for the object with the budget the global mode picks; on refusal give the fallback cue, otherwise apply the effect and raise the tile marker unless the owning entry is flagged. */
s32 func_800CD384(void *object) {
    s32 amount;
    S_800CD384_1 *entry;

    amount = 0x40;
    if (D_800E3D40 != 0) {
        amount = 0x400;
    }
    if (func_800C8844(object, amount, 8) == 0) {
        if (((Rec_D_800E3D7C *)object)->unk_14.as_s32 & 0x4000) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    func_80099844(object, &D_800E1C14);
    if (((Rec_D_800E3D7C *)object)->unk_10.at03_u8.v == 0) {
        func_800DC1B8(D_800DCF1C);
    }
    entry = ((S_800CD384_0_pre *)object)[-1].unk_00;
    if (!(entry->unk_14 & 0x8000)) {
        func_800C5BBC((entry->unk_24 << 6) | 0x20,
                      (entry->unk_25 << 6) | 0x20,
                      ((Rec_D_800E3D7C *)object)->unk_88.as_s16, 0x802080, 0x20, 1);
    }
    return 1;
}
