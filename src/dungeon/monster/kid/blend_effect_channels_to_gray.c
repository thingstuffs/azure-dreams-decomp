#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "slus.h"

extern void unlink_node(void *node);

extern s32 D_80175220;

/* Processes input, then blends three state channels toward 0x80 and marks completion. */
void blend_effect_channels_to_gray(u8 *task, void *context, SpriteFrameState *input)
{
    s16 frames_left;
    GameWork *fade_state = &g_game_work;

    if (task[0x9A] == 0) {
        D_80175220 = *(s32 *)&input->source;
        advance_sprite_animation_and_textures(input);
        if (input->flags & 0xE000) {
            unlink_node(task - 0x20);
            *(s16 *)(task + 0x96) = 0x10;
            task[0x9A]++;
            return;
        }
    } else {
        fade_state->view.tint.parts.tint_r = (u8)(fade_state->view.tint.parts.tint_r +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_r) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_g = (u8)(fade_state->view.tint.parts.tint_g +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_g) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_b = (u8)(fade_state->view.tint.parts.tint_b +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_b) / *(s16 *)(task + 0x96)));

        frames_left = *(u16 *)(task + 0x96) - 1;
        *(s16 *)(task + 0x96) = frames_left;
        if (frames_left <= 0) {
            *(u16 *)(task - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
