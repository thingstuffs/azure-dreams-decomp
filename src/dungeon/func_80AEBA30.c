#include "common.h"
#include "shared/sprite_frame_state.h"
extern int abs(int);
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

#ifndef DUNGEON_ACTOR_ITEM_SLOTS_VIEW
#define DUNGEON_ACTOR_ITEM_SLOTS_VIEW
/* Three adjacent 3-byte action records begin at +0x08. */
typedef struct ActorItemSlotsView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorItemSlotsView;
#endif

#ifndef DUNGEON_PLAYER_ACTION_COUNT_VIEW
#define DUNGEON_PLAYER_ACTION_COUNT_VIEW
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remainingActions;
} PlayerActionCountView;
#endif

#ifndef DUNGEON_ACTOR_ACTION_BYTES_VIEW
#define DUNGEON_ACTOR_ACTION_BYTES_VIEW
typedef struct ActorActionBytesView {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[0xA];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 actionFlags;
    u8 pad_48[0x18];
    void *target;
    u8 pad_64[0x9];
    u8 remainingActions;
    u8 pad_6E[4];
    u8 targetX;
    u8 targetY;
} ActorActionBytesView;
#endif

typedef struct {
    u32 words[12];
} Copy48;

extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s32 get_cd_command_queue_depth(void);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context);

extern u8 D_8014D020[];
extern s32 D_8014D728;
extern u8 D_80150DEC[];
extern u8 D_80150E34[];

typedef struct ItemEffectActionState {
    u8 pad_00[0x8C];
    void * nextBehavior;
    u8 pad_90[0x6];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
    u8 pad_9C[0x10];
    u16 savedDrawAttributes;
} ItemEffectActionState;

typedef struct TargetTileView {
    u8 pad_00[0x24];
    u8 tileX;
    u8 tileY;
} TargetTileView;

typedef struct ItemEffectStateView {
    u8 pad_00[0x94];
    u16 facing;
    u16 timer;
    u8 pad_98[0x10];
    void * motion;
} ItemEffectStateView;

typedef struct ItemEffectObjectView {
    u8 pad_00[0x8];
    u8 * position;
    u8 * sprite;
    void * update;
} ItemEffectObjectView;

typedef struct ItemEffectSpriteView {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
    u8 red;
    u8 green;
    u8 blue;
    u8 pad_0F[0x1];
    u16 drawOffset;
    u16 drawAttributes;
    u16 flags;
    u8 pad_16[0x6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[0xC];
    void * animationTable;
} ItemEffectSpriteView;

typedef struct ActionObjectView {
    u8 pad_00[0xC];
    void * sprite;
} ActionObjectView;

typedef struct AnimationObjectView {
    u8 pad_00[0x8];
    void * animation;
} AnimationObjectView;

void advance_multi_slot_action_sequence(void *action, ObjectPosition *motion, void *sprite, void *actor)
{
    u8 *effect_state;
    s32 effect_handle;
    s16 use_player_target;
    u16 effect_offset[4];
    u8 *item_slot;
    u8 *action_object;
    s32 next_state;
    u8 state;
    void *item_target;

    use_player_target = 0;
    action_object = (u8 *)action - 0x20;
    state = ((ItemEffectActionState *)action)->phase;
    if ((u32)state >= 5) {
        return;
    }
    switch (state) {
    case 0:
        if (((ActorActionBytesView *)actor)->flags & 0x2000) {
            switch (((ActorActionBytesView *)actor)->actionFlags & 0x3FFF) {
            case 7:
                use_player_target = 1;
                /* fallthrough */
            case 3:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 6:
                use_player_target = 1;
                /* fallthrough */
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 5:
                use_player_target = 1;
                /* fallthrough */
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            switch (((ActorActionBytesView *)actor)->actionFlags & 0x3FFF) {
            case 3:
                item_slot = ((ActorItemSlotsView *)actor)->slots[2];
                break;
            case 2:
                item_slot = ((ActorItemSlotsView *)actor)->slots[1];
                break;
            case 1:
                item_slot = ((ActorItemSlotsView *)actor)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            ((ItemEffectActionState *)action)->flags &= 0xFF7F;
            if ((s16)use_player_target != 0) {
                item_target = primary_actor_record;
                ((ActorActionBytesView *)actor)->target = item_target;
                    effect_state = ((ObjectNodeHeader *)((u8 *)item_target - 0x20))->unk_0C;
                    ((ActorActionBytesView *)actor)->targetX = ((TargetTileView *)effect_state)->tileX;
                    ((ActorActionBytesView *)actor)->targetY = ((TargetTileView *)effect_state)->tileY;
            } else {
                u8 item_id = *item_slot;
                DefEntry *item_defs = item_action_definitions;
                if (item_defs[item_id].kind == 2) {
                    item_target = ((ActorActionBytesView *)actor)->target;
                    if (item_target != 0) {
                    effect_state = ((ObjectNodeHeader *)((u8 *)item_target - 0x20))->unk_0C;
                    ((ActorActionBytesView *)actor)->targetX = ((TargetTileView *)effect_state)->tileX;
                    ((ActorActionBytesView *)actor)->targetY = ((TargetTileView *)effect_state)->tileY;
                    }
                } else {
                    s32 dx;
                    s32 dy;

                    dx = (s32)scan_monster_along_heading(
                        actor, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25,
                        ((ActorActionBytesView *)actor)->facing, 0x10);
                    ((ActorActionBytesView *)actor)->target = (void *)dx;
                    dx = abs(((ActorRecord *)actor)->target_tile_x);
                    dy = abs(((ActorRecord *)actor)->target_tile_y);
                    ((ActorActionBytesView *)actor)->targetX = dx;
                    ((ActorActionBytesView *)actor)->targetY = dy;
                }
            }

            if (create_actor_spell_effect(actor, item_slot, use_player_target, &((ItemEffectActionState *)action)->flags) == 0) {
                return;
            }
            ((ItemEffectActionState *)action)->timer.unsignedTicks = 0x11;
            ((ItemEffectActionState *)action)->phase++;
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
        g_dungeon_status.active_actor = 0;
        ((PlayerActionCountView *)primary_actor_record)->remainingActions--;
        advance_status_timers(actor);
        ((ActorActionBytesView *)actor)->remainingActions--;
        ((ItemEffectActionState *)action)->nextBehavior = &D_8014D728;
        ((ActorActionBytesView *)actor)->targetY = 0;
        ((ActorActionBytesView *)actor)->targetX = 0;
        ((ActorActionBytesView *)actor)->actionFlags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth()) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((ItemEffectActionState *)action)->phase++;
        play_sound_if_enabled(0x703);

    case 2:
        {
            s16 timer;

            timer = ((ItemEffectActionState *)action)->timer.unsignedTicks - 1;
            ((ItemEffectActionState *)action)->timer.unsignedTicks = timer;
            if (timer == 0xB || (((SpriteFrameState *)sprite)->flags & 0xE000)) {
                effect_handle = (s32)allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
                if (effect_handle != 0) {
                    void *actor_model;
                    u8 animation_id;

                    effect_state = (u8 *)effect_handle + 0x20;
                    ((ItemEffectStateView *)effect_state)->timer = 9;
                    ((ItemEffectObjectView *)((void *)effect_handle))->update = D_8014D020;
                    ((ItemEffectStateView *)effect_state)->motion = motion;
                    ((ItemEffectStateView *)effect_state)->facing = ((ActorActionBytesView *)actor)->facing;
                    item_slot = ((ItemEffectObjectView *)((void *)effect_handle))->sprite;
                    *(Copy48 *)item_slot = *(Copy48 *)sprite;
                    ((ItemEffectSpriteView *)item_slot)->scaleY = 0x1000;
                    ((ItemEffectSpriteView *)item_slot)->scaleX = 0x1000;
                    ((ItemEffectSpriteView *)item_slot)->blue = 0x80;
                    ((ItemEffectSpriteView *)item_slot)->green = 0x80;
                    ((ItemEffectSpriteView *)item_slot)->red = 0x80;
                    register_node((void *)effect_handle, project_sprite_chain);
                    animation_id = D_80150E34[0];
                    ((ItemEffectSpriteView *)item_slot)->animationTable = D_80150E34;
                    select_sprite_entry(item_slot, animation_id, 0);
                    ((ItemEffectSpriteView *)item_slot)->drawOffset = 0x20;
                    ((ItemEffectSpriteView *)item_slot)->drawAttributes = 0xFF80;
                    ((ItemEffectSpriteView *)item_slot)->flags |= 0x0C;

                    actor_model = ((ActionObjectView *)action_object)->sprite;
                    item_slot = ((ItemEffectObjectView *)((void *)effect_handle))->position;
                    if (resolve_record_orientation_or_fallback(
                            ((AnimationObjectView *)actor_model)->animation, actor_model, effect_offset, 1) != 0) {
                        ((ItemEffectSpriteView *)item_slot)->x = ((u16)motion->x.w.i);
                        ((ItemEffectSpriteView *)item_slot)->y = ((u16)motion->y.w.i);
                        ((ItemEffectSpriteView *)item_slot)->z = ((u16)motion->z.w.i);
                        ((ItemEffectSpriteView *)item_slot)->x += effect_offset[0];
                        ((ItemEffectSpriteView *)item_slot)->y += effect_offset[1];
                        ((ItemEffectSpriteView *)item_slot)->z += effect_offset[2];
                    }
                }
            }

            if (((ItemEffectActionState *)action)->timer.signedTicks == 0xB ||
                (((SpriteFrameState *)sprite)->flags & 0xE000)) {
                ((SpriteFrameState *)sprite)->flags |= 0x800;
            }
            if (((ItemEffectActionState *)action)->timer.signedTicks == 0 ||
                (((SpriteFrameState *)sprite)->flags & 0xE000)) {
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
            if (((ItemEffectActionState *)action)->timer.signedTicks <= 0 ||
                (((SpriteFrameState *)sprite)->flags & 0xE000)) {
                next_state = ((ItemEffectActionState *)action)->phase + 1;
                ((ItemEffectActionState *)action)->phase = next_state;
            }
        }
        return;

    case 3:
        if ((((SpriteFrameState *)sprite)->unk_04 == 3 &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((ItemEffectActionState *)action)->timer.unsignedTicks = 0x14;
            ((ItemEffectActionState *)action)->flags |= 0x80;
            ((SpriteFrameState *)sprite)->flags |= 0x100;
            ((ItemEffectActionState *)action)->savedDrawAttributes = ((SpriteFrameState *)sprite)->clut;
            ((SpriteFrameState *)sprite)->clut = 0x7E80;
            ((ItemEffectActionState *)action)->phase++;
        }

    case 4:
        {
            s16 timer;

            if (((s32)g_dungeon_status.active_actor) == 0) {
                ((ItemEffectActionState *)action)->timer.unsignedTicks = 0;
            }
            timer = ((ItemEffectActionState *)action)->timer.unsignedTicks - 1;
            ((ItemEffectActionState *)action)->timer.unsignedTicks = timer;
            if (timer <= 0) {
                ((ItemEffectActionState *)action)->timer.unsignedTicks = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
            if (((ItemEffectActionState *)action)->timer.signedTicks == 0x12) {
                ((SpriteFrameState *)sprite)->flags &= 0xFEFF;
                ((SpriteFrameState *)sprite)->clut = ((ItemEffectActionState *)action)->savedDrawAttributes;
            }
            if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
                return;
            }

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->flags &= 0xFEFF;
            ((SpriteFrameState *)sprite)->clut = ((ItemEffectActionState *)action)->savedDrawAttributes;

            if (*(u8 * *)&((SpriteFrameState *)sprite)->frameTable != D_80150DEC) {
                u8 *animations;
                s32 direction;

                animations = D_80150DEC;
                ((SpriteFrameState *)sprite)->frameTable = animations;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorActionBytesView *)actor)->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, animations[direction], 0);
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((ItemEffectActionState *)action)->nextBehavior = &D_8014D728;
            advance_status_timers(actor);
            ((ActorActionBytesView *)actor)->targetY = 0;
            ((ActorActionBytesView *)actor)->targetX = 0;
            ((ActorActionBytesView *)actor)->remainingActions--;
            ((ActorActionBytesView *)actor)->actionFlags &= 0x7FFF;
            play_sound_if_enabled(0xB4);
        }
    }
}
