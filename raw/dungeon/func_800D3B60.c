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

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonEntry;

extern s32 D_80083460[3];
extern int D_800814A8[4];
extern u8 D_80082E80_initial[] __asm__("D_80082E80");
extern u8 D_80082E80_later[] __asm__("D_80082E80");
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_8006CCD8_bytes[] __asm__("D_8006CCD8");
extern u8 D_8006CCE8_bytes[] __asm__("D_8006CCE8");
extern DungeonEntry D_800E2970[];
extern s16 D_8006CD00[];
extern u16 D_80082EA4[8];
M2C_UNK func_8009A3D0();
s32 func_8009A180();
s32 func_8009A21C();
s32 func_8009A66C();
s32 func_8009FD7C();
M2C_UNK func_800A0E6C();
M2C_UNK func_800A0818();
M2C_UNK func_800A19E4();
M2C_UNK func_800A6D30();
M2C_UNK func_800A9A0C();
s16 func_800BCB04();

void func_800D92C0(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_UNK var_a2_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0_3;
    s16 temp_v0_2;
    register M2C_UNK temp_a0_2 ASM_REG("$4");
    register s32 temp_call_a1 ASM_REG("$5");
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_v0 ASM_REG("$2");
    register s32 temp_v1 ASM_REG("$3");
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s6;
    s8 temp_a0;
    register s16 var_s1 ASM_REG("$17");
    u8 *table_base;
    u16 *state = (u16 *)D_80083460;

    var_s6 = 0;
    if ((state[1] & 0x4000) || (M2C_FIELD(arg3, s8 *, 0x71) >= 0)) {
        func_800A9A0C(arg3);
        return;
    }
    if (state[1] & 0x2000) {
        temp_s0 = arg0 + 0x9C;
        func_800A19E4(arg2, arg3, 3, 6, temp_s0);
        temp_v1 = M2C_FIELD(arg3, s32 *, 0x1C);
        temp_v0 = temp_v1 & 0x410;
        if (temp_v0) {
            temp_v0 = temp_v1 & 0x400;
            if (temp_v0) {
                temp_v0 = M2C_FIELD(arg3, s32 *, 0x14);
                if (temp_v0 >= 0) {
                    M2C_FIELD(arg3, s32 *, 0x14) = (s32) (temp_v0 | 0x80000000);
                    temp_v0 = func_800A6D30();
                    temp_v0 &= 7;
                    ASM_KEEP_NV(temp_v0);
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16)(M2C_FIELD(arg3, u16 *, 0x2A) + (temp_v0 << 9));
                }
            }
            goto init_loop;
        }
        if ((M2C_FIELD(arg3, s8 *, 0x71) < 0) && (state[1] & 0x2000)) {
            func_800A19E4(arg2, arg3, 3, 6, temp_s0);
            temp_v1_2 = M2C_FIELD(arg3, s32 *, 0x1C);
            if (temp_v1_2 & 0x2000) {
                if (temp_v1_2 & 0x20000) {
                    {
                        u8 *coord_base = D_80082E80_initial;
                        temp_v1_3 = (M2C_FIELD(arg3, u8 *, 0x45) + ((s32) (M2C_FIELD(*D_800814A8, u16 *, 0x2A) << 0x10) >> 0x19)) & 7;
                        temp_a2 = coord_base[0x24] + D_8006CCD8[temp_v1_3];
                        temp_a1 = coord_base[0x25] + D_8006CCE8[temp_v1_3];
                    }
                    if ((M2C_FIELD(arg2, u8 *, 0x24) != (temp_a2 & 0xFFFF)) || (M2C_FIELD(arg2, u8 *, 0x25) != (temp_a1 & 0xFFFF))) {
                        ASM_MEM_BARRIER();
                        temp_s0_2 = arg0 + 0x98;
                        temp_v0_2 = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16)temp_a2, (s16)temp_a1, temp_s0_2);
                        M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_v0_2;
                        if ((func_8009A66C(temp_v0_2, arg2, arg3, 0x20) << 0x10) <= 0) {
                            u8 *coord_later = D_80082E80_later;
                            M2C_FIELD(arg3, u16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), coord_later[0x24], coord_later[0x25], temp_s0_2);
                        }
                        {
                            u8 *coord_later = D_80082E80_later;
                            temp_v0 = func_8009FD7C(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), coord_later[0x24], coord_later[0x25]);
                            ASM_SCHED_BARRIER();
                            var_s1 = 0;
                            if ((temp_v0 << 0x10) != 0) {
                                var_s6 = 1;
                                goto loop_entry;
                            }
                        }
                        goto loop_entry;
                    }
                    goto mask_and_return;
                }
                goto block_24;
            }
            temp_a0 = M2C_FIELD(arg2, s8 *, 0x26);
            if ((temp_a0 < 0) || !(D_800E2970[temp_a0].flags & 2)) {
                if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
block_24:
                    goto block_25;
                }
            } else {
block_25:
                func_800A0E6C(arg2, M2C_FIELD(arg0, s8 *, 0x9C), arg3, arg0 + 0x98);
            }
init_loop:
            var_s1 = 0;
loop_entry:
            ASM_KEEP_NV(var_s1);
            ASM_KEEP_NV(var_s1);
            ASM_KEEP_NV(var_s1);
            table_base = (u8 *)D_8006CD00;
loop_27:
            temp_v0 = M2C_FIELD(arg0, u16 *, 0x98);
            temp_v1 = M2C_FIELD(arg3, s16 *, 0x2A);
            if (temp_v0 & 2) {
                temp_v0 = (s32) (var_s1 << 0x10) >> 0xF;
                temp_v0 += (s32) table_base;
                temp_s0_3 = temp_v1 - *(s16 *)temp_v0;
            } else {
                temp_v0 = (s32) (var_s1 << 0x10) >> 0xF;
                temp_v0 += (s32) table_base;
                temp_s0_3 = temp_v1 + *(s16 *)temp_v0;
            }
            if ((func_8009A66C((s16)temp_s0_3, arg2, arg3, 0x20) << 0x10) > 0) {
                if (var_s1 >= 3) {
                    temp_v0 = var_s6;
                    ASM_KEEP_NV(temp_v0);
                    if (temp_v0 != 0) {
                        goto mask_and_return;
                    }
                }
                {
                    M2C_FIELD(arg3, u16 *, 0x2A) = (u16) temp_s0_3;
                    M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x74) = (u8) M2C_FIELD(arg2, u8 *, 0x24);
                    M2C_FIELD((arg3 + ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F)), u8 *, 0x7C) = (u8) M2C_FIELD(arg2, u8 *, 0x25);
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) + 1);
                    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25),
                                  (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) ? 0x300 : 0x3000);
                    temp_a0_2 = ((u16) M2C_FIELD(arg3, u16 *, 0x2A) >> 8) & 0xE;
                    {
                        register u8 *x_table_base ASM_REG("$3") = D_8006CCD8_bytes;
                        register s32 x_value ASM_REG("$2") = M2C_FIELD(arg2, u8 *, 0x24);
                        x_value += x_table_base[temp_a0_2];
                        M2C_FIELD(arg2, u8 *, 0x24) = (u8) x_value;
                    }
                    M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(arg2, u8 *, 0x25) + D_8006CCE8_bytes[temp_a0_2]);
                    temp_a0_2 = M2C_FIELD(arg2, u8 *, 0x24);
                    temp_call_a1 = M2C_FIELD(arg2, u8 *, 0x25);
                    var_a2_2 = 0x3000;
                    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x2000) {
                        var_a2_2 = 0x300;
                    }
                    func_8009A21C(temp_a0_2, temp_call_a1, var_a2_2);
                    goto post_loop;
                }
            }
            {
                register s16 next_index ASM_REG("$2");
                if (var_s1 != 0) {
                    next_index = var_s1 + 1;
                    goto increment_index;
                }
                if (*D_80082EA4 == M2C_FIELD(arg2, u16 *, 0x24)) {
                    next_index = var_s1 + 1;
                    goto increment_index;
                }
                ASM_SCHED_BARRIER();
                if ((func_8009A180(arg3, M2C_FIELD(*D_800814A8, s32 *, 0x58) + 0x20) << 0x10) != 0) {
                    return;
                }
                next_index = var_s1 + 1;
increment_index:
                var_s1 = next_index;
                if (next_index < 8) {
                    goto loop_27;
                }
            }

post_loop:
            {
                register s32 post_index ASM_REG("$2") = var_s1;
                if (post_index >= 8) {
                    M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
                    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
                    func_800A9A0C(arg3);
                    return;
                }
            }
            M2C_FIELD(arg0, s8 *, 0x9C) = (s8) (u8) M2C_FIELD(arg2, s8 *, 0x26);
            M2C_FIELD(arg3, u8 *, 0x6D) = (u8) (M2C_FIELD(arg3, u8 *, 0x6D) - 1);
            {
                u16 *end_state = (u16 *)D_80083460;
                end_state[4] = (u16)(end_state[4] + 1);
            }
            if (M2C_FIELD(arg3, s8 *, 0x6D) != 0) {
                goto final_update;
            }

mask_and_return:
            M2C_FIELD(arg3, s8 *, 0x71) = (s8) ((u8) M2C_FIELD(arg3, s8 *, 0x71) & 0x7F);
            return;

final_update:
            var_s1 = func_800BCB04((M2C_FIELD(arg2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(arg2, u8 *, 0x25) << 6) | 0x20, (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
            if (var_s1 < 0x200) {
                M2C_FIELD(arg3, u16 *, 0x88) = (u16) var_s1;
            }
        }
    }
}
