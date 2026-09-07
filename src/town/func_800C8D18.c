#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C6478_0 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C6478_0;   /* arg0 in func_800C6478 */

typedef struct S_800C6478_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C6478_1;   /* ((S_800C6478_0 *)arg0)->unk_80 in func_800C6478 */




extern M2C_UNK D_800D5930;


void func_800C6478(S_800C6478_0 *arg0) {
    ((S_800C6478_1 *)(arg0->unk_80))->unk_04 = &D_800D5930;
}
