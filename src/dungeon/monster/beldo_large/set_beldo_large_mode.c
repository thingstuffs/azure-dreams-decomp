#include "common.h"

typedef struct { u8 pad[0x96]; s16 timer; u8 pad98[2]; u8 mode, next; } Work;
extern u8 *beldo_script_node;
/* Stores the Beldo script data mode and clears its next pointer and timer. */
void set_beldo_large_mode(s32 value) {
    Work *state = (Work *)(beldo_script_node + 0x20);
    state->mode = value; state->next = 0; state->timer = 0;
}
