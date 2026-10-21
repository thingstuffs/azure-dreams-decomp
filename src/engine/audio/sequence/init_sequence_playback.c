#include "common.h"
#include "engine/audio/sequence.h"
#include "slus/data.h"

/* S_80058B70: view of the D_80085FA8[] element struct touched here (base passed
 * to read_big_endian_word/read_sequence_halfword/read_next_byte_and_finish; direct fields f00,f1c,f20,f24). */
typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s32 f30, f34, f38, f3c, f40, f44;
    s8 f48;
    u8 f49;
    s8 f4a, f4b, f4c, f4d[3];
} S_80058B70;

extern S_80058B70 audio_sequence_tracks[32];
extern s32 audio_sequence_data_base[4];   /* [0] = base pointer to another struct */
extern s32 audio_sequence_format[4];
extern s32 audio_sequence_timing_division[4];
extern s32 audio_sequence_track_count[4];
extern s32 audio_sequence_multitrack_mode[4];

extern void read_next_byte_and_finish(S_80058B70 *);

/* Configures the first playback slot and playback parameters for the current mode. */
s32 init_sequence_playback(void)
{
    S_80058B70 *slot = &audio_sequence_tracks[0];
    s32 stream_offset = 0;
    s32 entry_index;
    u32 timing_divisor;
    u32 playback_rate;
    u32 scaled_rate;

    D_800737D4[0] = 0;
    switch (audio_sequence_format[0]) {
    case 1:
    {
        s32 header_offset = find_sequence_magic_after_offset(0);
        slot->f00 = header_offset;
        if (header_offset == -1) {
            return 0;
        }
    }
        sequence_header_word[0] = read_big_endian_word(slot);
        audio_sequence_multitrack_mode[0] = read_sequence_halfword(slot) & 0xFFFF;
        audio_sequence_track_count[0] = read_sequence_halfword(slot) & 0xFFFF;
        audio_sequence_timing_division[0] = read_sequence_halfword(slot) & 0xFFFF;
        if (audio_sequence_multitrack_mode[0] == 0) {
            s32 first_entry_offset;
            audio_sequence_stream_limit[0] = 0x10000;
            first_entry_offset = scan_stream_for_three_byte_marker(0);
            audio_sequence_stream_limit[0] = first_entry_offset;
            slot->f1c = first_entry_offset;
        } else {
            entry_index = 0;
            audio_sequence_stream_limit[0] = 0x10000;
            if ((u32)stream_offset < (u32)audio_sequence_track_count[0]) {
                do {
                    stream_offset = scan_stream_for_three_byte_marker(stream_offset);
                    entry_index++;
                    slot->f1c = stream_offset;
                } while ((u32)entry_index < (u32)audio_sequence_track_count[0]);
            }
            audio_sequence_stream_limit[0] = stream_offset;
        }
        break;
    case 0:
        slot->f00 = 8;
        audio_sequence_timing_division[0] = read_sequence_halfword(slot) & 0xFFFF;
        audio_sequence_multitrack_mode[0] = 0;
        audio_sequence_track_count[0] = 1;
        audio_sequence_stream_limit[0] = 0x10000;
        audio_sequence_stream_limit[0] = scan_stream_for_three_byte_marker(0);
        timing_divisor = read_big_endian_word(slot) >> 8;
        playback_rate = 0x3938700 / timing_divisor;
        slot->f20 = timing_divisor;
        slot->f24 = playback_rate;
        slot->f20 = playback_rate;
        scaled_rate = (playback_rate * 100) / 115;
        slot->f24 = scaled_rate;
        if (scaled_rate >= 0x100) {
            slot->f24 = 0xFF;
        }
        switch ((u32)audio_sequence_timing_division[0]) {
        case 0x18:
        case 0x3C:
            slot->f24 = (u32)slot->f24 >> 1;
            break;
        case 0x1E:
            slot->f24 = (u32)slot->f24 >> 2;
            break;
        }
        read_next_byte_and_finish(slot);
        break;
    case 2:
        audio_sequence_multitrack_mode[0] = 1;
        {
            s8 *mode_data = (s8 *)audio_sequence_data_base[0];
            audio_sequence_timing_division[0] = *(s32 *)(mode_data + 8);
            audio_sequence_track_count[0] = *(s32 *)(mode_data + 0xC);
            audio_sequence_stream_limit[0] = *(s32 *)(mode_data + 4);
        }
        break;
    }
    if ((u32)audio_sequence_timing_division[0] >= 0x60) {
        audio_sequence_timing_word[0] = audio_sequence_timing_division[0];
    } else {
        audio_sequence_timing_word[0] = 0;
    }
    audio_sequence_timing_word[0] = audio_sequence_timing_division[0];
    return 1;
}
