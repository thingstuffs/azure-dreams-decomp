#include "common.h"

/* S_800590E0: opaque MIDI/sequencer-stream state pointer passed straight
 * through to func_80058A04 (reads a variable-length-quantity count) and
 * func_800589B8 (reads/advances one byte from the stream); this function
 * never touches its fields directly. */
typedef struct S_800590E0 S_800590E0;

extern s32 func_80058A04(S_800590E0 *a0);
extern s32 func_800589B8(S_800590E0 *a0);

/* Consumes at least one stream byte, stopping at the VLQ byte count or 0xF7. */
void func_800590E0(S_800590E0 *stream)
{
    u32 bytes_read = 0;
    u32 byte_count;
    s32 vlq_count;

    vlq_count = func_80058A04(stream);
    byte_count = (u32)vlq_count;
    while (1) {
        bytes_read++;
        if ((func_800589B8(stream) & 0xFF) == 0xF7) break;
        if (!(bytes_read < byte_count)) break;
    }
}
