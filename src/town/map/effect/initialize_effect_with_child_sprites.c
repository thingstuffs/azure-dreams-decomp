#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 rsin(s32);
extern s32 rand(void);
extern void configure_the_set_mode_n_3(void *, void *, void *);

extern u8 clipped_sprite_renderer_address[];
extern u8 lit_mesh_renderer_address[];
extern u8 map_particle_owner_update_address[];
extern u8 D_800B9D64[];
extern u8 town_initialize_effect_with_child_sprites_address[];
extern u8 map_particle_child_update_address[];
extern void *map_particle_part_parameters[];
extern u8 map_particle_first_sprite_entries[];
extern u8 map_particle_second_sprite_entries[];

typedef struct S_800BA00C_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BA00C_0_pre;   /* the 0x10 bytes before arg0 in initialize_effect_with_child_sprites, addressed as arg0[-1] */

typedef struct S_800BA00C_0 {
    u8 pad_00[0x66];
    union { s16 s; u16 u; } unk_66;   /* accessed as both */
    u8 pad_68[0x2F];
    s8 unk_97;
    s32 unk_98;
} S_800BA00C_0;   /* arg0 in initialize_effect_with_child_sprites */

typedef struct S_800BA00C_1 {
    s32 unk_00;
    s32 unk_04;
    union { u8 * p; s32 i; } unk_08;   /* accessed as both */
    u8 * unk_0C;
    void * unk_10;
} S_800BA00C_1;   /* obj in initialize_effect_with_child_sprites */


typedef struct S_800BA00C_5 {
    u8 pad_00[0x66];
    s16 unk_66;
} S_800BA00C_5;   /* (*(void * *)((u8 *)entity + 0x9C)) in initialize_effect_with_child_sprites */

/* Initializes a randomly oriented effect and its child sprites at the supplied position. */
void initialize_effect_with_child_sprites(void *parent, ObjectPosition *position)
{
    void *part_callback;
    GameWork *work;
    u8 *obj;
    u8 *entity;
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
    SpriteFrameState *sprite;
    void *parent_obj;

    ((S_800BA00C_0_pre *)parent)[-1].unk_00 = map_particle_owner_update_address;
    angle_random = rand();
    ((S_800BA00C_0 *)parent)->unk_66.s = angle_random % 0x1000;
    variation_random = rand();
    initial_angle = ((S_800BA00C_0 *)parent)->unk_66.s;
    ((S_800BA00C_0 *)parent)->unk_97 = (variation_random % 9) + 12;
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
        obj = allocate_list_node(0x136, (u8 *)parent - 0x20);
        if (obj != 0) {
            ((S_800BA00C_1 *)obj)->unk_10 = part_callback;
            register_node(obj, lit_mesh_renderer_address);
            parent_value = ((S_800BA00C_0 *)parent)->unk_98;
            entity = obj + 0x20;
            (*(void * *)((u8 *)entity + 0x9C)) = parent;
            (*(s16 *)((u8 *)entity + 0x66)) = 0;
            (*(s8 *)((u8 *)entity + 0x97)) = part_index;
            (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
            sprite = ((S_800BA00C_1 *)obj)->unk_0C;
            sprite->scale_x = 0x1000;
            sprite->scale_y = 0x1000;
            sprite->offset_x = 0xAAA;
            sprite->color.c.r = work->view.tint.parts.tint_r;
            sprite->color.c.g = work->view.tint.parts.tint_g;
            blue = work->view.tint.parts.tint_b;
            sprite->source = part_index + 0x1A;
            sprite->color.c.b = blue;
            obj = ((S_800BA00C_1 *)obj)->unk_08.p;
            ((S_800BA00C_1 *)obj)->unk_00 = position->x.v;
            ((S_800BA00C_1 *)obj)->unk_04 = position->y.v;
            angle = (s8)quadrant;
            if ((*(s8 *)((u8 *)entity + 0x97)) == angle) {
                angle = ((S_800BA00C_5 *)((*(void * *)((u8 *)entity + 0x9C))))->unk_66;
                ((S_800BA00C_1 *)obj)->unk_08.i = -((rsin(((angle % 0x200) << 16) >> 15) >> 4) * 0x1E00);
                (*(s16 *)((u8 *)entity + 0x66)) = 0x1E;
            } else {
                ((S_800BA00C_1 *)obj)->unk_08.i = 0;
            }
            configure_the_set_mode_n_3(entity, obj, *part_params);
        }
        part_index++;
        part_params++;
    } while (part_index < 4);

    part_index = 0;
    sprite_callback = town_initialize_effect_with_child_sprites_address;
    sprite_texture = map_particle_first_sprite_entries;
    brightness = 0x80;
    do {
        obj = allocate_list_node(0x36, (u8 *)parent - 0x20);
        if (obj != 0) {
            ((S_800BA00C_1 *)obj)->unk_10 = sprite_callback;
            register_node(obj, clipped_sprite_renderer_address);
            parent_value = ((S_800BA00C_0 *)parent)->unk_98;
            entity = obj + 0x20;
            (*(void * *)((u8 *)entity + 0x9C)) = parent;
            (*(s8 *)((u8 *)entity + 0x97)) = part_index;
            (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
            sprite = ((S_800BA00C_1 *)obj)->unk_0C;
            sprite->source = sprite_texture;
            sprite->color.c.b = brightness;
            sprite->color.c.g = brightness;
            sprite->color.c.r = brightness;
            sprite->angle_x = 0x370;
            sprite->angle_y = 0;
            sprite_angle = ((S_800BA00C_0 *)parent)->unk_66.u;
            scale = 0x1000;
            sprite->scale_y = scale;
            sprite->scale_x = scale;
            angle_offset = part_index << 10;
            sprite_angle += angle_offset;
            sprite->angle_z = sprite_angle;
            obj = ((S_800BA00C_1 *)obj)->unk_08.p;
            depth = position->x.v;
            ((S_800BA00C_1 *)obj)->unk_00 = depth;
            offset_y = position->y.v;
            depth = 0xFF2C0000;
            ((S_800BA00C_1 *)obj)->unk_08.i = depth;
            depth = 0x200000;
            offset_y += depth;
            ((S_800BA00C_1 *)obj)->unk_04 = offset_y;
        }
        part_index++;
    } while (part_index < 4);

    parent_obj = (u8 *)parent - 0x20;
    obj = allocate_list_node(0x36, parent_obj);
    if (obj != 0) {
        ((S_800BA00C_1 *)obj)->unk_10 = town_initialize_effect_with_child_sprites_address;
        register_node(obj, clipped_sprite_renderer_address);
        parent_value = ((S_800BA00C_0 *)parent)->unk_98;
        entity = obj + 0x20;
        (*(void * *)((u8 *)entity + 0x9C)) = parent;
        (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
        sprite = ((S_800BA00C_1 *)obj)->unk_0C;
        sprite->source = map_particle_second_sprite_entries;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->angle_x = 0x370;
        sprite->angle_y = 0;
        sprite_angle = ((S_800BA00C_0 *)parent)->unk_66.u;
        scale = 0x1000;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
        sprite->angle_z = sprite_angle;
        obj = ((S_800BA00C_1 *)obj)->unk_08.p;
        depth = position->x.v;
        ((S_800BA00C_1 *)obj)->unk_00 = depth;
        offset_y = position->y.v;
        depth = 0xFF2C0000;
        ((S_800BA00C_1 *)obj)->unk_08.i = depth;
        depth = 0x200000;
        offset_y += depth;
        ((S_800BA00C_1 *)obj)->unk_04 = offset_y;
    }

    obj = allocate_list_node(0x136, parent_obj);
    if (obj != 0) {
        ((S_800BA00C_1 *)obj)->unk_10 = map_particle_child_update_address;
        register_node(obj, lit_mesh_renderer_address);
        parent_value = ((S_800BA00C_0 *)parent)->unk_98;
        entity = obj + 0x20;
        (*(void * *)((u8 *)entity + 0x9C)) = parent;
        (*(s32 *)((u8 *)entity + 0x98)) = parent_value;
        sprite = ((S_800BA00C_1 *)obj)->unk_0C;
        sprite->scale_x = 0x1000;
        sprite->scale_y = 0x1000;
        sprite->offset_x = 0x1000;
        sprite->angle_z = ((S_800BA00C_0 *)parent)->unk_66.u;
        palette_red = g_game_work.view.tint.parts.tint_r;
        sprite->color.c.r = palette_red;
        palette_green = g_game_work.view.tint.parts.tint_g;
        sprite->color.c.g = palette_green;
        palette_blue = g_game_work.view.tint.parts.tint_b;
        sprite->color.c.b = palette_blue;
        obj = ((S_800BA00C_1 *)obj)->unk_08.p;
        sprite->source = 0x19;
        ((S_800BA00C_1 *)obj)->unk_00 = position->x.v;
        position_y = position->y.v;
        ((S_800BA00C_1 *)obj)->unk_08.i = 0;
        ((S_800BA00C_1 *)obj)->unk_04 = position_y;
    }
}
