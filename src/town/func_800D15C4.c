#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    s8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} D_80082660_entry;

M2C_UNK func_800C2E84();          /* extern */
extern D_80082660_entry D_80082660[];
extern M2C_UNK D_800CE8CC;
extern M2C_UNK D_800D72D4;


typedef struct S_800CED24_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CED24_1;   /* arg1 in func_800CED24 */

void func_800CED24(Rec_func_80094268_arg0 *arg0, S_800CED24_1 *arg1, M2C_UNK arg2) {
    s8 byteval;

    func_800C2E84(arg0, arg2, &D_800D72D4);
    D_80082660[5].unk0 = 0;
    byteval = D_80082660[arg0->unk_60].unk2;
    arg0->unk_54 = &D_800CE8CC;
    arg0->unk_90.as_s16 = (s16) byteval;
    arg1->unk_14 = 0xFFF60000;
}
