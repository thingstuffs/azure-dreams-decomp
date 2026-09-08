#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"



typedef struct S_80172E80_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172E80_1;   /* flags_base in func_80172E80 */




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

    ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 &= 0x7F;
    global_flags = &D_80083460;
    action_ready = 0;
    if (((S_80172E80_1 *)global_flags)->unk_02 & 0x2000) {
        goto return_minus_one;
    }

    direction = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                         ((Rec_D_80082E80 *)sprite)->unk_25,
                         ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
    result = 0;
    if ((func_800A2CB8(actor, direction) << 16) == 0) {
        goto return_zero;
    }

    result = -1;
    action_flags = ((S_80172E80_1 *)global_flags)->unk_02;
    if (action_flags & 0x2000) {
        return result;
    }
    if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000)) {
        if (action_flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(direction, actor)) + 0x40) >= 0x81U) {
        return action_ready;
    }

    action_ready = 1;
    if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000)) {
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
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
    if (result != 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_D_800E3D7C *)actor)->unk_84.as_u8 = 0x7C;
        ((Rec_D_800E3D7C *)actor)->unk_85.as_u8 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xFFFBFFFF;
        anim_table = &D_800E2378;
        (*(u8 **)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
                      anim_table[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                      0);
        ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
        func_8009C93C(actor, sprite, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
    }
    return result;

return_zero:
    return 0;
}
