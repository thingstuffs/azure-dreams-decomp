#include "common.h"

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

extern s32 func_800589B8(S_80085FA8 *a0);
extern s32 func_80058A04(S_80085FA8 *a0);
extern s32 func_80058ABC(S_80085FA8 *a0);
extern s32 func_80058E50(S_80085FA8 *a0, s32 a1);
extern s32 D_800737C8[];
extern S_80085FA8 D_80085FA8[];
extern u32 D_800869A8[];
extern u32 D_800869B4[];

/* Handles sequence metadata events, updating tempo and marking track endings. */
void func_80058E6C(S_80085FA8 *track, s32 event_type)
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
    if (event_or_bpm == 0x51) {
        goto set_tempo;
    }
    if (event_or_bpm < 0x52) {
        if (event_or_bpm < 0) {
            goto skip_event;
        }
        if (event_or_bpm < 0x10) {
            goto skip_event;
        }
        if (event_or_bpm == 0x2F) {
            goto end_track;
        }
        goto skip_event;
    }
    if (event_or_bpm == 0x58) {
        goto time_signature;
    }
    if (event_or_bpm < 0x59) {
        if (event_or_bpm == 0x54) {
            goto skip_time_code;
        }
        goto skip_event;
    }
    if (event_or_bpm == 0x59) {
        goto skip_key_signature;
    }
    goto skip_event;

end_track:
        track->f2c = 1;
        goto consume_byte;
set_tempo:
        if (D_800737C8[0] == 1) {
            track->f20 = func_80058ABC(track) & 0xFFFFFF;
        } else {
            track->f20 = func_800589B8(track) << 0x10;
            track->f20 = track->f20 | (func_800589B8(track) << 8);
            track->f20 = track->f20 | func_800589B8(track);
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
        timing_value = D_800869A8[0];
        if (timing_value != 0x1E) {
            if (timing_value < 0x1FU) {
                track_index = 0;
                if (timing_value != 0x18) {
                } else {
                    goto halve_tempo;
                }
            } else {
                track_index = 0;
                if (timing_value == 0x3C) {
halve_tempo:
                    scaled_tempo = (u32) track->f24 >> 1;
                    goto store_tempo;
                }
            }
        } else {
            scaled_tempo = (u32) track->f24 >> 2;
store_tempo:
            track->f24 = scaled_tempo;
            track_index = 0;
        }
        track_tempo = track->f24;
        track_count = D_800869B4[0];
        if (track_count != 0) {
            track_limit = track_count;
            tempo_track = D_80085FA8;
            do {
                tempo_track->f24 = track_tempo;
                tempo_track->f20 = track_tempo;
                tempo_track++;
            } while (++track_index < track_limit);
            return;
        }
        return;
skip_time_code:
        func_800589B8(track);
        func_800589B8(track);
        func_800589B8(track);
        goto skip_key_signature;
time_signature:
        func_800589B8(track);
        track->f34 = func_80058ABC(track);
        return;
skip_key_signature:
        func_800589B8(track);
        func_800589B8(track);
consume_byte:
        func_800589B8(track);
        return;
skip_event:
        func_80058E50(track, func_80058A04(track));
}
