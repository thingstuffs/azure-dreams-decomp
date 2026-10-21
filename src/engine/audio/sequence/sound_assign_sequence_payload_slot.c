#include "common.h"
#include "engine/audio.h"
#include "engine/audio/sequence.h"

/* Reports the low-byte event code and forwards an index for events 0x11, 0x12, 0x14 and 0x18. */
void assign_sound_payload_and_release_channel(s32 event)
{
    s32 event_code = event & 0xFF;
    s32 event_index;

    sound_assign_sequence_payload_slot(event_code);

    switch (event_code) {
    case 0x11:
        event_index = 0;
        break;
    case 0x12:
        event_index = 1;
        break;
    case 0x14:
        event_index = 2;
        break;
    case 0x18:
        event_index = 3;
        break;
    default:
        return;
    }

    release_sound_channel_and_mark_pending(event_index);
}
