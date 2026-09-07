#include "common.h"

extern int abs(int);

/* PsyQ 4.0 LIBSPU: _spu_note2pitch (tail is _spu_2pitch inlined). */
u32 func_8005F7D0(u16 centerNote, u16 centerFine, u16 note, u16 fine)
{
    s32 centre;
    /* 8 bytes of frame below reload's spill slot: retail's product carrier
     * spills to 8($sp) in a 16-byte frame (see MATCH receipt). */
    s32 pad[2];
    s32 delta;
    s32 mag;
    s32 oct;
    s32 rem;
    s32 raw;
    s32 n;
    s32 count;
    s32 previous;
    s32 cur;
    u32 steps;
    u32 frac;
    u32 scale;
    u32 result;

    centre = ((s32)centerNote << 7) + centerFine;
    delta = (((s32)note << 7) + fine) - centre;
    mag = delta;
    if (delta < 0) {
        mag = -delta;
    }
    oct = mag / 1536;
    rem = mag % 1536;
    if (delta >= 0) {
        raw = 0x1000 << oct;
    } else {
        if (rem != 0) {
            oct++;
            rem = 1536 - rem;
        }
        raw = 0x1000 >> oct;
    }
    delta = (s32)((u32)raw & 0xFFFF);
    scale = 0x103B;
    previous = (s32)((u32)delta << 12);
    n = abs(rem);
    steps = (u32)n >> 5;
    frac = (u32)n & 0x1F;
    cur = delta * scale;
    count = 0;
    if (steps != 0) {
        do {
            previous = delta * scale;
            scale *= 0x103B;
            scale >>= 12;
            count++;
            cur = delta * scale;
        } while (count < (s32)steps);
    }
    result = (u32)(previous + (((u32)(cur - previous) >> 5) * frac)) >> 12;
    if (result >= 0x4000) {
        result = 0x3FFF;
    }
    return result & 0xFFFF;
}
