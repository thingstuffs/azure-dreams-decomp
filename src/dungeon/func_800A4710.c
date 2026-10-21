#include "common.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

extern s32 uses_direct_actor_sprite_frames(void *record);
extern s32 has_pending_dungeon_activity(void *entity);
extern void select_record_entry_and_value(void *state, s32 entries, s8 index);
extern void select_indirect_table_entry(void *state, u8 table_index, s8 entry_index);
extern void advance_sprite_animation_and_textures(void *entity);
extern void begin_actor_flagged_action(void *entity, s32 unused, void *status, void *event_state);
extern void initialize_actor_object_action(void *object_state, s32 unused_context, void *properties, void *status);

extern s16 pending_marked_actor_count;

typedef struct S_800A9E70_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x16];
    union { s32 * p; u8 * p2; } unk_2C;   /* accessed as both */
} S_800A9E70_2;   /* arg2 in refresh_actor_facing_and_lifecycle */

typedef struct S_800A9E70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0x2];
    void * unk_0C;
    s32 unk_10;
} S_800A9E70_3;   /* state in refresh_actor_facing_and_lifecycle */

/* Updates entity facing and applies pending animation changes. */
s32 refresh_actor_facing_and_lifecycle(Rec_func_800A9E70_arg0 *anim, s32 action_arg, S_800A9E70_2 *sprite, EntityRec *entity) {
    void *active_entity;
    s32 entity_flags;
    s32 direction;
    s32 action_type;
    u16 action_flags;

    if (entity->flags14 & 0x100000) {
        direction = ((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
        if (anim->unk_94 != direction) {
            if (uses_direct_actor_sprite_frames(entity) != 0) {
                select_record_entry_and_value(sprite, sprite->unk_2C.p[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            } else {
                select_indirect_table_entry(sprite, sprite->unk_2C.p2[direction],
                              sprite->unk_04);
                anim->unk_94 = direction;
            }
        }
        if (dir_sprite_flag[direction] != 0) {
            sprite->unk_14 |= 1;
        } else {
            sprite->unk_14 &= 0xFFFE;
        }
        advance_sprite_animation_and_textures(sprite);
        return 1;
    }

    if (entity->flags1C & 0x400) {
        action_flags = entity->unk_46;
        if (action_flags & 0x8000) {
            if (!(action_flags & 0x4000)) {
                action_type = action_flags & 0x3FFF;
                if (((u32)(action_type - 5) < 3U) || (action_type == 0xC)) {
                    entity->unk_46 = action_flags & 0x7FFF;
                }
            }
        }
    }

    if (!(sprite->unk_14 & 0x8000)) {
        if (anim->unk_98 & 0x400) {
            direction = ((g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            if (uses_direct_actor_sprite_frames(entity) != 0) {
                select_record_entry_and_value(sprite, sprite->unk_2C.p[direction],
                              sprite->unk_04);
            } else {
                select_indirect_table_entry(sprite, sprite->unk_2C.p2[direction],
                              sprite->unk_04);
            }
            anim->unk_98 &= 0xFBFF;
        }
    } else {
        anim->unk_98 |= 0x400;
    }

    if ((entity->flags1C & 0x2000) ||
        (entity->flags14 & 0x4000)) {
        if ((u32)(anim->unk_9A.as_u8 - 0x13) >= 2U) {
            if (entity->unk_6D == 0) {
                if (pending_marked_actor_count == 0) {
                    if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
                        return 0;
                    }
                } else {
                    active_entity = g_dungeon_status.unk_0C;
                    if (active_entity != entity) {
                        if ((((s32)g_dungeon_status.unk_10) == 0) && (active_entity == 0) &&
                            (g_dungeon_status.unk_08 == 0) &&
                            !(g_dungeon_status.flags & 0x2008) &&
                            (entity->unk_43 == 0xFD)) {
                            g_dungeon_status.unk_0C = entity;
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
                    entity->unk_71 = 0;
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
