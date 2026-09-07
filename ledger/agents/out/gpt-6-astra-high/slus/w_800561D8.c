#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x18];
    u8 unk18;
    u8 pad19[2];
    u8 unk1B;
} S_800561D8_D80086A40;

typedef struct {
    u8 pad00[8];
    s16 unk8;
    s16 unkA;
} S_800561D8_D80086C00;

typedef struct {
    u16 f0;
    s16 pad[7];
} S_800561D8_D80073738;

typedef struct {
    u8 pad00[0x10];
    u16 unk10;
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s16 unk18;
    u8 pad1A[2];
    u8 unk1C;
} S_800561D8_Arg0;

typedef struct {
    u8 pad00[4];
    s32 unk4;
    u8 pad08[4];
    s32 unkC;
    u8 pad10[4];
    s32 unk14;
    u8 pad18[0x14];
    s32 unk2C;
} S_800561D8_Arg1;

extern S_800561D8_D80086A40 D_80086A40[16];
extern S_800561D8_D80086C00 D_80086C00[8];
extern s16 D_80086D50[8];
extern u8 D_8007382A[16];
extern S_800561D8_D80073738 D_80073738;

/* Compute voice pan and stereo volumes from channel gains and sound parameters. */
void func_800561D8(S_800561D8_Arg0 *voice_arg, S_800561D8_Arg1 *sound_params)
{
    S_800561D8_Arg0 *voice = voice_arg;
    S_800561D8_D80086A40 *channels = D_80086A40;
    S_800561D8_D80086A40 *channel;
    register s32 pan_value ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 product;
    s32 left_volume;
    s32 right_volume;
    s32 scale;
    s32 pan_sum;

    pan_value = D_80086D50[0];
    channel = &channels[pan_value];
    pan_sum = channel->unk1B + voice->unk16;
    ASM_KEEP(pan_sum);   /* MATCH pin: slus-diff */
    pan_sum += voice->unk17;
    pan_value = sound_params->unk4;
    pan_sum += pan_value;
    pan_value = pan_sum - 0xC0;
    if (D_8007382A[0] != 0) {
        pan_value = 0x40;
    }
    if (pan_value < 0) {
        pan_value = 0;
    }
    if (pan_value >= 0x80) {
        pan_value = 0x7F;
    }
    voice->unk18 = pan_value;

    product = channel->unk18 * D_80073738.f0;
    product *= sound_params->unk14;
    product *= sound_params->unkC;
    product = (u32)product >> 0xE;
    product *= voice->unk14;
    scale = product * voice->unk15;
    {
        register s32 volume ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        volume = scale >> 0xE;
        left_volume = volume;
        if (pan_value >= 0x40) {
            right_volume = volume;
            product = pan_value & 0x3F;
            scale = 0x40 - product;
            product = right_volume * 2;
            left_volume = (scale * product) >> 7;
        } else {
            s32 doubled_volume;
            doubled_volume = left_volume * 2;
            right_volume = (pan_value * doubled_volume) >> 7;
        }
    }

    {
        S_800561D8_D80086C00 *channel_gains = D_80086C00;
        S_800561D8_D80086C00 *gain_entry;
        pan_value = D_80086D50[0];
        gain_entry = &channel_gains[pan_value];
        product = left_volume * gain_entry->unk8;
        scale = gain_entry->unkA;
        pan_value = right_volume * scale;
        left_volume = product >> 7;
        right_volume = pan_value >> 7;
        voice->unk10 = (u16)((left_volume * (voice->unk1C & 0x7F)) >> 7);
        voice->unk12 = (u16)((right_volume * (voice->unk1C & 0x7F)) >> 7);
    }

    if (((u32)sound_params->unk2C) >= 0x40) {
        voice->unk10 = (u16)((voice->unk10 * voice->unk10) >> 14);
        voice->unk12 = (u16)((voice->unk12 * voice->unk12) >> 14);
    }
}
