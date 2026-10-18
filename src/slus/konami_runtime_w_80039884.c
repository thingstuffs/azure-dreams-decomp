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
    GameWork *global = &g_game_work;

    return state->field87 != 0 || (global->buttons & 0x60) == 0;
}
