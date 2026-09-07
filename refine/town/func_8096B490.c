#include "common.h"
#include "m2c_compat.h"

s32 func_8004D880();                             /* extern */
M2C_UNK func_8004D91C();              /* extern */
M2C_UNK func_800673A0();         /* extern */

typedef struct S_80123928_0 {
    u8 unk_00;
    u8 unk_01;
} S_80123928_0;   /* var_s0 in func_80123928 */

/* Outputs two-byte character codes, advancing the position by two per character. */
void func_80123928(u8 *text, s16 start_x, s16 y) {
    M2C_UNK glyph;
    s16 x;
    u8 *cursor;
    u8 code_hi;
    u8 code_lo;

    cursor = text;
    x = start_x;
    if (*cursor != 0) {
        do {
            code_hi = ((S_80123928_0 *)cursor)->unk_00;
            code_lo = ((S_80123928_0 *)cursor)->unk_01;
            cursor += 2;
            func_8004D91C(func_8004D880(code_lo | (code_hi << 8)) & 0xFF, &glyph);
            func_800673A0(&glyph, x, y);
            x += 2;
        } while (*cursor != 0);
    }
}
