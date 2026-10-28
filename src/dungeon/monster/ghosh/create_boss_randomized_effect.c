#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "engine/node.h"

typedef struct S_80172F44_0 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x40];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_80172F44_0;   /* state in create_boss_randomized_effect */

typedef struct S_80172F44_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172F44_4;   /* arg0 in create_boss_randomized_effect */

extern s32 rand(void);
extern void select_record_entry_and_value(void *state, void *entries, short index);
extern void update_accelerating_growing_particle(void);

/* Creates a visual effect at an offset position with randomized state. */
/* Creates an offset dark-gray Ghosh particle with randomized velocity, scale 0x400, and the
 * growing-particle callback. */
void create_boss_randomized_effect(S_80172F44_4 *position, s32 x_offset, s32 y_offset, s32 z_offset)
{
    ObjectNodeHeader *object;
    ObjectPosition *transform;
    SpriteFrameState *display;
    S_80172F44_0 *state;
    s32 random_value;
    s32 z_fixed;
    u16 x_integer;

    object = allocate_flagged_object_node(0x212);
    if (object != 0) {
        state = (S_80172F44_0 *)((u8 *)object + 0x20);
        state->unk_16 = 0x1A;
        object->update_callback = update_accelerating_growing_particle;
        register_node(object, project_sprite_chain);

        display = object->sprite;
        display->tpage_abr = 0x40;
        display->depth_bias = 6;
        display->flags |= 0xC;

        transform = object->position;
        transform->x.v = position->unk_00;
        transform->y.v = position->unk_04;

        x_integer = *(u16 *)&transform->x.w.i;
        z_fixed = position->unk_08;
        transform->x.w.i = x_integer + x_offset;
        transform->z.v = z_fixed;
        *(u16 *)&transform->y.w.i += y_offset;
        *(u16 *)&transform->z.w.i += z_offset;

        random_value = rand();
        state->unk_58 = random_value - 0x8000;
        random_value = rand();
        state->unk_5C = random_value - 0x8000;
        random_value = rand();
        state->unk_60 = random_value - 0x40000;

        display = object->sprite;
        display->scale_y = 0x400;
        display->scale_x = 0x400;
        display->color.c.b = 0x16;
        display->color.c.g = 0x16;
        display->color.c.r = 0x16;
        display->clut = 0x7DCF;
        display->flags |= 0x100;
        select_record_entry_and_value(display, effect_sprite_sources, 0);
    }
}
