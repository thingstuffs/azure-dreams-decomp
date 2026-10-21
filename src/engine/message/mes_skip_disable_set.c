#include "common.h"

#include "common.h"
#include "engine/message.h"

extern s8 message_skip_disabled[];

/* mes_skip_disable_set: Sets the message skip disable flag. */
void mes_skip_disable_set(s8 skip_disabled) {
    message_skip_disabled[0] = skip_disabled;
}
