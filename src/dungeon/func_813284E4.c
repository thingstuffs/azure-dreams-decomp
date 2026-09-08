#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800814A8.h"
#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef u32 uptr;
#endif

typedef struct S_8016FCE4_0 {
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
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} S_8016FCE4_0;   /* arg3 in func_8016FCE4 */

typedef struct S_8016FCE4_1 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
} S_8016FCE4_1;   /* arg2 in func_8016FCE4 */

typedef struct S_8016FCE4_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8016FCE4_2_pre;   /* the 0x14 bytes before temp_v0 in func_8016FCE4, addressed as temp_v0[-1] */

typedef struct S_8016FCE4_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016FCE4_3;   /* temp_v0_2 in func_8016FCE4 */

typedef struct S_8016FCE4_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8016FCE4_4;   /* heading_base in func_8016FCE4 */



typedef struct S_8016FCE4_7 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8016FCE4_7;   /* counter_base in func_8016FCE4 */

typedef struct S_8016FCE4_8 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_8016FCE4_8;   /* (arg3 + ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F)) in func_8016FCE4 */


s32 func_8009A180(void *, void *);
void func_8009A21C(s32, s32, s32);
void func_8009A3D0(s32, s32, s32);
s32 func_8009A66C(s32, void *, void *, s32);
s32 func_8009FD7C(s32, s32, s32, s32);
void *func_800A02AC(void *, s32, s32);
s32 func_800A04F0(void *, s32, s32, s32);
s16 func_800A0818(s32, s32, s32, s32, void *);
void func_800A0E6C(void *, s32, void *, void *);
void func_800A19E4(void *, void *, s32, s32, void *);
s32 func_800A6D30(void);
void func_800A9A0C(void *);
extern void call_800A9A0C_top(void *) __asm__("func_800A9A0C");
s16 func_800BCB04(s32, s32, s32);
void func_8016FF80(void) __attribute__((noreturn));
void func_8016FF84(void) __attribute__((noreturn));
void func_8016FFC0(void) __attribute__((noreturn));
void func_80170110(void) __attribute__((noreturn));
void func_8017018C(void) __attribute__((noreturn));
void func_801701E4(void) __attribute__((noreturn));
extern void call_8016FF80(void) __asm__("func_8016FF80") __attribute__((noreturn));
extern void call_8016FF84(void) __asm__("func_8016FF84") __attribute__((noreturn));
extern void call_8016FFC0(void) __asm__("func_8016FFC0") __attribute__((noreturn));
extern void call_80170110(void) __asm__("func_80170110") __attribute__((noreturn));
extern void call_8017018C(void) __asm__("func_8017018C") __attribute__((noreturn));
extern void call_801701E4(void) __asm__("func_801701E4") __attribute__((noreturn));
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_8006CD00[];
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_b[] __asm__("D_80082E80");
extern u8 D_80082E80_c[] __asm__("D_80082E80");
extern u16 D_80082EA4;
extern u16 D_80083462;
extern u8 D_80083460[];

void func_8016FCE4(void *arg0, void *arg1, void *in2, void *in3) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    register void *arg2 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *arg3 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 *var_s1;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s0_2;
    s16 temp_v0_4;
    register s32 temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 temp_call_a1;
    s32 temp_s0;
    register s32 temp_v0_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    register s32 temp_v1_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *counter_base;
    register s32 var_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 var_s6;
    u8 *var_s7;
    void *temp_v0;
    S_8016FCE4_3 *temp_v0_2;

    arg2 = in2;
    arg3 = in3;
    var_s6 = 0;
    if ((D_80083462 & 0x4000) || (((S_8016FCE4_0 *)arg3)->unk_71.s >= 0)) {
        call_800A9A0C_top(arg3);
        call_801701E4();
        return;
    }
    if (D_80083462 & 0x2000) {
        func_800A19E4(arg2, arg3, 3, 6, arg0 + 0x9C);
        ASM_KEEP_NV(arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP_NV(arg3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_v1 = ((S_8016FCE4_0 *)arg3)->unk_1C;
        if (temp_v1 & 0x410) {
            if (temp_v1 & 0x400) {
                temp_v0 = func_800A02AC(arg3, ((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v);
                if (temp_v0 != NULL) {
                    temp_v0_2 = ((S_8016FCE4_2_pre *)temp_v0)[-1].unk_00;
                    ((S_8016FCE4_0 *)arg3)->unk_2A.u = func_800A0818(((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v, temp_v0_2->unk_24, temp_v0_2->unk_25, arg0 + 0x98);
                    ((S_8016FCE4_0 *)arg3)->unk_71.u = ((S_8016FCE4_0 *)arg3)->unk_71.u & 0x7F;
                    call_801701E4();
                    return;
                }
                temp_v0_3 = ((S_8016FCE4_0 *)arg3)->unk_14;
                if (temp_v0_3 >= 0) {
                    ((S_8016FCE4_0 *)arg3)->unk_14 = (s32) (temp_v0_3 | 0x80000000);
                    ((S_8016FCE4_0 *)arg3)->unk_2A.u += (func_800A6D30() & 7) << 9;
                    call_8016FF80();
                    return;
                }
                goto block_26;
            }
            temp_v0_3 = func_800A04F0(arg3, ((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v, (s16) ((S_8016FCE4_0 *)arg3)->unk_2A.u);
            var_s4 = 0;
            if (temp_v0_3 != 0) {
                call_8017018C();
                return;
            }
            goto block_27;
        }
        var_s4 = 0;
        if (!(((S_8016FCE4_0 *)arg3)->unk_46 & 0x8000)) {
            if (temp_v1 & 0x20000) {
                u8 **heading_ref = &D_800814A8;
                register u8 *position_base = D_80082E80;
                u8 *heading_base;
                u8 *x_table_base;
                s32 dir_index;

                x_table_base = D_8006CCD8;
                heading_base = *heading_ref;
                dir_index = ((((S_8016FCE4_0 *)arg3)->unk_45 + ((s32) (((S_8016FCE4_4 *)heading_base)->unk_2A << 0x10) >> 0x19)) & 7) * 2;
                temp_a2 = position_base[0x24] + *(u16 *)(x_table_base + dir_index);
                temp_a1 = D_80082E80[0x25] + *(u16 *)(D_8006CCE8 + dir_index);
                if ((((S_8016FCE4_1 *)arg2)->unk_24.at00.v != (temp_a2 & 0xFFFF)) || (((S_8016FCE4_1 *)arg2)->unk_24.at01.v != (temp_a1 & 0xFFFF))) {
                    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    temp_s0 = arg0 + 0x98;
                    temp_v0_4 = func_800A0818(((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v, (s16) temp_a2, (s16) temp_a1, temp_s0);
                    ((S_8016FCE4_0 *)arg3)->unk_2A.u = (u16) temp_v0_4;
                    if ((func_8009A66C(temp_v0_4, arg2, arg3, 0x20) << 0x10) <= 0) {
                        ((S_8016FCE4_0 *)arg3)->unk_2A.u = func_800A0818(((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v, D_80082E80_b[0x24], D_80082E80_b[0x25], temp_s0);
                    }
                    temp_v0_3 = func_8009FD7C(((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v, D_80082E80_b[0x24], D_80082E80_b[0x25]);
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                    var_s4 = 0;
                    if ((temp_v0_3 << 0x10) != 0) {
                        var_s6 = 1;
                        ASM_TAILSLOT_PIN(var_s6);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                        call_8016FF84();
                        return;
                    }
                    goto block_27;
                }
                goto block_cleanup;
            }
            func_800A0E6C(arg2, ((Rec_func_800A9E70_arg0 *)arg0)->unk_9C.as_s8, arg3, arg0 + 0x98);
block_26:
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            var_s4 = 0;
            goto block_27;
        }
block_27:
        var_s7 = D_8006CCD8;
        var_s1 = D_8006CD00;
loop_28:
        temp_v1_2 = ((S_8016FCE4_0 *)arg3)->unk_2A.s;
        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_98 & 2) {
            temp_v0_3 = *var_s1;
            temp_s0_2 = temp_v1_2 - temp_v0_3;
            ASM_TAILSLOT_PIN(temp_s0_2);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            call_8016FFC0();
            return;
        }
        temp_v0_3 = *var_s1;
        ASM_KEEP(temp_v0_3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        temp_s0_2 = temp_v1_2 + temp_v0_3;
        if ((func_8009A66C((s16) temp_s0_2, arg2, arg3, 0x20) << 0x10) > 0) {
            if (var_s4 < 3) {
                goto block_step;
            }
            temp_v0_3 = var_s6;
            ASM_KEEP_NV(temp_v0_3);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            if (temp_v0_3 != 0) {
                goto block_cleanup;
            }
block_step:
            {
                ((S_8016FCE4_0 *)arg3)->unk_2A.u = (u16) temp_s0_2;
                ((S_8016FCE4_8 *)((arg3 + ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F))))->unk_74 = (u8) ((S_8016FCE4_1 *)arg2)->unk_24.at00.v;
                ((S_8016FCE4_8 *)((arg3 + ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F))))->unk_7C = (u8) ((S_8016FCE4_1 *)arg2)->unk_24.at01.v;
                ((S_8016FCE4_0 *)arg3)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s + 1);
                func_8009A3D0(((S_8016FCE4_1 *)arg2)->unk_24.at00.v, ((S_8016FCE4_1 *)arg2)->unk_24.at01.v,
                              (((S_8016FCE4_0 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
                temp_a0 = ((u16) ((S_8016FCE4_0 *)arg3)->unk_2A.u >> 8) & 0xE;
                ((S_8016FCE4_1 *)arg2)->unk_24.at00.v = (u8) (((S_8016FCE4_1 *)arg2)->unk_24.at00.v + *(u8 *) ((uptr) temp_a0 + (uptr) var_s7));
                ((S_8016FCE4_1 *)arg2)->unk_24.at01.v = (u8) (((S_8016FCE4_1 *)arg2)->unk_24.at01.v + D_8006CCE8[temp_a0]);
                temp_a0 = ((S_8016FCE4_1 *)arg2)->unk_24.at00.v;
                temp_call_a1 = ((S_8016FCE4_1 *)arg2)->unk_24.at01.v;
                if (((S_8016FCE4_0 *)arg3)->unk_1C & 0x2000) {
                    var_a2_2 = 0x300;
                } else {
                    var_a2_2 = 0x3000;
                }
                func_8009A21C(temp_a0, temp_call_a1, var_a2_2);
                temp_v0_3 = var_s4 < 8;
                ASM_TAILSLOT_PIN(temp_v0_3);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                call_80170110();
            }
        }
        if ((var_s4 != 0) || (D_80082EA4 == ((S_8016FCE4_1 *)arg2)->unk_24.at00u.v) || ((func_8009A180(arg3, ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 0x10) == 0)) {
            var_s4 += 1;
            var_s1 += 1;
            if (var_s4 >= 8) {
block_48:
                ASM_KEEP_NV(var_s4);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
                temp_v0_3 = var_s4 < 8;
                if (temp_v0_3 == 0) {
                    ((S_8016FCE4_0 *)arg3)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F);
                    ((S_8016FCE4_0 *)arg3)->unk_46 = (u16) (((S_8016FCE4_0 *)arg3)->unk_46 & 0x7FFF);
                    func_800A9A0C(arg3);
                    call_801701E4();
                    return;
                }
                ((S_8016FCE4_0 *)arg3)->unk_46 = (u16) (((S_8016FCE4_0 *)arg3)->unk_46 & 0x7FFF);
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_9C.as_s8 = (s8) ((S_8016FCE4_1 *)arg2)->unk_26;
                ((S_8016FCE4_0 *)arg3)->unk_6D.u = (u8) (((S_8016FCE4_0 *)arg3)->unk_6D.u - 1);
                counter_base = D_80083460;
                ((S_8016FCE4_7 *)counter_base)->unk_08 = (u16) (((S_8016FCE4_7 *)counter_base)->unk_08 + 1);
                if (((S_8016FCE4_0 *)arg3)->unk_6D.s != 0) {
                    goto block_life_nonzero;
                }
block_cleanup:
                ((S_8016FCE4_0 *)arg3)->unk_71.s = (s8) ((u8) ((S_8016FCE4_0 *)arg3)->unk_71.s & 0x7F);
                call_801701E4();
                return;
block_life_nonzero:
                var_s4 = (s16) func_800BCB04((((S_8016FCE4_1 *)arg2)->unk_24.at00.v << 6) | 0x20, (((S_8016FCE4_1 *)arg2)->unk_24.at01.v << 6) | 0x20, (s16) (((S_8016FCE4_0 *)arg3)->unk_88 - 0x20));
                if (var_s4 < 0x200) {
                    ((S_8016FCE4_0 *)arg3)->unk_88 = (u16) var_s4;
                }
            } else {
                goto loop_28;
            }
        }
    }
}
