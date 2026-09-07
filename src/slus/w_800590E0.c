#include "common.h"

/* S_800590E0: opaque MIDI/sequencer-stream state pointer passed straight
 * through to func_80058A04 (reads a variable-length-quantity count) and
 * func_800589B8 (reads/advances one byte from the stream); this function
 * never touches its fields directly. */
typedef struct S_800590E0 S_800590E0;

extern s32 func_80058A04(S_800590E0 *a0);
extern s32 func_800589B8(S_800590E0 *a0);

/* Reads a VLQ count via func_80058A04(a0), then pulls that many bytes from
 * the stream via func_800589B8(a0) one at a time, stopping early if a byte
 * equal to 0xF7 is encountered. Return value (if any) is unused by callers. */
void func_800590E0(S_800590E0 *a0)
{
    u32 i = 0;
    u32 count;
    s32 last;

    last = func_80058A04(a0);
    count = (u32)last;
    while (1) {
        i++;
        if ((func_800589B8(a0) & 0xFF) == 0xF7) break;
        if (!(i < count)) break;
    }
}
