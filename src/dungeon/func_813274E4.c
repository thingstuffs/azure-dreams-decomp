#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016ECE4_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016ECE4_0;   /* base in func_8016ECE4 */

typedef struct S_8016ECE4_1 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0xA];
    void * unk_24;
    u8 pad_28[0x1C];
    s8 unk_44;
    s8 unk_45;
    s8 unk_46;
    s8 unk_47;
    s8 unk_48;
    s8 unk_49;
    u8 pad_4A[0x2];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_8016ECE4_1;   /* temp_s1 in func_8016ECE4 */

typedef struct S_8016ECE4_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_8016ECE4_2;   /* temp_v0 in func_8016ECE4 */

typedef struct S_8016ECE4_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016ECE4_3;   /* temp_a0 in func_8016ECE4 */

typedef struct S_8016ECE4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8016ECE4_4;   /* temp_v1 in func_8016ECE4 */

typedef struct S_8016ECE4_5 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016ECE4_5;   /* temp_s2 in func_8016ECE4 */

typedef struct S_8016ECE4_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x7E];
    s16 unk_AA;
} S_8016ECE4_6;   /* temp_s3 in func_8016ECE4 */


typedef struct {
    s16 field0;
    s16 field2;
} TableEntry;

void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern u8 D_80013611[];
extern M2C_UNK D_80045340;
extern M2C_UNK D_800777F4;
extern M2C_UNK D_8016E528;
extern void *D_80174704[];
extern TableEntry D_80174708[];

void func_8016ECE4(void) {
    volatile s32 frame_pad[2];
    s32 var_v0;
    s32 var_v0_2;
    u32 mode;
    u32 page;
    u32 one;
    register S_8016ECE4_3 *temp_a0;
    S_8016ECE4_1 *temp_s1;
    S_8016ECE4_5 *temp_s2;
    S_8016ECE4_6 *temp_s3;
    void *temp_v0;
    S_8016ECE4_4 *temp_v1;
    void *base;

    base = D_80174704[0];
    page = 0x80010000;
    ASM_KEEP_NV(page);   /* MATCH pin: keeps a constant in a register as retail does */
    one = 1;
    ASM_KEEP_DEP_NV(one, base);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_SCHED_BARRIER();   /* MATCH pin: retail immediate-load split depends on it */
    mode = page;
    mode = *(u8 *)(mode + 0x3611);
    ASM_KEEP_NV(mode);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s2 = ((S_8016ECE4_0 *)base)->unk_08;
    temp_s3 = base + 0x20;
    if (((mode & 3) == one) && !(func_80069EF8(base) & 1)) {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_s1 = temp_v0 + 0x20;
            temp_s1->unk_12 = 3;
            ((S_8016ECE4_2 *)temp_v0)->unk_10 = &D_8016E528;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = ((S_8016ECE4_2 *)temp_v0)->unk_0C;
            temp_a0->unk_14 = (u16) (temp_a0->unk_14 & 0xFFF3);
            temp_s1->unk_24 = temp_s3;
            temp_v1 = ((S_8016ECE4_2 *)temp_v0)->unk_08;
            temp_v1->unk_02 = (u16) temp_s2->unk_02.s;
            temp_v1->unk_06 = (u16) temp_s2->unk_06.s;
            temp_v1->unk_0A = (s16) (temp_s2->unk_0A - 0x80);
            temp_s1->unk_50 = 0;
            temp_s1->unk_4C = 0;
            temp_s1->unk_54 = 0;
            temp_s1->unk_60 = 0;
            temp_s1->unk_18 = (s16) (((u16) temp_s3->unk_2A >> 9) & 7);
            temp_a0 = ((S_8016ECE4_2 *)temp_v0)->unk_0C;
            temp_a0->unk_1E = 0x1000;
            temp_a0->unk_1C = 0x1000;
            temp_a0->unk_06 = (s16) (D_80174708[((u16) temp_s3->unk_2A >> 9) & 7].field2 * 6);
            temp_s3->unk_AA = 0x4D;
            var_v0 = temp_s2->unk_02.u;
            if (var_v0 < 0) {
                var_v0 += 0x3F;
            }
            temp_s1->unk_48 = (s8) (var_v0 >> 6);
            var_v0_2 = temp_s2->unk_06.u;
            if (var_v0_2 < 0) {
                var_v0_2 += 0x3F;
            }
            temp_s1->unk_49 = (s8) (var_v0_2 >> 6);
            temp_a0->unk_0E = 0x80;
            temp_a0->unk_0D = 0x80;
            temp_a0->unk_0C = 0x80;
            temp_a0->unk_08 = &D_800777F4;
            temp_a0->unk_14 = (u16) (temp_a0->unk_14 | 0x80);
            temp_s1->unk_44 = 3;
            temp_s1->unk_45 = 6;
            temp_s1->unk_46 = 0;
            temp_s1->unk_47 = 0;
        }
    }
}
