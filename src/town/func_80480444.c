#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019540;
extern s32 D_80019544;

typedef struct S_80480444_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80480444_0;   /* D_80019540 in func_80480444 */

/* Save the referenced object's unk_24 in D_80019544 and return its unk_20. */
s32 func_80480444(void) {
    D_80019544 = ((S_80480444_0 *)D_80019540)->unk_24;
    return ((S_80480444_0 *)D_80019540)->unk_20;
}
