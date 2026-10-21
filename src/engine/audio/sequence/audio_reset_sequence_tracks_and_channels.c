#include "common.h"
#include "engine/audio/sequence.h"
#include "slus.h"

typedef struct { s16 f0; s16 pad[7]; } S_80073738;

typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s32 f30, f34, f38, f3c, f40, f44;
    s8 f48;
    u8 f49;
    s8 f4a, f4b, f4c, f4d[3];
} S_80085FA8;

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

extern s32 audio_voice_count[4];
extern S_80073738 audio_master_level;
extern s32 audio_voice_masks[64];
extern S_80084960 audio_channel_controls[16];
extern S_80085458 audio_voice_records[64];
extern S_80085FA8 audio_sequence_tracks[32];

/* Resets global state tables and applies per-entry and combined flags. */
void audio_reset_sequence_tracks_and_channels(void) {
    s32 combined_flags;
    s32 entry_index;
    s32 entry_flags;

    combined_flags = 0;
    audio_master_level.f0 = 0x7F;
    for (entry_index = 0; entry_index < 0x20; entry_index++) {
        audio_sequence_tracks[entry_index].f00 = 0;
        audio_sequence_tracks[entry_index].f04 = 0;
        audio_sequence_tracks[entry_index].f08 = 0;
        audio_sequence_tracks[entry_index].f0c = 0;
        audio_sequence_tracks[entry_index].f10 = 0;
        audio_sequence_tracks[entry_index].f18 = 0;
        audio_sequence_tracks[entry_index].f1c = 0;
        audio_sequence_tracks[entry_index].f20 = 0;
        audio_sequence_tracks[entry_index].f24 = 0;
        audio_sequence_tracks[entry_index].f28 = 0;
        audio_sequence_tracks[entry_index].f2c = 1;
        audio_sequence_tracks[entry_index].f34 = 0;
        audio_sequence_tracks[entry_index].f38 = 0;
        audio_sequence_tracks[entry_index].f3c = 0x78;
        audio_sequence_tracks[entry_index].f40 = 0;
        audio_sequence_tracks[entry_index].f48 = 0;
        audio_sequence_tracks[entry_index].f49 = 0xFF;
        audio_sequence_tracks[entry_index].f4a = 0;
        audio_sequence_tracks[entry_index].f4c = 0;
    }

    for (entry_index = 0; entry_index < audio_voice_count[0]; entry_index++) {
        if ((u16)audio_voice_records[entry_index].f06 < 0x10) {
            audio_voice_records[entry_index].f00 = entry_index;
            audio_voice_records[entry_index].f1a = 0;
            audio_voice_records[entry_index].f18 = 0x40;
            audio_voice_records[entry_index].f1d = 0;
            audio_voice_records[entry_index].f27 = 0;
            audio_voice_records[entry_index].f26 = 0;
            audio_voice_records[entry_index].f28 = 0;
            audio_voice_records[entry_index].f2c = 0;
            audio_voice_records[entry_index].f30 = 0;
            audio_voice_records[entry_index].f3c = 0;
            audio_voice_records[entry_index].f43 = 0;
            audio_voice_records[entry_index].f42 = 0;
            audio_voice_records[entry_index].f44 = 0;
            audio_voice_records[entry_index].f48 = 0;
            audio_voice_records[entry_index].f4c = 0;
            audio_voice_records[entry_index].f58 = 0;
            audio_voice_records[entry_index].f70 = 0x40;
            audio_voice_records[entry_index].f74 = 0x40;
            entry_flags = audio_voice_masks[entry_index];
            sound_reset_indexed_voice_envelope(entry_index);
            combined_flags |= entry_flags;
            set_spu_voice_keys(0, entry_flags);
        }
    }

    for (entry_index = 0; entry_index < 0x10; entry_index++) {
        audio_channel_controls[entry_index].f0c = 0x7F;
        audio_channel_controls[entry_index].f04 = 0x40;
        audio_channel_controls[entry_index].f18 = 0;
        audio_channel_controls[entry_index].f1c = 0x40;
        audio_channel_controls[entry_index].f14 = 0x7F;
        audio_channel_controls[entry_index].f20 = 0x7F;
        audio_channel_controls[entry_index].f24 = 0x7F;
        audio_channel_controls[entry_index].f08 = 0;
        audio_channel_controls[entry_index].f3a = 0;
        audio_channel_controls[entry_index].f44 = 0;
        audio_channel_controls[entry_index].f40 = 0;
        audio_channel_controls[entry_index].f48 = 0;
        audio_channel_controls[entry_index].f94 = 0;
        audio_channel_controls[entry_index].f30 = 0;
        audio_channel_controls[entry_index].f60 = 0;
        audio_channel_controls[entry_index].f5f = 0;
        audio_channel_controls[entry_index].f61 = 0;
        audio_channel_controls[entry_index].f64 = 0;
        audio_channel_controls[entry_index].f68 = 0;
        audio_channel_controls[entry_index].f7b = 0;
        audio_channel_controls[entry_index].f7a = 0;
        audio_channel_controls[entry_index].f7c = 0;
        audio_channel_controls[entry_index].f80 = 0;
        audio_channel_controls[entry_index].f84 = 0;
        audio_channel_controls[entry_index].f28 = 0;
        audio_channel_controls[entry_index].f2c = 0;
        audio_channel_controls[entry_index].f50 = 0;
        audio_channel_controls[entry_index].f98 = 0;
    }

    set_spu_voice_keys(0, combined_flags);
}
