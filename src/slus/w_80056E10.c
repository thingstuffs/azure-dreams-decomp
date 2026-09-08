#include "common.h"

/* D_80084960: per-request channel record, stride 0x9C */
typedef struct Chan {
    /* 0x00 */ u16 f00;
    u8 pad02[0x10 - 0x02];
    /* 0x10 */ s32 f10;
    u8 pad14[0x18 - 0x14];
    /* 0x18 */ u8 f18;
    u8 pad19[0x1C - 0x19];
    /* 0x1C */ s32 f1C;
    u8 pad20[0x28 - 0x20];
    /* 0x28 */ u32 f28;
    u8 pad2C[0x30 - 0x2C];
    /* 0x30 */ u8 f30;
    u8 pad31[0x3A - 0x31];
    /* 0x3A */ u16 f3A;
    u8 pad3C[0x50 - 0x3C];
    /* 0x50 */ s16 f50;
    /* 0x52 */ u16 f52;
    /* 0x54 */ s16 f54;
    /* 0x56 */ u16 f56;
    /* 0x58 */ s32 f58;
    /* 0x5C */ u8 f5C;
    /* 0x5D */ u8 f5D;
    u8 pad5E[0x68 - 0x5E];
    /* 0x68 */ s32 f68;
    /* 0x6C */ u8 f6C;
    /* 0x6D */ u8 f6D;
    /* 0x6E */ u8 f6E;
    u8 pad6F;
    /* 0x70 */ s32 f70;
    u8 pad74[0x78 - 0x74];
    /* 0x78 */ u8 f78;
    u8 pad79[0x84 - 0x79];
    /* 0x84 */ s32 f84;
    /* 0x88 */ u8 f88;
    /* 0x89 */ u8 f89;
    /* 0x8A */ u8 f8A;
    u8 pad8B;
    /* 0x8C */ s32 f8C;
    u8 pad90[0x98 - 0x90];
    /* 0x98 */ u8 f98;
    u8 pad99[0x9C - 0x99];
} Chan;

/* D_80085458: voice record, stride 0x78 */
typedef struct Voice {
    /* 0x00 */ s16 f00;
    u8 pad02[2];
    /* 0x04 */ u16 f04;
    /* 0x06 */ u16 f06;
    /* 0x08 */ u16 f08;
    /* 0x0A */ u16 f0A;
    /* 0x0C */ u16 f0C;
    u8 pad0E[2];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 f14;
    /* 0x15 */ u8 f15;
    /* 0x16 */ u8 f16;
    /* 0x17 */ u8 f17;
    u8 pad18[2];
    /* 0x1A */ u16 f1A;
    /* 0x1C */ u8 f1C;
    /* 0x1D */ u8 f1D;
    u8 pad1E[2];
    /* 0x20 */ u8 f20;
    /* 0x21 */ u8 f21;
    /* 0x22 */ u8 f22;
    /* 0x23 */ u8 f23;
    /* 0x24 */ u8 f24;
    u8 pad25;
    /* 0x26 */ u8 f26;
    /* 0x27 */ u8 f27;
    /* 0x28 */ u8 f28;
    u8 pad29[3];
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s32 f30;
    /* 0x34 */ u8 f34;
    /* 0x35 */ u8 f35;
    /* 0x36 */ u8 f36;
    u8 pad37;
    /* 0x38 */ s32 f38;
    /* 0x3C */ u16 f3C;
    u8 pad3E[2];
    /* 0x40 */ u8 f40;
    u8 pad41;
    /* 0x42 */ u8 f42;
    /* 0x43 */ u8 f43;
    /* 0x44 */ u8 f44;
    u8 pad45[3];
    /* 0x48 */ s32 f48;
    /* 0x4C */ s32 f4C;
    /* 0x50 */ u8 f50;
    /* 0x51 */ u8 f51;
    /* 0x52 */ u8 f52;
    u8 pad53;
    /* 0x54 */ s32 f54;
    /* 0x58 */ s32 f58;
    u8 pad5C[4];
    /* 0x60 */ s32 f60;
    /* 0x64 */ s32 f64;
    /* 0x68 */ s32 f68;
    u8 pad6C[4];
    /* 0x70 */ s32 f70;
    /* 0x74 */ s32 f74;
} Voice;

/* D_80086A40: stride 0x1C */
typedef struct Slot {
    u8 pad00[4];
    /* 0x04 */ u8 *f04;
    u8 pad08[0x10 - 0x08];
    /* 0x10 */ s32 f10;
    u8 pad14[0x1C - 0x14];
} Slot;

/* event record, stride 0x20, at song + 0x820 */
typedef struct Ev {
    u8 pad00;
    /* 0x01 */ u8 f01;
    /* 0x02 */ u8 f02;
    /* 0x03 */ u8 f03;
    /* 0x04 */ u8 f04;
    /* 0x05 */ u8 f05;
    /* 0x06 */ u8 f06;
    /* 0x07 */ u8 f07;
    u8 pad08[4];
    /* 0x0C */ u8 f0C;
    /* 0x0D */ u8 f0D;
    u8 pad0E[2];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    u8 pad14[2];
    /* 0x16 */ s16 f16;
    u8 pad18[8];
} Ev;

typedef struct Hdr {
    /* 0x00 */ u8 f00;
    /* 0x01 */ u8 f01;
    u8 pad02[2];
    /* 0x04 */ u8 f04;
} Hdr;

typedef struct Song {
    u8 pad00[0x12];
    /* 0x12 */ u16 f12;
} Song;

typedef struct Req {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ s16 f0C;
    /* 0x0E */ s16 f0E;
    u8 pad10[6];
    /* 0x16 */ s16 f16;
    u8 pad18[4];
    /* 0x1C */ s32 f1C;
    u8 pad20[4];
    /* 0x24 */ s32 f24;
    u8 pad28[0x3A - 0x28];
    /* 0x3A */ u16 f3A;
    /* 0x3C */ u16 f3C;
} Req;

extern Chan D_80084960[16];
extern Voice D_80085458[64];
extern Slot D_80086A40[16];
extern s16 D_80086D50[8];
extern s32 D_80073740[];
extern s32 D_80073734[4];
extern s32 D_80073734_1[4] __asm__("D_80073734");
extern s32 D_80073734_2[4] __asm__("D_80073734");
extern s32 D_80073734_3[4] __asm__("D_80073734");
extern s32 D_80073734_4[4] __asm__("D_80073734");
extern s32 D_80073734_5[4] __asm__("D_80073734");
extern s32 D_80073734_6[4] __asm__("D_80073734");
extern s32 D_80073734_7[4] __asm__("D_80073734");
extern Req D_80084918;
extern s16 D_80084930;

extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 mode, s32 mask);
extern s32 func_8005EB78(s32 mask);
extern void func_80055E74(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800561D8(Voice *a0, Chan *a1);
extern s32 func_800565D8(Voice *a0, s32 a1);
extern void func_8005E4A0(s32 a0, s32 a1);
extern s32 func_8005E78C(void);
extern void func_8005EC0C(Req *a0);

/* Allocates or reuses voices for matching tones and applies channel note settings. */
void func_80056E10(u8 channel_id, s32 note, u8 velocity)
{
    u8 tone_pan;
    u8 channel_param_5d;
    s32 stack_pad[6];
    s32 note_value;
    u16 tone_idx;
    s32 program_count;
    s32 program_limit;
    u16 program_id;
    u8 *song_data;
    Song *song;
    Hdr *program;
    s32 voice_held;
    u32 note_key;
    u16 channel_key;
    Chan *channel;
    Ev *tone;
    Voice *voice;
    u8 *program_data;
    u16 *sample_sizes;
    s32 start_note;
    s16 voice_idx;
    s32 entry_idx;
    s32 sample_offset;
    s16 sample_id;
    s32 voice_status;
    u32 prev_note;
    s32 glide_note;
    s32 match_note;
    u32 match_channel;
    u16 adsr1;
    u16 adsr2;

    note_value = note;
    program_count = 0;
    entry_idx = 0;
    channel = &D_80084960[channel_id];
    song = (Song *)D_80086A40[D_80086D50[0]].f04;
    program_id = channel->f00;
    song_data = (u8 *)song;
    if ((s32)program_id != 0) {
        program_limit = program_id;
        program_data = song_data;
        do {
            if (program_data[0x20] != 0) {
                program_count++;
            }
            program_data += 0x10;
            entry_idx++;
        } while (entry_idx < program_limit);
    }
    program = (Hdr *)(song_data + (program_id * 0x10 + 0x20));
    start_note = (u8) note_value;
    tone_idx = 0;
    if (program->f00 == 0) {
        return;
    }
    note_key = note_value & 0xFF;
    channel_key = channel_id;
    do {
        tone = (Ev *)(song_data + (((program_count * 0x10 + tone_idx) << 5) + 0x820));
        voice_held = 0;
        if ((note_key >= tone->f06) && (tone->f07 >= note_key)) {
            voice_idx = -1;
            if (channel->f98 != 0) {
                voice_idx = 0;
                while (1) {
                    if (channel_key == D_80085458[voice_idx].f06) {
                        break;
                    }
                    if (++voice_idx >= D_80073734_1[0]) {
                        voice_idx = -1;
                        break;
                    }
                }
                if (voice_idx != -1) {
                    if (D_80085458[voice_idx].f1A == 0) {
                        func_80056DB4(voice_idx);
                        func_8005E97C(0, D_80073740[voice_idx]);
                    } else {
                        voice_held = 1;
                    }
                } else {
                    voice_idx = 0;
                    while (1) {
                        if (func_8005EB78(D_80073740[voice_idx]) == 0) {
                            break;
                        }
                        if (++voice_idx >= D_80073734_2[0]) {
                            voice_idx = -1;
                            break;
                        }
                    }
                    if (voice_idx == -1) {
                        voice_idx = 0;
                        while (1) {
                            voice_status = func_8005EB78(D_80073740[voice_idx]);
                            if (voice_status == 2) {
                                break;
                            }
                            if (voice_status == 0) {
                                break;
                            }
                            if (++voice_idx >= D_80073734_3[0]) {
                                voice_idx = -1;
                                break;
                            }
                        }
                    }
                }
                if (channel->f50 != 0) {
                    glide_note = channel->f5C & 0x7F;
                    ASM_KEEP_NV(glide_note);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    start_note = (u8) glide_note;
                    ASM_KEEP_NV(channel);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    prev_note = channel->f5C;
                    channel->f52 = 0;
                    if (prev_note < note_key) {
                        channel->f56 = ((note_value & 0xFF) - channel->f5C) << 7;
                        channel->f58 = 1;
                        channel->f54 = (channel->f56 * 4) / channel->f50;
                    } else if (prev_note == note_key) {
                        channel->f54 = 0;
                        start_note = (u8) note_value;
                    } else {
                        channel->f56 = (channel->f5C - (note_value & 0xFF)) << 7;
                        channel->f58 = 0;
                        channel->f54 = (channel->f56 * 4) / channel->f50;
                    }
                } else {
                    channel->f52 = 0;
                }
            } else {
                if (channel->f50 != 0) {
                    glide_note = channel->f5C & 0x7F;
                    ASM_KEEP_NV(glide_note);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    start_note = (u8) glide_note;
                    ASM_KEEP_NV(channel);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    prev_note = channel->f5C;
                    channel->f52 = 0;
                    if (prev_note < note_key) {
                        channel->f56 = ((note_value & 0xFF) - channel->f5C) << 7;
                        channel->f58 = 1;
                        channel->f54 = (channel->f56 * 4) / channel->f50;
                    } else if (prev_note == note_key) {
                        channel->f54 = 0;
                        start_note = (u8) note_value;
                    } else {
                        channel->f56 = (channel->f5C - (note_value & 0xFF)) << 7;
                        channel->f58 = 0;
                        channel->f54 = (channel->f56 * 4) / channel->f50;
                    }
                } else {
                    channel->f52 = 0;
                }
            }
            if (voice_idx == -1) {
                voice_idx = 0;
                while (1) {
                    if (func_8005EB78(D_80073740[voice_idx]) == 0) {
                        break;
                    }
                    if (++voice_idx >= D_80073734_4[0]) {
                        voice_idx = -1;
                        break;
                    }
                }
                if (voice_idx == -1) {
                    voice_idx = 0;
                    while (1) {
                        voice_status = func_8005EB78(D_80073740[voice_idx]);
                        if (voice_status == 2) {
                            break;
                        }
                        if (voice_status == 0) {
                            break;
                        }
                        if (++voice_idx >= D_80073734_5[0]) {
                            voice_idx = -1;
                            break;
                        }
                    }
                    if (voice_idx == -1) {
                        voice_idx = 0;
                        match_channel = channel_key;
                        match_note = note_value & 0xFF;
                        while (1) {
                            if ((match_channel == D_80085458[voice_idx].f06) && (D_80085458[voice_idx].f0A == match_note)) {
                                break;
                            }
                            if (++voice_idx >= D_80073734_6[0]) {
                                voice_idx = -1;
                                break;
                            }
                        }
                        if (voice_idx == -1) {
                            voice_idx = 0;
                            while (1) {
                                if (D_80085458[voice_idx].f1A == 0) {
                                    break;
                                }
                                if (++voice_idx >= D_80073734_7[0]) {
                                    voice_idx = -1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (voice_idx != -1) {
                voice = &D_80085458[voice_idx];
                if (channel->f98 == 0) {
                    func_80056DB4(voice_idx);
                    func_8005E97C(0, D_80073740[voice_idx]);
                    func_80055E74(voice_idx, note_value & 0xFF, channel_id, D_80084918.f08, D_80084918.f0A);
                }
                entry_idx = 0;
                sample_offset = 0;
                sample_sizes = (u16 *)((D_80086A40[D_80086D50[0]].f04 + (song->f12 << 9)) + 0x820);
                sample_id = tone->f16;
                for (; entry_idx < sample_id; entry_idx++) {
                    sample_offset += *sample_sizes;
                    sample_sizes++;
                }
                D_80084918.f04 = 0x601EF;
                D_80084918.f0C = 0;
                D_80084918.f0E = 0;
                D_80084918.f00 = D_80073740[voice_idx];
                sample_offset <<= 3;
                D_80084918.f1C = D_80086A40[D_80086D50[0]].f10 + sample_offset;
                adsr1 = tone->f10;
                D_80084918.f3A = adsr1;
                voice->f60 = adsr1;
                adsr2 = tone->f12;
                D_80084918.f3C = adsr2;
                voice->f64 = adsr2;
                if (tone->f10 & 0x80) {
                    D_80084918.f24 = 5;
                } else {
                    D_80084918.f24 = 1;
                }
                voice->f68 = D_80084918.f24;
                channel->f5C = note_value;
                channel->f10 = velocity;
                voice->f22 = tone->f04;
                voice->f23 = tone->f05;
                voice->f21 = tone->f0C;
                voice->f20 = tone->f0D;
                voice->f00 = voice_idx;
                voice->f04 = program_id;
                voice->f08 = tone_idx;
                voice->f0A = start_note & 0x7F;
                voice->f0C = start_note & 0x7F;
                voice->f06 = channel_key;
                voice->f1A = 1;
                channel->f3A = 0;
                voice->f14 = program->f01;
                voice->f16 = program->f04;
                voice->f15 = tone->f02;
                tone_pan = tone->f03;
                voice->f1C = velocity;
                voice->f27 = 0;
                voice->f26 = 0;
                voice->f28 = 0;
                voice->f17 = tone_pan;
                voice->f34 = channel->f6C;
                voice->f36 = channel->f6E;
                voice->f38 = channel->f70;
                voice->f30 = channel->f68;
                voice->f35 = channel->f6D;
                channel_param_5d = channel->f5D;
                voice->f2C = 0;
                *((s32 *) &voice->f3C) = 0;
                voice->f43 = 0;
                voice->f42 = 0;
                voice->f44 = 0;
                voice->f24 = channel_param_5d;
                voice->f50 = channel->f88;
                voice->f52 = channel->f8A;
                voice->f54 = channel->f8C;
                voice->f4C = channel->f84;
                voice->f51 = channel->f89;
                voice->f40 = channel->f78;
                voice->f48 = 0;
                voice->f58 = 0;
                func_800561D8(&D_80085458[voice_idx], &D_80084960[channel_id]);
                D_80084918.f08 = voice->f10;
                D_80084918.f0A = voice->f12;
                voice->f1D = channel->f18;
                voice->f0A = note_value & 0x7F;
                voice->f74 = channel->f1C;
                voice->f70 = -1;
                if (channel->f28 < 0x40) {
                    s32 semitone;
                    s16 pitch = voice->f3C + (channel->f3A + channel->f52);
                    pitch = pitch + ((voice->f0C << 7) + func_800565D8(voice, channel->f1C));
                    semitone = ((s32)(pitch << 16)) >> 23;
                    pitch = (pitch & 0x7F) + (semitone << 8);
                    D_80084918.f16 = pitch;
                } else {
                    channel->f1C = 0x40;
                    D_80084918.f16 = start_note << 8;
                }
                if (tone->f05 != 0) {
                    D_80084930 = ((tone->f04 - 1) << 8) | (0x7F - tone->f05);
                } else {
                    D_80084930 = tone->f05 | (tone->f04 << 8);
                }
                if (voice_held == 0) {
                    func_8005EC0C(&D_80084918);
                }
                if (channel->f30 == 0) {
                    if (tone->f01 & 4) {
                        do {
                            func_8005E4A0(1, D_80073740[voice_idx]);
                        } while (!(func_8005E78C() & D_80073740[voice_idx]));
                    } else {
                        do {
                            func_8005E4A0(0, D_80073740[voice_idx]);
                        } while (func_8005E78C() & D_80073740[voice_idx]);
                    }
                } else if (channel->f30 != 1) {
                    do {
                        func_8005E4A0(1, D_80073740[voice_idx]);
                    } while (!(func_8005E78C() & D_80073740[voice_idx]));
                } else {
                    do {
                        func_8005E4A0(0, D_80073740[voice_idx]);
                    } while (func_8005E78C() & D_80073740[voice_idx]);
                }
            }
        }
        tone_idx++;
    } while (tone_idx < program->f00);
    ASM_SET(note_value);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
}
