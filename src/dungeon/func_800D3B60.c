#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D92C0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    s8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
} S_800D92C0_0;   /* arg3 in func_800D92C0 */

typedef struct S_800D92C0_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x2C];
    s32 unk_58;
} S_800D92C0_1;   /* *D_800814A8 in func_800D92C0 */

typedef struct S_800D92C0_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
} S_800D92C0_2;   /* arg2 in func_800D92C0 */

typedef struct S_800D92C0_3 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    s8 unk_9C;
} S_800D92C0_3;   /* arg0 in func_800D92C0 */

typedef struct S_800D92C0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D92C0_4;   /* (arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F)) in func_800D92C0 */


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

void func_800D92C0(void *arg0, void *arg1, S_800D92C0_2 *arg2, void *arg3) {
    M2C_UNK var_a2_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0_3;
    s16 temp_v0_2;
    register M2C_UNK temp_a0_2 ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 temp_call_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s6;
    s8 temp_a0;
    s16 var_s1;
    u8 *table_base;
    u16 *state = (u16 *)D_80083460;

    var_s6 = 0;
    if ((state[1] & 0x4000) || (((S_800D92C0_0 *)arg3)->unk_71 >= 0)) {
        func_800A9A0C(arg3);
        return;
    }
    if (state[1] & 0x2000) {
        temp_s0 = arg0 + 0x9C;
        func_800A19E4(arg2, arg3, 3, 6, temp_s0);
        temp_v1 = ((S_800D92C0_0 *)arg3)->unk_1C;
        temp_v0 = temp_v1 & 0x410;
        if (temp_v0) {
            temp_v0 = temp_v1 & 0x400;
            if (temp_v0) {
                temp_v0 = ((S_800D92C0_0 *)arg3)->unk_14;
                if (temp_v0 >= 0) {
                    ((S_800D92C0_0 *)arg3)->unk_14 = (s32) (temp_v0 | 0x80000000);
                    temp_v0 = func_800A6D30();
                    temp_v0 &= 7;
                    ((S_800D92C0_0 *)arg3)->unk_2A.u = (u16)(((S_800D92C0_0 *)arg3)->unk_2A.u + (temp_v0 << 9));
                }
            }
            goto init_loop;
        }
        if ((((S_800D92C0_0 *)arg3)->unk_71 < 0) && (state[1] & 0x2000)) {
            func_800A19E4(arg2, arg3, 3, 6, temp_s0);
            temp_v1_2 = ((S_800D92C0_0 *)arg3)->unk_1C;
            if (temp_v1_2 & 0x2000) {
                if (temp_v1_2 & 0x20000) {
                    {
                        u8 *coord_base = D_80082E80_initial;
                        temp_v1_3 = (((S_800D92C0_0 *)arg3)->unk_45 + ((s32) (((S_800D92C0_1 *)(*D_800814A8))->unk_2A << 0x10) >> 0x19)) & 7;
                        temp_a2 = coord_base[0x24] + D_8006CCD8[temp_v1_3];
                        temp_a1 = coord_base[0x25] + D_8006CCE8[temp_v1_3];
                    }
                    if ((arg2->unk_24.at00.v != (temp_a2 & 0xFFFF)) || (arg2->unk_24.at01.v != (temp_a1 & 0xFFFF))) {
                        ASM_MEM_BARRIER();   /* MATCH pin: retail delay-slot fill depends on it */
                        temp_s0_2 = arg0 + 0x98;
                        temp_v0_2 = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, (s16)temp_a2, (s16)temp_a1, temp_s0_2);
                        ((S_800D92C0_0 *)arg3)->unk_2A.u = (u16) temp_v0_2;
                        if ((func_8009A66C(temp_v0_2, arg2, arg3, 0x20) << 0x10) <= 0) {
                            u8 *coord_later = D_80082E80_later;
                            ((S_800D92C0_0 *)arg3)->unk_2A.u = func_800A0818(arg2->unk_24.at00.v, arg2->unk_24.at01.v, coord_later[0x24], coord_later[0x25], temp_s0_2);
                        }
                        {
                            u8 *coord_later = D_80082E80_later;
                            temp_v0 = func_8009FD7C(arg2->unk_24.at00.v, arg2->unk_24.at01.v, coord_later[0x24], coord_later[0x25]);
                            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
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
            temp_a0 = arg2->unk_26;
            if ((temp_a0 < 0) || !(D_800E2970[temp_a0].flags & 2)) {
                if (!(((S_800D92C0_0 *)arg3)->unk_46 & 0x8000)) {
block_24:
                    goto block_25;
                }
            } else {
block_25:
                func_800A0E6C(arg2, ((S_800D92C0_3 *)arg0)->unk_9C, arg3, arg0 + 0x98);
            }
init_loop:
            var_s1 = 0;
loop_entry:
            table_base = (u8 *)D_8006CD00;
loop_27:
            temp_v0 = ((S_800D92C0_3 *)arg0)->unk_98;
            temp_v1 = ((S_800D92C0_0 *)arg3)->unk_2A.s;
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
                    if (temp_v0 != 0) {
                        goto mask_and_return;
                    }
                }
                {
                    ((S_800D92C0_0 *)arg3)->unk_2A.u = (u16) temp_s0_3;
                    ((S_800D92C0_4 *)((arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F))))->unk_74 = (u8) arg2->unk_24.at00.v;
                    ((S_800D92C0_4 *)((arg3 + ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F))))->unk_7C = (u8) arg2->unk_24.at01.v;
                    ((S_800D92C0_0 *)arg3)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)arg3)->unk_71 + 1);
                    func_8009A3D0(arg2->unk_24.at00.v, arg2->unk_24.at01.v,
                                  (((S_800D92C0_0 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                    temp_a0_2 = ((u16) ((S_800D92C0_0 *)arg3)->unk_2A.u >> 8) & 0xE;
                    {
                        u8 *x_table_base = D_8006CCD8_bytes;
                        register s32 x_value ASM_REG("$2") = arg2->unk_24.at00.v;   /* MATCH pin: load-bearing for the whole function shape */
                        x_value += x_table_base[temp_a0_2];
                        arg2->unk_24.at00.v = (u8) x_value;
                    }
                    arg2->unk_24.at01.v = (u8) (arg2->unk_24.at01.v + D_8006CCE8_bytes[temp_a0_2]);
                    temp_a0_2 = arg2->unk_24.at00.v;
                    temp_call_a1 = arg2->unk_24.at01.v;
                    var_a2_2 = 0x3000;
                    if (((S_800D92C0_0 *)arg3)->unk_1C & 0x2000) {
                        var_a2_2 = 0x300;
                    }
                    func_8009A21C(temp_a0_2, temp_call_a1, var_a2_2);
                    goto post_loop;
                }
            }
            {
                register s16 next_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                if (var_s1 != 0) {
                    next_index = var_s1 + 1;
                    goto increment_index;
                }
                if (*D_80082EA4 == arg2->unk_24.at00u.v) {
                    next_index = var_s1 + 1;
                    goto increment_index;
                }
                ASM_SCHED_BARRIER();   /* MATCH pin: keeps a constant in a register as retail does */
                if ((func_8009A180(arg3, ((S_800D92C0_1 *)(*D_800814A8))->unk_58 + 0x20) << 0x10) != 0) {
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
                s32 post_index = var_s1;
                if (post_index >= 8) {
                    ((S_800D92C0_0 *)arg3)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F);
                    ((S_800D92C0_0 *)arg3)->unk_46 = (u16) (((S_800D92C0_0 *)arg3)->unk_46 & 0x7FFF);
                    func_800A9A0C(arg3);
                    return;
                }
            }
            ((S_800D92C0_3 *)arg0)->unk_9C = (s8) (u8) arg2->unk_26;
            ((S_800D92C0_0 *)arg3)->unk_6D.u = (u8) (((S_800D92C0_0 *)arg3)->unk_6D.u - 1);
            {
                u16 *end_state = (u16 *)D_80083460;
                end_state[4] = (u16)(end_state[4] + 1);
            }
            if (((S_800D92C0_0 *)arg3)->unk_6D.s != 0) {
                goto final_update;
            }

mask_and_return:
            ((S_800D92C0_0 *)arg3)->unk_71 = (s8) ((u8) ((S_800D92C0_0 *)arg3)->unk_71 & 0x7F);
            return;

final_update:
            var_s1 = func_800BCB04((arg2->unk_24.at00.v << 6) | 0x20, (arg2->unk_24.at01.v << 6) | 0x20, (s16) (((S_800D92C0_0 *)arg3)->unk_88 - 0x20));
            if (var_s1 < 0x200) {
                ((S_800D92C0_0 *)arg3)->unk_88 = (u16) var_s1;
            }
        }
    }
}
