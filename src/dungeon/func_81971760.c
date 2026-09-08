#include "common.h"
#include "m2c_compat.h"

extern u8 D_80045340[];
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800249E0;
extern M2C_UNK D_80025FE8;

typedef struct S_81971760_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    void * unk_40;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
} S_81971760_0;   /* temp_s0 in func_81971760 */

typedef struct S_81971760_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81971760_1;   /* temp_v0 in func_81971760 */

typedef struct S_81971760_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81971760_2;   /* temp_a3 in func_81971760 */

typedef struct S_81971760_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81971760_3;   /* temp_s1 in func_81971760 */

typedef struct S_81971760_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81971760_4;   /* temp_arg1 in func_81971760 */

void func_81971760(void *unused0, void *arg1, s32 unused2, s32 arg3, s32 arg4, s32 arg5) {
    register u16 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *temp_call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 temp_v1 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 temp_sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    s32 temp_rand;
    S_81971760_2 *temp_a3;
    S_81971760_0 *temp_s0;
    S_81971760_3 *temp_s1;
    void *temp_v0;
    S_81971760_4 *temp_arg1 = arg1;
    register s32 temp_arg3 ASM_REG("$17") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register s32 temp_s3 ASM_REG("$19") = *(volatile s32 *)&arg4;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 temp_s4 ASM_REG("$20") = *(volatile s32 *)&arg5;   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_call_a0 = temp_v0;
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_38 = 0x1E;
        temp_s0->unk_3A = 0x1E;
        ASM_KEEP4_NV(temp_arg3, temp_s0, temp_s3, temp_s4);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_s0->unk_44 = temp_arg3;
        temp_s0->unk_46 = (u16) temp_s3;
        temp_s0->unk_48 = (u16) temp_s4;
        temp_s0->unk_40 = temp_arg1;
        ((S_81971760_1 *)temp_v0)->unk_10 = &D_800249E0;
        func_8004491C(temp_call_a0, D_80045340);
        temp_a3 = ((S_81971760_1 *)temp_v0)->unk_0C;
        temp_a3->unk_10 = 0x20;
        temp_a3->unk_06 = 6;
        temp_a3->unk_14 = (u16) (temp_a3->unk_14 | 0xC);
        temp_s1 = ((S_81971760_1 *)temp_v0)->unk_08;
        temp_rand = func_80069EF8();
        temp_v1 = temp_s0->unk_44;
        temp_v1 -= 0x10;
        temp_s0->unk_44 = temp_v1 + (temp_rand & 0x1F);
        temp_rand = func_80069EF8();
        temp_v1 = temp_s0->unk_46;
        temp_v1 -= 0x10;
        temp_s0->unk_46 = temp_v1 + (temp_rand & 0x1F);
        temp_rand = func_80069EF8();
        temp_v1 = temp_s0->unk_48;
        temp_a0 = temp_s0->unk_44;
        temp_v1 -= 0x10;
        temp_s0->unk_48 = temp_v1 + (temp_rand & 0x1F);
        temp_s1->unk_02 = temp_a0;
        temp_s1->unk_06 = (u16) temp_s0->unk_46;
        temp_s1->unk_0A = (u16) temp_s0->unk_48;
        temp_v1 = temp_arg1->unk_02;
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        temp_sum = temp_a0;
        ASM_KEEP(temp_sum);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_sum = (u16) (temp_sum + temp_v1);
        temp_s1->unk_02 = temp_sum;
        temp_s1->unk_06 = (u16) (temp_s1->unk_06 + temp_arg1->unk_06);
        temp_s1->unk_0A = (u16) (temp_s1->unk_0A + temp_arg1->unk_0A);
        temp_a3 = ((S_81971760_1 *)temp_v0)->unk_0C;
        temp_a3->unk_1E = 0x800;
        temp_a3->unk_1C = 0x800;
        temp_a3->unk_0E = 0x80;
        temp_a3->unk_0D = 0x80;
        temp_a3->unk_0C = 0x80;
        memcpy((u8 *) temp_v0 + 0xA2, (u8 *) &D_80025FE8, 12);
        temp_a3->unk_08 = (void *) (temp_v0 + 0xA2);
    }
}
