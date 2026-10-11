#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8016B3CC(void *, void *, void *, void *);
extern void func_8016B624(void *, void *, void *, void *);
extern s32 func_8016BDD0(void *, void *, void *, void *);
extern void func_8016BF94(void *, void *, void *, void *);
extern s32 func_8016C0AC(void *, void *, void *, s32);
extern void func_8016DF28(void *, void *, void *, void *);

extern u8 D_8016AE84;
extern u8 D_8016E820[];
extern u8 D_8016E830[];
extern u8 D_8016E848[];
extern u8 D_8016E858[];
extern u8 D_8016E860[];

typedef struct ActorSpriteView {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x; u8 y; } bytes;
        u16 packed;
    } tile;
    u8 room;
    u8 pad_27[0x5];
    void * animationTable;
} ActorSpriteView;

void func_8016AE84(void *controller, void *context, void *entity, EntityRec *actor_state)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8016B3CC(controller, context, entity, actor_state);
        return;
    }

    if (actor_state->tileY == 0) {
        func_800AA79C(controller, context, entity, actor_state);
        if (((ActorSpriteView *)entity)->animationTable != D_8016E860) {
            u8 *early_table = D_8016E858;
            ((ActorSpriteView *)entity)->animationTable = early_table;
            func_80047784(entity,
                early_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor_state->flags1C) & 0x200) {
        if (((ActorSpriteView *)entity)->animationTable == D_8016E860) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor_state->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(controller, context, entity, D_8016E858)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)actor_state->flags1C) & 0x100) {
            func_800AA258(controller, context, entity, actor_state);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 != 0xE) {
            u8 control_state = 0xE;

            anim_table = D_8016E820;
            if (((ActorSpriteView *)entity)->animationTable != anim_table) {
                ((ActorSpriteView *)entity)->animationTable = anim_table;
                func_80047784(entity,
                    anim_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = control_state;
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor_state->unk_64 != 0) {
            if (func_800AA6B4(controller, context, entity, D_8016E830)) {
                return;
            }
        }

        if (((u32)actor_state->flags1C) & 0x80000) {
            func_800AA888(controller, context, entity, actor_state);
            func_8016DF28(controller, context, entity, actor_state);
            return;
        }

        if ((s16)func_800A1C58(actor_state) != 0) {
            func_800AAB10(controller, context, entity, actor_state);
        }
    }

    room_id = func_8009FB34(((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y);
    ((ActorSpriteView *)entity)->room = room_id;

    if (actor_state->unk_6D > 0) {
        if (((u32)actor_state->flags1C) & 0x20) {
            func_800A9A0C(actor_state);
            return;
        }
        if (((ActorSpriteView *)entity)->tile.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8016B624(controller, context, entity, actor_state);
            return;
        }
        if (!(actor_state->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(actor_state,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016C0AC(controller, context, entity, 0) == 0) {
                return;
            }
            actor_state->unk_46 |= 0x4000;
            if (!(actor_state->unk_46 & 0x8000)) {
                func_8016B624(controller, context, entity, actor_state);
                return;
            }
        }

        switch (actor_state->unk_46 & 0x3FFF) {
        case 8:
        case 9:
            if ((s16)func_8016BDD0(controller, context, entity, actor_state) == 0) {
                func_8016BF94(controller, context, entity, actor_state);
                return;
            }
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player_controller;
                s32 direction;

                direction = func_800A0818(
                    ((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_flags);
                player_controller = D_800814A8;
                actor_state->facing = direction;
                if (player_controller->unk_9A != 0x11) {
                    func_800A9A0C(actor_state);
                    return;
                }
                func_800AAF00(controller, context, entity, D_8016E848, &D_8016AE84);
                return;
            }
        case 12:
            func_800A9A0C(actor_state);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(controller, context, entity, D_8016E848, &D_8016AE84);
            return;
        default:
            break;
        }

        func_8016B624(controller, context, entity, actor_state);
        return;
    } else if (!(((u32)actor_state->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor_state->flags1C) & 0x430)) {

                if ((s16)func_8009FD7C(((ActorSpriteView *)entity)->tile.bytes.x,
                    ((ActorSpriteView *)entity)->tile.bytes.y, D_80082E80.tileX,
                    D_80082E80.tileY) != 0) {
                    actor_state->facing = func_800A0818(
                        ((ActorSpriteView *)entity)->tile.bytes.x, ((ActorSpriteView *)entity)->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (((ActorSpriteView *)entity)->flags & 0x40) {
        return;
    }
    anim_table = D_8016E820;
    if (((ActorSpriteView *)entity)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)entity)->animationTable = anim_table;
    func_80047784(entity,
        anim_table[((gameWork.view.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
        0);
}
