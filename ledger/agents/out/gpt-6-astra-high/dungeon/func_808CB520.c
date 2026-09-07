#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800661B0(); /* extern */
s32 func_80122FA8();                             /* extern */

typedef struct S_801239B8_0 {
    u8 unk_00;
    u8 unk_01;
} S_801239B8_0;   /* var_s0 in func_801239B8 */

/* Draws two-byte character codes, advancing horizontally after each successful lookup. */
void func_801239B8(u8 *encodedText, s16 startX, s16 y) {
    s16 currentX;
    s32 glyph;
    u8 *cursor;
    u8 codeHigh;
    u8 codeLow;

    cursor = encodedText;
    currentX = startX;
    if (*cursor != 0) {
        do {
            codeHigh = ((S_801239B8_0 *)cursor)->unk_00;
            codeLow = ((S_801239B8_0 *)cursor)->unk_01;
            cursor += 2;
            glyph = func_80122FA8(codeLow | (codeHigh << 8));
            if (glyph != 0) {
                func_800661B0(glyph, 0, 0, currentX, (s32) y, 0xC, 0x10);
                currentX += 3;
            }
        } while (*cursor != 0);
    }
}
