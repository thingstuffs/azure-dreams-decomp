#include "common.h"

extern s32 scale_random_to_unsigned_halfword_limit(s32);
extern void initialize_object_entries(void *, s32, void *);
extern u8 D_800C7604[];
extern u8 D_800D5FC4[];

/* Clear two state values, initialize the actor, and set its handler and randomized counter. */
void initialize_mother_event_actor(void *actor, void *state, s32 init_param) {
    *(s32 *)((u8 *)state + 0x10) = 0;
    *(s32 *)((u8 *)state + 0xC) = 0;
    initialize_object_entries(actor, init_param, D_800D5FC4);
    *(void **)((u8 *)actor + 0x50) = D_800C7604;
    *(s16 *)((u8 *)actor + 0x6C) = (s16) (scale_random_to_unsigned_halfword_limit(0x3F) + 0x15);
}
