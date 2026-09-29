#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
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

extern u8 D_800E2378;

/* Checks action readiness and initializes the actor state and directional animation. */
s32 func_80172E80(void *action_state, M2C_UNK action_param, void *sprite, void *actor) {
    s32 result;
    s32 action_ready;
    s32 direction;
    s32 action_flags;
    u8 *anim_table;

    ((EntityRec *)actor)->unk_71 &= 0x7F;
    action_ready = 0;
    if (dungeonStatus.flags & 0x2000) {
        return -1;
    }

    direction = func_800A04F0(actor, ((Rec_D_80082E80 *)sprite)->unk_24,
                         ((Rec_D_80082E80 *)sprite)->unk_25,
                         ((EntityRec *)actor)->facing);
    result = 0;
    if ((func_800A2CB8(actor, direction) << 16) == 0) {
        return 0;
    }

    result = -1;
    action_flags = dungeonStatus.flags;
    if (action_flags & 0x2000) {
        return result;
    }
    if (!(((EntityRec *)actor)->unk_46 & 0x8000)) {
        if (action_flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(direction, actor)) + 0x40) >= 0x81U) {
        return action_ready;
    }

    action_ready = 1;
    if (!(((EntityRec *)actor)->unk_46 & 0x8000)) {
        if (dungeonStatus.flags & 8) {
            return -1;
        }
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((s8 *)actor - 0x20, action_param, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    result = action_ready;
    ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_u8 = 0;
    if (result != 0) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_u8 = 0x11;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((EntityRec *)actor)->unk_84 = 0x7C;
        ((EntityRec *)actor)->unk_85 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 &= 0xFFF7;
        ((EntityRec *)actor)->flags1C &= 0xFFFBFFFF;
        anim_table = &D_800E2378;
        (*(u8 **)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(sprite,
                      anim_table[((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                      0);
        ((EntityRec *)actor)->unk_6D--;
        func_8009C93C(actor, sprite, ((EntityRec *)actor)->facing, 1, 0);
    }
    return result;
}
