#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

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
extern s32 audio_sequence_format[];
extern S_80085FA8 audio_sequence_tracks[];
extern u32 audio_sequence_timing_division[];
extern u32 audio_sequence_track_count[];

/* Handles sequence metadata events, updating tempo and marking track endings. */
void handle_sequence_meta_event(S_80085FA8 *track, s32 event_type)
{
    S_80085FA8 *tempo_track;
    s32 event_or_bpm;
    u32 track_tempo;
    u32 track_limit;
    u32 track_count;
    u32 bpm;
    u32 timing_value;
    u32 track_index;
    u32 scaled_tempo;

    event_or_bpm = event_type & 0xFF;
    switch (event_or_bpm) {
    case 0 ... 0xF:
        add_to_sequence_counter(track, read_base_128_vlq(track));
        return;
    case 0x2F:
        track->f2c = 1;
        read_next_byte_and_finish(track);
        return;
    case 0x51:
        if (audio_sequence_format[0] == 1) {
            track->f20 = read_big_endian_word(track) & 0xFFFFFF;
        } else {
            track->f20 = read_next_byte_and_finish(track) << 0x10;
            track->f20 = track->f20 | (read_next_byte_and_finish(track) << 8);
            track->f20 = track->f20 | read_next_byte_and_finish(track);
        }
        bpm = 0x03938700U / (u32) track->f20;
        track->f24 = bpm;
        track->f20 = bpm;
        event_or_bpm = track->f24;
        timing_value = ((u32) event_or_bpm * 100U) / 115U;
        track->f24 = timing_value;
        timing_value = timing_value < 0x100U;
        if (timing_value == 0) {
            track->f24 = 0xFF;
        }
        timing_value = audio_sequence_timing_division[0];
        if (timing_value != 0x1E) {
            if (timing_value < 0x1FU ? timing_value == 0x18 : timing_value == 0x3C) {
                scaled_tempo = (u32) track->f24 >> 1;
                track->f24 = scaled_tempo;
            }
        } else {
            scaled_tempo = (u32) track->f24 >> 2;
            track->f24 = scaled_tempo;
        }
        track_index = 0;
        track_tempo = track->f24;
        track_count = audio_sequence_track_count[0];
        if (track_count != 0) {
            track_limit = track_count;
            do {
                tempo_track = &audio_sequence_tracks[track_index];
                tempo_track->f24 = track_tempo;
                tempo_track->f20 = track_tempo;
            } while (++track_index < track_limit);
            return;
        }
        return;
    case 0x54:
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        return;
    case 0x58:
        read_next_byte_and_finish(track);
        track->f34 = read_big_endian_word(track);
        return;
    case 0x59:
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        read_next_byte_and_finish(track);
        return;
    default:
        add_to_sequence_counter(track, read_base_128_vlq(track));
        return;
    }
}
