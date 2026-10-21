#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"
#include "slus/data.h"



typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
    s32 f30;
    s32 f34;
    s32 f38;
    s32 f3c;
    s32 f40;
    s32 f44;
    s8 f48;
    u8 f49;
    u8 f4a;
    s8 f4b;
    s8 f4c;
    s8 f4d[3];
} S_80085FA8;

extern s32 read_next_byte_and_finish(S_80085FA8 *a0);
extern void handle_sequence_meta_event(S_80085FA8 *a0, s32 a1);
extern s32 audio_dispatch_midi_event(S_80085FA8 *a0, s32 a1, s32 a2, s32 a3);

/* Read and dispatch the next event, reusing the previous status when needed. */
s32 dispatch_sequence_event(S_80085FA8 *stream)
{
    s16 status;
    u8 first_data;
    s32 second_data;
    s32 data_count;
    s32 input_byte;
    u8 event_byte;
    u32 status_group;
    s32 subcommand;

    second_data = 0;
    input_byte = read_next_byte_and_finish(stream);
    event_byte = input_byte;
    if (!(input_byte & 0x80)) {
        status = stream->f4a;
        stream->f49 = 1;
    } else {
        if (event_byte != 0xFF) {
            stream->f4a = input_byte;
        }
        status = input_byte;
        stream->f49 = 0;
    }
    status_group = (u32)status;
    status_group >>= 4;
    data_count = audio_event_data_counts[status_group & 0xF];
    if (data_count != 0) {
        if (stream->f49 != 0) {
            first_data = event_byte;
        } else {
            first_data = read_next_byte_and_finish(stream);
        }
        if (data_count == 2) {
            second_data = read_next_byte_and_finish(stream);
        }
        audio_dispatch_midi_event(stream, status & 0xFF, first_data, second_data & 0xFF);
        return 0;
    }
    if (event_byte != 0xF0) {
        if (event_byte == 0xFF) {
            subcommand = read_next_byte_and_finish(stream);
            handle_sequence_meta_event(stream, subcommand & 0xFF);
            return 0;
        }
    } else {
        skip_vlq_payload_until_f_7(stream);
        return 0;
    }
    func_80058E64(event_byte);
    return 0;
}
