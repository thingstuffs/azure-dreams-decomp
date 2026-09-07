#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80093C70_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80093C70_0;   /* temp_v0 in func_80093C70 */

typedef struct S_80093C70_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80093C70_1;   /* temp_v1 in func_80093C70 */


typedef struct S_80093C70_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    union { volatile u16 s; u16 u; } unk_14;   /* accessed as both */
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80093C70_3;   /* temp_s0 in func_80093C70 */


typedef struct S_80093C70_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_80093C70_5;   /* temp_v1_2 in func_80093C70 */


void *func_8003FD64();                  /* extern */
M2C_UNK func_8004491C();           /* extern */
M2C_UNK func_80048A44(); /* extern */
extern M2C_UNK D_80045340;
extern u16 D_80082E94;
extern M2C_UNK D_80093A94;

void func_80093C70(s32 arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2) {
    S_80093C70_3 *temp_s0;
    void *temp_v0;
    S_80093C70_1 *temp_v1;
    S_80093C70_5 *temp_v1_2;
    u16 temp_flags;

    temp_v0 = func_8003FD64(0x310, arg0 - 0x20);
    if (temp_v0 != NULL) {
        temp_v1 = ((S_80093C70_0 *)temp_v0)->unk_08;
        ((S_80093C70_0 *)temp_v0)->unk_10 = &D_80093A94;
        temp_v1->unk_02 = (u16) arg1->unk_00.at02_u16.v;
        temp_v1->unk_06 = (u16) arg1->unk_04.at02_u16.v;
        temp_v1->unk_0A = (u16) arg1->unk_08.at02_u16.v;
        temp_s0 = ((S_80093C70_0 *)temp_v0)->unk_0C;
        temp_s0->unk_28 = (s32) arg2->unk_28.at00_s32.v;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_flags = temp_s0->unk_14.s;
        temp_s0->unk_06 = 4;
        temp_s0->unk_14.u = (u16) (temp_flags | 0x200);
        ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        if (D_80082E94 & 1) {
            temp_s0->unk_14.u = (u16) (temp_s0->unk_14.u | 1);
        }
        func_80048A44(temp_s0, 0xCE, 0, 3);
        func_8004491C(temp_v0, &D_80045340);
        temp_v1_2 = temp_v0 + 0x20;
        ((S_80093C70_0 *)temp_v0)->unk_20 = arg2;
        temp_v1_2->unk_06 = 0x10;
        temp_s0->unk_0C = 0x2C808080;
        temp_v1_2->unk_08 = 1;
    }
}
/* MECHANISM: The natural three-pointer lifetimes reproduce retail's 0x20 frame
   and s0/s2/s1 save contract. A volatile first flags read fixes load placement;
   ASM_MEM_BARRIER forces the second lhu while preserving the branch-delay move. */
