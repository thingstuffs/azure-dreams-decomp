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

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BA930_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BA930_0_pre;   /* the 0x10 bytes before arg0 in initialize_effect_with_random_angle, addressed as arg0[-1] */

   /* particlePrim in initialize_effect_with_random_angle */

typedef struct Primitive {
    u8 pad0[8];
    void *image;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 angle;
    s16 scaleX;
    s16 scaleY;
    s16 scaleZ;
} Primitive;

typedef struct Core {
    u8 pad0[0x66];
    u16 angle;
    u8 pad68[0x2F];
    s8 index;
    s32 value;
    struct Core *parent;
} Core;

typedef struct Object {
    u8 pad0[8];
    IntVector3 *position;
    Primitive *primitive;
    void *update;
} Object;

extern void *allocate_list_node();
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern u8 map_particle_owner_update_address[];
extern u8 town_child_sprite_callback_address[];
extern u8 map_particle_child_update_address[];
extern u8 map_random_particle_update_address[];
extern void *map_particle_part_parameters[];
extern u8 map_particle_first_sprite_entries[];
extern u8 map_particle_second_sprite_entries[];

/* Initialize an effect with a random angle and spawn its particle and textured children. */
void initialize_effect_with_random_angle(Core *effect, IntVector3 *origin) {
    s32 random_angle;
    s32 biased_angle;
    s32 child_index;
    s32 child_value;
    s32 particle_y;
    s32 sprite_y;
    s32 overlay_y;
    s32 center_y;
    u8 particle_blue;
    ObjectNodeHeader *child_obj;
    Core *child_core;
    void *parent_obj;
    SpriteFrameState *particle_prim;
    SpriteFrameState *texture_prim;
    IntVector3 *child_pos;

    ((S_800BA930_0_pre *)effect)[-1].unk_00 = map_particle_owner_update_address;
    random_angle = rand();
    biased_angle = random_angle;
    if (random_angle < 0) {
        biased_angle = random_angle + 0xFFF;
    }

    child_index = 0;
    effect->angle = random_angle - ((biased_angle >> 12) << 12);
    effect->index = 0;
    do {
        child_obj = allocate_list_node(0x136, (u8 *)effect - 0x20);
        if (child_obj != NULL) {
            child_obj->update_callback = map_random_particle_update_address;
            register_node(child_obj, draw_linked_lit_meshes);
            child_value = effect->value;
            child_core = (Core *)((u8 *)child_obj + 0x20);
            child_core->parent = effect;
            child_core->angle = 0;
            child_core->index = child_index;
            child_core->value = child_value;
            particle_prim = child_obj->sprite;
            particle_prim->scale_x = 0x1000;
            particle_prim->scale_y = 0x1000;
            particle_prim->offset_x = 0xAAA;
            particle_prim->color.c.r = g_game_work.view.tint.parts.tint_r;
            particle_prim->color.c.g = g_game_work.view.tint.parts.tint_g;
            particle_blue = g_game_work.view.tint.parts.tint_b;
            particle_prim->source = child_index + 0x1A;
            particle_prim->color.c.b = particle_blue;
            child_pos = *(IntVector3 * *)&child_obj->position;
            child_pos->x = origin->x;
            particle_y = origin->y;
            child_pos->z = 0;
            child_pos->y = particle_y;
            configure_the_set_mode_n_3(child_core, child_pos, map_particle_part_parameters[child_index]);
        }
        child_index += 1;
    } while (child_index < 4);

    child_index = 0;
    do {
        child_obj = allocate_list_node(0x36, (u8 *)effect - 0x20);
        if (child_obj != NULL) {
            child_obj->update_callback = town_child_sprite_callback_address;
            register_node(child_obj, draw_linked_sprites_clipped);
            child_value = effect->value;
            child_core = (Core *)((u8 *)child_obj + 0x20);
            child_core->parent = effect;
            child_core->index = child_index;
            child_core->value = child_value;
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
            child_pos = *(IntVector3 * *)&child_obj->position;
            child_pos->x = origin->x;
            sprite_y = origin->y;
            child_pos->z = 0xFF2C0000;
            sprite_y += 0x200000;
            child_pos->y = sprite_y;
        }
        child_index += 1;
    } while (child_index < 4);

    parent_obj = (u8 *)effect - 0x20;
    child_obj = allocate_list_node(0x36, parent_obj);
    if (child_obj != NULL) {
        child_obj->update_callback = town_child_sprite_callback_address;
        register_node(child_obj, draw_linked_sprites_clipped);
        child_value = effect->value;
        child_core = (Core *)((u8 *)child_obj + 0x20);
        child_core->parent = effect;
        child_core->value = child_value;
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
        child_pos = *(IntVector3 * *)&child_obj->position;
        child_pos->x = origin->x;
        overlay_y = origin->y;
        child_pos->z = 0xFF2C0000;
        overlay_y += 0x200000;
        child_pos->y = overlay_y;
    }

    child_obj = allocate_list_node(0x136, parent_obj);
    if (child_obj != NULL) {
        child_obj->update_callback = map_particle_child_update_address;
        register_node(child_obj, draw_linked_lit_meshes);
        child_value = effect->value;
        child_core = (Core *)((u8 *)child_obj + 0x20);
        child_core->parent = effect;
        child_core->value = child_value;
        particle_prim = child_obj->sprite;
        particle_prim->scale_x = 0x1000;
        particle_prim->scale_y = 0x1000;
        particle_prim->offset_x = 0x1000;
        particle_prim->angle_z = effect->angle;
        particle_prim->color.c.r = g_game_work.view.tint.parts.tint_r;
        particle_prim->color.c.g = g_game_work.view.tint.parts.tint_g;
        particle_prim->color.c.b = g_game_work.view.tint.parts.tint_b;
        child_pos = *(IntVector3 * *)&child_obj->position;
        particle_prim->source = 0x19;
        child_pos->x = origin->x;
        center_y = origin->y;
        child_pos->z = 0;
        child_pos->y = center_y;
    }
}
