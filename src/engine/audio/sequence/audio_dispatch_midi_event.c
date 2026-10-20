#include "common.h"

typedef struct
{
    s32 unk00;
    s32 unk04;
    u32 unk08;
    u8 pad0C[0x10 - 0x0C];
    s32 unk10;
    s32 unk14;
    u8 pad18[0x2C - 0x18];
    s32 unk2C;
    s32 unk30;
    u8 pad34[0x40 - 0x34];
    s32 unk40;
    s32 unk44;
    u8 pad48[0x4A - 0x48];
    u8 unk4A;
    u8 unk4B;
    u8 pad4C[0x50 - 0x4C];
}
S_80085FA8;
typedef struct
{
    u8 pad00[0x4D];
    u8 unk4D;
    u8 pad4E[0x9C - 0x4E];
}
S_80084960;
extern S_80085FA8 audio_sequence_tracks[];
extern S_80084960 audio_channel_controls[];
extern s32 audio_sequence_track_count[3];
extern s32 audio_sequence_multitrack_mode[3];
extern void start_channel_note(s32 a0, s32 a1, s32 a2);
extern void audio_sequence_note_off(s32 a0, s32 a1, s32 a2);
extern void func_80057A48(s32 a0, s32 a1, s32 a2);
extern void audio_apply_channel_control(s32 a0, s32 a1, s32 a2);
extern void set_audio_channel_program(s32 a0, s32 a1);
extern void func_8005848C(s32 a0, s32 a1);
extern void sound_set_seven_bit_channel_value_and_notify(s32 a0, s32 a1, s32 a2);
/* Dispatch a MIDI channel event and handle track state save, restore, and repeat controls. */
void audio_dispatch_midi_event(S_80085FA8 *track_arg, s32 status, s32 first_data, s32 second_data)
{
    s32 channel;
    u32 track_index;
    s32 track_count;
    u8 event_data;
    channel = status & 0xF;
    event_data = first_data;
    switch (status & 0xF0) {
    case 0x80:
        audio_sequence_note_off(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0x90:
        if ((second_data & 0xFF) != 0) {
            start_channel_note(channel, event_data & 0xFF, second_data & 0xFF);
        }
        else {
            audio_sequence_note_off(channel, event_data & 0xFF, 0);
        }
        return;

    case 0xA0:
        func_80057A48(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xB0:
        if ((event_data & 0xFF) == 0x63) {
            if ((second_data & 0xFF) == 0x14) {
                if (audio_sequence_multitrack_mode[0] != 0) {
                    for (track_index = 0; track_index < *(u32 *)&audio_sequence_track_count; track_index++) {
                        audio_sequence_tracks[track_index].unk04 = audio_sequence_tracks[track_index].unk00;
                        audio_sequence_tracks[track_index].unk08 = 0x14;
                        audio_sequence_tracks[track_index].unk14 = audio_sequence_tracks[track_index].unk10;
                        audio_sequence_tracks[track_index].unk44 = audio_sequence_tracks[track_index].unk40;
                        audio_sequence_tracks[track_index].unk30 = audio_sequence_tracks[track_index].unk2C;
                        audio_sequence_tracks[track_index].unk4B = audio_sequence_tracks[track_index].unk4A;
                    }
                }
                else {
                    track_arg->unk08 = 0x7F;
                    track_arg->unk04 = track_arg->unk00;
                }
            }
            else if ((second_data & 0xFF) == 0x1E) {
                if (track_arg->unk08 != 0) {
                    if (track_arg->unk08 < 0x7FU) {
                        track_arg->unk08 = track_arg->unk08 - 1;
                    }
                    if (audio_sequence_multitrack_mode[0] != 0) {
                        for (track_index = 0; track_index < *(u32 *)&audio_sequence_track_count; track_index++) {
                            audio_sequence_tracks[track_index].unk00 = audio_sequence_tracks[track_index].unk04;
                            audio_sequence_tracks[track_index].unk10 = audio_sequence_tracks[track_index].unk14;
                            audio_sequence_tracks[track_index].unk40 = audio_sequence_tracks[track_index].unk44;
                            audio_sequence_tracks[track_index].unk2C = audio_sequence_tracks[track_index].unk30;
                            audio_sequence_tracks[track_index].unk4A = audio_sequence_tracks[track_index].unk4B;
                        }
                    }
                    else {
                        track_arg->unk00 = track_arg->unk04;
                    }
                }
            }
        }
        if ((event_data & 0xFF) == 6) {
            if (audio_channel_controls[channel & 0xFF].unk4D == 0x14) {
                if (audio_sequence_multitrack_mode[0] != 0) {
                    if (audio_sequence_track_count[0] != 0) {
                        s32 repeat_count;
                        track_index = 0;
                        repeat_count = second_data & 0xFF;
                        track_count = audio_sequence_track_count[0];
                        do {
                            audio_sequence_tracks[track_index].unk08 = repeat_count;
                            track_index++;
                        }
                        while (track_index < ((u32) track_count));
                    }
                }
                else {
                    track_arg->unk08 = second_data & 0xFF;
                    return;
                }
            }
        }
        audio_apply_channel_control(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xE0:
        sound_set_seven_bit_channel_value_and_notify(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xC0:
        set_audio_channel_program(channel, event_data & 0xFF);
        return;

    case 0xD0:
        func_8005848C(channel, event_data & 0xFF);
        return;
    }
}
