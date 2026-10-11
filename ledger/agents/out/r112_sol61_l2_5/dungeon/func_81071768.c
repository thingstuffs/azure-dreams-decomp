#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern void func_80042B68(void *, s32);
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
extern void func_80159510(void *, void *, void *, void *);
extern void func_80159768(u8 *move_work, void *entry_context, u8 *position, u8 *actor);
extern s32 func_80159F24(void *, void *, void *, void *);
extern void func_8015A110(void *, void *, void *, void *);
extern s32 func_8015A228(void *, void *, void *, s32);
extern void func_8015B900(void *, void *, void *, void *);
extern void func_8015BAD4(void *, void *, void *, void *);

extern s32 D_80158F68;
extern u8 D_8015BFB8[];
extern u8 D_8015BFC0[];
extern u8 D_8015BFF0[];
extern u8 D_8015BFF8[];
extern u8 D_8015C000[];

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 animationKind;
    u8 animationEnabled;
    u8 pad_06[0xE];
    u16 animationFlags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    union { s8 signedValue; u8 value; } roomId;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void func_80158F68(Rec_func_800A9E70_arg0 *action, void *context, ActorSpriteView *sprite, EntityRec *actor)
{
    u8 *anim_table;
    s32 tile_id;
    s32 distance;
    u32 initial_flags = dungeonStatus.flags;

    if (initial_flags & 0x1000) {
        action->unk_9A.as_u8 = 0xE;
        func_80159510(action, context, sprite, actor);
        return;
    }

    if (actor->tileY == 0) {
        u8 *inactive_anims;

        func_800AA79C(action, context, sprite, actor);
        if (sprite->directionFrames != D_8015C000) {
            inactive_anims = D_8015BFF8;
            sprite->directionFrames = inactive_anims;
            func_80047784(sprite,
                inactive_anims[((gameWork.view.viewAngle + actor->facing + 0x100)
                    >> 9) & 7],
                0);
        }
        action->unk_AE = 0;
        func_80042B68(actor, 0x1A);
        return;
    }

    if (actor->flags1C & 0x200) {
        if (sprite->directionFrames == D_8015C000) {
            action->unk_9A.as_u8 = 0xD;
            action->unk_9B.as_u8 = 1;
            action->unk_8C = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (func_800AA924(action, context, sprite, D_8015BFF8)) {
            return;
        }
    }

    if (!(dungeonStatus.flags & 0x2000)) {
        if (actor->flags1C & 0x100) {
            func_800AA258(action, context, sprite, actor);
            return;
        }

        if (action->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_8015BFB8;
            if (sprite->directionFrames != anim_table) {
                sprite->directionFrames = anim_table;
                func_80047784(sprite,
                    anim_table[((gameWork.view.viewAngle + actor->facing + 0x100)
                        >> 9) & 7],
                    0);
            }
            action->unk_9A.as_u8 = next_state;
        }

        action->unk_98 &= 0xFFF3;
        if (actor->unk_64 != 0) {
            if (func_800AA6B4(action, context, sprite, D_8015BFC0)) {
                    return;
            }
        }

        if (actor->flags1C & 0x80000) {
            func_800AA888(action, context, sprite, actor);
            func_8015B900(action, context, sprite, actor);
            return;
        }

        if ((s16)func_800A1C58(actor) != 0) {
            func_800AAB10(action, context, sprite, actor);
        }
    }

    tile_id = func_8009FB34(sprite->position.tile.x,
        sprite->position.tile.y);
    sprite->roomId.value = tile_id;

    if (actor->unk_6D > 0) {
        if (actor->flags1C & 0x20) {
            func_800A9A0C(actor);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_80159768(action, context, sprite, actor);
            return;
        }
        if (!(actor->unk_46 & 0x8000)) {
            if (dungeonStatus.flags & 0x2000) {
                if ((s16)func_8009A180(actor,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8015A228(action, context, sprite, 0) == 0) {
                    return;
            }
            actor->unk_46 |= 0x4000;
            if (!(actor->unk_46 & 0x8000)) {
                func_80159768(action, context, sprite, actor);
                return;
            }
        }

        switch (actor->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80159F24(action, context, sprite, actor) == 0) {
                func_8015A110(action, context, sprite, actor);
                    return;
            }
            return;
        case 9:
            func_8015BAD4(action, context, sprite, actor);
            return;
        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s32 direction;

                direction = func_800A0818(
                    sprite->position.tile.x, sprite->position.tile.y,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                actor->facing = direction;
                if (player->unk_9A == 0x11) {
                    func_800AAF00(action, context, sprite, D_8015BFF0, &D_80158F68);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            func_800A9A0C(actor);
            return;
        case 1:
        case 2:
        case 3:
            func_800AAF00(action, context, sprite, D_8015BFF0, &D_80158F68);
            return;
        default:
            func_80159768(action, context, sprite, actor);
            return;
        }
    } else if (!(actor->flags1C & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(actor->flags1C & 0x430)) {

                if ((s16)func_8009FD7C(sprite->position.tile.x,
                        sprite->position.tile.y, D_80082E80.tileX,
                        D_80082E80.tileY) != 0) {
                    actor->facing = func_800A0818(
                        sprite->position.tile.x,
                            sprite->position.tile.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (dungeonStatus.flags & 0x2000) {
        return;
    }
    if (sprite->animationFlags & 0x40) {
        return;
    }
    anim_table = D_8015BFB8;
    if (sprite->directionFrames == anim_table) {
        return;
    }
    sprite->directionFrames = anim_table;
    func_80047784(sprite,
        ((((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
