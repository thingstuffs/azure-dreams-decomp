#ifndef ENGINE_MESSAGE_STATE_H
#define ENGINE_MESSAGE_STATE_H
/* Prototypes of the functions defined in src/engine/message/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80038464_0;
struct S_80038570_0;
struct S_800385D0_0;
struct S_80038630_0;

/* wait_for_message_flag.c */
void wait_for_message_flag(struct S_80038464_0 *object);

/* wait_for_message_confirm_flag.c */
void wait_for_message_confirm_flag(struct S_80038570_0 *state);

/* wait_for_message_ready_flag.c */
void wait_for_message_ready_flag(struct S_80038630_0 *state);

/* wait_for_message_input_flag.c */
void wait_for_message_input_flag(struct S_800385D0_0 *state);

#endif
