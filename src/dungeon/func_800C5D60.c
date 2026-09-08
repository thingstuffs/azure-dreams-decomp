#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB4C0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800CB4C0_6;   /* arg0 in func_800CB4C0 */

typedef struct S_800CB4C0_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB4C0_7;   /* ((S_800CB4C0_6 *)arg0)->unk_08 in func_800CB4C0 */




M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800CB374;
extern M2C_UNK D_800E02CC;

typedef struct S_800CB4C0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CB4C0_0;   /* temp_v0 in func_800CB4C0 */

typedef struct S_800CB4C0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800CB4C0_1;   /* temp_s0 in func_800CB4C0 */

typedef struct S_800CB4C0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB4C0_2;   /* arg0 in func_800CB4C0 */

typedef struct S_800CB4C0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB4C0_3;   /* temp_v1 in func_800CB4C0 */

typedef struct S_800CB4C0_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800CB4C0_4;   /* temp_v0_3 in func_800CB4C0 */

typedef struct S_800CB4C0_5 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB4C0_5;   /* temp_v0_2 in func_800CB4C0 */

void *func_800CB4C0(void *arg0, s16 arg1) {
    s32 temp_s32;
    S_800CB4C0_1 *temp_s0;
    void *temp_v0;
    S_800CB4C0_5 *temp_v0_2;
    S_800CB4C0_4 *temp_v0_3;
    S_800CB4C0_3 *temp_v1;

    temp_v0 = func_8003FD64(0x100, arg0);
    if (temp_v0 != NULL) {
        ((S_800CB4C0_0 *)temp_v0)->unk_10 = &D_800CB374;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = ((S_800CB4C0_0 *)temp_v0)->unk_0C;
        func_8003DB94(temp_s0, &D_800E02CC, 0);
        temp_s0->unk_1E = 0x1400;
        temp_s0->unk_1C = 0x1400;
        temp_s0->unk_10 = 0x20;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        if ((arg1 << 0x10) == 0) {
            ((S_800CB4C0_0 *)temp_v0)->unk_08 = ((S_800CB4C0_2 *)arg0)->unk_08;
        } else {
            temp_v1 = ((S_800CB4C0_0 *)temp_v0)->unk_08;
            temp_v1->unk_02 = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)arg0)->unk_08))->unk_02;
            temp_v1->unk_06 = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)arg0)->unk_08))->unk_06;
            temp_v1->unk_0A = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)arg0)->unk_08))->unk_0A;
            temp_v0_3 = ((S_800CB4C0_2 *)arg0)->unk_0C;
            temp_s32 = temp_v0_3->unk_0C;
            temp_s0->unk_10 = 0x60;
            temp_s0->unk_0C = temp_s32;
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_s0->unk_06 = -1;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v0_2 = temp_v0 + 0x20;
        ASM_KEEP(temp_v0_2);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v0_2->unk_A8 = arg0;
        temp_v0_2->unk_B4 = arg1;
        temp_v0_2->unk_96 = 8;
    }
    return temp_v0;
}
/* MECHANISM: The zero-arg tail arm copies arg0->8 into the allocation before LEAD 22.
   Split $v0/$v1 load names and a pinned +0x20 base reproduce the retail live ranges.
   Two zero-word fences hold the final stores/base birth; one kept return joins both paths. */
