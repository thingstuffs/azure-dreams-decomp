#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define NULL 0

M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
M2C_UNK func_800478B8();
s32 func_800BCB04();
void func_80174438(void) __attribute__((noreturn));
extern M2C_UNK D_80045340;
extern u16 D_8006CCD8[8];
extern u16 D_8006CCE8[8];
extern M2C_UNK D_800DEEC0;
extern M2C_UNK D_80174254;

typedef struct {
    s32 words[6];
} Copy24;

s32 func_80DE6AAC(void *arg0, void *arg1, void *arg2) {
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80174254;
        M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
        M2C_FIELD(temp_s1, s16 *, 2) = (s16)(((u16)M2C_FIELD(arg0, u16 *, 0x2A) >> 9) & 7);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E40;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        func_8003DB94(temp_s0, &D_800DEEC0, 0);
        func_800478B8(temp_s0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x800;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0_2 = M2C_FIELD(temp_v0, void **, 8);
        *(Copy24 *)temp_s0_2 = *(Copy24 *)arg1;
        ASM_SCHED_BARRIER();
        {
            s32 temp_a1;
            s32 temp_a2;
            s32 temp_v0_2;
            s32 temp_v1;

            temp_a2 = M2C_FIELD(temp_s1, s16 *, 2) * 2;
            temp_v1 = (s32)((M2C_FIELD(arg2, u8 *, 0x24) + *(u16 *)((u8 *)D_8006CCD8 + temp_a2)) << 0x10) >> 0xA;
            temp_a1 = (s32)((M2C_FIELD(arg2, u8 *, 0x25) + *(u16 *)((u8 *)D_8006CCE8 + temp_a2)) << 0x10) >> 0xA;
            M2C_FIELD(temp_s0_2, s16 *, 2) = (s16)(temp_v1 + 0x20);
            M2C_FIELD(temp_s0_2, s16 *, 6) = (s16)(temp_a1 + 0x20);
            temp_v0_2 = func_800BCB04(temp_v1 & 0xFFC0, temp_a1 & 0xFFC0, (s16)(M2C_FIELD(arg0, u16 *, 0x88) - 0x20)) << 0x10;
            if (temp_v0_2 < M2C_FIELD(temp_s0_2, s32 *, 8)) {
                M2C_FIELD(temp_s0_2, s32 *, 8) = temp_v0_2;
            }
        }
        {
            register s32 dispatch_result ASM_REG("$2") = (s32)temp_v0;

            ASM_TAILSLOT_PIN(dispatch_result);
            func_80174438();
        }
        return (s32)temp_v0;
    }
    return 0;
}

/* MECHANISM: A typed 24-byte assignment restores the packed lw/sw copy and natural seven-register frame.
   An unsigned color byte plus a post-copy schedule seam fixes the immediate and held table-base order.
   The moved shape selects 2.7.2-cdk-G0; a scoped $v0 tail-slot pin closes the noreturn dispatch delay. */
