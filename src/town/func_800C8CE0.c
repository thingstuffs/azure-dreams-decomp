#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C6440_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C6440_1;   /* arg0 in func_800C6440 */

typedef struct S_800C6440_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C6440_2;   /* ((S_800C6440_1 *)arg0)->unk_80 in func_800C6440 */




extern M2C_UNK D_800D58B8;

typedef struct S_800C6440_0 {
    u8 pad_00[0x7C];
    M2C_UNK ** unk_7C;
} S_800C6440_0;   /* arg0 in func_800C6440 */

void func_800C6440(S_800C6440_0 *arg0) {
    *arg0->unk_7C = &D_800D58B8;
    ((S_800C6440_2 *)(((S_800C6440_1 *)arg0)->unk_80))->unk_04 = &D_800D58B8;
}
