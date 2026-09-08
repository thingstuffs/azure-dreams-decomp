#include "common.h"

typedef struct {
    u8 pad0[0xC];
    u16 field_C;
    u16 padE;
} S_8005EB78_VoiceSlot;

typedef struct {
    S_8005EB78_VoiceSlot *ptr;
    u32 pad[2];
} S_8005EB78_79958;

extern S_8005EB78_79958 D_80079958;
extern s32 D_800794F0[3];

/* Returns the active/key-on state of the first selected voice, or -1 if none is selected. */
s32 func_8005EB78(s32 voice_mask)
{
    s32 voice;
    s32 bit_base;
    s32 voice_index;
    s32 result;
    u16 active;

    voice = -1;
    voice_index = 0;
    bit_base = 1;
    while (voice_index < 24) {
        if ((voice_mask & (bit_base << voice_index)) != 0) {
            goto found;
        }
        voice_index++;
    }

after_loop:
    result = -1;
    if (voice != result) {
        goto has_voice;
    }
    return result;

found:
    voice = voice_index;
    goto after_loop;

has_voice:
    voice_mask = voice << 4;
    result = (s32)D_80079958.ptr;
    voice_index = D_800794F0[0];
    voice_mask = voice_mask + result;
    result = 1;
    result = result << voice;
    voice_index = voice_index & result;
    active = *(u16 *)(voice_mask + 0xC);
    if (voice_index != 0) {
        if (active != 0) {
            return 1;
        }
        return 3;
    }

    return active != 0 ? 2 : 0;
}
