#include "common.h"

typedef struct {
    s32 unk00;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s8  pad0C[0x1C];
} S_8005A5C8_Snd;

extern void func_8005EDA0(S_8005A5C8_Snd *arg0);

/* Applies left and right sound volumes scaled by 128 with zero volume modes. */
void func_8005A5C8(s32 left_volume, s32 right_volume)
{
    S_8005A5C8_Snd sound_params;

    sound_params.unk00 = 0xF;
    sound_params.unk04 = left_volume << 7;
    sound_params.unk06 = right_volume << 7;
    sound_params.unk08 = 0;
    sound_params.unk0A = 0;
    func_8005EDA0(&sound_params);
}
