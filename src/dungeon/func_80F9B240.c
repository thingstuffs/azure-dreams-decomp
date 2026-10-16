#include "shared/object_node.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

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

/* The selected three-byte action records overlap the entity's position view. */
typedef struct ActorActionSlotsView {
    u8 pad_00[8];
    u8 first[3];
    u8 second[3];
    u8 third[3];
} ActorActionSlotsView;

/* Halfword view of the player's action counter at EntityRec + 0xA6. */
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remaining;
} PlayerActionCountView;

extern int abs(int);

extern s32 getCdCommandQueueDepth(void);
extern void func_80047784(void *, u8, s16);
extern void *dungeonScanMonsterAlongHeading(void *, u8, u8, s16, s32);
extern void dungeonSetRecordIntegerTileCenter(void *, u8, u8);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A56E0(s32);
extern s32 dungeonCreateActorSpellEffect(void *actor, EntityRec *effect_record, s16 mode, void *context);
extern void dungeonCreateSourcePositionedObject(EntityRec *source_pos, s16 initial_value);

extern u8 D_8015F138[];
extern u8 D_80162AD4[];

void func_80160A40(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, EntityRec *actor)
{
    s16 use_player_target;
    u8 *item_slot;
    s32 state;
    s32 action_kind;
    s32 player_target_flag;
    DefEntry *item_entry;
    DefEntry *item_table;
    void *target;
    EntityRec *target_position;
    s32 abs_x;
    s32 abs_y;
    s32 action_index;
    s32 item_id;

    state = action->phase;
    use_player_target = 0;
    switch (state) {
    case 0:
        if (((u32)actor->flags1C) & 0x2000) {
            action_index = (actor->unk_46 & 0x3FFF) - 1;
            switch (action_index) {
            case 6:
                use_player_target = 1;
                /* fall through */
            case 2:
                item_slot = ((ActorActionSlotsView *)actor)->third;
                break;
            case 5:
                use_player_target = 1;
                /* fall through */
            case 1:
                item_slot = ((ActorActionSlotsView *)actor)->second;
                break;
            case 4:
                use_player_target = 1;
                /* fall through */
            case 0:
                item_slot = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            action_kind = actor->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = ((ActorActionSlotsView *)actor)->third;
                break;
            case 2:
                item_slot = ((ActorActionSlotsView *)actor)->second;
                break;
            case 1:
                item_slot = ((ActorActionSlotsView *)actor)->first;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            action->flags &= 0xFF7F;

            player_target_flag = use_player_target;
            if (player_target_flag) {
                target = D_800814A8;
                actor->target = target;
                target_position = ((ObjectNodeHeader *)target)[-1].unk_0C;
                actor->unk_72 = target_position->tileX;
                actor->unk_73 = target_position->tileY;
            } else {
                item_table = D_8006DE24;
                item_id = *item_slot;
                item_entry = &item_table[item_id];
                if (item_entry->kind == 2) {
                    target = actor->target;
                    if (target != 0) {
                        target_position = ((ObjectNodeHeader *)target)[-1].unk_0C;
                        actor->unk_72 = target_position->tileX;
                        actor->unk_73 = target_position->tileY;
                    }
                } else {
                    actor->target = dungeonScanMonsterAlongHeading(
                        actor, sprite->position.tile.x, sprite->position.tile.y,
                        actor->facing, 0x10);

                    abs_x = abs(actor->unk_72);
                    abs_y = abs(actor->unk_73);
                    actor->unk_72 = abs_x;
                    actor->unk_73 = abs_y;
                }
            }

            if (dungeonCreateActorSpellEffect(actor, item_slot, use_player_target,
                              &action->flags) == 0) {
                return;
            }
            sprite->flags &= 0xF7FF;
            dungeonCreateSourcePositionedObject(motion, 4);
            func_800A56E0(0x703);
            action->timer.unsignedTicks = 4;
            action->phase++;
            action->flags |= 8;
            actor->flags1C &= 0xF7FFFFFF;
            actor->flags1C &= 0xFFFBFFFF;
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, sprite->position.tile.x, sprite->position.tile.y);
        dungeonStatus.unk_0C = 0;
        ((PlayerActionCountView *)D_800814A8)->remaining--;
        dungeonAdvanceStatusTimers(actor);
        actor->unk_6D = (u8)actor->unk_6D - 1;
        action->nextAction.record = D_8015F138;
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (getCdCommandQueueDepth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        action->phase++;
        /* fall through */

    case 2:
        action->motionOffset.w.i +=
            (-0x30 - action->motionOffset.w.i) >> 3;
        action->timer.unsignedTicks--;
        if (action->timer.signedTicks > 0) {
            if ((sprite->flags & 0xE000) == 0) {
                return;
            }
        }
        action->flags |= 0x80;
        if ((sprite->flags & 0xE000) == 0) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, sprite->position.tile.x, sprite->position.tile.y);
        action->flags &= 0xFFF7;
        actor->flags1C |= 0x08000000;
        actor->flags1C |= 0x00040000;

        if (sprite->directionFrames != D_80162AD4) {
            sprite->directionFrames = D_80162AD4;
            func_80047784(sprite,
                          D_80162AD4[((gameWork.view.viewAngle +
                                       actor->facing + 0x100) >> 9) & 7],
                          action->frameParameter);
        }

        if (((s32)dungeonStatus.unk_0C) != 0) {
            return;
        }
        dungeonStatus.unk_0A--;
        sprite->flags &= 0xF7FF;
        action->nextAction.record = D_8015F138;
        dungeonAdvanceStatusTimers(actor);
        if (actor->unk_6D > 0) {
            actor->unk_6D = (u8)actor->unk_6D - 1;
        }
        actor->unk_73 = 0;
        actor->unk_72 = 0;
        actor->unk_46 &= 0x7FFF;
        func_800A56E0(0xB4);
        break;
    default:
        return;
    }
}
