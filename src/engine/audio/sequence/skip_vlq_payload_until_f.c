#include "common.h"
#include "engine/audio/sequence.h"

/* S_800590E0: opaque MIDI/sequencer-stream state pointer passed straight
 * through to read_base_128_vlq (reads a variable-length-quantity count) and
 * read_next_byte_and_finish (reads/advances one byte from the stream); this function
 * never touches its fields directly. */
typedef struct S_800590E0 S_800590E0;

extern s32 read_next_byte_and_finish(S_800590E0 *a0);

/* Consumes at least one stream byte, stopping at the VLQ byte count or 0xF7. */
void skip_vlq_payload_until_f_7(S_800590E0 *stream)
{
    u32 bytes_read = 0;
    u32 byte_count;
    s32 vlq_count;

    vlq_count = read_base_128_vlq(stream);
    byte_count = (u32)vlq_count;
    while (1) {
        bytes_read++;
        if ((read_next_byte_and_finish(stream) & 0xFF) == 0xF7)
            break;
        if (!(bytes_read < byte_count))
            break;
    }
}
