#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#ifdef NON_MATCHING
#define ASM_DEP(var) ((void)0)
#else
#define ASM_DEP(var) __asm__("" : "+r"(var))
#endif

extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80065420();
extern s32 func_800A8C84();

typedef struct S_800A8CA8_0 {
    u8 pad_00[0x74];
    u16 unk_74;
    u16 unk_76;
    u8 pad_78[0x4];
    u16 unk_7C;
    u16 unk_7E;
    u16 unk_80;
    u8 pad_82[0x2];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u8 pad_8A[0x3A];
    s32 unk_C4;
    u8 pad_C8[0x4C];
    s8 unk_114;
    s8 unk_115;
    s8 unk_116;
} S_800A8CA8_0;   /* arg0 in func_800A8CA8 */

typedef struct S_800A8CA8_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} S_800A8CA8_1;   /* temp_src in func_800A8CA8 */

typedef struct S_800A8CA8_2 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
} S_800A8CA8_2;   /* arg3 in func_800A8CA8 */

void func_800A8CA8(void *arg0, s32 arg1, void *arg2, S_800A8CA8_2 *arg3) {
    register S_800A8CA8_1 *temp_src ASM_REG("$18");   /* MATCH pin: load-bearing for the whole function shape */
    u32 temp_arg1;
    s32 temp_a1;
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    s32 temp_s1;
    s32 temp_s4;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s2;
    void *temp_s5;
    void *temp_s6;
    u16 temp_v0_6;

    temp_src = arg2;
    ASM_DEP(temp_src);   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_arg1 = (u32) arg1 + 0x800;
    temp_arg1 <<= 16;
    temp_a1 = (s32) temp_arg1 >> 16;
    temp_s0 = temp_a1 * 2;
    ((S_800A8CA8_0 *)arg0)->unk_114 = (s8) ((func_800644B8(temp_src->unk_0E + temp_s0) + 0x1000) / 128);
    ((S_800A8CA8_0 *)arg0)->unk_115 = (s8) ((func_800644B8(temp_src->unk_12 + temp_s0) + 0x1000) / 128);
    ((S_800A8CA8_0 *)arg0)->unk_116 = (s8) ((func_800644B8(temp_src->unk_16 + temp_s0) + 0x1000) / 128);
    temp_s0_2 = arg0 + 0x74;
    func_800A8C84(temp_s0_2, temp_src);
    temp_s5 = arg0 + 0x7C;
    func_800A8C84(temp_s5, temp_src);
    temp_s6 = arg0 + 0x84;
    func_800A8C84(temp_s6, temp_src);
    temp_s4 = (func_800644B8(temp_a1) * arg3->unk_1C) / 4096;
    temp_s1 = (func_80064584(temp_a1) * arg3->unk_1E) / 4096;
    temp_s0_3 = arg0 + 0x94;
    temp_s2 = arg0 + 0x98;
    ((S_800A8CA8_0 *)arg0)->unk_74 = (u16) (((S_800A8CA8_0 *)arg0)->unk_74 + temp_s4);
    ((S_800A8CA8_0 *)arg0)->unk_76 = (u16) (((S_800A8CA8_0 *)arg0)->unk_76 + temp_s1);
    ((S_800A8CA8_0 *)arg0)->unk_C4 = func_80065420(temp_s0_2, arg0 + 0xE8, temp_s0_3, temp_s2);
    ((S_800A8CA8_0 *)arg0)->unk_7C = (u16) (((S_800A8CA8_0 *)arg0)->unk_7C + temp_s4);
    ((S_800A8CA8_0 *)arg0)->unk_7E = (u16) (((S_800A8CA8_0 *)arg0)->unk_7E + temp_s1);
    temp_v0_6 = arg3->unk_20;
    ((S_800A8CA8_0 *)arg0)->unk_80 = (u16) (((S_800A8CA8_0 *)arg0)->unk_80 + ((s16) temp_v0_6 / 2));
    ((S_800A8CA8_0 *)arg0)->unk_C4 = ((((S_800A8CA8_0 *)arg0)->unk_C4 + func_80065420(temp_s5, arg0 + 0xEC, temp_s0_3, temp_s2)) / 2) - 8;
    ((S_800A8CA8_0 *)arg0)->unk_84 = (u16) (((S_800A8CA8_0 *)arg0)->unk_84 + temp_s4);
    ((S_800A8CA8_0 *)arg0)->unk_86 = (u16) (((S_800A8CA8_0 *)arg0)->unk_86 + temp_s1);
    ((S_800A8CA8_0 *)arg0)->unk_88 = (u16) (((S_800A8CA8_0 *)arg0)->unk_88 + arg3->unk_20);
    func_80065420(temp_s6, arg0 + 0x124, temp_s0_3, temp_s2);
}
