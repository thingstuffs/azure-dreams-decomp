#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
typedef s32 M2C_UNK;



typedef struct S_8016A36C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    union { M2C_UNK * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_8016A36C_3;   /* arg2 in func_8016A36C */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80047784();
void func_800478B8();
s32 func_80069EF8();
s32 func_8009A180();
s8 func_8009FB34();
s32 func_8009FD7C();
s32 func_800A0818();
s32 func_800A1C58();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AA258();
s32 func_800AA6B4();
M2C_UNK func_800AA79C();
M2C_UNK func_800AA888();
s32 func_800AA924();
M2C_UNK func_800AAF00();
M2C_UNK func_8016AFC4(void *, void *, void *, void *);
M2C_UNK func_8016B230();
s32 func_8016B954();
M2C_UNK func_8016BAE0();
s32 func_8016BBC0();
void func_8016D4B8();
M2C_UNK func_8016D6F8();
void func_8016DAC0();
s32 func_801732A4();
extern u8 D_801739A0;
extern u8 D_801739A8;
extern u8 D_801739B0;
extern u8 D_801739B8;
extern M2C_UNK D_801739E0;
extern M2C_UNK D_801739E8;
extern M2C_UNK D_801739F0;
extern M2C_UNK D_801739F8;
extern M2C_UNK D_80173A00;
extern M2C_UNK D_80173A08;
extern M2C_UNK D_80173A10;
extern M2C_UNK D_80173A18;
extern u8 D_80173A50;
extern u8 D_80173A58;
extern M2C_UNK D_80173AC0;
extern M2C_UNK D_80173AC8;

/* Updates dungeon actor actions, facing, and idle animations. */
void func_8016A36C(void *actor, void *context, void *sprite_arg, EntityRec *entity) {
    register void *sprite = sprite_arg;
    M2C_UNK distance;
    u8 *idle_table;
    u8 *pose2_table;
    u8 *pose3_table;
    unsigned long table_index;
    u8 *next_table;
    u8 *current_table;
    s32 entity_flags;
    s32 action_id;
    s8 room_id;
    u16 action_flags;
    u16 pose2_idle_ticks;
    u16 pose2_anim_ticks;
    u16 pose3_idle_ticks;
    u16 pose3_anim_ticks;
    s32 inactive_pose;
    s32 flagged_pose;
    s32 anim_state;
    s32 active_pose;
    s32 action_pose;
    s32 idle_pose;
    u32 clear_mask;
    s32 state_changed;

    if (dungeonStatus.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
        func_8016AFC4(actor, context, sprite, entity);
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 != 1) {
            return;
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = (u8) (((Rec_func_800A9E70_arg0 *)actor)->unk_AD + 1);
        dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) + 1);
        return;
    }
    if (((Rec_func_800A9E70_arg0 *)actor)->unk_B0 == 1) {
        if (((Rec_func_800A9E70_arg0 *)actor)->unk_AD != 0) {
            dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - ((Rec_func_800A9E70_arg0 *)actor)->unk_AD);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_AD = 0U;
        }
    }
    if (entity->tileY == 0) {
        func_800AA79C(actor, context, sprite, entity);
        ASM_KEEP_NV(actor);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(sprite);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        inactive_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
        switch (inactive_pose) {
            case 0xD:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p == (M2C_UNK *)((u8 *)&D_80173AC0 + 8)) {
                    return;
                }
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = (M2C_UNK *)((u8 *)&D_80173A58 + 0x68);
                table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
                table_index += (unsigned long)(M2C_UNK *)((u8 *)&D_80173A58 + 0x68);
                func_80047784(sprite, *(u8 *)table_index, 0);
                return;
            case 0xE:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p == (M2C_UNK *)((u8 *)&D_80173A58 + 0x70)) {
                    return;
                }
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173AC0;
                table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
                table_index += (unsigned long)&D_80173AC0;
                func_80047784(sprite, *(u8 *)table_index, 0);
                return;
            case 0xF:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
                    return;
                }
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = (M2C_UNK *)((u8 *)&D_80173A00 + 0xC0);
                table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
                table_index += (unsigned long)(M2C_UNK *)((u8 *)&D_80173A00 + 0xC0);
                func_80047784(sprite, *(u8 *)table_index, 0);
                return;
        }
        return;
    }
    if (entity->flags1C & 0x200) {
        flagged_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
        switch (flagged_pose) {
            case 0xD:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
                    break;
                }
                clear_mask = 0xFFFB0000U;
                state_changed = 1;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = flagged_pose;
                goto block_32;
            case 0xE:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p == &D_80173AC8) {
                    goto block_31;
                }
                break;
            case 0xF:
                if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173AC8) {
                    break;
                }
block_31:
                clear_mask = 0xFFFB0000U;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xDU;
                state_changed = 1;
block_32:
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_s8 = (s8)state_changed;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
                entity->flags1C = (s32) (entity->flags1C & (clear_mask | 0xFFFFU));
                return;
            default:
                goto block_37;
        }
        if (func_800AA924(actor, context, sprite, &D_80173AC0) != 0) {
            return;
        }
    }
block_37:
    if (!(dungeonStatus.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }
        {
            s16 idle_state = 0xE;
            anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8;
            if (anim_state != idle_state) {
                anim_state = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
                switch (anim_state) {
                    case 0:
                        if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A0) {
                            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739A0;
                            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_801739A0), 0);
                        }
                        break;
                    case 1:
                        if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739A8) {
                            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739A8;
                            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_801739A8), 0);
                        }
                        break;
                    case 2:
                        if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B0) {
                            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739B0;
                            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_801739B0), 0);
                        }
                        break;
                    case 3:
                        if (((S_8016A36C_3 *)sprite)->unk_2C.p2 != &D_801739B8) {
                            (*(u8 **)((u8 *)sprite + 0x2C)) = &D_801739B8;
                            func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_801739B8), 0);
                        }
                        break;
                }
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xEU;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x1F) + 0xF);
            }
        }
        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 = (u16) (((Rec_func_800A9E70_arg0 *)actor)->unk_98 & 0xFFF3);
        if (entity->unk_64 != 0) {
            active_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
            switch (active_pose) {
                case 0:
                    if (func_800AA6B4(actor, context, sprite, &D_80173A00) != 0) {
                        return;
                    }
                    break;
                case 1:
                    if (func_800AA6B4(actor, context, sprite, &D_80173A08) != 0) {
                        return;
                    }
                    break;
                case 2:
                    if (func_800AA6B4(actor, context, sprite, &D_80173A10) != 0) {
                        return;
                    }
                    break;
                case 3:
                    if (func_800AA6B4(actor, context, sprite, &D_80173A18) != 0) {
                        return;
                    }
                    break;
            }
        }
        if (entity->flags1C & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_8016D4B8(actor, context, sprite, entity);
            return;
        }
        if ((func_800A1C58(entity) << 0x10) != 0) {
            if (((s32)dungeonStatus.unk_0C) != entity) {
                return;
            }
            if (((s32)dungeonStatus.unk_10) != 0) {
                return;
            }
            if ((s16) ((u16)dungeonStatus.unk_0A) >= 2) {
                return;
            }
            if (dungeonStatus.flags & 8) {
                return;
            }
            entity->unk_18 = 0;
            dungeonStatus.unk_0C = 0;
        }
    }
    room_id = func_8009FB34(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v);
    ((S_8016A36C_3 *)sprite)->unk_26 = room_id;
    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (((S_8016A36C_3 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8016B230(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((func_8009A180(entity, ((s32)D_800814A8->unk_58) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if (D_80013714 & 8) {
                func_801732A4(actor, context, sprite);
                entity->unk_71 = (u8) (entity->unk_71 & 0x7F);
                func_800A9A0C(entity);
                entity->unk_46 = (u16) (entity->unk_46 & 0x7FFF);
                return;
            }
            if ((func_8016BBC0(actor, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = entity->unk_46 | 0x4000;
            entity->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8016B230(actor, context, sprite, entity);
                return;
            }
        }
        action_id = entity->unk_46 & 0x3FFF;
        switch (action_id) {
            case 8:
                if ((func_8016B954(actor, context, sprite, entity) << 0x10) != 0) {
                    return;
                }
                func_8016BAE0(actor, context, sprite, entity);
                return;
            case 9:
                func_8016D6F8(actor, context, sprite, entity);
                return;
            case 10:
                func_8016DAC0(actor, context, sprite, entity);
                return;
            case 12:
                func_800A9A0C(entity);
                return;
            case 5:
            case 6:
            case 7:
                {
                    s32 angle = func_800A0818(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &distance);
                    EntityRec *owner = D_800814A8;
                    entity->facing = (s16)angle;
                    if (owner->unk_9A != 0x11) {
                        func_800A9A0C(entity);
                        return;
                    }
                }
            case 1:
            case 2:
            case 3:
                action_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
                switch (action_pose) {
                case 0:
                    func_800AAF00(actor, context, sprite, &D_801739E0, &func_8016A36C);
                    return;
                case 1:
                    func_800AAF00(actor, context, sprite, &D_801739E8, &func_8016A36C);
                    return;
                case 2:
                    func_800AAF00(actor, context, sprite, &D_801739F0, &func_8016A36C);
                    return;
                case 3:
                    func_800AAF00(actor, context, sprite, &D_801739F8, &func_8016A36C);
                    return;
                }
                return;
            default:
                func_8016B230(actor, context, sprite, entity);
                return;
        }
    }
    entity_flags = entity->flags1C;
    if (!(entity_flags & 0x2000)) {
        if (!(D_80013714 & 8)) {
            if (room_id < 0 || !(D_800E2970[room_id].flags & 2)) {
                if (!(entity_flags & 0x430)) {
                    if ((func_8009FD7C(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY) << 0x10) != 0) {
                        entity->facing = func_800A0818(((S_8016A36C_3 *)sprite)->unk_24.at00.v, ((S_8016A36C_3 *)sprite)->unk_24.at01.v, D_80082E80.tileX, D_80082E80.tileY, &distance);
                    }
                }
            }
        }
    }
    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((S_8016A36C_3 *)sprite)->unk_14 & 0x40) {
        return;
    }
    if (entity->flags1C & 0x20) {
        return;
    }
    if ((*(u16 *)0x80013714) & 8) {
        return;
    }
    idle_pose = ((Rec_func_800A9E70_arg0 *)actor)->unk_AC;
    switch (idle_pose) {
        case 0:
            next_table = &D_801739A0;
            current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
            if (current_table == next_table) {
                return;
            }
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = next_table;
            table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)next_table;
            func_80047784(sprite, *(u8 *)table_index, 0);
            return;
        case 1:
            current_table = ((S_8016A36C_3 *)sprite)->unk_2C.p2;
            next_table = &D_801739A8;
            if (current_table == next_table) {
                return;
            }
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = next_table;
            table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)next_table;
            func_80047784(sprite, *(u8 *)table_index, 0);
            return;
        case 2:
            pose2_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
            if (pose2_table != &D_801739B0 && pose2_table != &D_80173A50) {
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801739B0;
                func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_801739B0), 0);
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
            }
            if (pose2_table == &D_801739B0 || ((S_8016A36C_3 *)sprite)->unk_2C.p == &D_801739B0) {
                pose2_idle_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose2_idle_ticks + 1);
                if ((s16) pose2_idle_ticks >= ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v) {
                    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173A50;
                    func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_80173A50), 0);
                    func_800478B8(sprite);
                    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                }
            }
            if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A50) {
                return;
            }
            pose2_anim_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose2_anim_ticks + 1);
            if ((s16) pose2_anim_ticks < 0x12) {
                return;
            }
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801739B0;
            table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)&D_801739B0;
            func_80047784(sprite, *(u8 *)table_index, 0);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
            return;
        case 3:
            pose3_table = ((S_8016A36C_3 *)sprite)->unk_2C.p;
            idle_table = &D_801739B8;
            if (pose3_table != idle_table && pose3_table != &D_80173A58) {
                (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = idle_table;
                func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + idle_table), 0);
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
            }
            if (pose3_table == idle_table || ((S_8016A36C_3 *)sprite)->unk_2C.p == idle_table) {
                pose3_idle_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
                ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose3_idle_ticks + 1);
                if ((s16) pose3_idle_ticks >= ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v) {
                    (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_80173A58;
                    func_80047784(sprite, *((((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7) + &D_80173A58), 0);
                    func_800478B8(sprite);
                    ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
                }
            }
            if (((S_8016A36C_3 *)sprite)->unk_2C.p != &D_80173A58) {
                return;
            }
            pose3_anim_ticks = ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = (u16) (pose3_anim_ticks + 1);
            if ((s16) pose3_anim_ticks < 0x12) {
                return;
            }
            (*(M2C_UNK **)((u8 *)sprite + 0x2C)) = &D_801739B8;
            table_index = ((s32) (gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            table_index += (unsigned long)&D_801739B8;
            func_80047784(sprite, *(u8 *)table_index, 0);
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9E.as_u16 = 0U;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_A0.at00_s16.v = (s16) ((func_80069EF8() & 0x3F) + 0x3C);
            return;
    }
}
