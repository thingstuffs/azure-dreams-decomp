#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024320(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern u8 D_80024230[];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];

#ifndef NON_MATCHING
register u32 match_v0 ASM_REG("$2");
#endif

void *func_818A4A64(s32 arg0, void *arg1) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    register u8 *call_data ASM_REG("$5");
#ifdef NON_MATCHING
    u32 match_v0;
#endif

    temp_v0 = func_8003FC64(0x212);
#ifndef NON_MATCHING
    call_data = (u8 *) 0x800E0000;
#else
    call_data = D_800DEAE0;
#endif
    if (temp_v0 == NULL) {
        match_v0 = 0;
        func_80024320();
    }
#ifndef NON_MATCHING
    ASM_KEEP(call_data);
    call_data -= 0x1520;
    match_v0 = 0x80020000;
    ASM_KEEP(match_v0);
    match_v0 += 0x4230;
#else
    match_v0 = (u32) D_80024230;
#endif
    temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = (M2C_UNK *) match_v0;
    M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
    M2C_FIELD(temp_s0, s8 *, 0xE) = 0;
    M2C_FIELD(temp_s0, s8 *, 0xD) = 0;
    M2C_FIELD(temp_s0, s8 *, 0xC) = 0;
    func_8003DB94(temp_s0, call_data, 0);
    match_v0 = M2C_FIELD(temp_s0, u16 *, 0x14);
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    match_v0 |= 0xC;
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) match_v0;
    func_8004491C(temp_v0, D_80045340);
    temp_v1 = M2C_FIELD(temp_v0, void **, 8);
#ifndef NON_MATCHING
    __asm__ __volatile__("" : : "r"(arg1));
#endif
    match_v0 = M2C_FIELD(arg1, u16 *, 2);
    M2C_FIELD(temp_v1, u16 *, 2) = (u16) match_v0;
    match_v0 = M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(temp_v1, u16 *, 6) = (u16) match_v0;
    M2C_FIELD(temp_v1, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    return temp_v0;
}
