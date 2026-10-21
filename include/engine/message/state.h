#ifndef ENGINE_MESSAGE_STATE_H
#define ENGINE_MESSAGE_STATE_H
/* Prototypes of the functions defined in src/engine/message/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80038464_0;
struct S_80038570_0;
struct S_800385D0_0;
struct S_80038630_0;

/* clear_runtime_state_and_set_handler.c */
void clear_runtime_state_and_set_handler(struct S_80038464_0 *object);

/* clear_two_state_fields.c */
void clear_two_state_fields(struct S_80038570_0 *state);

/* clear_two_state_fields_and_set_handler.c */
void clear_two_state_fields_and_set_handler(struct S_80038630_0 *state);

/* clear_two_state_fields_b.c */
void clear_two_state_fields_b(struct S_800385D0_0 *state);

#endif
