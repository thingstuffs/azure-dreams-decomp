#include "common.h"
#include "town/scene/list_setup.h"
#include "slus.h"
#include "engine/graphics.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_effect_views.h"
#include "shared/vector.h"
#include "sdk/libc.h"
#include "town/map/effect.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/map/state.h"
#include "town/map/state_callbacks_api.h"

#ifndef NULL
#define NULL 0
#endif


extern void *allocate_list_node();
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */



extern u8 map_particle_child_update_address[];


/* Initialize an effect with a random angle and spawn its particle and textured children. */
void initialize_effect_with_random_angle(MapParticleEffect *effect, ObjectPosition *origin, struct SpriteFrameState *sprite_unused) {
    s32 random_angle;
    s32 biased_angle;
    s32 child_index;
    u8 *active_flag;
    s32 particle_y;
    s32 sprite_y;
    s32 overlay_y;
    s32 center_y;
    u8 particle_blue;
    ObjectNodeHeader *child_obj;
    MapParticleEffect *child_core;
    ObjectNodeHeader **child_list;
    SpriteFrameState *particle_prim;
    SpriteFrameState *texture_prim;
    ObjectPosition *child_pos;

    NODE_HEADER(effect)->update_callback = spin_object_until_outside_bounds;
    random_angle = rand();
    biased_angle = random_angle;
    if (random_angle < 0) {
        biased_angle = random_angle + 0xFFF;
    }

    child_index = 0;
    effect->angle = random_angle - ((biased_angle >> 12) << 12);
    effect->index = 0;
    do {
        child_obj = allocate_list_node(0x136, &NODE_HEADER(effect)->next);
        if (child_obj != NULL) {
            child_obj->update_callback = retire_record_when_status_clear;
            register_node(child_obj, draw_linked_lit_meshes);
            active_flag = effect->active_flag;
            child_core = NODE_BODY(child_obj);
            child_core->parent = effect;
            child_core->angle = 0;
            child_core->index = child_index;
            child_core->active_flag = active_flag;
            particle_prim = child_obj->sprite;
            particle_prim->scale_x = 0x1000;
            particle_prim->scale_y = 0x1000;
            particle_prim->offset_x = 0xAAA;
            particle_prim->color.c.r = g_game_work.view.tint.parts.tint_r;
            particle_prim->color.c.g = g_game_work.view.tint.parts.tint_g;
            particle_blue = g_game_work.view.tint.parts.tint_b;
            particle_prim->source = child_index + 0x1A;
            particle_prim->color.c.b = particle_blue;
            child_pos = child_obj->position;
            child_pos->x.v = origin->x.v;
            particle_y = origin->y.v;
            child_pos->z.v = 0;
            child_pos->y.v = particle_y;
            init_scene_node_mode_3(child_core, child_pos, map_particle_part_parameters[child_index]);
        }
        child_index += 1;
    } while (child_index < 4);

    child_index = 0;
    do {
        child_obj = allocate_list_node(0x36, &NODE_HEADER(effect)->next);
        if (child_obj != NULL) {
            child_obj->update_callback = spin_object_until_flag_clears;
            register_node(child_obj, draw_linked_sprites_clipped);
            active_flag = effect->active_flag;
            child_core = NODE_BODY(child_obj);
            child_core->parent = effect;
            child_core->index = child_index;
            child_core->active_flag = active_flag;
            texture_prim = child_obj->sprite;
            texture_prim->source = map_particle_first_sprite_entries;
            texture_prim->color.c.b = 0x80;
            texture_prim->color.c.g = 0x80;
            texture_prim->color.c.r = 0x80;
            texture_prim->angle_x = 0x370;
            texture_prim->angle_y = 0;
            texture_prim->angle_z = effect->angle + (child_index << 10);
            texture_prim->scale_y = 0x1000;
            texture_prim->scale_x = 0x1000;
            child_pos = child_obj->position;
            child_pos->x.v = origin->x.v;
            sprite_y = origin->y.v;
            child_pos->z.v = 0xFF2C0000;
            sprite_y += 0x200000;
            child_pos->y.v = sprite_y;
        }
        child_index += 1;
    } while (child_index < 4);

    child_list = &NODE_HEADER(effect)->next;
    child_obj = allocate_list_node(0x36, child_list);
    if (child_obj != NULL) {
        child_obj->update_callback = spin_object_until_flag_clears;
        register_node(child_obj, draw_linked_sprites_clipped);
        active_flag = effect->active_flag;
        child_core = NODE_BODY(child_obj);
        child_core->parent = effect;
        child_core->active_flag = active_flag;
        texture_prim = child_obj->sprite;
        texture_prim->source = map_particle_second_sprite_entries;
        texture_prim->color.c.b = 0x80;
        texture_prim->color.c.g = 0x80;
        texture_prim->color.c.r = 0x80;
        texture_prim->angle_x = 0x370;
        texture_prim->angle_y = 0;
        texture_prim->angle_z = effect->angle;
        texture_prim->scale_y = 0x1000;
        texture_prim->scale_x = 0x1000;
        child_pos = child_obj->position;
        child_pos->x.v = origin->x.v;
        overlay_y = origin->y.v;
        child_pos->z.v = 0xFF2C0000;
        overlay_y += 0x200000;
        child_pos->y.v = overlay_y;
    }

    child_obj = allocate_list_node(0x136, child_list);
    if (child_obj != NULL) {
        child_obj->update_callback = map_particle_child_update_address;
        register_node(child_obj, draw_linked_lit_meshes);
        active_flag = effect->active_flag;
        child_core = NODE_BODY(child_obj);
        child_core->parent = effect;
        child_core->active_flag = active_flag;
        particle_prim = child_obj->sprite;
        particle_prim->scale_x = 0x1000;
        particle_prim->scale_y = 0x1000;
        particle_prim->offset_x = 0x1000;
        particle_prim->angle_z = effect->angle;
        particle_prim->color.c.r = g_game_work.view.tint.parts.tint_r;
        particle_prim->color.c.g = g_game_work.view.tint.parts.tint_g;
        particle_prim->color.c.b = g_game_work.view.tint.parts.tint_b;
        child_pos = child_obj->position;
        particle_prim->source = 0x19;
        child_pos->x.v = origin->x.v;
        center_y = origin->y.v;
        child_pos->z.v = 0;
        child_pos->y.v = center_y;
    }
}
