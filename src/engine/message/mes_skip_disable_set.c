#include "common.h"

#include "engine/message.h"
#include "engine/message/data.h"

/* mes_skip_disable_set: Sets the message skip disable flag. */
void mes_skip_disable_set(s8 skip_disabled) {
    runtime_script_state.window.skip_disabled = skip_disabled;
}
