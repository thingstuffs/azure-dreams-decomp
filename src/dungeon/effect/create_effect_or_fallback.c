#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_800B8228_3 {
    u8 pad_00[0xB0];
    s16 unk_B0;
    s16 unk_B2;
} S_800B8228_3;

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

extern void register_node(void *, void *);
extern void play_sound_if_enabled(s32);
extern s32 get_item_category_value(void *, s32);
extern void place_item_at_valid_floor_position(s32, s32, s32, void *, void *);
extern void create_tracked_effect(void *, s32, s32, s32);

extern u8 item_effect_descriptor[9];
extern u8 D_800B80D8[];

/* Creates and initializes an effect, or invokes its fallback if allocation fails. */
void *create_effect_or_fallback(u32 x, u32 y, s32 z, void *effect_data) {
    SpriteFrameState *appearance;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    S_800B8228_3 *grid_position;

    effect = allocate_flagged_object_node(0x12);
    if (effect != NULL) {
        register_node(effect, project_sprite_chain);
        effect->unk_10 = D_800B80D8;
        position = effect->position;
        position->x.w.i = x;
        position->y.w.i = y;
        position->z.w.i = z;
        *((s16 *)&position->velocity_z + 1) = -0x12;
        appearance = effect->sprite;
        appearance->color.word = 0x808080;
        appearance->scale_y = 0xC90;
        appearance->scale_x = 0xC90;
        appearance->source = get_item_category_value(effect_data, appearance->color.word);
        grid_position = (u8 *)effect + 0x20;
        grid_position->unk_B0 = x >> 6;
        grid_position->unk_B2 = y >> 6;
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
