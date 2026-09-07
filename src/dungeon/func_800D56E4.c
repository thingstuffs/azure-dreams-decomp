#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_800DAE44_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DAE44_3;   /* temp_v0 in func_800DAE44 */

typedef struct S_800DAE44_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800DAE44_4;   /* ((S_800DAE44_3 *)temp_v0)->unk_08 in func_800DAE44 */




void *func_8003FD64();            /* extern */
s16 func_800BCB04();                   /* extern */
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DAEF4;

typedef struct S_800DAE44_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800DAE44_0;   /* temp_v0 in func_800DAE44 */


typedef struct S_800DAE44_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
} S_800DAE44_2;   /* temp_s0 in func_800DAE44 */

void func_800DAE44(Rec_D_800E3D7C *arg0, s16 arg1) {
    S_800DAE44_2 *temp_s0;
    void *temp_v0;

    temp_v0 = func_8003FD64(0x312, &D_80083498);
    if (temp_v0 != NULL) {
        ((S_800DAE44_0 *)temp_v0)->unk_10 = &D_800DAEF4;
        ((S_800DAE44_4 *)(((S_800DAE44_3 *)temp_v0)->unk_08))->unk_02 = (u16) arg0->unk_00.at02_u16.v;
        ((S_800DAE44_4 *)(((S_800DAE44_3 *)temp_v0)->unk_08))->unk_06 = (u16) arg0->unk_04.at02_u16.v;
        temp_s0 = temp_v0 + 0x20;
        ((S_800DAE44_4 *)(((S_800DAE44_3 *)temp_v0)->unk_08))->unk_0A = (u16) arg0->unk_08.at02_u16.v;
        temp_s0->unk_10 = func_800BCB04(arg0->unk_00.at02_u16.v, arg0->unk_04.at02_u16.v, (s16) (arg0->unk_08.at02_u16.v - 0x80));
        temp_s0->unk_48 = arg1;
    }
}
