#include "common.h"
#include "shared/game_work.h"

#include "common.h"

typedef struct {
    char pad0[0x87];
    s8 field87;
} S_80039884_Arg;


/* Returns whether the state flag is set or global flag bits 0x60 are clear. */
s32 check_state_or_global_flags(S_80039884_Arg *state)
{
    s32 result = 0;
    GameWork *global = &g_game_work;

    if (state->field87 == 0) {
        if ((global->buttons & 0x60) != 0) {
            goto done;
        }
    }

    result = 1;
done:
    return result;
}
