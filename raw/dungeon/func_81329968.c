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
#define M2C_UNALIGNED32(expr) (expr)

extern s32 D_80174CD8[3];
extern u8 D_80082E80[];
typedef struct {
    u8 data[24];
} Config24;
extern u8 D_8016A87C[];
extern void func_8009A3D0(u8, u8, s32);
extern void func_800A2B04(s32, u8, u8);
extern void func_8009A21C(u8, u8, s32);

void func_80171168(s32 arg0) {
    const Config24 *config;
    Config24 local;
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    u8 *local_bytes;
    u8 *global_base;
    u8 call_a0;
    u8 call_a1;
    u8 final_a0;
    u8 final_a1;
    register s16 *temp_a0;
    s32 temp_s3;
    void *temp_s0;
    void *temp_s2;

    config = (const Config24 *)D_8016A87C;
    local = *config;
    temp_a0 = (s16 *)local.data;
    var_a2 = 0x3000;
    temp_s2 = *D_80174CD8 + 0x20;
    temp_s0 = M2C_FIELD(*D_80174CD8, void **, 0xC);
    temp_s3 = M2C_FIELD(*D_80174CD8, s32 *, 8);
    M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) & 0xFF7F);
    call_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    call_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    if (M2C_FIELD(temp_s2, s32 *, 0x1C) & 0x2000) {
        var_a2 = 0x300;
    }
    func_8009A3D0(call_a0, call_a1, var_a2);
    global_base = D_80082E80;
    temp_a0 = &temp_a0[arg0];
    local_bytes = (u8 *)temp_a0;
    M2C_FIELD(temp_s0, u8 *, 0x24) = (u8) (global_base[0x24] + local_bytes[0]);
    M2C_FIELD(temp_s0, u8 *, 0x25) = (u8) (global_base[0x25] + local_bytes[1]);
    func_800A2B04(temp_s3, M2C_FIELD(temp_s0, u8 *, 0x24), M2C_FIELD(temp_s0, u8 *, 0x25));
    final_a0 = M2C_FIELD(temp_s0, u8 *, 0x24);
    final_a1 = M2C_FIELD(temp_s0, u8 *, 0x25);
    var_a2_2 = 0x3000;
    if (M2C_FIELD(temp_s2, s32 *, 0x1C) & 0x2000) {
        var_a2_2 = 0x300;
    }
    func_8009A21C(final_a0, final_a1, var_a2_2);
}
