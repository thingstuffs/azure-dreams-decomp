#include "shared/object_node.h"
#include "dungeon/effect/motion.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "dungeon/effect.h"
#include "engine/node.h"
#include "dungeon/system.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

s32 get_item_category_value(void *item_data);
extern void place_item_at_valid_floor_position(s32, s32, s32, void *, void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void create_tracked_effect(void *, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

extern u8 item_effect_descriptor[9];

/* Creates and initializes an effect, or invokes its fallback if allocation fails. */
void *create_item_drop_effect(u32 x, u32 y, s32 z, void *effect_data) {
    SpriteFrameState *appearance;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    ItemDropEffectBody *grid_position;

    effect = allocate_flagged_object_node(0x12);
    if (effect != NULL) {
        register_node(effect, project_sprite_chain);
        effect->update_callback = animate_item_drop_effect;
        position = effect->position;
        position->x.w.i = x;
        position->y.w.i = y;
        position->z.w.i = z;
        *((s16 *)&position->velocity_z + 1) = -0x12;
        appearance = effect->sprite;
        appearance->color.word = 0x808080;
        appearance->scale_y = 0xC90;
        appearance->scale_x = 0xC90;
        appearance->source = get_item_category_value(effect_data);
        grid_position = NODE_BODY(effect);
        grid_position->grid_x = x >> 6;
        grid_position->grid_y = y >> 6;
        *(PackedWord *)((u8 *)effect + 0xB8) = *(PackedWord *)effect_data;
        create_tracked_effect(effect, 0, 0, 0);
        play_sound_if_enabled(0x51C);
    } else {
        place_item_at_valid_floor_position((s32)(x << 0xA) >> 0x10,
                      (s32)(y << 0xA) >> 0x10,
                      (s32)(z << 0x10) >> 0x10,
                      item_effect_descriptor, effect_data);
    }
    return effect;
}
