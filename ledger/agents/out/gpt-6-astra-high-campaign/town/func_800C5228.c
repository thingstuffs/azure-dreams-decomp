#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F074();         /* extern */
s32 func_800C296C();                         /* extern */
extern s32 D_8006ADD4;
extern M2C_UNK D_800C2A10;

typedef struct S_800C2988_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C2988_0;   /* motion in func_800C2988 */

typedef struct S_800C2988_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x38];
    M2C_UNK * unk_50;
    u8 pad_54[0x1E];
    u16 unk_72;
} S_800C2988_1;   /* object in func_800C2988 */

/* Sets the motion page and updates the object state and orientation. */
void func_800C2988(void *object_data, void *motion_data) {
    S_800C2988_1 *object = object_data;
    register S_800C2988_0 *motion ASM_REG("$16") = motion_data;

    u32 page;

    if (D_8006ADD4 == 0x17000C) {
        page = 0xFF600000;
    } else {
        ASM_KEEP(object);
        page = 0xFFE00000;
    }
    motion->unk_08 = page;
    ASM_SCHED_BARRIER();
    func_8008F074(object, motion, func_800C296C(0));
    object->unk_50 = &D_800C2A10;
    object->unk_16 = (s16) ((object->unk_72 - 0x800) & 0xFFF);
    ASM_KEEP(motion);
}
