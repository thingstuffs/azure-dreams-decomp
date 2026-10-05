#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
extern int abs(int);

typedef struct S_801727C8_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    s16 unk_A8;
} S_801727C8_0;   /* arg0 in func_801727C8 */


typedef struct S_801727C8_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801727C8_2_pre;   /* the 0x14 bytes before owner in func_801727C8, addressed as owner[-1] */

typedef struct S_801727C8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801727C8_3;   /* temp_v1_3 in func_801727C8 */


typedef struct S_801727C8_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_801727C8_5;   /* temp_s6 in func_801727C8 */


extern void *D_80170838[];
s32 func_8003F270();
void func_80047784();
void *func_800A05A4();
void func_800A2B04();
s32 func_800A4ACC();
s32 func_800A56E0();
s32 func_800A94A0();
void func_800DB2DC();
extern M2C_UNK D_801711A4;
extern u8 D_8017418C;
extern u8 D_801741B4;
extern u8 D_801741BC;

/* Updates an actor's action state, target selection, and animation. */
void func_801727C8(void *action, EntityRec *motion, void *sprite, EntityRec *actor) {
    u8 *anim_table;
    s32 visual_base;
    s32 special_slot;
    s32 slot;
    s16 is_special;
    s32 target_x;
    s32 abs_x;
    s32 abs_y;
    s32 target_y;
    u16 ticks_left;
    u8 *entry;
    s32 current_state;
    s32 state;
    void *visual_flags;
    void *effect_sprite;
    void *target_owner;

    is_special = 0;
    visual_base = ((S_801727C8_0 *)action)->unk_A4;
    state = ((S_801727C8_0 *)action)->unk_9B;
    visual_flags = visual_base + 0x20;
    effect_sprite = visual_base + 0x28;
    switch (state) {
    case 0:
        if (actor->flags1C & 0x2000) {
            special_slot = actor->unk_46 & 0x3FFF;
            switch (special_slot) {
            case 7:
                is_special = 1;
                /* fallthrough */
            case 3:
                entry = (u8 *)actor + 0xE;
                break;
            case 6:
                is_special = 1;
                /* fallthrough */
            case 2:
                entry = (u8 *)actor + 0xB;
                break;
            case 5:
                is_special = 1;
                /* fallthrough */
            case 1:
                entry = (u8 *)actor + 8;
                break;
            default:
                entry = NULL;
                break;
            }
        } else {
            slot = actor->unk_46 & 0x3FFF;
            switch (slot) {
            case 3:
                entry = (u8 *)actor + 0xE;
                break;
            case 2:
                entry = (u8 *)actor + 0xB;
                break;
            case 1:
                entry = (u8 *)actor + 8;
                break;
            default:
                entry = NULL;
                break;
            }
        }
        if (*entry != 0) {
            *(u16 *)((s8 *)action + 0x98) = (u16) (((S_801727C8_0 *)action)->unk_98 & 0xFF7F);
            {
                s32 special_check;

                special_check = is_special;
                if (special_check != 0) {
                    target_owner = D_800814A8;
                    actor->target = target_owner;
                    {
                        void *owner = target_owner;

                        slot = (s32)(((S_801727C8_2_pre *)owner)[-1].unk_00);
                        actor->unk_72 = (s8) ((S_801727C8_3 *)((void *)slot))->unk_24;
                        actor->unk_73 = (s8) ((S_801727C8_3 *)((void *)slot))->unk_25;
                    }
                } else if (D_8006DE24[*entry].kind == 2) {
                    target_owner = actor->target;
                    if (target_owner != NULL) {
                        void *owner = target_owner;

                        slot = (s32)(((S_801727C8_2_pre *)owner)[-1].unk_00);
                        actor->unk_72 = (s8) ((S_801727C8_3 *)((void *)slot))->unk_24;
                        actor->unk_73 = (s8) ((S_801727C8_3 *)((void *)slot))->unk_25;
                    }
                } else {
                    void *spawned_owner;

                    spawned_owner = func_800A05A4(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                        actor->facing, 0x10);
                    actor->target = spawned_owner;
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }
            anim_table = &D_801741B4;
            ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 & 0x7FFF);
            (*(M2C_UNK **)((u8 *)effect_sprite + 0x2C)) = anim_table;
            func_80047784(effect_sprite, *((u8 *) ((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + (s32) anim_table)), 0);
            if (func_800A94A0(actor, entry, is_special, action + 0x98) == 0) {
                return;
            }
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
            func_800DB2DC(motion, sprite, actor, 0xA);
            func_800A56E0(0x703);
            current_state = ((S_801727C8_0 *)action)->unk_9B;
            {
                state = 6;

                ((S_801727C8_0 *)action)->unk_96 = (u16)state;
            }
            ((S_801727C8_0 *)action)->unk_9B = (u8) (current_state + 1);
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        dungeonStatus.unk_0C = 0;
        (*(u16 *)((u8 *)&D_800814A8->unk_A4 + 2)) = (u16) ((*(u16 *)((u8 *)D_800814A8 + 0xA6)) - 1);
        func_800A4ACC(actor);
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        ((S_801727C8_0 *)action)->unk_8C = &D_801711A4;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        return;

    case 1:
        if (func_8003F270() != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v | 0x800);
            return;
        }
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        ((S_801727C8_0 *)action)->unk_9B = (u8) (((S_801727C8_0 *)action)->unk_9B + 1);

    case 2:
        ticks_left = ((S_801727C8_0 *)action)->unk_96 - 1;
        ((S_801727C8_0 *)action)->unk_96 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
                return;
            }
        }
        ((S_801727C8_0 *)action)->unk_98 = (u16) (((S_801727C8_0 *)action)->unk_98 | 0x80);
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801741BC;
        func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + &D_801741BC), 0);
        current_state = ((S_801727C8_0 *)action)->unk_9B;
        ((S_801727C8_0 *)action)->unk_9B = (u8) (current_state + 1);
        return;

    case 3:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pm != &D_8017418C) {
            if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
                ((S_801727C8_5 *)visual_flags)->unk_04 = (u16) (((S_801727C8_5 *)visual_flags)->unk_04 | 0x8000);
                ((S_801727C8_0 *)action)->unk_A8 = 0;
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_8017418C;
                func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7)
                    + &D_8017418C), 0);
            }
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
        ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = (u16) (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xF7FF);
        ((S_801727C8_0 *)action)->unk_8C = &D_801711A4;
        func_800A4ACC(actor);
        if ((s8) ((u8)actor->unk_6D) > 0) {
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        func_800A56E0(0xB4);
        return;
    default:
        return;
    }
}
