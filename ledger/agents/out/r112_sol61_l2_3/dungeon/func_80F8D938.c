#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *action, s32 unused, void *sprite, u8 *direction_frames);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *action, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8016B670(void *, void *);
extern void func_8016B82C(void *, void *, void *, void *);
extern s32 func_8016BF74(void *, void *, void *, void *);
extern void func_8016C138(void *, void *, void *, void *);
extern s32 func_8016C258(void *, void *, void *, s32);
extern void func_8016DD38(void *, void *, void *, void *);
extern void func_8016E0F4(void *, void *, void *, void *);

extern u8 D_8016B138[];
extern u8 D_8016EAD4[];
extern u8 D_8016EADC[];
extern u8 D_8016EAEC[];
extern u8 D_8016EAF4[];
extern u8 D_8016EAFC[];

void func_8016B138(ActorActionView *action_input, EntityRec *motion_input, ActorSpriteView *sprite_in, EntityRec *entity_input)
{
    ActorActionView *action;
    EntityRec *motion;
    ActorSpriteView *sprite;
    EntityRec *entity;
    s32 facing_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = dungeonStatus.flags;

    action = action_input;
    motion = motion_input;
    sprite = sprite_in;
    entity = entity_input;

    if (dungeon_flags & 0x1000) {
        action->behavior = 0xE;
        func_8016B670(action_input, motion_input);
        return;
    }

    if (entity->tileY == 0) {
        func_800AA79C(action, motion, sprite, entity);
        if (sprite->directionFrames == D_8016EAFC) {
            return;
        }
        sprite->directionFrames = D_8016EAF4;
        func_80047784(sprite,
            D_8016EAF4[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (entity->flags1C & 0x200) {
        if (sprite->directionFrames == D_8016EAFC) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextAction.code = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(action, motion, sprite, D_8016EAF4) != 0) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            func_800AA258(action, motion, sprite, entity);
            return;
        }

        if (action->behavior != 0xE) {
            action->behavior = 0xE;
        }

        if (sprite->directionFrames != D_8016EAD4) {
            action->frameParameter = 0;
            sprite->directionFrames = D_8016EAD4;
            func_80047784(sprite,
                D_8016EAD4[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                action->frameParameter);
        }

        entity->flags1C |= 0x40000;
        action->flags &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (func_800AA6B4(action, motion, sprite, D_8016EADC) != 0) {
                return;
            }
        }

        if (entity->flags1C & 0x80000) {
            func_800AA888(action, motion, sprite, entity);
            action->frameParameter = 0;
            func_8016DD38(action, motion, sprite, entity);
            return;
        }

        if ((s16)func_800A1C58(entity) != 0) {
            func_800AAB10(action, motion, sprite, entity);
        }
    }

    tile_index = func_8009FB34(sprite->position.tile.x, sprite->position.tile.y);
    sprite->tileIndex.unsignedIndex = tile_index;

    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            func_800A9A0C(entity);
            return;
        }
        if (!(sprite->position.packed == ((TilePairView *)&D_80082E80.tileX)->packed)) {
            action_state = entity->unk_46;
            if (!(action_state & 0x8000)) {
                if (dungeonStatus.flags & 0x2000) {
                    if ((s16)func_8009A180(entity,
                            (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                        return;
                    }
                }
                if ((s16)func_8016C258(action, motion, sprite, 0) == 0) {
                    return;
                }
                action_state = entity->unk_46 | 0x4000;
                entity->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (entity->unk_46 & 0x3FFF) {
                case 9:
                    func_8016E0F4(action, motion, sprite, entity);
                    return;

                case 8:
                    if ((s16)func_8016BF74(action, motion, sprite, entity) != 0) {
                        return;
                    }
                    func_8016C138(action, motion, sprite, entity);
                    return;

                case 12:
                    func_800A9A0C(entity);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = func_800A0818(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &facing_aux);
                    player = D_800814A8;
                    entity->facing = facing_angle;
                    if (player->unk_9A != 0x11) {
                        func_800A9A0C(entity);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    func_800AAF00(action, motion, sprite, D_8016EAEC, D_8016B138);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        func_8016B82C(action, motion, sprite, entity);
        return;
    }

    status_flags = entity->flags1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((s16)func_8009FD7C(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tileX, D_80082E80.tileY) != 0) {
            entity->facing = func_800A0818(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tileX, D_80082E80.tileY, &facing_aux);
        }
    }
    return;
}
