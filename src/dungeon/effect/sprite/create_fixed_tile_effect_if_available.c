#include "shared/object_node.h"
#include "engine/graphics.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

extern s32 test_resident_bit();
extern void file_load_com(void *packed_data);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s16 get_surface_height_at_coordinates();
 /* overlays/dungeon/first_pass_matched/func_80D403A8.c */
extern void update_pulsing_actor_color(void *state_data, s32 unused, void *actor_data);
extern M2C_UNK D_800F6F28;
extern M2C_UNK D_800F6F30;

/* Conditionally creates and initializes a type 0x12 object. */
void create_fixed_tile_effect_if_available(void) {
    ObjectPosition *graphics;
    ObjectNodeHeader *object;
    SpriteFrameState *animation;

    if (test_resident_bit(0xA2) == 0) {
        file_load_com(&D_800F6F28);
        object = allocate_flagged_object_node(0x12);
        if (object != NULL) {
            object->update_callback = &update_pulsing_actor_color;
            register_node(object, draw_linked_sprites_clipped);
            graphics = object->position;
            graphics->x.w.i = 0x820;
            graphics->y.w.i = 0x820;
            graphics->z.w.i = get_surface_height_at_coordinates(*(u16 *)&graphics->x.w.i, 0x820);
            animation = object->sprite;
            animation->scale_y = 0x1000;
            animation->scale_x = 0x1000;
            animation->source = &D_800F6F30;
            animation->tpage_abr = 0x20;
            animation->flags = 0xC;
            animation->depth_bias = 6;
        }
    }
}
