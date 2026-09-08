#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D7D0_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8009D7D0_0;   /* var_a0 in func_8009D7D0 */

/* Clear each record's first byte until the end marker is reached. */
void func_8009D7D0(s8 *records) {
    s8 *record;

    record = records;
    if ((((S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80) {
        do {
            *record = 0;
            record += 0x14;
        } while ((((S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80);
    }
}
