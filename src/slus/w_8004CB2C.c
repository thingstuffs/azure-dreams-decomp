#include "common.h"

extern u8 D_80080A84[16];

typedef struct FrameNode {
    u16 duration;
    s16 tag;
    s32 value;
} FrameNode;

typedef struct FrameState {
    s32 countdown;
    s32 *output;
    FrameNode *node;
} FrameState;

s32 func_8004CB2C(FrameState *state)
{
    s32 status = -1;
    s32 countdown;
    FrameNode *node;
    FrameNode *tail_node;
    s32 duration;
    s32 divisor;

    if (state->output != 0) {
        countdown = state->countdown--;
        if (countdown <= 0) {
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

            tail_node = state->node;
            ASM_KEEP(tail_node);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            divisor = D_80080A84[0];
            duration = tail_node->duration;
            state->countdown = duration / divisor;
        }
    }
    return status;
}
