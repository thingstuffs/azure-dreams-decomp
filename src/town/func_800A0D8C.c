#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100A08;
typedef struct S_8009E4EC_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8009E4EC_0;   /* D_80100A08 in func_8009E4EC */

/* Returns the high-bit flag in the referenced object's unk_1E field. */
s32 func_8009E4EC(void) {
    return ((S_8009E4EC_0 *)D_80100A08)->unk_1E & 0x8000;
}
