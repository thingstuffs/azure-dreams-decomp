#include "dungeon/player.h"
#include "common.h"

/* Initializes object state 0x2E with the supplied word and halfword values. */
void begin_parameterized_actor_action(void *object, void *unused_1, void *unused_2, void *word_value, s32 halfword_value) {
    *((s8 *)object + 0x9A) = 0x2E;
    *((s8 *)object + 0x9B) = 0;
    *(s32 *)((s8 *)object + 0x8C) = 0;
    *(void **)((s8 *)object + 0xCC) = word_value;
    *(s16 *)((s8 *)object + 0x10E) = (s16) halfword_value;
}
