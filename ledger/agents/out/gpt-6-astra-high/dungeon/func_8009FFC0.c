#include "common.h"

extern s32 func_800353F4(s8 *arg0);
extern u16 D_80013714;

typedef struct S_800A5720_0 {
    u8 unk_00;
    u8 unk_01;
} S_800A5720_0;   /* var_a1 in func_800A5720 */

/* When enabled, uppercase a fullwidth Latin letter after the ASCII prefix and process the text. */
s32 func_800A5720(s8 *text) {
    s8 *cursor;
    u8 trail_byte;

    if (!(D_80013714 & 2)) {
        cursor = text;
        if (*text > 0) {
            do {
                cursor += 1;
            } while (*cursor > 0);
        }
        if (((S_800A5720_0 *)cursor)->unk_00 == 0x82) {
            trail_byte = ((S_800A5720_0 *)cursor)->unk_01;
            if ((u32) ((trail_byte + 0x7F) & 0xFF) < 0x1AU) {
                ((S_800A5720_0 *)cursor)->unk_01 = (u8) (trail_byte - 0x21);
            }
        }
        return func_800353F4(text);
    }
    return 0;
}
