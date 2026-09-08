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

/* Initializes the object from its table entry and resets the companion state. */
void func_800CED24(Rec_func_80094268_arg0 *object, S_800CED24_1 *state, M2C_UNK init_data) {
    s8 entry_value;

    func_800C2E84(object, init_data, &D_800D72D4);
    D_80082660[5].unk0 = 0;
    entry_value = D_80082660[object->unk_60].unk2;
    object->unk_54 = &D_800CE8CC;
    object->unk_90.as_s16 = (s16) entry_value;
    state->unk_14 = 0xFFF60000;
}
