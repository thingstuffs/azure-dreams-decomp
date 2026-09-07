#include "common.h"

/* PsyQ 4.0 SDK helper: converts a pitch and fractional note offset.
 *
 * The 8($sp) store/load pair retail emits is NOT an address-taken local: it is a
 * genuine reload spill.  Reload spills the hard register that services the
 * `sra <reg>,hi,8` reload for the /1536 smulsi3_highpart and then reuses it as
 * the reload register for the spilled product pseudo -- retail's $t1.  Writing
 * the product as an ordinary local (`cur`) lets reload produce that shape by
 * itself; an address-taken array instead pins the value in an allocated register
 * and leaves a 4-word carrier residual.
 *
 * `pad[2]` is the 8 bytes of frame that sit BELOW reload's spill slot in retail
 * (retail frame = 16, slot at 8($sp)); without it the frame is 8 and the slot
 * lands at 0($sp).
 *
 * Receipt: work/mainexe_audit_20260818/solve_C_libspu/_bonus_func_8005F740/
 */
u32 func_8005F740(s32 pitch, u32 note)
{
    s32 pad[2];
    s32 count;
    s32 previous;
    s32 cur;
    u32 steps;
    u32 scale;

    scale = 0x103B;
    previous = (u32)pitch << 12;
    count = 0;
    steps = note >> 5;
    note &= 0x1F;
    cur = pitch * scale;
    if (steps != 0) {
        do {
            previous = pitch * scale;
            scale *= 0x103B;
            scale >>= 12;
            count++;
            cur = pitch * scale;
        } while (count < (s32)steps);
    }
    return (u32)(previous + (((u32)(cur - previous) >> 5) * note)) >> 12;
}
