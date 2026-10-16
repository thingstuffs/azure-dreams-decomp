#include "common.h"

extern s16 pollDriverCompletionEvent(s32 a0);

/* Checks SPU transfer completion, waiting when requested. */
s16 soundCheckOrWaitForSpuTransfer(s16 wait_for_completion)
{
    if (!wait_for_completion)
        return pollDriverCompletionEvent(0);
    return pollDriverCompletionEvent(1);
}
