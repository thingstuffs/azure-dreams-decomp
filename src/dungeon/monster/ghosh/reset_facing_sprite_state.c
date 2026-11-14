#include "common.h"
#include "dungeon/monster/ghosh.h"

typedef struct { u8 pad[0x96]; s16 timer; u8 pad98[3]; u8 next; } Work;
/* Clears the next pointer and timer in the work data following D_80174CDC. */
void reset_facing_sprite_state(void) { Work *work = NODE_BODY(D_80174CDC); work->next = 0; work->timer = 0; }
