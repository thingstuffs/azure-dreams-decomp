#include "shared/sound_state.h"
#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_800553D4.c, etc). */


/* CD attenuator-volume struct, matches libcd.h CdlATV. */
typedef struct CdlATV {
    u8 val0;
    u8 val1;
    u8 val2;
    u8 val3;
} CdlATV;

extern void func_8005A3D4(void);
extern int func_8005A3E0(void);
extern int CdMix(CdlATV *vol);

/* Applies the selected CD-audio mix and updates the corresponding status flags. */
void func_80055B44(unsigned char mix_mode) {
    CdlATV cd_volume;

    if (mix_mode == 1) {
        func_8005A3E0();
        cd_volume.val0 = cd_volume.val2 = 0x4F;
        cd_volume.val1 = cd_volume.val3 = 0x4F;
        D_800847D0.flags00 = (D_800847D0.flags00 & ~0x10) | 0x20;
    } else {
        func_8005A3D4();
        cd_volume.val0 = cd_volume.val2 = 0x7F;
        cd_volume.val1 = cd_volume.val3 = 0;
        D_800847D0.flags00 = (D_800847D0.flags00 & ~0x20) | 0x10;
    }

    CdMix(&cd_volume);
}
