#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C641C_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C641C_1;   /* arg0 in func_800C641C */

typedef struct S_800C641C_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C641C_2;   /* ((S_800C641C_1 *)arg0)->unk_80 in func_800C641C */




extern M2C_UNK D_800D5820;
extern M2C_UNK D_800D5844;

typedef struct S_800C641C_0 {
    u8 pad_00[0x7C];
    M2C_UNK ** unk_7C;
} S_800C641C_0;   /* arg0 in func_800C641C */

void func_800C641C(S_800C641C_0 *arg0) {
    *arg0->unk_7C = &D_800D5820;
    ((S_800C641C_2 *)(((S_800C641C_1 *)arg0)->unk_80))->unk_04 = &D_800D5844;
}
