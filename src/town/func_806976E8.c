#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80018BE8;
extern s32 D_80018BEC;

typedef struct S_806976E8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_806976E8_0;   /* D_80018BE8 in func_806976E8 */

s32 func_806976E8(void) {
    D_80018BEC = ((S_806976E8_0 *)D_80018BE8)->unk_24;
    return ((S_806976E8_0 *)D_80018BE8)->unk_20;
}
