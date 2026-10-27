#include "common.h"
#include "shared/game_work.h"

#include "common.h"

#include "engine/script.h"
#include "engine/message.h"


/* Returns whether the state flag is set or global flag bits 0x60 are clear. */
s32 check_state_or_global_flags(MessageVoiceState *state)
{
    GameWork *global = &g_game_work;

    return state->gate != 0 || (global->buttons & 0x60) == 0;
}
