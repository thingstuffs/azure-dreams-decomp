#include "common.h"

/* PsyQ 4.0 LIBSPU: pitch -> (note, fine) reverse of _spu_note2pitch.
 * Finds the MSB of ~pitch to get the octave, then walks the 48x32 pitch
 * table (built incrementally from the 0x103B semitone ratio) for the
 * 1/32-semitone slot that brackets `pitch`. */
u32 func_8005F90C(u16 centerNote, u16 centerFine, u16 pitch)
{
    u16 inv;
    s32 msb;
    s32 octave;
    s32 bitval;
    u32 scale;
    u32 base;
    u32 next;
    u32 step;
    u32 acc;
    u32 hi;
    u32 lo;
    u32 up;
    u32 sa;
    u32 sb;
    s32 o;
    s32 i;
    s32 index;
    s32 oi;
    s32 q;
    s32 r;
    s32 note;
    s32 fine;

    inv = (~(s32)pitch) & 0xFFFF;
    msb = 0;
    for (o = 15; o >= 0; o--) {
        if (((inv >> o) & 1) == 0) {
            msb = o;
            break;
        }
    }
    octave = msb - 12;
    bitval = 1 << msb;
    scale = 0x1000;
    for (o = 0; o < 0x30; o++) {
        base = (u32)bitval * scale;
        scale *= 0x103B;
        scale >>= 12;
        next = (u32)bitval * scale;
        step = (next - base) >> 5;
        i = 0;
        oi = o * 32;
        acc = 0;
        hi = step;
        for (; i < 0x20; i++) {
            sa = base + acc;
            sb = base + hi;
            lo = sa >> 12;
            up = sb >> 12;
            if ((u32)pitch >= lo) {
                if ((u32)pitch < up) {
                    index = oi + i;
                    goto done;
                }
            }
            hi += step;
            acc += step;
        }
    }
    index = 1536;
done:
    q = index / 128;
    r = index - q * 128;
    note = (s32)centerNote + q + octave * 12;
    fine = (s32)centerFine + r;
    return (u32)((note << 8) | fine);
}
