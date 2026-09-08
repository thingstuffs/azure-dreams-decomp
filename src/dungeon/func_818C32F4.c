#include "common.h"

typedef struct S_818C32F4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C32F4_0;   /* temp_v0 in func_818C32F4 */

typedef struct S_818C32F4_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C32F4_1;   /* temp_v0_2 in func_818C32F4 */

typedef struct S_818C32F4_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C32F4_2;   /* temp_s0 in func_818C32F4 */

typedef struct S_818C32F4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xA];
    u16 unk_1A;
} S_818C32F4_3;   /* template_arg in func_818C32F4 */

typedef struct S_818C32F4_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_4;   /* arg1 in func_818C32F4 */

typedef struct S_818C32F4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_5;   /* temp_v1 in func_818C32F4 */



extern void func_80024C28() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern u8 D_80024A08[9];
extern u8 D_80025B38[9];
extern u8 D_80045C34[9];

s32 func_818C32F4(s32 *arg0, S_818C32F4_4 *arg1, void *arg2) {
    S_818C32F4_3 *template_arg = arg2;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    u16 temp_angle;
    void *temp_init;
    S_818C32F4_2 *temp_s0;
    void *temp_v0;
    S_818C32F4_1 *temp_v0_2;
    S_818C32F4_5 *temp_v1;

    temp_v0 = func_8003FC64(0x212);
    ASM_KEEP(template_arg);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    if (temp_v0 != 0) {
        ((S_818C32F4_0 *)temp_v0)->unk_10 = D_80024A08;
        ((S_818C32F4_0 *)temp_v0)->unk_20 = *arg0;
        temp_v0_2 = (u8 *)temp_v0 + 0x20;
        temp_v0_2->unk_04 = 0;
        temp_v0_2->unk_06 = 0;
        temp_s0 = ((S_818C32F4_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0C.at00.v = template_arg->unk_0C;
        if ((u8)temp_s0->unk_0C.at00.v != 0) {
            temp_s0->unk_0C.at00u.v = 0xC0;
        }
        if (temp_s0->unk_0C.at01.v != 0) {
            temp_s0->unk_0C.at01.v = 0xC0;
        }
        if (temp_s0->unk_0C.at02.v != 0) {
            temp_s0->unk_0C.at02.v = 0xC0;
        }
        temp_s0->unk_14 = temp_s0->unk_14 | 0xC;
        temp_s0->unk_10 = temp_s0->unk_10 | 0x60;
        func_8003DB94(temp_s0, D_80025B38, 0);
        temp_init = D_80045C34;
        temp_angle = template_arg->unk_1A;
        temp_s0->unk_1E = 0x1400;
        temp_s0->unk_1C = 0x1400;
        temp_s0->unk_1A = temp_angle;
        func_8004491C(temp_v0, temp_init);
        temp_v1 = ((S_818C32F4_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        result = (s32)temp_v0;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        temp_a0 = arg1->unk_00;
        temp_a1 = arg1->unk_04;
        temp_a2 = arg1->unk_08;
        temp_a3 = arg1->unk_0C;
        temp_v1->unk_00 = temp_a0;
        temp_v1->unk_04 = temp_a1;
        temp_v1->unk_08 = temp_a2;
        temp_v1->unk_0C = temp_a3;
        temp_a0 = arg1->unk_10;
        temp_a1 = arg1->unk_14;
        temp_v1->unk_10 = temp_a0;
        temp_v1->unk_14 = temp_a1;
        func_80024C28(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
