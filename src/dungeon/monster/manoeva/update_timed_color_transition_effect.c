#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "slus.h"

#define U8_AT(p, off)  (*(u8 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32_AT(p, off) (*(u32 *)((u8 *)(p) + (off)))

extern s32 actor_fade_draw_address;

s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern void unlink_node();
extern void retire_tracked_effect_by_id();

/* Advances the effect through color fades and animation changes, then marks it complete. */
void update_timed_color_transition_effect(u8 *effect_state, s32 unused, SpriteFrameState *render_data) {
    ObjectNodeHeader *effect;
    void *node_storage;

    switch (S16_AT(effect_state, 0x1E)) {
    case 0:
        render_data->color.c.code++;
        render_data->color.c.r += (0x80 - render_data->color.c.r) / render_data->color.c.code;
        render_data->color.c.g += (0x80 - render_data->color.c.g) / render_data->color.c.code;
        render_data->color.c.b += (0x80 - render_data->color.c.b) / render_data->color.c.code;
        if (render_data->color.c.code < 8) {
            break;
        }
        render_data->color.word = 0x00808080;
        U16_AT(effect_state, 0x1E)++;
        break;

    case 1:
        render_data->color.c.code--;
        if (render_data->color.c.code != 0) {
            break;
        }
        node_storage = effect_state - 0x20;
        effect = node_storage;
        unlink_node(effect);
        render_data->clut += 0x80;
        render_data->flags &= 0xFFF3;
        register_node(effect, project_sprite_chain);
        U16_AT(effect_state, 0x1E)++;
        break;

    case 2:
        if (**(u8 **)(effect_state + 4) != 0x14) {
            break;
        }
        node_storage = effect_state - 0x20;
        effect = node_storage;
        unlink_node(effect);
        render_data->clut -= 0x80;
        render_data->flags |= 0xC;
        register_node(effect, &actor_fade_draw_address);
        render_data->color.c.code = 0;
        U16_AT(effect_state, 0x1E)++;
        break;

    case 3:
        if (render_data->color.c.code < 8) {
            render_data->color.c.code++;
            render_data->color.c.r = render_data->color.c.g =
                render_data->color.c.b += -render_data->color.c.b / render_data->color.c.code;
        } else {
            U16_AT(effect_state, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            retire_tracked_effect_by_id(effect_state - 0x20);
        }
        break;
    }

    advance_sprite_animation_and_textures(render_data);
}
