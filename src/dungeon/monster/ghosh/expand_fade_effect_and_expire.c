#include "common.h"
#include "dungeon/monster/ghosh.h"

typedef struct { u8 pad[0x96]; s16 timer; u8 pad98[3]; u8 next; } Work;
/* Clears the next pointer and timer in the work data following D_80174CDC. */
void expand_fade_effect_and_expire(void) { Work *work = (Work *)(D_80174CDC + 1); work->next = 0; work->timer = 0; }
