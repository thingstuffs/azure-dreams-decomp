#include "common.h"

/* extern/typedef decls */
/* D_80085FA4: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (slusReadNextByteAndFinish, func_800599B0, scanStreamForThreeByteMarker, func_80058B70) -> declare size > 8 bytes. */
extern s32 D_80085FA4[4];

/* D_800869B0: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (slusReadNextByteAndFinish, scanStreamForThreeByteMarker, func_80058B70) -> declare size > 8 bytes. */
extern s32 D_800869B0[4];

/* D_800737A4: hi/lo access -> size must be > 8 bytes (see func_800584E4 in src/code.c) */
extern s32 D_800737A4[4];

extern void audioResetAllVoices(void);
extern void func_800599B0(void);

/* Sets the byte table base and bound, initializes two subsystems, and marks them active. */
void audioInitializeResidentSequence(void)
{
    D_80085FA4[0] = 0x80080000;
    D_800869B0[0] = 0xC000;
    audioResetAllVoices();
    func_800599B0();
    D_800737A4[0] = 1;
}
