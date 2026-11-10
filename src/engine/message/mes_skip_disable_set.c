#include "common.h"

#include "engine/message.h"
#include "slus/data.h"

/* mes_skip_disable_set: Sets the message skip disable flag. */
void mes_skip_disable_set(s8 skip_disabled) {
    message_skip_disabled[0] = skip_disabled;
}
