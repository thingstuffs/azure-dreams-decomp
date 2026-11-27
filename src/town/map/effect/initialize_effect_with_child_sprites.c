#include "common.h"
#include "slus.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "town/map/effect.h"
#include "town/scene.h"
#include "town/data.h"
#include "town/map.h"
#include "town/map/state.h"
#include "town/map/state_callbacks_api.h"




extern u8 map_particle_child_update_address[];





/* Initializes a randomly oriented effect and its child sprites at the supplied position. */
void initialize_effect_with_child_sprites(TownObjectRecord *parent, ObjectPosition *position, struct SpriteFrameState *sprite_unused)
{
    void *part_callback;
    GameWork *work;
    ObjectNodeHeader *node;
    ObjectPosition *obj;
    u8 *entity;
    void *sprite_callback;
    void *sprite_texture;
    s32 brightness;
    s32 initial_angle;
    s32 angle_sector;
    s32 sector_multiple;
    u8 *active_flag;
    s32 scale;
    s32 angle_offset;
    s32 depth;
    s32 palette_blue;
    s32 position_y;
    s32 sprite_angle;
    s32 offset_y;
    s32 palette_red;
    s32 palette_green;
    s32 angle_random;
    s32 variation_random;
    s32 angle;
    s32 blue;
    s32 quadrant;
    s32 part_index;
    void **part_params;
    SpriteFrameState *sprite;
    ObjectNodeHeader **child_list;

    NODE_HEADER(parent)->update_callback = spin_object_until_outside_bounds;
    angle_random = rand();
    parent->unk_66 = angle_random % 0x1000;
    variation_random = rand();
    initial_angle = parent->unk_66;
    parent->effect_radius = (variation_random % 9) + 12;
    if (initial_angle < 0) {
        initial_angle += 511;
    }
    angle_sector = initial_angle >> 9;
    sector_multiple = angle_sector;
    sector_multiple /= 4;
    sector_multiple <<= 2;
    quadrant = angle_sector - sector_multiple;

    part_index = 0;
    part_callback = update_angle_driven_offset;
    work = &g_game_work;
    part_params = map_particle_part_parameters;
    do {
        node = allocate_list_node(0x136, &NODE_HEADER(parent)->next);
        if (node != 0) {
            node->update_callback = part_callback;
            register_node(node, draw_linked_lit_meshes);
            active_flag = parent->spawn_active;
            entity = NODE_BODY(node);
            (*(void * *)(entity + 0x9C)) = parent;
            (*(s16 *)(entity + 0x66)) = 0;
            (*(s8 *)(entity + 0x97)) = part_index;
            (*(u8 **)(entity + 0x98)) = active_flag;
            sprite = node->sprite;
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            sprite->offset_x = 0xAAA;
            sprite->color.c.r = work->view.tint.parts.tint_r;
            sprite->color.c.g = work->view.tint.parts.tint_g;
            blue = work->view.tint.parts.tint_b;
            sprite->source = part_index + 0x1A;
            sprite->color.c.b = blue;
            obj = node->position;
            obj->x.v = position->x.v;
            obj->y.v = position->y.v;
            angle = (s8)quadrant;
            if ((*(s8 *)(entity + 0x97)) == angle) {
                angle = ((TownObjectRecord *)((*(void * *)(entity + 0x9C))))->unk_66;
                obj->z.v = -((rsin(((angle % 0x200) << 16) >> 15) >> 4) * 0x1E00);
                (*(s16 *)(entity + 0x66)) = 0x1E;
            } else {
                obj->z.v = 0;
            }
            init_scene_node_mode_3(entity, obj, *part_params);
        }
        part_index++;
        part_params++;
    } while (part_index < 4);

    part_index = 0;
    sprite_callback = spin_object_until_flag_clears;
    sprite_texture = map_particle_first_sprite_entries;
    brightness = 0x80;
    do {
        node = allocate_list_node(0x36, &NODE_HEADER(parent)->next);
        if (node != 0) {
            node->update_callback = sprite_callback;
            register_node(node, draw_linked_sprites_clipped);
            active_flag = parent->spawn_active;
            entity = NODE_BODY(node);
            (*(void * *)(entity + 0x9C)) = parent;
            (*(s8 *)(entity + 0x97)) = part_index;
            (*(u8 **)(entity + 0x98)) = active_flag;
            sprite = node->sprite;
            sprite->source = sprite_texture;
            sprite->color.c.b = brightness;
            sprite->color.c.g = brightness;
            sprite->color.c.r = brightness;
            sprite->angle_x = 0x370;
            sprite->angle_y = 0;
            sprite_angle = ((u16)parent->unk_66);
            scale = 0x1000;
            sprite->scale_y = scale;
            sprite->scale_x = scale;
            angle_offset = part_index << 10;
            sprite_angle += angle_offset;
            sprite->angle_z = sprite_angle;
            obj = node->position;
            depth = position->x.v;
            obj->x.v = depth;
            offset_y = position->y.v;
            depth = 0xFF2C0000;
            obj->z.v = depth;
            depth = 0x200000;
            offset_y += depth;
            obj->y.v = offset_y;
        }
        part_index++;
    } while (part_index < 4);

    child_list = &NODE_HEADER(parent)->next;
    node = allocate_list_node(0x36, child_list);
    if (node != 0) {
        node->update_callback = spin_object_until_flag_clears;
        register_node(node, draw_linked_sprites_clipped);
        active_flag = parent->spawn_active;
        entity = NODE_BODY(node);
        (*(void * *)(entity + 0x9C)) = parent;
        (*(u8 **)(entity + 0x98)) = active_flag;
        sprite = node->sprite;
        sprite->source = map_particle_second_sprite_entries;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->angle_x = 0x370;
        sprite->angle_y = 0;
        sprite_angle = ((u16)parent->unk_66);
        scale = 0x1000;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
        sprite->angle_z = sprite_angle;
        obj = node->position;
        depth = position->x.v;
        obj->x.v = depth;
        offset_y = position->y.v;
        depth = 0xFF2C0000;
        obj->z.v = depth;
        depth = 0x200000;
        offset_y += depth;
        obj->y.v = offset_y;
    }

    node = allocate_list_node(0x136, child_list);
    if (node != 0) {
        node->update_callback = map_particle_child_update_address;
        register_node(node, draw_linked_lit_meshes);
        active_flag = parent->spawn_active;
        entity = NODE_BODY(node);
        (*(void * *)(entity + 0x9C)) = parent;
        (*(u8 **)(entity + 0x98)) = active_flag;
        sprite = node->sprite;
        sprite->scale_x = 0x1000;
        sprite->scale_y = 0x1000;
        sprite->offset_x = 0x1000;
        sprite->angle_z = ((u16)parent->unk_66);
        palette_red = g_game_work.view.tint.parts.tint_r;
        sprite->color.c.r = palette_red;
        palette_green = g_game_work.view.tint.parts.tint_g;
        sprite->color.c.g = palette_green;
        palette_blue = g_game_work.view.tint.parts.tint_b;
        sprite->color.c.b = palette_blue;
        obj = node->position;
        sprite->source = 0x19;
        obj->x.v = position->x.v;
        position_y = position->y.v;
        obj->z.v = 0;
        obj->y.v = position_y;
    }
}
