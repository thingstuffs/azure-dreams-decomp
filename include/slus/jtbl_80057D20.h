#ifndef SLUS_JTBL_80057D20_H
#define SLUS_JTBL_80057D20_H


#include "common.h"
typedef struct S_80084960
{
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
    s8 f30;
    u8 pad31[7];
    s16 f38;
    s16 f3a;
    u8 pad3c[4];
    s16 f40;
    u8 pad42[2];
    s32 f44;
    s32 f48;
    s8 f4c;
    u8 f4d;
    s8 f4e;
    u8 pad4f[1];
    s16 f50;
    u8 pad52[11];
    s8 f5d;
    u8 pad5e[1];
    s8 f5f;
    s8 f60;
    s8 f61;
    u8 pad62[2];
    s32 f64;
    s32 f68;
    s8 f6c;
    s8 f6d;
    s8 f6e;
    u8 pad6f[1];
    s32 f70;
    u8 pad74[4];
    s8 f78;
    u8 pad79[1];
    s8 f7a;
    s8 f7b;
    s8 f7c;
    u8 pad7d[3];
    s32 f80;
    s32 f84;
    s8 f88;
    s8 f89;
    s8 f8a;
    u8 pad8b[1];
    s32 f8c;
    u8 pad90[4];
    s32 f94;
    s8 f98;
    u8 pad99[3];
}
S_80084960;
typedef struct S_80085458
{
    s16 f00;
    s16 f02;
    s16 f04;
    u16 f06;
    u8 pad08[8];
    u16 f10;
    u16 f12;
    u8 pad14[4];
    s16 f18;
    u16 f1a;
    u8 f1c;
    u8 f1d;
    u8 pad1e[0x5A];
}
S_80085458;
typedef struct S_80073738
{
    s16 f0;
    s16 pad[7];
}
S_80073738;
extern s32 audio_voice_count[4];
extern S_80073738 audio_master_level;
extern s32 audio_voice_masks[64];
extern S_80084960 audio_channel_controls[16];
extern S_80085458 audio_voice_records[64];
extern void noop_channel_control_notification();
extern void audio_refresh_sequence_voice_volumes();
extern void audio_update_voice_pitch(S_80085458 *e, s32 value);
extern void apply_tone_parameter_command(S_80084960 *e);
extern void func_80057A94(S_80084960 *e);
extern void audio_compute_voice_stereo_volumes(S_80085458 *e, S_80084960 *rec);
extern s32 sound_set_indexed_voice_volumes(s32 a0, u16 a1, u16 a2);
extern void audio_reset_sequence_tracks_and_channels(void);
extern void SpuSetKey(s32 a0, s32 a1);
extern s32 SpuGetKeyStatus(s32 a0);
/* Applies a channel control change and updates affected voices. */
void audio_apply_channel_control(u8 channel, u8 control, u32 value);

#endif
