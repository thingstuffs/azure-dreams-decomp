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

void func_800C2988(void *arg0, void *arg1) {
    S_800C2988_1 *object = arg0;
    register S_800C2988_0 *motion ASM_REG("$16") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    u32 page;

    if (D_8006ADD4 == 0x17000C) {
        ASM_KEEP(object);   /* MATCH: Keep object live in each arm and preserve the shared-tail jump. */
        page = 0xFF600000;
    } else {
        ASM_KEEP(object);   /* MATCH: Keep object live in each arm and preserve the shared-tail jump. */
        page = 0xFFE00000;
    }
    motion->unk_08 = page;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    func_8008F074(object, motion, func_800C296C(0));
    object->unk_50 = &D_800C2A10;
    object->unk_16 = (s16) ((object->unk_72 - 0x800) & 0xFFF);
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
}

/* MECHANISM: Guarded s1/s0 pins encode the retail arg0/arg1 callee-saved roles and 0x20 frame.
   ASM_PAGEBASE_PIN preserves the dead 0xFF600000 page in the sibcall delay slot.
   A post-store scheduling fence restores retail's lui;sw;jal;move emission order. */
