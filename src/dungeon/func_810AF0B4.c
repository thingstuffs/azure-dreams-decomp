#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801728B4_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
} S_801728B4_0;   /* arg0 in func_801728B4 */


typedef struct S_801728B4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801728B4_2_pre;   /* the 0x14 bytes before var_v0 in func_801728B4, addressed as var_v0[-1] */

typedef struct S_801728B4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801728B4_3;   /* temp_v1_3 in func_801728B4 */


typedef struct S_801728B4_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    s8 unk_BB;
} S_801728B4_6;   /* temp_v0_2 in func_801728B4 */

typedef struct S_801728B4_7 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_801728B4_7;   /* temp_a0 in func_801728B4 */


typedef struct S_801728B4_9 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xAB];
    u8 unk_BB;
} S_801728B4_9;   /* var_s0 in func_801728B4 */

typedef struct S_801728B4_11 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801728B4_11;   /* ((S_801728B4_6 *)temp_v0_2)->unk_08 in func_801728B4 */

s32 func_8003F270(void);
void *func_8003FD64();
s32 func_8004491C();
void func_80047784();
void *func_800A05A4();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A94A0(void *, u8 *, s32, void *);
extern M2C_UNK D_800D7960;
extern M2C_UNK D_80170E54;
extern u8 D_80173C6C[];

/* Updates an actor action, its visual effect, and completion cleanup. */
void func_801728B4(void *actor, EntityRec *motion, void *sprite, EntityRec *action) {
    s32 action_id;
    s32 action_value;
    s32 effect_anim;
    s16 use_player;
    u16 saved_pos[4];
    u16 sprite_flags;
    u16 ticks_left;
    u16 sprite_angle;
    u8 *slot_or_effect;
    s32 state;
    void *effect_sprite;
    void *new_effect;
    void *target;

    state = ((S_801728B4_0 *)actor)->unk_9B;
    use_player = 0;
    switch (state) {
    case 0:
        if (action->flags1C & 0x2000) {
            action_id = action->unk_46 & 0x3FFF;
            switch (action_id - 1) {
            case 6:
                use_player = 1;
            case 2:
                slot_or_effect = (u8 *)action + 0xE;
                break;
            case 5:
                use_player = 1;
            case 1:
                slot_or_effect = (u8 *)action + 0xB;
                break;
            case 4:
                use_player = 1;
            case 0:
                slot_or_effect = (u8 *)action + 8;
                break;
            default:
                slot_or_effect = NULL;
                break;
            }
        } else {
            switch (action->unk_46 & 0x3FFF) {
            case 3:
                slot_or_effect = (u8 *)action + 0xE;
                break;
            case 2:
                slot_or_effect = (u8 *)action + 0xB;
                break;
            case 1:
                slot_or_effect = (u8 *)action + 8;
                break;
            default:
                slot_or_effect = NULL;
                break;
            }
        }
        if (*slot_or_effect != 0) {
            ((S_801728B4_0 *)actor)->unk_98 = (u16) (((S_801728B4_0 *)actor)->unk_98 & 0xFF7F);
            if (use_player != 0) {
                target = D_800814A8;
                action->target = target;
                action_value = ((S_801728B4_2_pre *)target)[-1].unk_00;
                action->unk_72 = (s8) ((S_801728B4_3 *)action_value)->unk_24;
                action->unk_73 = (s8) ((S_801728B4_3 *)action_value)->unk_25;
            } else if (D_8006DE24[*slot_or_effect].kind == 2) {
                target = action->target;
                if (target != NULL) {
                    action_value = ((S_801728B4_2_pre *)target)[-1].unk_00;
                    action->unk_72 = (s8) ((S_801728B4_3 *)action_value)->unk_24;
                    action->unk_73 = (s8) ((S_801728B4_3 *)action_value)->unk_25;
                }
            } else {
                action->target = func_800A05A4(action, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                    action->facing, 0x10);
                action->unk_72 = abs(action->unk_72);
                action->unk_73 = abs(action->unk_73);
            }
            saved_pos[0] = ((u16)motion->x.w.i);
            saved_pos[1] = ((u16)motion->y.w.i);
            saved_pos[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(action, slot_or_effect, use_player, actor + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
            func_800A56E0(0x703);
            ((S_801728B4_0 *)actor)->unk_9B = (u8) (((S_801728B4_0 *)actor)->unk_9B + 1);
            new_effect = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
            ((S_801728B4_0 *)actor)->unk_A0 = new_effect;
            if (new_effect == NULL) {
                return;
            }
            func_8004491C(new_effect, func_80045340);
            ((S_801728B4_6 *)new_effect)->unk_10 = &D_800D7960;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_00 = (s32) motion->x.v;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_04 = (s32) motion->y.v;
            ((S_801728B4_11 *)(((S_801728B4_6 *)new_effect)->unk_08))->unk_08 = (s32) (motion->z.v + 0xFF800000);
            ((S_801728B4_6 *)new_effect)->unk_BB = 0;
            effect_sprite = ((S_801728B4_6 *)new_effect)->unk_0C;
            ((S_801728B4_6 *)new_effect)->unk_4A = (u16) action->facing;
            action_value = ((Rec_D_80082E80 *)sprite)->unk_28.at00_s32.v;
            ((S_801728B4_7 *)effect_sprite)->unk_1E = 0x1000;
            ((S_801728B4_7 *)effect_sprite)->unk_1C = 0x1000;
            ((S_801728B4_7 *)effect_sprite)->unk_28 = action_value;
            sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            effect_anim = 0x2D;
            ((S_801728B4_7 *)effect_sprite)->unk_14 = sprite_flags;
            sprite_angle = ((Rec_D_80082E80 *)sprite)->unk_12.at00_u16.v;
            ((S_801728B4_7 *)effect_sprite)->unk_10 = 0;
            ((S_801728B4_7 *)effect_sprite)->unk_14 = (u16) (sprite_flags | 0xC);
            ((S_801728B4_7 *)effect_sprite)->unk_12 = (s16) (sprite_angle - 0x80);
            ((S_801728B4_7 *)effect_sprite)->unk_0C = (s32) ((Rec_D_80082E80 *)sprite)->unk_0C.at00_s32.v;
            func_80047784(effect_sprite, effect_anim, 0);
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            dungeonStatus.unk_0C = 0;
            (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
            func_800A4ACC(action);
            action->unk_6D = (u8) (((u8)action->unk_6D) - 1);
            ((S_801728B4_0 *)actor)->unk_8C = &D_80170E54;
            action->unk_73 = 0;
            action->unk_72 = 0;
            action->unk_46 = (u16) (action->unk_46 & 0x7FFF);
            return;
        }
    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        ((S_801728B4_0 *)actor)->unk_9B = (u8) (((S_801728B4_0 *)actor)->unk_9B + 1);
    case 2:
        target = ((S_801728B4_0 *)actor)->unk_A0;
        if (target != NULL) {
            slot_or_effect = target;
            effect_sprite = ((S_801728B4_9 *)slot_or_effect)->unk_0C;
            if (((S_801728B4_7 *)effect_sprite)->unk_14 & 0xE000) {
                ((S_801728B4_9 *)slot_or_effect)->unk_BB = 0xFF;
                ((S_801728B4_0 *)actor)->unk_A0 = NULL;
            }
        }
        if ((((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 4 && (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
            ((S_801728B4_0 *)actor)->unk_96 = 3U;
            ((S_801728B4_0 *)actor)->unk_98 = (u16) (((S_801728B4_0 *)actor)->unk_98 | 0x80);
        }
        ticks_left = ((S_801728B4_0 *)actor)->unk_96 - 1;
        ((S_801728B4_0 *)actor)->unk_96 = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            ((S_801728B4_0 *)actor)->unk_96 = 0U;
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        }
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm != &D_80173C6C) {
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173C6C;
            func_80047784(sprite, D_80173C6C[((s32) (gameWork.view.viewAngle + action->facing + 0x100) >> 9) & 7], 0);
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        ((S_801728B4_0 *)actor)->unk_8C = &D_80170E54;
        func_800A4ACC(action);
        if ((s8) ((u8)action->unk_6D) > 0) {
            action->unk_6D = (u8) (((u8)action->unk_6D) - 1);
        }
        action->unk_73 = 0;
        action->unk_72 = 0;
        action->unk_46 = (u16) (action->unk_46 & 0x7FFF);
        func_800A56E0(0xB4);
        return;
    default:
        return;
    }
}
