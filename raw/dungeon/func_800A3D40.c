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

extern u8 D_80083498[];
extern s32 D_800814A0[3];
extern volatile s16 D_80013714[8];
extern u8 D_80082E80[];
extern u8 D_800E3CC8[];
extern u8 *D_800E3D7C[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
struct S_8006DE24_Entry;
typedef struct S_8006DE24_Entry S_8006DE24_Entry;
struct S_8006DE24_Entry {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    u8 padC[8];
};
extern S_8006DE24_Entry D_8006DE24[];

void *func_8003FD64();
M2C_UNK func_80069EF8();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099734();
M2C_UNK func_8009FD40();
M2C_UNK func_800A5720();
s16 func_800A9400();
void func_800A96D8() __attribute__((noreturn));
void *func_800A971C();
void *func_800A97CC();
void *func_800A97FC();
s32 func_800A982C();
M2C_UNK func_800C77D0();
M2C_UNK func_800C78A0();
M2C_UNK func_800C7A3C();
void func_800AD594();
extern M2C_UNK D_80089080;
extern u8 D_800DD880[];
extern u8 D_800DD8B4[];
extern M2C_UNK D_800E1C58;
extern u8 D_800E3D68;

void *func_800A94A0(void *arg0, void *arg1, s16 arg2, void *arg3) {
    register s32 temp_s0_2 ASM_REG("$16");
    s32 temp_v0_2;
    register s32 temp_v0_5 ASM_REG("$19");
    s32 temp_v0_5_result;
    M2C_UNK temp_v1_2;
    s16 temp_v0_6;
    s32 entry_arg2;
    u16 temp_a0;
    s32 temp_a1;
    register s32 temp_a1_2 ASM_REG("$5");
    register void *temp_a0_3 ASM_REG("$4");
    u8 temp_a0_2;
    register s16 temp_s2 ASM_REG("$18");
    void *temp_s0;
    void *temp_s5;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v1;
    u8 *temp_t0;

    temp_s5 = M2C_FIELD(arg0, void **, -0x14);
    temp_v0 = func_8003FD64(0x12, D_80083498);
    if (temp_v0 != NULL) {
        entry_arg2 = ((s32) arg2 << 0x10) >> 0x10;
        {
            register s32 entry_a1 ASM_REG("$5") = entry_arg2;
            register u8 entry_v1 ASM_REG("$3");
            ASM_KEEP_NV(entry_a1);
            do { temp_s2 = M2C_FIELD(arg1, u8 *, 0); } while (0);
            entry_v1 = M2C_FIELD(arg1, u8 *, 1);
            D_800E3D68 = entry_v1;
            temp_v0_2 = func_800A982C((u8) temp_s2, entry_a1, M2C_FIELD(arg0, u8 *, 0x13));
        }
        ASM_KEEP_NV(temp_s2);
        if (temp_v0_2 == 0) {
            temp_a0 = M2C_FIELD(temp_v0, u16 *, 0x1E) | 0x8000;
            temp_a1 = D_800814A0[0] | 0x8000;
            M2C_FIELD(temp_v0, u16 *, 0x1E) = temp_a0;
            D_800814A0[0] = temp_a1;
            return NULL;
        }
        M2C_FIELD(temp_v0, s32 *, 0x10) = temp_v0_2;
        temp_v0_3 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_v0_3, void **, 4) = arg3;
        M2C_FIELD(temp_v0_3, u8 *, 8) = temp_s2;
        D_800E3CC8[0] = temp_s2;
        temp_a0_2 = M2C_FIELD(arg1, u8 *, 1);
        M2C_FIELD(temp_v0_3, u8 *, 9) = temp_a0_2;
        D_800E3CC8[1] = temp_a0_2;
        if (arg2 == 0) {
            temp_v1 = M2C_FIELD(arg0, void **, -0x18);
            temp_s0 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_s0, u16 *, 2) = (u16) M2C_FIELD(temp_v1, u16 *, 2);
            M2C_FIELD(temp_s0, u16 *, 6) = (u16) M2C_FIELD(temp_v1, u16 *, 6);
            M2C_FIELD(temp_s0, u16 *, 0xA) = (u16) M2C_FIELD(temp_v1, u16 *, 0xA);
            temp_v0_5 = func_80069EF8();
            if (!((u16) *D_80013714 & 1)) {
                temp_v0_4 = M2C_FIELD(arg0, void **, 0x60);
                if (temp_v0_4 != NULL) {
                    func_8009FD40(M2C_FIELD(arg0, void **, -0x14), M2C_FIELD(temp_v0_4, s32 *, -0x14));
                }
            }
            func_800C77D0(temp_v0, temp_s0, 8, 0x300);
            ASM_KEEP(temp_v0_5);
            goto block_21;
        }
        temp_t0 = D_80082E80;
        if (!(M2C_FIELD(temp_s5, u16 *, 0x14) & 0x8000)) {
            if (!(M2C_FIELD(temp_t0, u16 *, 0x14) & 0x8000)) {
                func_800C7A3C(temp_t0, temp_s5, M2C_FIELD(*D_800E3D7C, s16 *, 0x88), M2C_FIELD(arg0, s16 *, 0x88), 8, 0x300);
                goto block_21;
            }
            goto block_16;
        }
block_16:
        temp_v1_2 = ((u16) M2C_FIELD(*D_800E3D7C, u16 *, 0x2A) >> 8) & 0xE;
        func_800C78A0(arg0 - 0x20, (M2C_FIELD(temp_t0, u8 *, 0x24) << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEAC + temp_v1_2) << 0x10) >> 0x11) + 0x20, (M2C_FIELD(temp_t0, u8 *, 0x25) << 6) + ((s32) (*(u16 *)((u8 *)D_800DCEBC + temp_v1_2) << 0x10) >> 0x11) + 0x20, M2C_FIELD(*D_800E3D7C, s16 *, 0x88), 8, 0x300);
block_21:
        if ((arg2 << 0x10) != 0) {
            register s32 lookup_index ASM_REG("$2") = temp_s2;
            temp_a1_2 = D_800DD8B4[lookup_index];
            ASM_KEEP_NV(temp_a1_2);
            temp_a0_3 = arg0;
            ASM_KEEP_NV(temp_a0_3);
            temp_a1_2 <<= 6;
        } else {
            register s32 lookup_index ASM_REG("$2") = temp_s2;
            temp_a1_2 = D_800DD880[lookup_index];
            ASM_KEEP_NV(temp_a1_2);
            temp_a0_3 = arg0;
            ASM_KEEP_NV(temp_a0_3);
            temp_a1_2 <<= 8;
        }
        func_800AD594(temp_a0_3, temp_a1_2);
        if ((temp_v0 != NULL) && ((s8) M2C_FIELD(arg0, u8 *, 0x13) > 0)) {
            temp_v0_5_result = func_800990FC();
            temp_a0_3 = arg0;
            ASM_KEEP_NV(temp_a0_3);
            temp_v0_5 = temp_v0_5_result;
            temp_s0_2 = func_80099194(&D_800E1C58, func_80099734(temp_a0_3, temp_v0_5));
            ASM_KEEP_NV(temp_s0_2);
            if (((u32)(u16)arg2 << 0x10) != 0) {
                temp_v0_6 = func_800A9400(((s32)temp_s2 << 0x10) >> 0x10);
                return func_800A97CC(D_8006DE24[temp_v0_6].unk8);
            }
            {
                register s32 entry_index ASM_REG("$3");
                register S_8006DE24_Entry *entry_base ASM_REG("$4");
                entry_index = (s32)temp_s2 << 0x10;
                ASM_KEEP_NV(entry_index);
                ASM_KEEP_NV(temp_s2);
                entry_base = D_8006DE24;
                ASM_KEEP_NV(entry_base);
                entry_index >>= 0x10;
                ASM_KEEP_NV(entry_index);
                temp_s0_2 = func_80099194(entry_base[entry_index].unk0, temp_s0_2);
                func_80099290(func_80099194(&D_80089080, temp_s0_2));
                ASM_KEEP(temp_s0_2);
            }
            func_800A5720(temp_v0_5);
            goto block_25;
        }
        return temp_v0;
    }
block_25:
    return temp_v0;
}
