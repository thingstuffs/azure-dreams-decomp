#include "common.h"
#include "engine/graphics.h"
#include "shared/timed_stream.h"

extern u8 animation_tick_scale;


/* Advances the frame sequence and updates its output when the countdown expires. */
s32 advance_timed_tagged_stream(FrameState *state)
{
    s32 status = -1;
    s32 ticks_left;
    FrameNode *node;
    FrameNode *timed_node;
    s32 duration;
    s32 duration_scale;

    if (state->output != 0) {
        ticks_left = state->countdown--;
        if (ticks_left <= 0) {
            node = state->node;
            if (node->tag == 2) {
                state->node = node + 1;
                status = 2;
            } else if (node->tag == 1) {
                state->node = (FrameNode *)node->value;
                status = 1;
            } else if (node->tag == 0) {
                state->node = (FrameNode *)node->value;
                status = 0;
            }

            node = state->node;
            if (node->tag == 2) {
                *state->output = node->value;
            } else {
                status = -2;
            }

            timed_node = state->node;
            duration_scale = animation_tick_scale;
            duration = timed_node->duration;
            state->countdown = duration / duration_scale;
        }
    }
    return status;
}
