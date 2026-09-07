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

void func_800A8CA8(void *arg0, s32 arg1, void *arg2, void *arg3) {
    register void *temp_src ASM_REG("$18");
    register u32 temp_arg1 ASM_REG("$5");
    register s32 temp_a1 ASM_REG("$17");
    register s32 temp_s0 ASM_REG("$16");
    s32 temp_s1;
    s32 temp_s4;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s2;
    void *temp_s5;
    void *temp_s6;
    u16 temp_v0_6;

    temp_src = arg2;
    ASM_DEP(temp_src);
    temp_arg1 = (u32) arg1 + 0x800;
    temp_arg1 <<= 16;
    temp_a1 = (s32) temp_arg1 >> 16;
    temp_s0 = temp_a1 * 2;
    M2C_FIELD(arg0, s8 *, 0x114) = (s8) ((func_800644B8(M2C_FIELD(temp_src, s16 *, 0xE) + temp_s0) + 0x1000) / 128);
    M2C_FIELD(arg0, s8 *, 0x115) = (s8) ((func_800644B8(M2C_FIELD(temp_src, s16 *, 0x12) + temp_s0) + 0x1000) / 128);
    M2C_FIELD(arg0, s8 *, 0x116) = (s8) ((func_800644B8(M2C_FIELD(temp_src, s16 *, 0x16) + temp_s0) + 0x1000) / 128);
    temp_s0_2 = arg0 + 0x74;
    func_800A8C84(temp_s0_2, temp_src);
    temp_s5 = arg0 + 0x7C;
    func_800A8C84(temp_s5, temp_src);
    temp_s6 = arg0 + 0x84;
    func_800A8C84(temp_s6, temp_src);
    temp_s4 = (func_800644B8(temp_a1) * M2C_FIELD(arg3, u16 *, 0x1C)) / 4096;
    temp_s1 = (func_80064584(temp_a1) * M2C_FIELD(arg3, u16 *, 0x1E)) / 4096;
    temp_s0_3 = arg0 + 0x94;
    temp_s2 = arg0 + 0x98;
    M2C_FIELD(arg0, u16 *, 0x74) = (u16) (M2C_FIELD(arg0, u16 *, 0x74) + temp_s4);
    M2C_FIELD(arg0, u16 *, 0x76) = (u16) (M2C_FIELD(arg0, u16 *, 0x76) + temp_s1);
    M2C_FIELD(arg0, s32 *, 0xC4) = func_80065420(temp_s0_2, arg0 + 0xE8, temp_s0_3, temp_s2);
    M2C_FIELD(arg0, u16 *, 0x7C) = (u16) (M2C_FIELD(arg0, u16 *, 0x7C) + temp_s4);
    M2C_FIELD(arg0, u16 *, 0x7E) = (u16) (M2C_FIELD(arg0, u16 *, 0x7E) + temp_s1);
    temp_v0_6 = M2C_FIELD(arg3, u16 *, 0x20);
    M2C_FIELD(arg0, u16 *, 0x80) = (u16) (M2C_FIELD(arg0, u16 *, 0x80) + ((s16) temp_v0_6 / 2));
    M2C_FIELD(arg0, s32 *, 0xC4) = ((M2C_FIELD(arg0, s32 *, 0xC4) + func_80065420(temp_s5, arg0 + 0xEC, temp_s0_3, temp_s2)) / 2) - 8;
    M2C_FIELD(arg0, u16 *, 0x84) = (u16) (M2C_FIELD(arg0, u16 *, 0x84) + temp_s4);
    M2C_FIELD(arg0, u16 *, 0x86) = (u16) (M2C_FIELD(arg0, u16 *, 0x86) + temp_s1);
    M2C_FIELD(arg0, u16 *, 0x88) = (u16) (M2C_FIELD(arg0, u16 *, 0x88) + M2C_FIELD(arg3, u16 *, 0x20));
    func_80065420(temp_s6, arg0 + 0x124, temp_s0_3, temp_s2);
}
