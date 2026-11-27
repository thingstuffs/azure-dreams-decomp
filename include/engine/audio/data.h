#ifndef ENGINE_AUDIO_DATA_H
#define ENGINE_AUDIO_DATA_H

#include "common.h"

typedef struct SoundEffectBankDescriptor {
    u16 bank_slot;
    s16 pad_02;
    void *body_read;
    void *header_read;
} SoundEffectBankDescriptor;

extern SoundEffectBankDescriptor sound_effect_bank_descriptors[];
extern u8 sound_effect_loaded_record_ids[];
extern void *audio_selection_record_pointers[][16];

/* Payload words selected by the pending bank slot. */
extern s32 audio_bank_owner_payloads[];

/* Resident flag that keeps the current music during scene transitions. */
extern s8 scene_music_hold;

#endif
