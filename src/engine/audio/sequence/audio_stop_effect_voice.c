#include "common.h"
#include "engine/audio/sequence.h"
#include "engine/audio/spu.h"
#include "slus.h"

typedef struct S_80085458 {
    s16 f00, f02, f04;
    u16 f06;
    u8 pad08[2];
    u16 f0a;
    u8 pad0c[0xC];
    s16 f18;
    u16 f1a;
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

extern S_80085458 audio_voice_records[64];
extern s32 audio_voice_masks[];
extern s32 audio_update_guard[3];

extern s32 sound_apply_indexed_voice_envelope(s32 slot_index, S_80085458 *envelope);

/* Services an active SPU slot until completion and clears the busy flag. */
s32 audio_stop_effect_voice(s16 slot_id)
{
    u8 *busy_or_slot = (u8 *)audio_update_guard;
    u8 *slots = (u8 *)audio_voice_records;
    s32 slot_index = slot_id;
    s32 slot_handle;
    u8 *slot;
    s32 status;
    u16 active;

    slot = slots + slot_index * 0x78;
    active = *(u16 *)(slot + 0x1A);
    *(s32 *)busy_or_slot = 1;
    if (!(active == 0 || *(u16 *)(slot + 6) < 0x10)) {
        slot_handle = audio_voice_masks[slot_index];
        busy_or_slot = slot;
        *(u16 *)(busy_or_slot + 0x1A) = 0;
        *(u16 *)(busy_or_slot + 0x0A) = 0;
        sound_apply_indexed_voice_envelope(slot_index, (S_80085458 *)busy_or_slot);
        sound_reset_indexed_voice_envelope(slot_index);
        set_spu_voice_keys(0, audio_voice_masks[slot_index]);
        do {
            set_spu_voice_keys(0, slot_handle);
            status = read_selected_voice_key_state(slot_handle);
            if (status == 2) {
                break;
            }
        } while (status != 0);
    } else {
        audio_update_guard[0] = 0;
        return -1;
    }
    audio_update_guard[0] = 0;
    return 0;
}
