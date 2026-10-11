#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
extern int abs(int);

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
    u8 pad_90[0x6];
    u16 ticks;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ActionState;

typedef struct ObjectHeaderTail {
    void * sprite;
    u8 pad_04[0x10];
} ObjectHeaderTail;   /* the 0x14 bytes before obj in func_8015ADEC, addressed as obj[-1] */

typedef struct TilePosition {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TilePosition;

extern s32 func_8003F270(void);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void func_800DB2DC(void *, void *, void *, s32);

extern u8 D_80158F6C[];
extern u8 D_8015D258[];

/* Advances an actor action through item_slot selection, execution, and recovery. */
void func_8015ADEC(ActionState *action_state, EntityRec *transform, ActorSprite *sprite, EntityRec *actor)
{
    u16 saved_position[3];
    u8 *item_slot;
    s32 use_global_target;
    void *target;
        s32 abs_x;
    s32 abs_y;
    TilePosition *target_sprite;
    s32 ticks_left;

    use_global_target = 0;
    switch (action_state->phase) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                use_global_target = 1;
                /* fall through */
            case 3:
                item_slot = &((ItemSlots *)actor)->third;
                break;
            case 6:
                use_global_target = 1;
                /* fall through */
            case 2:
                item_slot = &((ItemSlots *)actor)->second;
                break;
            case 5:
                use_global_target = 1;
                /* fall through */
            case 1:
                item_slot = &((ItemSlots *)actor)->first;
                break;
            default:
                item_slot = (u8 *)0;
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
                item_slot = (u8 *)0;
                break;
            }
        }
        if (*item_slot != 0) {
            action_state->flags &= 0xFF7F;
            {
                s16 global_target_flag = use_global_target;

                if (global_target_flag != 0) {
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
                        func_800A05A4(actor, sprite->tileX, sprite->tileY,
                                      actor->facing, 0x10);
                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }
            saved_position[0] = ((u16)transform->x.w.i);
            saved_position[1] = ((u16)transform->y.w.i);
            saved_position[2] = ((u16)transform->z.w.i);
            if (func_800A94A0(actor, item_slot, use_global_target, &action_state->flags) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            func_800A56E0(0x703);
            func_800DB2DC(transform, sprite, actor, 0x10);
            action_state->phase = action_state->phase + 1;
            return;
        }

        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        func_800A2B04(transform, sprite->tileX, sprite->tileY);
        dungeonStatus.unk_0C = 0;
        ((PlayerActionCounter *)D_800814A8)->pendingActions = ((PlayerActionCounter *)D_800814A8)->pendingActions - 1;
        func_800A4ACC(actor);
        actor->unk_6D = ((u8)actor->unk_6D) - 1;
        action_state->handler = D_80158F6C;
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
        action_state->phase = action_state->phase + 1;
        /* fall through */
    case 2:
        if ((sprite->frame == 3 && (sprite->flags & 0x1000))
            ||
            (sprite->flags & 0xE000)) {
            sprite->flags |= 0x800;
            action_state->ticks = 0xE;
            action_state->flags |= 0x80;
        }
        ticks_left = action_state->ticks - 1;
        action_state->ticks = ticks_left;
        if ((s16)ticks_left <= 0) {
            action_state->ticks = 0;
            sprite->flags &= 0xF7FF;
        }
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }
        transform->flags14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        func_800A2B04(transform, sprite->tileX, sprite->tileY);
        {
            u8 *direction_table = D_8015D258;

            if (sprite->directionFrames != direction_table) {
                sprite->directionFrames = direction_table;
                func_80047784(sprite,
                    direction_table[((gameWork.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
            }
        }
        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
        sprite->flags &= 0xF7FF;
        action_state->handler = D_80158F6C;
        func_800A4ACC(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    }
}
