#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009ED30_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8009ED30_0;   /* temp_v0 in func_8009ED30 */

typedef struct S_8009ED30_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009ED30_1;   /* temp_a2 in func_8009ED30 */

typedef struct S_8009ED30_2 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_8009ED30_2;   /* temp_v1 in func_8009ED30 */

typedef struct S_8009ED30_3 {
    u8 pad_00[0x3638];
    u16 unk_3638;
    u16 unk_363A;
    u16 unk_363C;
} S_8009ED30_3;   /* temp_page in func_8009ED30 */

typedef struct S_8009ED30_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    u16 unk_1E;
} S_8009ED30_4;   /* temp_a0 in func_8009ED30 */


void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern s32 D_80013630;
extern s32 D_80013634;
extern M2C_UNK D_8001363C;
extern M2C_UNK D_8009E038;
extern M2C_UNK D_8009E798;
extern M2C_UNK D_800DD7E0;
extern M2C_UNK D_800E296C;

void func_8009ED30(void) {
    void *temp_v0;

    if (!(D_800E296C & 0x80)) {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            ((S_8009ED30_0 *)temp_v0)->unk_10 = &D_8009E038;
            func_8004491C(temp_v0, &D_8009E798);
            {
            u16 temp_a1;
            void *temp_a0;
            register void *temp_a2 ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
            register s32 temp_a3 ASM_REG("$7");   /* MATCH pin: retail register colouring depends on it */
            void *temp_page;
            register void *temp_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

            temp_a2 = ((S_8009ED30_0 *)temp_v0)->unk_08;
            ((S_8009ED30_1 *)temp_a2)->unk_0A = -1;
            temp_v1 = ((S_8009ED30_0 *)temp_v0)->unk_0C;
            ((S_8009ED30_2 *)temp_v1)->unk_14 = 0xC;
            ((S_8009ED30_2 *)temp_v1)->unk_08 = &D_800DD7E0;
            ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
            temp_page = (void *) 0x80010000;
            ((S_8009ED30_2 *)temp_v1)->unk_1E = 0;
            ((S_8009ED30_2 *)temp_v1)->unk_1C = 0;
            temp_a1 = ((S_8009ED30_3 *)temp_page)->unk_363C;
            temp_a0 = temp_v0 + 0x20;
            ((S_8009ED30_4 *)temp_a0)->unk_1E = temp_a1;
            temp_a1 = ((S_8009ED30_3 *)temp_page)->unk_3638;
            ((S_8009ED30_1 *)temp_a2)->unk_02 = temp_a1;
            ((S_8009ED30_4 *)temp_a0)->unk_14 = temp_a1;
            ((S_8009ED30_1 *)temp_a2)->unk_06 = (*(u16 *)((u8 *)temp_page + 0x363A));
            ((S_8009ED30_4 *)temp_a0)->unk_16 = ((S_8009ED30_3 *)temp_page)->unk_363A;
            ((S_8009ED30_4 *)temp_a0)->unk_1A = 0x10;
            ((S_8009ED30_4 *)temp_a0)->unk_1C = 8;
            temp_a3 = 0x808080;
            ((S_8009ED30_2 *)temp_v1)->unk_0C = temp_a3;
            ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
            temp_page = (void *) D_80013630;
            ((S_8009ED30_2 *)temp_v1)->unk_18 = 0;
            ((S_8009ED30_2 *)temp_v1)->unk_16 = 0;
            ((S_8009ED30_2 *)temp_v1)->unk_18 = 0;
            ((S_8009ED30_2 *)temp_v1)->unk_16 = 0;
            ((S_8009ED30_4 *)temp_a0)->unk_04 = (s32) temp_page;
            ((S_8009ED30_4 *)temp_a0)->unk_0C = (s32) temp_page;
            temp_page = (void *) D_80013634;
            ((S_8009ED30_4 *)temp_a0)->unk_18 = 0;
            (*(s32 *)((u8 *)temp_a0 + 8)) = (s32) temp_page;
            (*(s32 *)((u8 *)temp_a0 + 0x10)) = (s32) temp_page;
            temp_v1 = (void *) D_800E296C;
            temp_page = (void *) 4;
            ((S_8009ED30_4 *)temp_a0)->unk_1C = (s16) (s32) temp_page;
            D_800E296C = (s32) temp_v1 | 0x80;
            }
        }
    }
}

/* MECHANISM: Direct D_800E296C RMW holds its page in s1, producing the 0x20 frame and retail save order.
   Post-call caller-register roles hold the 0x8001 page in v0, child/secondary/subobject in a2/v1/a0,
   and color in a3; reusing dead v0/v1 for the two globals, literal 4, and flag reload removes the tail nop. */
