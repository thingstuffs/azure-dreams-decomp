#include "common.h"
#include "m2c_compat.h"

s32 func_800AAE98();                          /* extern */
M2C_UNK func_800AAFE0();          /* extern */
M2C_UNK func_800AB014();             /* extern */
s32 func_800AB030();                          /* extern */
extern M2C_UNK D_800AB5C0;

typedef struct {
    s16 unk0;
    u16 value;
} LocalEntry;

typedef struct S_800AB708_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800AB708_0;   /* arg1 in func_800AB708 */

typedef struct S_800AB708_1 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x4];
    s16 unk_72;
    u8 pad_74[0x1C];
    s16 unk_90;
} S_800AB708_1;   /* arg0 in func_800AB708 */

/* Move the position halfway toward the adjusted target and update the object state. */
void func_800AB708(S_800AB708_1 *object, S_800AB708_0 *position) {
    LocalEntry target_entries[6];
    void *object_arg;
    register s32 offset ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 total_offset;
    u16 target_z;

    func_800AAFE0(target_entries, 4);
    offset = func_800AAE98(position);
    ASM_KEEP(offset);   /* MATCH pin: retail schedule: same instructions, different order without it */
    object_arg = object;
    ASM_KEEP(object_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
    total_offset = offset;
    offset = func_800AB030(object_arg);
    target_z = target_entries[2].value;
    total_offset += offset;
    target_entries[2].value = target_z - total_offset;
    position->unk_02 = (s16) ((s32) (position->unk_02 + (s16) target_entries[0].value) / 2);
    position->unk_06 = (s16) ((s32) (position->unk_06 + (s16) target_entries[1].value) / 2);
    position->unk_0A = (s16) ((s32) (position->unk_0A + (s16) target_entries[2].value) / 2);
    func_800AB014(object, 4);
    if (object->unk_90 >= 0x64) {
        object->unk_50 = &D_800AB5C0;
        object->unk_72 = 0;
        object->unk_6C = 0xA;
    }
}
