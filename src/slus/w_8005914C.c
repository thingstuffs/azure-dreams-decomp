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
extern S_80085FA8 D_80085FA8[];
extern S_80084960 D_80084960[];
extern s32 D_800869B4[3];
extern s32 D_800869B8[3];
extern void func_80056E10(s32 a0, s32 a1, s32 a2);
extern void func_80057948(s32 a0, s32 a1, s32 a2);
extern void func_80057A48(s32 a0, s32 a1, s32 a2);
extern void func_80057D20(s32 a0, s32 a1, s32 a2);
extern void func_8005845C(s32 a0, s32 a1);
extern void func_8005848C(s32 a0, s32 a1);
extern void func_80058494(s32 a0, s32 a1, s32 a2);
/* Dispatch a MIDI channel event and handle track state save, restore, and repeat controls. */
void func_8005914C(S_80085FA8 *track_arg, s32 status, s32 first_data, s32 second_data)
{
    s32 channel;
    u32 track_index;
    s32 track_count;
    S_80085FA8 *track_iter;
    u8 event_data;
    channel = status & 0xF;
    event_data = first_data;
    switch (status & 0xF0) {
    case 0x80:
        func_80057948(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0x90:
        if ((second_data & 0xFF) != 0) {
            func_80056E10(channel, event_data & 0xFF, second_data & 0xFF);
        }
        else {
            func_80057948(channel, event_data & 0xFF, 0);
        }
        return;

    case 0xA0:
        func_80057A48(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xB0:
        if ((event_data & 0xFF) == 0x63) {
            if ((second_data & 0xFF) == 0x14) {
                if (D_800869B8[0] != 0) {
                    s32 repeat_count;
                    track_index = 0;
                    if (track_index < *(u32 *)&D_800869B4) {
                        repeat_count = 0x14;
                        track_iter = D_80085FA8;
                        while (track_index < *(u32 *)&D_800869B4) {
                            track_iter->unk04 = track_iter->unk00;
                            track_iter->unk08 = repeat_count;
                            track_iter->unk14 = track_iter->unk10;
                            track_iter->unk44 = track_iter->unk40;
                            track_iter->unk30 = track_iter->unk2C;
                            track_iter->unk4B = track_iter->unk4A;
                            track_iter++;
                            track_index++;
                        }
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
                    if (D_800869B8[0] != 0) {
                        track_index = 0;
                        if (track_index < *(u32 *)&D_800869B4) {
                            track_iter = D_80085FA8;
                            while (track_index < *(u32 *)&D_800869B4) {
                                track_iter->unk00 = track_iter->unk04;
                                track_iter->unk10 = track_iter->unk14;
                                track_iter->unk40 = track_iter->unk44;
                                track_iter->unk2C = track_iter->unk30;
                                track_iter->unk4A = track_iter->unk4B;
                                track_iter++;
                                track_index++;
                            }
                        }
                    }
                    else {
                        track_arg->unk00 = track_arg->unk04;
                    }
                }
            }
        }
        if ((event_data & 0xFF) == 6) {
            if (D_80084960[channel & 0xFF].unk4D == 0x14) {
                if (D_800869B8[0] != 0) {
                    if (D_800869B4[0] != 0) {
                        s32 repeat_count;
                        register S_80085FA8 *broadcast_track;
                        track_index = 0;
                        repeat_count = second_data & 0xFF;
                        track_count = D_800869B4[0];
                        broadcast_track = D_80085FA8;
                        do {
                            broadcast_track->unk08 = repeat_count;
                            broadcast_track++;
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
        func_80057D20(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xE0:
        func_80058494(channel, event_data & 0xFF, second_data & 0xFF);
        return;

    case 0xC0:
        func_8005845C(channel, event_data & 0xFF);
        return;

    case 0xD0:
        func_8005848C(channel, event_data & 0xFF);
        return;
    }
}
