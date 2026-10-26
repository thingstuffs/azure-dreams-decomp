#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
/* Actor sprite lifecycle and its file-private helper. */
#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
static s32 uses_direct_actor_sprite_frames(void *record);
#include "dungeon/player/object/action_state.h"
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void select_indirect_table_entry(void *state, u8 table_index, s8 entry_index);
extern void advance_sprite_animation_and_textures(void *entity);

extern void initialize_actor_object_action(void *object_state, s32 unused_context, void *properties, void *status);
extern s16 pending_marked_actor_count;
/* arg2 in refresh_actor_facing_and_lifecycle */

static s32 uses_direct_actor_sprite_frames(void *record) {
    if (*(s32 *)(*(void **)((s8 *)record - 0x14)) == 0) {
        return 1;
    }

    {
        s32 value_offset = *(u8 *)((s8 *)record + 19) - 46;

        return (u32)value_offset < 2;
    }
}

/* Updates directional sprite frames and starts pending actor actions when dungeon activity allows. */
s32 refresh_actor_facing_and_lifecycle(Rec_func_800A9E70_arg0 *anim, s32 action_arg, SpriteFrameState *sprite, ActorRecord *entity) {
    void *active_entity;
    s32 entity_flags;
    s32 direction;
    s32 action_type;
    u16 action_flags;

    if (entity->flags14 & 0x100000) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
        if (anim->unk_94 != direction) {
            if (uses_direct_actor_sprite_frames(entity) != 0) {
                select_record_entry_and_value(sprite, (*(s32 **)&sprite->frameTable)[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            } else {
                select_indirect_table_entry(sprite, (*(u8 **)&sprite->frameTable)[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            }
        }
        if (dir_sprite_flag[direction] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
        advance_sprite_animation_and_textures(sprite);
        return 1;
    }

    if (entity->flags1C & ACTOR_CONFUSED) {
        action_flags = entity->action_flags;
        if (action_flags & 0x8000) {
            if (!(action_flags & 0x4000)) {
                action_type = action_flags & 0x3FFF;
                if (((u32)(action_type - 5) < 3U) || (action_type == 0xC)) {
                    entity->action_flags = action_flags & 0x7FFF;
                }
            }
        }
    }

    if (!(sprite->flags & 0x8000)) {
        if (anim->unk_98 & 0x400) {
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7;
            if (uses_direct_actor_sprite_frames(entity) != 0) {
                select_record_entry_and_value(sprite, (*(s32 **)&sprite->frameTable)[direction],
                              sprite->unk_04);
            } else {
                select_indirect_table_entry(sprite, (*(u8 **)&sprite->frameTable)[direction],
                              sprite->unk_04);
            }
            anim->unk_98 &= 0xFBFF;
        }
    } else {
        anim->unk_98 |= 0x400;
    }

    if ((entity->flags1C & ACTOR_PLAYER_SIDE) ||
        (entity->flags14 & ACTOR_PARTY_MEMBER)) {
        if ((u32)(anim->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->pending_turn_updates == 0) {
                if (pending_marked_actor_count == 0) {
                    if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
                        return 0;
                    }
                } else {
                    active_entity = g_dungeon_status.active_actor;
                    if (active_entity != entity) {
                        if ((((s32)g_dungeon_status.pending_display_owner) == 0) && (active_entity == 0) &&
                            (g_dungeon_status.activity_counts.parts.pending_movement_count == 0) &&
                            !(g_dungeon_status.flags & 0x2008) &&
                            (entity->unk_43 == 0xFD)) {
                            g_dungeon_status.active_actor = entity;
                        } else {
                            return 0;
                        }
                    }
                    if (entity->unk_43 != 0xFD) {
                        return 0;
                    }
                }
                if (entity->flags1C & 0x400000) {
                    anim->unk_8C = 0;
                    entity_flags = entity->flags14;
                    entity->flags1C &= 0xFFBFFFFF;
                    if (entity_flags & 0x20000000) {
                        entity->flags14 = entity_flags | 0x400000;
                        begin_actor_flagged_action(anim, action_arg, sprite, entity);
                        return 0;
                    }
                    entity->flags14 = entity_flags & 0xFFBFFFFF;
                    {
                        u32 next_anim = entity_flags & 0x4000;
                        if (next_anim) {
                            next_anim = 1;
                        } else {
                            next_anim = 2;
                        }
                        anim->unk_9A.as_u8 = next_anim;
                    }
                    anim->unk_9B.as_u8 = 0;
                } else if (entity->flags1C & 0x02000000) {
                    anim->unk_8C = 0;
                    entity->movement_queue_state = 0;
                    entity->flags1C &= 0xFDFFFFFF;
                    if (entity->flags14 & 0x20000000) {
                        initialize_actor_object_action(anim, action_arg, sprite, entity);
                        return 0;
                    }
                    anim->unk_9A.as_u8 = 0;
                    anim->unk_9B.as_u8 = 0;
                }
            }
        }
    }
    return 0;
}
