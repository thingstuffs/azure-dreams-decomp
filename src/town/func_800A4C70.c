#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A23D0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0xE];
    s16 unk_1A;
} S_800A23D0_0;   /* arg2 in func_800A23D0 */

typedef struct S_800A23D0_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_800A23D0_1;   /* arg1 in func_800A23D0 */

typedef struct S_800A23D0_2 {
    M2C_UNK * unk_00;
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A23D0_2;   /* arg0 in func_800A23D0 */

typedef struct S_800A23D0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A23D0_3;   /* ((S_800A23D0_2 *)arg0)->unk_14 in func_800A23D0 */


extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;
extern M2C_UNK D_800A24A8;
extern M2C_UNK D_800D0A48;

void func_800A23D0(void *arg0, S_800A23D0_1 *arg1, S_800A23D0_0 *arg2) {
    M2C_UNK *table;
    arg2->unk_00 = 0;
    arg2->unk_04 = 0;
    arg2->unk_05 = 0;
    func_8004491C(arg0 - 0x20, &D_80046398);
    arg1->unk_00.at00.v = (s32) ((S_800A23D0_3 *)(((S_800A23D0_2 *)arg0)->unk_14))->unk_00;
    arg1->unk_04.at00.v = (s32) ((S_800A23D0_3 *)(((S_800A23D0_2 *)arg0)->unk_14))->unk_04;
    arg1->unk_08 = (s32) ((S_800A23D0_3 *)(((S_800A23D0_2 *)arg0)->unk_14))->unk_08;
    ((S_800A23D0_2 *)arg0)->unk_00 = &D_800A24A8;
    table = &D_800D0A48;
    arg2->unk_08 = (s32) table[((S_800A23D0_2 *)arg0)->unk_20];
    arg1->unk_00.at02.v = (u16) (arg1->unk_00.at02.v + 0x28);
    arg1->unk_04.at02.v = (u16) (arg1->unk_04.at02.v - 8);
    arg2->unk_1A = 0;
}
