#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80172E80_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
} S_80172E80_0;   /* arg3 in func_80172E80 */

typedef struct S_80172E80_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172E80_1;   /* flags_base in func_80172E80 */

typedef struct S_80172E80_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172E80_2;   /* arg2 in func_80172E80 */

typedef struct S_80172E80_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80172E80_3;   /* arg0 in func_80172E80 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
M2C_UNK func_8009C93C();
s32 func_800A0134();
s32 func_800A04F0();
s32 func_800A2B5C();
s32 func_800A2CB8();
M2C_UNK func_800C7930();

extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_800E2378;

/* Checks action readiness and initializes the actor state and directional animation. */
s32 func_80172E80(void *action_state, M2C_UNK action_param, void *sprite, void *actor) {
    s32 result;
    s32 action_ready;
    s32 direction;
    s32 action_flags;
    s32 *global_flags;
    u8 *anim_table;

    ((S_80172E80_0 *)actor)->unk_71 &= 0x7F;
    global_flags = &D_80083460;
    action_ready = 0;
    if (((S_80172E80_1 *)global_flags)->unk_02 & 0x2000) {
        goto return_minus_one;
    }

    direction = func_800A04F0(actor, ((S_80172E80_2 *)sprite)->unk_24,
                         ((S_80172E80_2 *)sprite)->unk_25,
                         ((S_80172E80_0 *)actor)->unk_2A);
    result = 0;
    if ((func_800A2CB8(actor, direction) << 16) == 0) {
        goto return_zero;
    }

    result = -1;
    action_flags = ((S_80172E80_1 *)global_flags)->unk_02;
    if (action_flags & 0x2000) {
        return result;
    }
    if (!(((S_80172E80_0 *)actor)->unk_46 & 0x8000)) {
        if (action_flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(direction, actor)) + 0x40) >= 0x81U) {
        return action_ready;
    }

    action_ready = 1;
    if (!(((S_80172E80_0 *)actor)->unk_46 & 0x8000)) {
        if (D_80083462 & 8) {
            return -1;
        }
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((s8 *)actor - 0x20, action_param, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
return_minus_one:
        return -1;
    }

    result = action_ready;
    ((S_80172E80_3 *)action_state)->unk_9B = 0;
    if (result != 0) {
        ((S_80172E80_3 *)action_state)->unk_9A = 0x11;
        ((S_80172E80_3 *)action_state)->unk_8C = 0;
        ((S_80172E80_0 *)actor)->unk_84 = 0x7C;
        ((S_80172E80_0 *)actor)->unk_85 = 0;
        ((S_80172E80_3 *)action_state)->unk_98 &= 0xFFF7;
        ((S_80172E80_0 *)actor)->unk_1C &= 0xFFFBFFFF;
        anim_table = &D_800E2378;
        (*(u8 **)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
                      anim_table[((D_80083228 + ((S_80172E80_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80172E80_0 *)actor)->unk_6D--;
        func_8009C93C(actor, sprite, ((S_80172E80_0 *)actor)->unk_2A, 1, 0);
    }
    return result;

return_zero:
    return 0;
}
