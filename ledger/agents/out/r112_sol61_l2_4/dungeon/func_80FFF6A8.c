#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_8014D438(void *, void *, void *, void *);
extern void func_8014D67C(void *, void *, void *, void *);
extern s32 func_8014DE28(void *, void *, void *, void *);
extern void func_8014E08C(void *, void *, void *, void *);
extern s32 func_8014E230(void *, void *, void *, s32);
extern void func_8014FA84(void *, void *, void *, void *);

extern u8 D_8014CEA8;
extern u8 D_80150038[];
extern u8 D_80150040[];
extern u8 D_80150070[];
extern u8 D_80150080[];
extern u8 D_80150088[];

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 action;
    u8 phase;
} ActionState;

typedef struct ActorSprite {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    u8 room;
    u8 pad_27[0x5];
    void * directionFrames;
} ActorSprite;

/* Updates the entity action, facing direction, and animation from dungeon state. */
void func_8014CEA8(ActionState *actor, void *context, ActorSprite *sprite, EntityRec *entity)
{
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 dungeon_flags = dungeonStatus.flags;

    if (dungeon_flags & 0x1000) {
        actor->action = 0xE;
        func_8014D438(actor, context, sprite, entity);
        return;
    }

    if (entity->tileY == 0) {
        func_800AA79C(actor, context, sprite, entity);
        if (sprite->directionFrames != D_80150088) {
            sprite->directionFrames = D_80150080;
            func_80047784(sprite,
                D_80150080[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (sprite->directionFrames == D_80150088) {
            actor->action = 0xD;
            actor->phase = 1;
            actor->handler = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(actor, context, sprite, D_80150080)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            func_800AA258(actor, context, sprite, entity);
            return;
        }

        if (actor->action != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80150038;
            if (sprite->directionFrames != anim_table) {
                sprite->directionFrames = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->action = next_state;
        }

        actor->flags &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (func_800AA6B4(actor, context, sprite, D_80150040)) {
                    return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            func_800AA888(actor, context, sprite, entity);
            func_8014FA84(actor, context, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            func_800AAB10(actor, context, sprite, entity);
        }
    }

    tile_record = func_8009FB34(sprite->position.tile.x, sprite->position.tile.y);
    sprite->room = tile_record;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_8014D67C(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8014E230(actor, context, sprite, 0) == 0) {
                    return;
            }
            entity->unk_46 |= 0x4000;
            if (!(entity->unk_46 & 0x8000)) {
                func_8014D67C(actor, context, sprite, entity);
                return;
            }
        }

        switch (entity->unk_46 & 0x3FFF) {
        case 9:
            actor->flags |= 0x8000;
        /* fall through */
        case 8:
            if (((u32)entity->flags1C) & 0x2000) {
                if ((entity->unk_46 & 0x3FFF) == 8) {
                    actor->flags &= 0x7FFF;
                }
            }
            if ((s16)func_8014DE28(actor, context, sprite, entity) == 0) {
                func_8014E08C(actor, context, sprite, entity);
                    return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *global_actor;
                s32 direction;

                direction = func_800A0818(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_aux);
                global_actor = D_800814A8;
                entity->facing = direction;
                if (global_actor->unk_9A == 0x11) {
                    func_800AAF00(actor, context, sprite, D_80150070, &D_8014CEA8);
                    return;
                }
            }
        /* fall through */
        case 12:
            func_800A9A0C(entity);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(actor, context, sprite, D_80150070, &D_8014CEA8);
            return;
        default:
            func_8014D67C(actor, context, sprite, entity);
            return;
        }
    } else if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((s16)func_8009FD7C(sprite->position.tile.x,
                        sprite->position.tile.y, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    entity->facing = func_800A0818(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = D_80150038;
    if (sprite->directionFrames == anim_table) {
        return;
    }
    sprite->directionFrames = anim_table;
    func_80047784(sprite,
        anim_table[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
