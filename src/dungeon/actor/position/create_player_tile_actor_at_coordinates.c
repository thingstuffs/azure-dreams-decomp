#include "shared/actor_status_ids.h"
#include "dungeon/actor/motion.h"
#include "shared/actor_status_flags.h"

struct ObjectNodeHeader;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

#define FLD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 D_800E0334[];

extern u8 actor_motion_resume_address;

typedef struct {
    s32 f0;
    s32 f4;
    s16 f8;
    s8 fA;
} D80089430_t;
extern D80089430_t D_80089430;
/* Eleven copied bytes; the source and destination are word aligned. */
typedef struct { u8 bytes[11]; } ResultCopy __attribute__((aligned(4)));

extern void *allocate_list_node(s32 a0, void *a1);
extern u8 find_active_rect_containing_point(u8 a0, u8 a1);
extern void set_record_integer_tile_center(void *a0, u8 a1, u8 a2);
extern s16 sample_terrain_surface_height(u16 a0, u16 a1, s16 a2);
extern void select_record_entry_and_value(void *a0, s32 a1, s32 a2);
extern void clear_entry_flag_and_link_owner(struct ObjectNodeHeader *a0);
extern void create_source_linked_fading_effect(struct ObjectNodeHeader *, s16);
extern void register_node(void *a0, void *a1);
extern void set_or_clear_actor_status_slot(void *a0, s32 a1, s32 a2);

/* Creates an entity at the given tile and height and initializes its sprite state. */
void *create_player_tile_actor_at_coordinates(u16 tile_x, u16 tile_z, u16 height) {
    u8 saved_tile_x = tile_x;
    u8 saved_tile_z = tile_z;
    ObjectNodeHeader *entity;
    void *state;
    SpriteFrameState *sprite;
    GameWork *camera;
    void *state_tail;
    s32 direction_entry;
    D80089430_t *result_base;
    u8 * result_word4;
    s32 tint;
    register s32 tint_arg;

    state = 0;
    entity = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (entity != 0) {
        state = (u8 *)entity + 0x20;
        entity->update_callback = update_actor_facing_and_lifecycle;
        FLD(state, s8, 0x13) = 0x2f;
        state_tail = entity->position;
        FLD(state_tail, u16, 0xA) = height;
        sprite = entity->sprite;
        sprite->tile_x = saved_tile_x;
        sprite->tile_y = saved_tile_z;
        sprite->room_index = find_active_rect_containing_point(FLD(sprite, u8, 0x24), sprite->tile_y);
        set_record_integer_tile_center(state_tail, FLD(sprite, u8, 0x24), sprite->tile_y);
        FLD(state, s16, 0x88) =
            sample_terrain_surface_height(FLD(state_tail, u16, 2), FLD(state_tail, u16, 6), (s16)(FLD(state_tail, u16, 0xA) - 0x20));
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.word = 0x2c808080;
        FLD(state, void *, 0xA4) = D_800E0334;
        sprite->frameTable = D_800E0334;
        camera = &g_game_work;
        direction_entry = ((camera->view.camera_rotation.parts.viewAngle + FLD(state, s16, 0x2A) + 0x100) >> 7) & 0x1C;
        direction_entry += (s32)FLD(state, void *, 0xA4);
        select_record_entry_and_value(sprite, FLD((void *)direction_entry, s32, 0), 0);
        clear_entry_flag_and_link_owner(entity);
        *(ResultCopy *)((u8 *)entity + 0x54) = *(ResultCopy *)&D_80089430;
        FLD(state, s32, 0x1C) |= ACTOR_REFRESH_GROUND;
        FLD(state, s8, 0x71) = 0;
        state_tail = state;
        {
            if (dir_sprite_flag[((camera->view.camera_rotation.parts.viewAngle + FLD(state, s16, 0x2A) + 0x100) >> 9) & 7] != 0) {
                sprite->flags |= 1;
            } else {
                sprite->flags &= 0xFFFE;
            }
        }
        tint = 0x404040;
        result_word4 = (u8 *)(entity);
        tint_arg = 0;
        FLD(state_tail, u8, 0x9A) = 0xFF;
        FLD(state_tail, s8, 0x9C) = -1;
        FLD(state_tail, void *, 0x8C) = &actor_motion_resume_address;
        FLD(state_tail, s16, 0xB6) = 0x10;
        FLD(state, s32, 0x1C) |= 0x40000;
        FLD(state_tail, s16, 0x92) = -0x20;
        FLD(state_tail, s32, 0xAC) = tint;
        create_source_linked_fading_effect((void *)result_word4, tint_arg);
        register_node(entity, project_sprite_chain);
        set_or_clear_actor_status_slot(state, STATUS_NO_TILE_OCCUPANCY, 0);
    }
    return state;
}
