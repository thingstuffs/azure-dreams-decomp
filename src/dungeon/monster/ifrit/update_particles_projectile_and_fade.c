#include "common.h"
#include "dungeon/monster/ifrit.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_80083460.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor.h"

typedef struct S_801733BC_0 {
    u8 pad_00[0xC];
    union { u32 u32; u8 u8; } unk_0C;   /* accessed as both */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x2];
    u32 unk_28;
} S_801733BC_0;   /* arg2 in update_particles_projectile_and_fade */

typedef struct S_801733BC_1 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xC];
    union { u16 u; s16 s; } unk_A8;   /* accessed as both */
} S_801733BC_1;   /* arg0 in update_particles_projectile_and_fade */

typedef struct S_801733BC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_801733BC_2;   /* object in update_particles_projectile_and_fade */

   /* arg1 in update_particles_projectile_and_fade */

typedef struct S_801733BC_4 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xC];
    u32 unk_A4;
} S_801733BC_4;   /* effectPart in update_particles_projectile_and_fade */

typedef struct S_801733BC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    u32 unk_08;
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
    u16 unk_18;
} S_801733BC_8;   /* projectilePart in update_particles_projectile_and_fade */

   /* ((S_801733BC_2 *)object)->unk_08 in update_particles_projectile_and_fade */

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern Rect D_80170874;

extern u8 D_801741A4[];

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s16, s16);
extern s32 rand(void);
extern void unlink_entity_node(void *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void distribute_experience_and_report_gains(void *);
extern void detach_record_and_update_slot_state(void *);
extern void play_sound_if_enabled(s32);
extern void draw_transformed_sprite_with_clip_rect(void *, Rect *, Point *, s32, s32);

/* Updates an entity's particles, projectile, and fade-out sequence before removing it. */
/* Animates Ifrit's defeat with particles and a projectile, fades the sprite, awards experience, and
 * removes the actor. */
void update_particles_projectile_and_fade(void *effect_state, MovingPosition *position, void *render_part, SpriteFrameState *entity)
{
    Rect rect;
    Point center;
    s32 particles_left;
    ObjectNodeHeader *spawned_object;
    void *particle_callback;
    void *particle_state;
    SpriteFrameState *particle_render;
    void *projectile_state;

    DungeonGlobalStatus *effect_list;
    s32 random_offset;
    u32 frames_left;
    u16 projectile_y;
    u16 projectile_z;

    rect = D_80170874;

    if (!(((S_801733BC_0 *)render_part)->unk_14 & 0x8000) &&
        ((S_801733BC_1 *)effect_state)->unk_9B == 1) {
        particles_left = 3;
        particle_callback = tick_object_motion_and_expire;
        ((S_801733BC_1 *)effect_state)->unk_A8.u += 0x12;
        do {
            spawned_object = allocate_list_node(0x112, &scene_object_list_anchor.next);
            if (spawned_object != 0) {
                register_node(spawned_object, project_sprite_chain);
                spawned_object->update_callback = particle_callback;

                random_offset = rand();
                ((MovingPosition *)(spawned_object->position))->x =
                    position->x + (random_offset & 0x3F) - 0x20;

                random_offset = rand();
                ((MovingPosition *)(spawned_object->position))->y =
                    position->y + (random_offset & 0x3F) - 0x20;

                random_offset = rand();
                {
                    u32 owner;
                    u16 source_z;
                    s32 draw_command;
                    s32 draw_zero;
                    u32 particle_color;
                    s32 draw_param;

                    random_offset %= ((S_801733BC_1 *)effect_state)->unk_A8.s + 0x60;
                    particle_render = 0x00040404;
                    particle_color = 0x00500000;
                    source_z = position->z;
                    particle_color |= 0x5050;
                    ((MovingPosition *)(spawned_object->position))->z =
                        source_z - random_offset - 0x10;

                    particle_state = (u8 *)spawned_object + 0x20;
                    ((S_801733BC_4 *)particle_state)->unk_A4 = particle_render;
                    ((S_801733BC_4 *)particle_state)->unk_96 = 6;

                    particle_render = spawned_object->sprite;
                    owner = ((S_801733BC_0 *)render_part)->unk_28;
                    draw_command = 0x2E;
                    particle_render->animation_resource = owner;
                    particle_render->scale_y = 0x1000;
                    particle_render->scale_x = 0x1000;
                    draw_zero = 0;
                    particle_render->flags = ((S_801733BC_0 *)render_part)->unk_14;
                    draw_param = ((S_801733BC_0 *)render_part)->unk_12;
                    particle_render->tpage_abr = 0x20;
                    particle_render->color.word = particle_color;
                    particle_render->flags |= 0xC;
                    particle_render->clut = draw_param;
                    select_sprite_entry(particle_render, draw_command, draw_zero);
                }
            }
            particles_left--;
        } while (particles_left >= 0);
    }

    switch (((S_801733BC_1 *)effect_state)->unk_9B) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            break;
        }
        if (*(u32 *)&entity->flags & 0x4000) {
            if (!(*(u32 *)&entity->flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        ((S_801733BC_1 *)effect_state)->unk_9B++;
                        /* fallthrough */
    case 1:
        if (!(((S_801733BC_0 *)render_part)->unk_14 & 0xE000)) {
            break;
        }
        ((S_801733BC_1 *)effect_state)->unk_A8.u = 0;
        {
            void *center_object;
            Rect *rect_ptr;
            Point *center_ptr;
            s16 center_y;

            center_object = effect_state;
            rect_ptr = &rect;
            center_ptr = &center;
            center.x = rect.x + ((s16)rect.w >> 1);
            center_y = rect.y + ((s16)rect.h >> 1);
            center.y = center_y;
            draw_transformed_sprite_with_clip_rect(center_object, rect_ptr, center_ptr, 1, 0);
        }

        *(u32 *)&entity->scale_x |= 0x10000000;
        ((S_801733BC_0 *)render_part)->unk_10 = 0x60;
        ((S_801733BC_0 *)render_part)->unk_0C.u32 = 0x00C0C0C0;
        ((S_801733BC_0 *)render_part)->unk_14 |= 0xC;
        ((S_801733BC_0 *)render_part)->unk_12 -= 0x80;
        ((S_801733BC_1 *)effect_state)->unk_9B++;
        play_sound_if_enabled(0x806);

        spawned_object = allocate_list_node(0x12, &scene_object_list_anchor.next);
        if (spawned_object == 0) {
            break;
        }
        register_node(spawned_object, render_linked_items_as_textured_strips);
        frames_left = (u32)D_801741A4;
        spawned_object->update_callback = (void *)frames_left;
        ((S_801733BC_2 *)spawned_object)->unk_20 = position->x;
        projectile_y = position->y;
        projectile_state = (u8 *)spawned_object + 0x20;
        ((S_801733BC_8 *)projectile_state)->unk_02 = projectile_y;
        projectile_z = position->z;
        ((S_801733BC_8 *)projectile_state)->unk_10 = 0xFFFC0000;
        ((S_801733BC_8 *)projectile_state)->unk_0C = 0;
        ((S_801733BC_8 *)projectile_state)->unk_14 = 0xFFFE8000;
        ((S_801733BC_8 *)projectile_state)->unk_18 = 0x14;
        ((S_801733BC_8 *)projectile_state)->unk_08 = 0;
        ((S_801733BC_8 *)projectile_state)->unk_04 = projectile_z;
        break;

    case 2:
        *(u32 *)&entity->scale_x |= 0x10000000;
        ((S_801733BC_0 *)render_part)->unk_0C.u32 += 0xFFEFEFF0;
        if (((S_801733BC_0 *)render_part)->unk_0C.u8 < 0x11) {
            ((S_801733BC_1 *)effect_state)->unk_96 = 10;
            ((S_801733BC_1 *)effect_state)->unk_9B++;
        }
        break;

    case 3:
        frames_left = ((S_801733BC_1 *)effect_state)->unk_96 - 1;
        ((S_801733BC_1 *)effect_state)->unk_96 = frames_left;
        if ((s16)frames_left > 0) {
            break;
        }
        effect_list = &g_dungeon_status;
        if (effect_list->pending_display_owner == (u8 *)entity - 0x20) {
            (*(u32 *)&effect_list->pending_display_owner) &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        update_map_cell_flags_with_item_limit(((S_801733BC_0 *)render_part)->unk_24, ((S_801733BC_0 *)render_part)->unk_25,
            (*(u32 *)&entity->scale_x & 0x2000) ? 0x300 : 0x3000);
        unlink_entity_node(entity);
        (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
