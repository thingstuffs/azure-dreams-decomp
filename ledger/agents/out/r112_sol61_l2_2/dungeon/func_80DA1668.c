#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* Sprite entity passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

extern void func_80047784();
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s32 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(ActorActionView *action, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8015F388(void *);
extern void func_8015F5CC(void *, void *, void *, void *);
extern s32 func_8015FD80(void *, void *, void *, void *);
extern void func_8015FF90(void *, void *, void *, void *);
extern s32 func_801600E0(void *, void *, void *, s32);
extern void func_80161478(void *, void *, void *, void *);

extern u8 D_8016186C[];
extern u8 D_80161874[];
extern u8 D_8016189C[];

/* Dispatch action behavior and update its facing animation from dungeon entity. */
void func_8015EE68(ActorActionView *action, void *context, ActorSpriteView *sprite, EntityRec *entity)
{
    s32 initial_flags;
    s32 flags;
    s32 room_or_facing;
    s32 action_kind;
    s32 room_index;
    u8 *room_table;
    u8 *room_entry;
    EntityRec *player;
    s16 distance;
    u16 status_flags;

    if (dungeonStatus.flags & 0x1000) {
        action->behavior = 14;
        func_8015F388(action);
        return;
    }

    if (entity->tileY == 0) {
        func_800AA79C(action, context, sprite, entity);
    } else {
        initial_flags = ((u32)entity->flags1C);
        entity->flags1C = initial_flags & -0x201;

        status_flags = dungeonStatus.flags;

        if ((status_flags & 0x2000) == 0) {
            if (initial_flags & 0x100) {
                func_800AA258(action, context, sprite, entity);
                return;
            }

            if (action->behavior != 14) {
                if (sprite->frameTable != D_8016186C) {
                    sprite->frameTable = D_8016186C;
                    func_80047784(
                        sprite,
                        D_8016186C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                }
                action->behavior = 14;
            }

            action->flags &= 0xFFF3;

            if (entity->unk_64 != 0) {
                if (func_800AA6B4(action, context, sprite, D_80161874) != 0) {
                    return;
                }
            }

            if (((u32)entity->flags1C) & 0x80000) {
                func_800AA888(action, context, sprite, entity);
                func_80161478(action, context, sprite, entity);
                return;
            }

            if ((s16)func_800A1C58(entity) != 0) {
                func_800AAB10(action, context, sprite, entity);
            }
        }

        room_or_facing = func_8009FB34(sprite->tile.bytes.x, sprite->tile.bytes.y);
        sprite->room.raw = room_or_facing;

        if (entity->unk_6D > 0) {
            if (((u32)entity->flags1C) & 0x20) {
                func_800A9A0C(entity);
                return;
            }

            if (sprite->tile.packed == *(u16 *)(&D_80082E80.tileX)) {
                func_8015F5CC(action, context, sprite, entity);
                return;
            }

            if ((entity->unk_46 & 0x8000) == 0) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((s16)func_8009A180(entity, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                        return;
                    }
                }

                if ((s16)func_801600E0(action, context, sprite, 0) == 0) {
                    return;
                }
                entity->unk_46 |= 0x4000;
                if ((entity->unk_46 & 0x8000) == 0) {
                    func_8015F5CC(action, context, sprite, entity);
                    return;
                }
            }

            action_kind = entity->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 9:
                action->flags |= 0x8000;
        /* fallthrough */
            case 8:
                if ((((u32)entity->flags1C) & 0x2000) &&
                    ((entity->unk_46 & 0x3FFF) == 8)) {
                    action->flags &= 0x7FFF;
                }
                if ((s16)func_8015FD80(action, context, sprite, entity) != 0) {
                    return;
                }
                func_8015FF90(action, context, sprite, entity);
                return;

            case 5:
            case 6:
            case 7:
                room_or_facing = func_800A0818(
                    sprite->tile.bytes.x, sprite->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY, (s16 *)&distance);
                player = D_800814A8;
                entity->facing = room_or_facing;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(action, context, sprite, D_8016189C, func_8015EE68);
                    return;
                }
        /* fallthrough */
            case 12:
                func_800A9A0C(entity);
                return;

            case 1:
            case 2:
            case 3:
                func_800AAF00(action, context, sprite, D_8016189C, func_8015EE68);
                return;

            case 4:
            case 10:
            case 11:
            default:
                func_8015F5CC(action, context, sprite, entity);
                return;
            }
        }

        flags = ((u32)entity->flags1C);
        if ((flags & 0x2000) == 0) {
            room_index = (s8)room_or_facing;
            if (room_index >= 0) {
                room_table = (u8 *)D_800E2970;
                room_entry = room_table + room_index * 20;
            }
            if (room_index < 0 ||
                !(((DungeonRoom *)room_entry)->flags & 2)) {
                if ((flags & 0x430) == 0) {
                    if ((s16)func_8009FD7C(
                            sprite->tile.bytes.x, sprite->tile.bytes.y,
                            D_80082E80.tileX, D_80082E80.tileY) != 0) {
                        room_or_facing = func_800A0818(
                            sprite->tile.bytes.x, sprite->tile.bytes.y,
                            D_80082E80.tileX, D_80082E80.tileY, (s16 *)&distance);
                        entity->facing = room_or_facing;
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
    }
    if (sprite->frameTable != D_8016186C) {
        sprite->frameTable = D_8016186C;
        func_80047784(
            sprite,
            D_8016186C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
    }
}

