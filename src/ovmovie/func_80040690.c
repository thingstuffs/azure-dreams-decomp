#include "modules/ovmovie_game.h"

/* Polls for a result and switches buffers when the result is negative. */
s32 decode_next_movie_frame(void *buffer_state) {
    s32 result;
    s32 buffer_index;
    s32 polls_left;

    polls_left = 0x800000;
    while (1) {
        result = poll_movie_frame_and_update_dimensions(buffer_state);
        if (result != 0) {
            break;
        }
        if (--polls_left == 0) {
            return 0;
        }
    }
    if (result > 0) {
        return 0;
    }
    buffer_index = *((s32 *)buffer_state + 2) == 0;
    *((s32 *)buffer_state + 2) = buffer_index;
    func_80177E6C(result, *((void **)buffer_state + buffer_index));
    func_80063734(result);
    return 1;
}
