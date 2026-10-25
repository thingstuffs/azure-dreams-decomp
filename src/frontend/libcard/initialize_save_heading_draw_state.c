#include "frontend/libcard.h"

/* Connect each draw node to its command copy and the shared heading state. */
void initialize_save_heading_draw_state(CardHeadingDrawState *work, s32 count)
{
    s32 i;

    for (i = 0; i < count; i++) {
        void *command;
        s32 first_word = D_8002E5D8.word0;
        work->links[i] = &work->nodes[i];
        work->commands[i].word0 = first_word;
        work->commands[i].word1 = D_8002E5D8.word1;
        work->commands[i].word2 = D_8002E5D8.word2;
        work->commands[i].word3 = D_8002E5D8.word3;
        command = &work->commands[i];
        work->nodes[i].command = command;
        work->nodes[i].common = &work->common;
    }
    work->common.word0 = D_8002E5E8.word0;
    work->common.word1 = D_8002E5E8.word1;
    work->common.word2 = D_8002E5E8.word2;
}
