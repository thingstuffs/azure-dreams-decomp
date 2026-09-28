#include "common.h"
#include "shared/sound_volume.h"

extern void func_8005BAB0(void);
extern s32 func_80055750(s16 arg0);
extern s32 func_8003E14C(void);
extern s32 func_8005B4D0(s32 a0, void *a1, u16 a2, u16 a3, s32 a4);

extern u16 D_800847EE[8];   /* size>8 forces %hi/%lo addressing */

/* Scales D_800847EE's level by volume scale [0] and starts the voices with a primary and an optional secondary gain. */
void func_8005560C(s32 target_id, void *target_data)
{
    s32 scale_value;
    s32 primary_amount;
    s32 secondary_amount;

    func_8005BAB0();

    scale_value = D_800847EE[0] * volumeScale[0];
    primary_amount = func_80055750((s16)(scale_value / 32767));

    scale_value = func_8003E14C();
    secondary_amount = (scale_value * (volumeScale[0] + volumeScale[0])) / 32767;

    if (secondary_amount == 0) {
        func_8005B4D0(target_id, target_data, primary_amount, primary_amount, 0);
    } else {
        primary_amount -= secondary_amount;
        func_8005B4D0(target_id, target_data, primary_amount, primary_amount, 0);
        func_8005B4D0(target_id, target_data, secondary_amount, secondary_amount, 1);
    }
}
