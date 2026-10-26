#include "shared/object_node.h"
#include "engine/graphics.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "sdk/libc.h"
#include "slus.h"

extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern u8 D_80025098[9];
extern u8 random_variant_sprite_entries[9];

typedef struct S_818C3A3C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C3A3C_0;

typedef struct S_818C3A3C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
} S_818C3A3C_1;

typedef struct S_818C3A3C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C3A3C_2;   /* arg0 in create_scaled_rotation_effect */

typedef struct S_818C3A3C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_4;   /* arg1 in create_scaled_rotation_effect */

typedef struct S_818C3A3C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C3A3C_5;

/* Creates an effect with randomized rotation, owner-dependent scale, and copied instance data. */
s32 create_scaled_rotation_effect(S_818C3A3C_2 *owner, S_818C3A3C_4 *initial_data) {
    s32 call_zero;
    void *handler;
    s32 scale;
    s32 random_value;
    s32 biased_random;
    SpriteFrameState *sprite;
    void *effect_state;
    ObjectNodeHeader *effect;
    S_818C3A3C_5 *effect_data;
    void *effect_name;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        handler = D_80025098;
        effect_state = (u8 *)effect + 0x20;
        effect_name = random_variant_sprite_entries;
        effect->update_callback = handler;
        ((S_818C3A3C_0 *)effect)->unk_20 = owner;
        ((S_818C3A3C_1 *)effect_state)->unk_10 = 0;
        call_zero = 0;
        *(u16 *)((u8 *)effect_state + 0x14) = owner->unk_14;

        sprite = effect->sprite;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->clut = 0x7DCF;
        sprite->flags |= 0xC;
        sprite->tpage_abr |= 0x20;
        sprite->flags |= 0x100;
        select_record_entry_and_value(sprite, effect_name, call_zero);

        biased_random = rand();
        random_value = biased_random;
        if (random_value < 0) {
            biased_random = random_value + 0xFFF;
        }
        sprite->angle_z = (random_value % 4096);

        scale = 0x1400 / ((S_818C3A3C_1 *)effect_state)->unk_14;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
        register_node(effect, draw_linked_sprites_clipped);

        effect_data = effect->position;
        *effect_data = *(S_818C3A3C_5 *)initial_data;
        return (s32)effect;
    }
    return 0;
}
