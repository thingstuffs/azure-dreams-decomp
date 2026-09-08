#include "common.h"
#include "m2c_compat.h"

extern s32 D_80083788;
extern M2C_UNK D_800C5BA8;
extern s32 D_800D0428;

typedef struct S_800C5B48_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800C5B48_0;   /* arg1 in func_800C5B48 */

typedef struct S_800C5B48_1 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C5B48_1;   /* arg0 in func_800C5B48 */

/* Move the motion value halfway toward the target sum and switch callbacks when the countdown expires. */
void func_800C5B48(S_800C5B48_1 *actor, S_800C5B48_0 *motion) {
    s32 current_value;
    u16 ticks_left;

    current_value = motion->unk_08;
    motion->unk_08 = (s32) (current_value + ((s32) ((D_80083788 + D_800D0428) - current_value) / 2));
    ticks_left = actor->unk_6C - 1;
    actor->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        actor->unk_54 = &D_800C5BA8;
    }
}
