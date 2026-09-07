#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800661B0(); /* extern */
s32 func_80122FA8();                             /* extern */

typedef struct S_801239B8_0 {
    u8 idHigh;
    u8 idLow;
} S_801239B8_0;   /* var_s0 in func_801239B8 */

/* Resolves each two-byte ID and places the resulting objects three units apart. */
void func_801239B8(u8 *encodedIds, s16 startPosition, s16 fixedPosition) {
    s16 currentPosition;
    s32 object;
    u8 *entry;
    u8 idHigh;
    u8 idLow;

    entry = encodedIds;
    currentPosition = startPosition;
    if (*entry != 0) {
        do {
            idHigh = ((S_801239B8_0 *)entry)->idHigh;
            idLow = ((S_801239B8_0 *)entry)->idLow;
            entry += 2;
            object = func_80122FA8(idLow | (idHigh << 8));
            if (object != 0) {
                func_800661B0(object, 0, 0, currentPosition, (s32) fixedPosition, 0xC, 0x10);
                currentPosition += 3;
            }
        } while (*entry != 0);
    }
}
