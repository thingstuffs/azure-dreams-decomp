#include "town/scene/effect.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "engine/node.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "town/scene.h"

static __inline__ EffectNode *effect_node(EffectState *state) {
    EffectPointer view;
    view.state = state;
    return view.node - 1;
}

extern u8 clipped_sprite_renderer_address[];
extern u8 lit_mesh_renderer_address[];
extern u8 map_particle_owner_update_address[];
extern u8 D_800B9D64[];
extern u8 town_child_sprite_callback_address[];
extern u8 map_particle_child_update_address[];
extern void *map_particle_part_parameters[];
extern u8 map_particle_first_sprite_entries[];
extern u8 map_particle_second_sprite_entries[];

void initialize_effect_with_sprite_set_nine(EffectState *parent, ObjectPosition *position, SpriteFrameState *unused_sprite)
{
    void *part_callback;
    GameWork *work;
    EffectPointer obj;
    EffectPointer entity;
    void *sprite_callback;
    void *sprite_texture;
    s32 brightness;
    s32 initial_angle;
    s32 angle_sector;
    s32 sector_multiple;
    s32 parent_value;
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
    EffectRender *sprite;
    EffectNode *parent_obj;
    s8 angle_byte;

    effect_node(parent)->callback = map_particle_owner_update_address;
    angle_random = rand();
    parent->angle.s = angle_random % 0x1000;
    variation_random = rand();
    initial_angle = parent->angle.s;
    parent->style = (variation_random % 9) + 12;
    if (initial_angle < 0) {
        initial_angle += 511;
    }
    angle_sector = initial_angle >> 9;
    sector_multiple = angle_sector;
    sector_multiple /= 4;
    sector_multiple <<= 2;
    quadrant = angle_sector - sector_multiple;

    part_index = 0;
    part_callback = D_800B9D64;
    work = &g_game_work;
    part_params = map_particle_part_parameters;
    do {
        obj.node = allocate_list_node(0x136, effect_node(parent));
        if (obj.node != 0) {
            obj.node->callback = part_callback;
            register_node(obj.node, lit_mesh_renderer_address);
            parent_value = parent->context;
            entity.node = obj.node + 1;
            entity.state->parent = parent;
            entity.state->angle.s = 0;
            entity.state->style = part_index;
            entity.state->context = parent_value;
            sprite = obj.node->render;
            sprite->state.scale_x = 0x1000;
            sprite->state.scale_y = 0x1000;
            sprite->state.offset_x = 0xAAA;
            sprite->state.color.c.r = work->view.tint.parts.tint_r;
            sprite->state.color.c.g = work->view.tint.parts.tint_g;
            blue = work->view.tint.parts.tint_b;
            sprite->source.source.id = part_index + 0xA;
            sprite->state.color.c.b = blue;
            obj.position = obj.node->position;
            obj.position->x.v = position->x.v;
            obj.position->y.v = position->y.v;
            angle_byte = quadrant;
            angle = angle_byte;
            if (entity.state->style == angle) {
                angle = entity.state->parent->angle.s;
                obj.position->z.v = -((rsin(((angle % 0x200) << 16) >> 15) >> 4) * 0x1E00);
                entity.state->angle.s = 0x1E;
            } else {
                obj.position->z.v = 0;
            }
            configure_the_set_mode_n_3(entity.state, obj.position, *part_params);
        }
        part_index++;
        part_params++;
    } while (part_index < 4);

    part_index = 0;
    sprite_callback = town_child_sprite_callback_address;
    sprite_texture = map_particle_first_sprite_entries;
    brightness = 0x80;
    do {
        obj.node = allocate_list_node(0x36, effect_node(parent));
        if (obj.node != 0) {
            obj.node->callback = sprite_callback;
            register_node(obj.node, clipped_sprite_renderer_address);
            parent_value = parent->context;
            entity.node = obj.node + 1;
            entity.state->parent = parent;
            entity.state->style = part_index;
            entity.state->context = parent_value;
            sprite = obj.node->render;
            sprite->source.source.pointer = sprite_texture;
            sprite->state.color.c.b = brightness;
            sprite->state.color.c.g = brightness;
            sprite->state.color.c.r = brightness;
            sprite->state.angle_x = 0x370;
            sprite->state.angle_y = 0;
            sprite_angle = parent->angle.u;
            scale = 0x1000;
            sprite->state.scale_y = scale;
            sprite->state.scale_x = scale;
            angle_offset = part_index << 10;
            sprite_angle += angle_offset;
            sprite->state.angle_z = sprite_angle;
            obj.position = obj.node->position;
            depth = position->x.v;
            obj.position->x.v = depth;
            offset_y = position->y.v;
            depth = 0xFF2C0000;
            obj.position->z.v = depth;
            depth = 0x200000;
            offset_y += depth;
            obj.position->y.v = offset_y;
        }
        part_index++;
    } while (part_index < 4);

    parent_obj = effect_node(parent);
    obj.node = allocate_list_node(0x36, parent_obj);
    if (obj.node != 0) {
        obj.node->callback = town_child_sprite_callback_address;
        register_node(obj.node, clipped_sprite_renderer_address);
        parent_value = parent->context;
        entity.node = obj.node + 1;
        entity.state->parent = parent;
        entity.state->context = parent_value;
        sprite = obj.node->render;
        sprite->source.source.pointer = map_particle_second_sprite_entries;
        sprite->state.color.c.b = 0x80;
        sprite->state.color.c.g = 0x80;
        sprite->state.color.c.r = 0x80;
        sprite->state.angle_x = 0x370;
        sprite->state.angle_y = 0;
        sprite_angle = parent->angle.u;
        scale = 0x1000;
        sprite->state.scale_y = scale;
        sprite->state.scale_x = scale;
        sprite->state.angle_z = sprite_angle;
        obj.position = obj.node->position;
        depth = position->x.v;
        obj.position->x.v = depth;
        offset_y = position->y.v;
        depth = 0xFF2C0000;
        obj.position->z.v = depth;
        depth = 0x200000;
        offset_y += depth;
        obj.position->y.v = offset_y;
    }

    obj.node = allocate_list_node(0x136, parent_obj);
    if (obj.node != 0) {
        obj.node->callback = map_particle_child_update_address;
        register_node(obj.node, lit_mesh_renderer_address);
        parent_value = parent->context;
        entity.node = obj.node + 1;
        entity.state->parent = parent;
        entity.state->context = parent_value;
        sprite = obj.node->render;
        sprite->state.scale_x = 0x1000;
        sprite->state.scale_y = 0x1000;
        sprite->state.offset_x = 0x1000;
        sprite->state.angle_z = parent->angle.u;
        palette_red = g_game_work.view.tint.parts.tint_r;
        sprite->state.color.c.r = palette_red;
        palette_green = g_game_work.view.tint.parts.tint_g;
        sprite->state.color.c.g = palette_green;
        palette_blue = g_game_work.view.tint.parts.tint_b;
        sprite->state.color.c.b = palette_blue;
        obj.position = obj.node->position;
        sprite->source.source.id = 9;
        obj.position->x.v = position->x.v;
        position_y = position->y.v;
        obj.position->z.v = 0;
        obj.position->y.v = position_y;
    }
}
