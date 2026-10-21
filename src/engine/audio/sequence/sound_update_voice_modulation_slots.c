#include "common.h"
#include "engine/audio/sequence.h"

/* Element of D_80084960 stat/entity table, stride 0x9C (156) bytes.
   Layout reconciled with src/w_80056A08.c (same TU family). */
typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s8 f30;
    u8 pad31[9];
    s16 f3a;
    u8 pad3c[4];
    s16 f40;
    u8 pad42[2];
    s32 f44, f48;
    u8 pad4c[4];
    s16 f50;
    u8 pad52[0xD];
    s8 f5f, f60, f61;
    u8 pad62[2];
    s32 f64, f68;
    u8 pad6c[0xE];
    s8 f7a, f7b, f7c;
    u8 pad7d[3];
    s32 f80, f84;
    u8 pad88[0xC];
    s32 f94;
    s8 f98;
    u8 pad99[3];
} S_80084960;

/* Element of D_80085458 table, stride 0x78 (120) bytes.
   Layout reconciled with src/w_80056A08.c (same TU family). */
typedef struct {
    s16 f00, f02, f04;
    u16 f06;
    u8 pad08[0x10];
    s16 f18, f1a;
    s8 f1c, f1d;
    u8 pad1e[8];
    s8 f26, f27, f28;
    u8 pad29[3];
    s32 f2c, f30;
    u8 pad34[8];
    s32 f3c;
    u8 pad40[2];
    s8 f42, f43, f44;
    u8 pad45[3];
    s32 f48, f4c;
    u8 pad50[8];
    s32 f58;
    u8 pad5c[0x14];
    s32 f70, f74;
} S_80085458;

extern s32 audio_voice_count[4];
extern S_80084960 audio_channel_controls[16];
extern S_80085458 audio_voice_records[64];

extern void audio_update_voice_vibrato(S_80085458 *envelope);

/* Refresh all 16 entity slots, then update active D_80085458 slots. */
void sound_update_voice_modulation_slots(void) {
    S_80084960 *entity;
    s32 slot;

    for (slot = 0, entity = audio_channel_controls; slot < 0x10; slot++, entity++) {
        sound_step_bipolar_oscillation(entity);
        sound_step_clamped_signed_ramp(entity);
    }

    for (slot = 0; slot < audio_voice_count[0]; slot++) {
        if ((u16)audio_voice_records[slot].f06 < 0x10) {
            audio_update_voice_vibrato(&audio_voice_records[slot]);
            audio_update_voice_tremolo(&audio_voice_records[slot]);
            audio_update_voice_pitch(&audio_voice_records[slot], 0);
        }
    }
}
