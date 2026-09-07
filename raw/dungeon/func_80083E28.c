#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 *D_80083160;
extern u8 D_801C9E40[16];
M2C_UNK func_8006658C(void *, void *);
M2C_UNK func_80067E2C();
M2C_UNK func_80067EF4();
M2C_UNK func_80067F20();
extern void func_80089654(void) __attribute__((noreturn));

void func_80089588(void) {
    s32 sp18[2];
    s32 temp_s0;
    register s32 temp_s3 ASM_REG("$19");
    u16 temp_v0;
    u16 temp_v0_3;
    void *temp_s2;
    register u32 temp_s1 ASM_REG("$17");

    temp_s0 = (s32) D_80083160 != (s32) D_801C9E40;
    temp_s2 = M2C_FIELD(D_80083160, void **, 0x8D0);
    func_80067E2C(temp_s2, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067E2C(temp_s2, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x830, temp_s2);
    temp_s2 += 0xC;
    func_80067EF4(temp_s2, 0, 0);
    func_8006658C((u8 *)D_80083160 + 0x830, temp_s2);
    temp_s2 += 0xC;
    {
        register s32 cmd_value ASM_REG("$2");
        do { cmd_value = 0x2A000000; } while (0);
        M2C_FIELD(temp_s2, volatile s32 *, 4) = cmd_value;
        cmd_value = 1;
        M2C_FIELD(temp_s2, volatile s16 *, 0x10) = cmd_value;
        M2C_FIELD(temp_s2, volatile s16 *, 8) = cmd_value;
        cmd_value = 0x100;
        M2C_FIELD(temp_s2, volatile s16 *, 0x14) = cmd_value;
        M2C_FIELD(temp_s2, s16 *, 0xC) = cmd_value;
    }
    temp_s1 = (u32) &D_80083160;
    ASM_KEEP_NV(temp_s1);
    temp_s3 = temp_s0;
    if (temp_s0 != 0) {
        register s32 tail_value ASM_REG("$2");
        tail_value = 0xE0;
        ASM_TAILSLOT_PIN(tail_value);
        func_80089654();
        return;
    }
    {
        register s32 first_value;
        first_value = 0x1C0;
        M2C_FIELD(temp_s2, volatile u16 *, 0xE) = first_value;
        ASM_KEEP(temp_s2);
    }
    temp_v0 = M2C_FIELD(temp_s2, volatile u16 *, 0xE);
    M2C_FIELD(temp_s2, volatile s8 *, 3) = 5;
    M2C_FIELD(temp_s2, volatile u16 *, 0xA) = temp_v0;
    M2C_FIELD(temp_s2, volatile s16 *, 0x16) = temp_v0 + 0xE;
    M2C_FIELD(temp_s2, volatile s16 *, 0x12) = temp_v0 + 0xE;
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x830, temp_s2);
    temp_s2 += 0x18;
    {
        register s32 cmd_value ASM_REG("$2");
        cmd_value = 0x2A000000;
        M2C_FIELD(temp_s2, volatile s32 *, 4) = cmd_value;
        cmd_value = 1;
        M2C_FIELD(temp_s2, volatile s16 *, 0x10) = cmd_value;
        M2C_FIELD(temp_s2, volatile s16 *, 8) = cmd_value;
        cmd_value = 0x100;
        M2C_FIELD(temp_s2, volatile s16 *, 0x14) = cmd_value;
        M2C_FIELD(temp_s2, volatile s16 *, 0xC) = cmd_value;
    }
    ASM_KEEP(temp_s3);
    {
        register s32 packet_width ASM_REG("$2");
        packet_width = temp_s3;
        ASM_KEEP_NV(packet_width);
        if (packet_width != 0) {
            packet_width = 0xE0;
        } else {
            packet_width = 0x1C0;
        }
        M2C_FIELD(temp_s2, volatile u16 *, 0xE) = packet_width;
        ASM_KEEP(temp_s2);
    }
    temp_v0_3 = M2C_FIELD(temp_s2, volatile u16 *, 0xE);
    M2C_FIELD(temp_s2, volatile s8 *, 3) = 5;
    M2C_FIELD(temp_s2, volatile u16 *, 0xA) = temp_v0_3;
    M2C_FIELD(temp_s2, volatile s16 *, 0x16) = temp_v0_3 + 0xE;
    M2C_FIELD(temp_s2, volatile s16 *, 0x12) = temp_v0_3 + 0xE;
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x7B0, temp_s2);
    temp_s2 += 0x18;
    func_80067EF4(temp_s2, 0, 1);
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x830, temp_s2);
    temp_s2 += 0xC;
    func_80067F20(temp_s2, 0, 0, 0x20, 0);
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067F20(temp_s2, 0, 0, 0x20, 0);
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x830, temp_s2);
    temp_s2 += 0xC;
    sp18[0] = 0x01C00000;
    sp18[1] = 0x100100;
    func_80067E2C(temp_s2, (s32) sp18);
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x7B0, temp_s2);
    temp_s2 += 0xC;
    func_80067E2C(temp_s2, (s32) sp18);
    func_8006658C(M2C_FIELD(temp_s1, s32 *, 0) + 0x830, temp_s2);
    temp_s2 += 0xC;
    M2C_FIELD(M2C_FIELD(temp_s1, s32 *, 0), void **, 0x8D0) = temp_s2;
}
