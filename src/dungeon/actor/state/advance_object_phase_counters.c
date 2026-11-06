#include "common.h"
#include "sdk/libgte.h"
#include "dungeon/actor/phase_body.h"

/* Advance the object counters and wrapped phase according to its state. */
void advance_object_phase_counters(ObjectPhaseBody *obj)
{
    s16 state;
    s16 phase;
    s32 offset;
    s32 tick;

    state = obj->state;
    switch (state) {
    case 0:
        offset = obj->offset;
        tick = obj->ticks;
        offset += 2;
        tick++;
        obj->offset = offset;
        obj->ticks = tick;
        return;
    case 1:
        offset = obj->offset;
        tick = obj->ticks;
        offset += 4;
        tick++;
        obj->offset = offset;
        obj->ticks = tick;
        return;
    case 2:
        phase = obj->phase + 0x40;
        obj->phase = phase % 0x1C00;
        return;
    case 3:
        obj->offset += 8;
        phase = (rsin((s16)obj->ticks << 5) >> 1) + 0xC00;
        obj->ticks++;
        obj->phase = phase % 0x1C00;
        return;
    }
}
