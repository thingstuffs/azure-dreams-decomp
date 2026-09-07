#include "common.h"

typedef struct S_80024918_0 {
    void * unk_00;
    u8 pad_04[0x30];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x28];
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
} S_80024918_0;   /* arg0 in func_80024918 */

typedef struct S_80024918_1 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_80024918_1;   /* temp_v1 in func_80024918 */



extern s32 func_80024700();
extern u32 func_800644B8();
extern s32 D_800814A0;

/* Advance object motion and animation, setting completion flags after nine ticks. */
void func_80024918(void *object) {
    s16 next_tick;
    s32 velocity_y;
    s32 velocity_z;
    s32 position_y;
    void *state;

    state = ((S_80024918_0 *)object)->unk_00;
    ((S_80024918_1 *)state)->unk_1A = ((S_80024918_1 *)state)->unk_1A + 1;
    ((S_80024918_0 *)object)->unk_78 = func_800644B8(((S_80024918_0 *)object)->unk_74 << 8) >> 6;
    velocity_y = ((S_80024918_0 *)object)->unk_44;
    ((S_80024918_0 *)object)->unk_34 += ((S_80024918_0 *)object)->unk_40;
    position_y = ((S_80024918_0 *)object)->unk_38;
    velocity_z = ((S_80024918_0 *)object)->unk_48;
    ((S_80024918_0 *)object)->unk_38 = position_y + velocity_y;
    ((S_80024918_0 *)object)->unk_3C += velocity_z;
    func_80024700(object, velocity_y, velocity_z);
    next_tick = (s16)((S_80024918_0 *)object)->unk_74 + 1;
    ((S_80024918_0 *)object)->unk_74 = next_tick;
    if (next_tick >= 9) {
        (*(u16 *)((u8 *)object + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
