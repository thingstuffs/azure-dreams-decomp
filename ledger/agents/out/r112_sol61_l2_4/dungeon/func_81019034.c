#include "common.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct ItemSlots {
    u8 pad_00[8];
    u8 first;
    u8 pad_09[2];
    u8 second;
    u8 pad_0C[2];
    u8 third;
} ItemSlots;

typedef struct PlayerActionCounter {
    u8 pad_00[0xA6];
    u16 pendingActions;
} PlayerActionCounter;

typedef struct ActorSprite {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[0xE];
    u8 tileX;
    u8 tileY;
    u8 pad_26[6];
    u8 *directionFrames;
} ActorSprite;

typedef struct ActionState {
    u8 pad_00[0x8C];
    void * handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ActionState;

typedef struct ObjectHeaderTail {
    void * sprite;
    u8 pad_04[0x10];
} ObjectHeaderTail;   /* the 0x14 bytes before object in func_80160834, addressed as object[-1] */

typedef struct TilePosition {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TilePosition;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(u16 *, s32);

extern u8 D_8015F058[];
extern u8 D_80162888[];

/* Starts the selected actor action, waits for completion, and resets its state. */
void func_80160834(ActionState *action_state, EntityRec *motion, ActorSprite *sprite, EntityRec *actor)
{
    u8 *item_slot;
    s32 phase;
    s32 use_player_target;
    void *target;
    s16 flags_or_target_mode;
    TilePosition *target_sprite;
    u16 position[3];

    phase = action_state->phase;
    use_player_target = 0;
    switch (phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fall through */
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            flags_or_target_mode = action_state->flags;
            flags_or_target_mode &= 0xFF7F;
            action_state->flags = flags_or_target_mode;
            flags_or_target_mode = use_player_target;
            if (flags_or_target_mode != 0) {
                target = D_800814A8;
                actor->target = target;
                target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                actor->unk_72 = target_sprite->tileX;
                actor->unk_73 = target_sprite->tileY;
            } else if (D_8006DE24[*item_slot].kind == 2) {
                target = actor->target;
                if (target != 0) {
                    target_sprite = ((ObjectHeaderTail *)target)[-1].sprite;
                    actor->unk_72 = target_sprite->tileX;
                    actor->unk_73 = target_sprite->tileY;
                }
            } else {
                actor->target =
                    func_800A05A4(actor,
                                  sprite->tileX,
                                  sprite->tileY,
                                  actor->facing, 0x10);
                {
                    s32 abs_x = abs(actor->unk_72);
                    s32 abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(actor, item_slot, use_player_target,
                              &action_state->flags) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            func_800DA840(position, (s16)(((s32)*item_slot - 1) % 3));
            func_800A56E0(0x703);
            action_state->phase++;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->tileX, sprite->tileY);
        dungeonStatus.unk_0C = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions--;
        func_800A4ACC(actor);
        (*(u8 *)&actor->unk_6D)--;
        action_state->handler = D_8015F058;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action_state->phase++;

    case 2:
        if (!((sprite->frame == 3) &&
              (sprite->flags & 0x1000)) &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        action_state->flags |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->tileX, sprite->tileY);
        if (sprite->directionFrames != D_80162888) {
            sprite->directionFrames = D_80162888;
            func_80047784(
                sprite,
                D_80162888[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {

            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        sprite->flags &= 0xF7FF;
        action_state->handler = D_8015F058;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            (*(u8 *)&actor->unk_6D)--;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);

        return;
    default:
        return;
    }
}
