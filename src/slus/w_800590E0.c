#include "common.h"

/* S_800590E0: opaque MIDI/sequencer-stream state pointer passed straight
 * through to readBase128Vlq (reads a variable-length-quantity count) and
 * slusReadNextByteAndFinish (reads/advances one byte from the stream); this function
 * never touches its fields directly. */
typedef struct S_800590E0 S_800590E0;

extern s32 readBase128Vlq(S_800590E0 *a0);
extern s32 slusReadNextByteAndFinish(S_800590E0 *a0);

/* Consumes at least one stream byte, stopping at the VLQ byte count or 0xF7. */
void skipVlqPayloadUntilF7(S_800590E0 *stream)
{
    u32 bytes_read = 0;
    u32 byte_count;
    s32 vlq_count;

    vlq_count = readBase128Vlq(stream);
    byte_count = (u32)vlq_count;
    while (1) {
        bytes_read++;
        if ((slusReadNextByteAndFinish(stream) & 0xFF) == 0xF7)
            break;
        if (!(bytes_read < byte_count))
            break;
    }
}
