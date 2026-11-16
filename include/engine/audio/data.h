#ifndef ENGINE_AUDIO_DATA_H
#define ENGINE_AUDIO_DATA_H

#include "common.h"

typedef struct SoundEffectBankDescriptor {
    u16 unk_00;
    s16 pad_02;
    void *unk_04;
    void *unk_08;
} SoundEffectBankDescriptor;

extern SoundEffectBankDescriptor sound_effect_bank_descriptors[];
extern u8 sound_effect_loaded_record_ids[];
extern void *audio_selection_record_pointers[][16];

#endif
