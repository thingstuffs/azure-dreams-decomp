#include "common.h"
#include "records/Rec_func_800AB030_arg0.h"
#include "town/person/lookup_motion.h"
#include "town/person.h"

typedef struct {
    s32 pad[3];
} StateHandler;

extern StateHandler D_800AB4A8;
extern StateHandler person_approach_state_address;

/* Updates coordinates and selects the state handler based on the threshold and timer. */
void update_person_coordinates(void *state, ObjectPosition *coords) {
    u16 timer;

    if (*(s16 *)((s8 *)state + 0x90) < 100) {
        *(StateHandler **)((s8 *)state + 0x50) = &person_approach_state_address;
    }
    coords->x.unsigned_parts.integer = *(u16 *)((s8 *)coords + 0xE);
    coords->y.unsigned_parts.integer = *(u16 *)((s8 *)coords + 0x12);
    coords->z.w.i = *(u16 *)((s8 *)coords + 0x16) + advance_person_lookup_value(state);
    timer = *(u16 *)((s8 *)state + 0x6C) - 1;
    *(u16 *)((s8 *)state + 0x6C) = timer;
    if ((s16)timer < 0) {
        *(StateHandler **)((s8 *)state + 0x50) = &D_800AB4A8;
        *(u16 *)((s8 *)state + 0x6C) = 10;
    }
}
