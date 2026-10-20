#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AB14_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_8003AB14_0;   /* arg0 in func_8003AB14 */

typedef struct S_8003AB14_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_8003AB14_1;   /* arg1 in func_8003AB14 */


/* Copies four halfwords from the source record into the destination. */
void func_8003AB14(S_8003AB14_0 *dest, S_8003AB14_1 *source) {
    dest->unk_00 = (u16) source->unk_04;
    dest->unk_02 = (u16) source->unk_06;
    dest->unk_04 = (u16) source->unk_08;
    dest->unk_06 = (u16) source->unk_0A;
}
