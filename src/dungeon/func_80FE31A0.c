#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
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

typedef struct {
    u32 x;
    u32 y;
    u32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} VecData;

typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} ItemData;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

typedef struct ActionState {
    u8 pad_00[0x8C];
    void *handler;
    u8 pad_90[0x08];
    u16 flags;
    u8 pad_9A[0x01];
    u8 phase;
    u8 pad_9C[0x0A];
    u16 actionsLeft;
    void *effect;
} ActionState;

typedef struct ActorSprite {
    u8 pad_00[0x04];
    s8 frame;
    u8 pad_05[0x07];
    s32 spriteLink;
    u8 pad_10[0x02];
    u16 renderParam;
    u16 flags;
    u8 pad_16[0x06];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[0x04];
    u8 tileX;
    u8 tileY;
    u8 pad_26[0x02];
    s32 renderFlags;
    u8 *directionFrames;
} ActorSprite;

typedef struct CreatureState {
    u8 pad_00[0x08];
    u8 item1;
    u8 pad_09[0x02];
    u8 item2;
    u8 pad_0C[0x02];
    u8 item3;
    u8 pad_0F[0x0D];
    u32 flags;
    u8 pad_20[0x0A];
    union { s16 s; u16 u; } facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x18];
    void *target;
    u8 pad_64[0x09];
    union { s8 s; u8 u; } actionsLeft;
    u8 pad_6E[0x04];
    union { s8 s; u8 u; } targetX;
    union { s8 s; u8 u; } targetY;
} CreatureState;

typedef struct EffectObject {
    u8 pad_00[0x08];
    VecData *motion;
    void *sprite;
    void *updateData;
    u8 pad_14[0x36];
    u16 facing;
    u8 pad_4C[0x6F];
    u8 phase;
} EffectObject;

typedef struct ObjectHeaderTail {
    void *sprite;
} ObjectHeaderTail;

typedef struct DungeonActionCounters {
    u8 pad_00[0x0A];
    u16 active;
    s32 pending;
} DungeonActionCounters;

extern s32 get_cd_command_queue_depth(void);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_two_row_object_group(void *, s16);

extern u8 effect_update_tag[];
extern u8 D_8016A838[16];
extern u8 D_8016AEA8;
extern u8 D_8016E038[];
extern u8 D_8016E078[];

/* Updates item use, its visual effect, and the actor's return to idle. */
void update_item_use_effect_and_idle_return(ActionState *actor, VecData *motion, ActorSprite *sprite, CreatureState *actor_data)
{
    s16 use_player = 0;
    EffectObject *effect = 0;
    void *target;
    u8 *item_slot;
    ActorSprite *effect_sprite;
    ShortVec sound_pos;
    u8 phase;
    u32 kind_index;

    phase = actor->phase;
    switch (phase) {
    case 0:
        if (actor_data->flags & 0x2000) {
            kind_index = (actor_data->action & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                use_player = 1;
                /* fall through */
            case 2:
                item_slot = &actor_data->item3;
                break;
            case 5:
                use_player = 1;
                /* fall through */
            case 1:
                item_slot = &actor_data->item2;
                break;
            case 4:
                use_player = 1;
                /* fall through */
            case 0:
                item_slot = &actor_data->item1;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind = actor_data->action & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = &actor_data->item3;
                break;
            case 2:
                item_slot = &actor_data->item2;
                break;
            case 1:
                item_slot = &actor_data->item1;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            actor->flags &= 0xFF7F;
            {
                s16 player_target;

                player_target = use_player;
                if (player_target != 0) {
                    target = primary_actor_record;
                    actor_data->target = target;
                    {
                        ActorSprite *target_sprite;

                        target_sprite = ((ObjectHeaderTail *)((u8 *)target - 0x14))->sprite;
                        actor_data->targetX.u = target_sprite->tileX;
                        actor_data->targetY.u = target_sprite->tileY;
                    }
                } else {
                    u32 selected_item_or_sprite;

                    /* The item ID is replaced by the target sprite address after selection. */
                    selected_item_or_sprite = *item_slot;
                    if (item_action_definitions[((u8)selected_item_or_sprite)].kind == 2) {
                        target = actor_data->target;
                        if (target != 0) {
                            selected_item_or_sprite = ((ObjectHeaderTail *)((u8 *)target - 0x14))->sprite;
                            actor_data->targetX.u = ((ActorSprite *)selected_item_or_sprite)->tileX;
                            actor_data->targetY.u = ((ActorSprite *)selected_item_or_sprite)->tileY;
                        }
                    } else {
                        s32 abs_x;
                        s32 abs_y;

                        target = scan_monster_along_heading(
                            actor_data,
                            sprite->tileX,
                            sprite->tileY,
                            actor_data->facing.s,
                            0x10);
                        actor_data->target = target;
                        abs_x = abs(actor_data->targetX.s);
                        abs_y = abs(actor_data->targetY.s);
                        actor_data->targetX.u = abs_x;
                        actor_data->targetY.u = abs_y;
                    }
                }
            }

            sound_pos.x = motion->x >> 16;
            sound_pos.y = motion->y >> 16;
            sound_pos.z = motion->z >> 16;

            if (!(actor->flags & 0x2000)) {
                void *new_effect;

                new_effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
                actor->effect = new_effect;
                effect = new_effect;
                if (effect != 0) {
                    VecData *effect_motion;

                    register_node(effect, project_sprite_chain);
                    effect->updateData = effect_update_tag;
                    effect_motion = effect->motion;
                    *effect_motion = *motion;
                    effect->phase = 0;
                    effect->facing = actor_data->facing.u;
                    {
                        s32 sprite_flags = sprite->renderFlags;
                        effect_sprite = effect->sprite;

                        effect_sprite->scaleY = 0x1000;
                        effect_sprite->scaleX = 0x1000;
                        effect_sprite->renderFlags = sprite_flags;
                        effect_sprite->flags = sprite->flags;
                        effect_sprite->renderParam = sprite->renderParam;
                        {
                            s32 sprite_link = sprite->spriteLink;

                            effect_sprite->directionFrames = D_8016E078;
                            effect_sprite->spriteLink = sprite_link;
                        }
                    }
                }
                actor->flags |= 0x2000;
            }

            {
                u8 *animations;
                s32 direction;

                effect_sprite = actor->effect;
                effect_sprite = ((EffectObject *)effect_sprite)->sprite;
                animations = effect_sprite->directionFrames;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing.s + 0x100) >> 9) & 7;
                select_sprite_entry(effect_sprite, animations[direction], 0);
            }
            if (create_actor_spell_effect(actor_data, item_slot, use_player,
                              &actor->flags) == 0) {
                return;
            }
            actor->flags &= 0xDFFF;
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(&sound_pos, (*item_slot - 1) % 3);
            actor->phase++;
            return;
        }
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
        g_dungeon_status.active_actor = 0;
        ((PlayerActionCounter *)primary_actor_record)->pendingActions--;
        advance_status_timers(actor_data);
        actor_data->actionsLeft.u--;
        actor->handler = &D_8016AEA8;
        actor_data->targetY.u = 0;
        actor_data->targetX.u = 0;
        actor_data->action &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        actor->phase++;
        /* fall through */

    case 2:
        if (actor->effect != 0) {
            effect = actor->effect;
            *effect->motion = *motion;
        }
        if ((sprite->frame != 4 ||
             !(sprite->flags & 0x1000)) &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        actor->flags |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        if (actor->effect != 0) {
            effect->phase = 0xFF;
            actor->effect = 0;
        }
        sprite->directionFrames = D_8016E038;
        select_sprite_entry(
            sprite,
            D_8016E038[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->facing.s + 0x100) >> 9) & 7],
            0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        set_record_integer_tile_center(motion, sprite->tileX, sprite->tileY);
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->flags &= 0xF7FF;
        actor->handler = &D_8016AEA8;
        advance_status_timers(actor_data);
        if (actor_data->actionsLeft.s > 0) {
            actor_data->actionsLeft.u--;
        }
        actor_data->targetY.u = 0;
        actor_data->targetX.u = 0;
        actor_data->action &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;

    default:
        return;
    }
}
