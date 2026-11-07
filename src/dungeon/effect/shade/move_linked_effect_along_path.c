#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect.h"
#include "dungeon/effect/shade.h"

typedef struct S_80024CD4_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80024CD4_0;   /* arg0 in move_linked_effect_along_path */


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s16 value;
    u8 pad[8];
} Flag;

extern Counter staged_fade_count;
extern Flag path_effect_release_flag;

/* Advance the effect state, update its ramp and color, and apply its transform. */
void move_linked_effect_along_path(void *effect, ObjectPosition *transform, SpriteFrameState *visual) {
    s16 state;
    u16 rising_value;
    u16 ramp_or_red;
    u16 delay_left;
    u16 final_ramp;
    u16 decaying_value;
    void *call_transform;
    s32 base_value;

    staged_fade_count.value++;
    state = (s16)((S_80024CD4_0 *)effect)->unk_0A;
    switch (state) {
    case 0:
        ramp_or_red = (u16) visual->depth_bias + 0x80;
        visual->depth_bias = ramp_or_red;
        if ((s16) ramp_or_red < 0x101) {
            break;
        }
        visual->depth_bias = 0x100U;
        if (((S_80024CD4_0 *)effect)->unk_22 < 0x61) {
            call_transform = transform;
            base_value = ((S_80024CD4_0 *)effect)->unk_16;
            decaying_value = ((S_80024CD4_0 *)effect)->unk_18;
            decaying_value = (u16) (decaying_value - ((s32) (decaying_value << 0x10) >> 0x13));
            ((S_80024CD4_0 *)effect)->unk_18 = decaying_value;
            rising_value = ((S_80024CD4_0 *)effect)->unk_1C;
            rising_value += 0x80;
            ((S_80024CD4_0 *)effect)->unk_1C = rising_value;
            create_moving_fading_particle(call_transform, base_value,
                (s16)((S_80024CD4_0 *)effect)->unk_18, (s16) rising_value,
                effect - 0x20);
        }
        ((S_80024CD4_0 *)effect)->unk_0A++;
        if (((S_80024CD4_0 *)effect)->unk_22 == 0x6F) {
            path_effect_release_flag.value = 1;
        }
        break;
    case 1:
        if (path_effect_release_flag.value != 0) {
            visual->depth_bias = -0x100;
            ((S_80024CD4_0 *)effect)->unk_1A = 0x10U;
            ((S_80024CD4_0 *)effect)->unk_0A++;
        }
        break;
    case 2:
        delay_left = ((S_80024CD4_0 *)effect)->unk_1A - 1;
        ((S_80024CD4_0 *)effect)->unk_1A = delay_left;
        if ((delay_left << 0x10) > 0) {
            break;
        }
        ((S_80024CD4_0 *)effect)->unk_0A++;
    case 3:
        final_ramp = (u16) visual->depth_bias + 0x80;
        visual->depth_bias = final_ramp;
        if ((s16) final_ramp >= 0) {
            NODE_HEADER(effect)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    default:
        break;
    }
    visual->color.c.r = 0x20;
    visual->color.c.g = 0xE0;
    visual->color.c.b = 0x40;
    create_effect_object_groups(transform->x.w.i, transform->y.w.i, transform->z.w.i);
}
