#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"


#define U8_AT(p, off)  (*(u8 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))

extern s32 D_800C6AEC;

extern void register_node();
extern void unlink_node();
extern void advance_sprite_animation_and_textures();
extern void retire_tracked_effect_by_id();

/* Advances the effect through color fades and animation changes, then marks it complete. */
void update_timed_color_transition_effect(u8 *effect_state, s32 unused, u8 *render_data) {
    u8 *effect;

    switch (S16_AT(effect_state, 0x1E)) {
    case 0:
        U8_AT(render_data, 0xF)++;
        U8_AT(render_data, 0xC) += (0x80 - U8_AT(render_data, 0xC)) / U8_AT(render_data, 0xF);
        U8_AT(render_data, 0xD) += (0x80 - U8_AT(render_data, 0xD)) / U8_AT(render_data, 0xF);
        U8_AT(render_data, 0xE) += (0x80 - U8_AT(render_data, 0xE)) / U8_AT(render_data, 0xF);
        if (U8_AT(render_data, 0xF) < 8) {
            break;
        }
        U32_AT(render_data, 0xC) = 0x00808080;
        U16_AT(effect_state, 0x1E)++;
        break;

    case 1:
        U8_AT(render_data, 0xF)--;
        if (U8_AT(render_data, 0xF) != 0) {
            break;
        }
        effect = effect_state - 0x20;
        unlink_node(effect);
        U16_AT(render_data, 0x12) += 0x80;
        U16_AT(render_data, 0x14) &= 0xFFF3;
        register_node(effect, project_sprite_chain);
        U16_AT(effect_state, 0x1E)++;
        break;

    case 2:
        if (**(u8 **)(effect_state + 4) != 0x14) {
            break;
        }
        effect = effect_state - 0x20;
        unlink_node(effect);
        U16_AT(render_data, 0x12) -= 0x80;
        U16_AT(render_data, 0x14) |= 0xC;
        register_node(effect, &D_800C6AEC);
        U8_AT(render_data, 0xF) = 0;
        U16_AT(effect_state, 0x1E)++;
        break;

    case 3:
        if (U8_AT(render_data, 0xF) < 8) {
            U8_AT(render_data, 0xF)++;
            U8_AT(render_data, 0xC) = U8_AT(render_data, 0xD) =
                U8_AT(render_data, 0xE) += -U8_AT(render_data, 0xE) / U8_AT(render_data, 0xF);
        } else {
            U16_AT(effect_state, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            retire_tracked_effect_by_id(effect_state - 0x20);
        }
        break;
    }

    advance_sprite_animation_and_textures(render_data);
}
