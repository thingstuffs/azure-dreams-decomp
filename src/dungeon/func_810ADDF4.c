#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801715F4_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_801715F4_0;   /* global in func_801715F4 */

typedef struct S_801715F4_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
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
} S_801715F4_1;   /* arg3 in func_801715F4 */

typedef struct S_801715F4_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} S_801715F4_2;   /* arg2 in func_801715F4 */

typedef struct S_801715F4_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801715F4_3_pre;   /* the 0x14 bytes before found in func_801715F4, addressed as found[-1] */

typedef struct S_801715F4_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_801715F4_3;   /* found in func_801715F4 */

typedef struct S_801715F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_4;   /* other in func_801715F4 */


typedef struct S_801715F4_6 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_801715F4_6;   /* monster_table + index * 0x14 in func_801715F4 */

typedef struct S_801715F4_7 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801715F4_7;   /* held_origin in func_801715F4 */

typedef struct S_801715F4_8 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} S_801715F4_8;   /* arg0 in func_801715F4 */

typedef struct S_801715F4_9 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_801715F4_9;   /* counter_state in func_801715F4 */

typedef struct S_801715F4_10 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801715F4_10;   /* (u8 *)arg3 + (((S_801715F4_1 *)arg3)->unk_71.u & 0x7F) in func_801715F4 */



extern s32 func_8009A180(void *, void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_8009A3D0(u8, u8, s32);
extern s32 func_8009A540(s32, u8, u8, s16);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0134(void *, void *);
extern void *func_800A02AC(void *, u8, u8);
extern void *func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A0E6C(void *, s8, void *, void *);
extern void func_800A19E4(void *, void *, s32, s32, void *);
extern s32 func_800A6D30(void);
extern s16 func_800A6E8C(void *, s32, s16 *, s16 *);
extern void func_800A9A0C(void *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 func_80171EBC(void *, void *, void *, void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s8 D_8006CD00;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern u8 D_80082E80_b[];
__asm__(".set D_80082E80_b, 0x80082E80");
extern s8 D_80082EA4;
extern s32 D_80083460;
extern s8 D_800E2970[];

void func_801715F4(void *arg0, void *arg1, void *arg2_p, void *arg3_p) {
    void *arg3;
    register void *arg2 ASM_REG("$18");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 sp18;
    s16 sp1A;
    s16 var_s3;
    s32 next_angle;
    s32 var_s6;
    s32 flags;
    s32 t0;
    s32 t1;
    s32 sx;
    s32 dx;
    s32 dy;
    u32 table_offset;
    void *found;
    u8 *global = (u8 *)&D_80083460;
    u8 *ctx_a;
    u8 *held_origin;
    u8 *held_context;
    s16 *turn_table;

    arg2 = arg2_p;
    arg3 = arg3_p;
    ASM_KEEP(arg2);   /* MATCH pin: retail basic-block layout depends on it */
    ASM_KEEP(arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
    var_s6 = 0;
    flags = ((S_801715F4_0 *)global)->unk_02;
    if ((flags & 0x4000) || (((S_801715F4_1 *)arg3)->unk_71.s >= 0)) {
        if ((((S_801715F4_1 *)arg3)->unk_12 >= 2) ||
            ((s16)func_80171EBC(arg0, arg1, arg2, arg3) == 0)) {
            func_800A9A0C(arg3);
            goto end;
        }
        if (((S_801715F4_0 *)global)->unk_0C == arg3) {
            ((S_801715F4_1 *)arg3)->unk_46 = 0xC008;
        }
        goto end;
    }

    if (!(flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(arg2, arg3, 3, 6, (u8 *)arg0 + 0x9C);
    flags = ((S_801715F4_1 *)arg3)->unk_1C;
    if (flags & 0x410) {
        if (flags & 0x400) {
            found = func_800A02AC(arg3, ((S_801715F4_2 *)arg2)->unk_24.at00.v,
                                  ((S_801715F4_2 *)arg2)->unk_24.at01.v);
            if (found != 0) {
                S_801715F4_4 *other = ((S_801715F4_3_pre *)found)[-1].unk_00;

                ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
                    ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                    other->unk_24, other->unk_25,
                    (u8 *)arg0 + 0x98);
                ((S_801715F4_1 *)arg3)->unk_71.u &= 0x7F;
                goto end;
            }
            {
                s32 m = 0x80000000;
                register s32 t14 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

                t14 = ((S_801715F4_1 *)arg3)->unk_14;
                if (t14 >= 0) {
                    t14 |= m;
                    ((S_801715F4_1 *)arg3)->unk_14 = t14;
                    ((S_801715F4_1 *)arg3)->unk_2A.u += (func_800A6D30() & 7) << 9;
                }
            }
            goto zero_s3;
        }

        found = func_800A04F0(arg3, ((S_801715F4_2 *)arg2)->unk_24.at00.v,
                              ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                              ((S_801715F4_1 *)arg3)->unk_2A.s);
        if (found == 0) {
            goto zero_s3;
        }
        goto clear_history;
    }

    if (flags & 0x2000) {
        var_s3 = 0;
        if (((S_801715F4_1 *)arg3)->unk_46 & 0x8000) {
            goto loop_setup;
        }

        if (flags & 0x20000) {
            {
                u8 *o;
                u32 offset;

                o = D_80082E80;
                offset =
                    ((((S_801715F4_1 *)arg3)->unk_45 +
                      ((s32)(((Rec_D_800814A8 *)D_800814A8)->unk_2A.as_u16 << 16) >> 25)) &
                     7) *
                    2;

                t0 = o[0x24] + *(u16 *)((u8 *)&D_8006CCD8 + offset);
                t1 = o[0x25] + *(u16 *)((u8 *)&D_8006CCE8 + offset);
            }
            sp18 = t0;
            sp1A = t1;

            if ((((S_801715F4_2 *)arg2)->unk_24.at00.v == (u16)t0) &&
                (((S_801715F4_2 *)arg2)->unk_24.at01.v == (u16)t1)) {
                goto clear_history;
            }

            ASM_MEM_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
                ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v, sp18, sp1A,
                ctx_a = (u8 *)arg0 + 0x98);
            if (func_8009A66C(((S_801715F4_1 *)arg3)->unk_2A.s, arg2, arg3, 0x20) <=
                0) {
                ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
                    ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                    D_80082E80_b[0x24], D_80082E80_b[0x25],
                    ctx_a);
            }
            {
                s16 path_ok = func_8009FD7C(((S_801715F4_2 *)arg2)->unk_24.at00.v,
                                             ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                                             D_80082E80_b[0x24],
                                             D_80082E80_b[0x25]);

                ASM_UNDEF(var_s3);   /* MATCH pin: keeps a constant in a register as retail does */
                var_s3 = 0;
                if (path_ok == 0) {
                    goto loop_setup;
                }
            }
            var_s6 = 1;
            goto loop_setup;
        }
        goto call_obstacle;
    }

    var_s3 = func_800A6E8C(arg2, 0x12, &sp18, &sp1A);
    if (((S_801715F4_2 *)arg2)->unk_26.s >= 0) {
        s32 index = ((S_801715F4_2 *)arg2)->unk_26.s;
        u8 *monster_table = D_800E2970;

        if (((S_801715F4_6 *)(monster_table + index * 0x14))->unk_0C & 2) {
            goto call_obstacle;
        }
    }

    if (((S_801715F4_1 *)arg3)->unk_46 & 0x8000) {
        goto zero_s3;
    }

    found = func_800A04F0(arg3, ((S_801715F4_2 *)arg2)->unk_24.at00.v,
                          ((S_801715F4_2 *)arg2)->unk_24.at01.v, ((S_801715F4_1 *)arg3)->unk_2A.s);
    if ((found != 0) && (((S_801715F4_3 *)found)->unk_1C & 0x2000) &&
        (func_800A0134(found, arg3) < 0x81) &&
        ((s16)func_8009A540(
             ((s32)(((S_801715F4_1 *)arg3)->unk_2A.u << 16) >> 25) & 0xFFFF,
             ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
             (s16)(((S_801715F4_1 *)arg3)->unk_88 - 0x20)) != 0)) {
        goto clear_history;
    }

    if (((S_801715F4_1 *)arg3)->unk_1C & 0x20000) {
        held_context = (u8 *)arg0 + 0x98;
        held_origin = D_80082E80;
        ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
            ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
            ((S_801715F4_7 *)held_origin)->unk_24, ((S_801715F4_7 *)held_origin)->unk_25,
            held_context);
        if ((s16)func_8009FD7C(((S_801715F4_2 *)arg2)->unk_24.at00.v,
                                ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                                ((S_801715F4_7 *)held_origin)->unk_24,
                                ((S_801715F4_7 *)held_origin)->unk_25) == 0) {
            goto zero_s3;
        }
        if (func_800A0134(D_800814A8, arg3) >= 0x81) {
            goto zero_s3;
        }
        if ((s16)func_8009A540(
                ((s32)(((S_801715F4_1 *)arg3)->unk_2A.u << 16) >> 25) & 0xFFFF,
                ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                (s16)(((S_801715F4_1 *)arg3)->unk_88 - 0x20)) != 0) {
            goto clear_history;
        }
        if (var_s3 == 0) {
            goto zero_s3;
        }

        dx = ((S_801715F4_2 *)arg2)->unk_24.at00.v;
        dx -= (sx = (u16)sp18);
        if (dx < 0) {
            dx = -dx;
        }
        if (dx >= 2) {
            goto call_path_held;
        }
        {
            s32 yv;

            yv = ((S_801715F4_2 *)arg2)->unk_24.at01.v;
            ASM_KEEP(yv);   /* MATCH pin: load-bearing for the whole function shape */
            dy = yv - (u16)sp1A;
        }
        if (dy < 0) {
            dy = -dy;
        }
        if (dy < 2) {
            goto random_angle;
        }

call_path_held:
        ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
            ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v, (s16)sx, sp1A,
            held_context);
        goto zero_s3;
    }

    if (var_s3 == 0) {
        goto call_obstacle;
    }
    dx = ((S_801715F4_2 *)arg2)->unk_24.at00.v;
    dx -= (sx = (u16)sp18);
    if (dx < 0) {
        dx = -dx;
    }
    if (dx >= 2) {
        goto call_path_direct;
    }
    {
        s32 yv;

        yv = ((S_801715F4_2 *)arg2)->unk_24.at01.v;
        ASM_KEEP(yv);   /* MATCH pin: load-bearing for the whole function shape */
        dy = yv - (u16)sp1A;
    }
    if (dy < 0) {
        dy = -dy;
    }
    if (dy < 2) {
        goto random_angle;
    }

call_path_direct:
    ((S_801715F4_1 *)arg3)->unk_2A.u = func_800A0818(
        ((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v, (s16)sx, sp1A,
        (u8 *)arg0 + 0x98);
    goto zero_s3;

random_angle:
    ((S_801715F4_1 *)arg3)->unk_2A.u = (func_800A6D30() & 7) << 9;
    var_s3 = 0;
    goto loop_setup;

call_obstacle:
    func_800A0E6C(arg2, ((S_801715F4_8 *)arg0)->unk_9C.s, arg3,
                  (u8 *)arg0 + 0x98);

zero_s3:
    var_s3 = 0;

loop_setup:
    turn_table = (s16 *)&D_8006CD00;

loop:
    {
        s32 angle;

        angle = ((S_801715F4_1 *)arg3)->unk_2A.s;
        if (((S_801715F4_8 *)arg0)->unk_98 & 2) {
            next_angle = angle - turn_table[var_s3];
        } else {
            next_angle = angle + turn_table[var_s3];
        }
        ASM_KEEP(angle);   /* MATCH pin: retail register colouring depends on it */
    }

    if (func_8009A66C((s16)next_angle, arg2, arg3, 0x20) > 0) {
        if (var_s3 >= 3) {
            s32 c;

            c = var_s6;
            ASM_KEEP(c);   /* MATCH pin: load-bearing for the whole function shape */
            if (c != 0) {
                goto clear_history;
            }
        }

        ((S_801715F4_1 *)arg3)->unk_2A.u = next_angle;
        ((S_801715F4_10 *)((u8 *)arg3 + (((S_801715F4_1 *)arg3)->unk_71.u & 0x7F)))->unk_74 =
            ((S_801715F4_2 *)arg2)->unk_24.at00.v;
        ((S_801715F4_10 *)((u8 *)arg3 + (((S_801715F4_1 *)arg3)->unk_71.u & 0x7F)))->unk_7C =
            ((S_801715F4_2 *)arg2)->unk_24.at01.v;
        ((S_801715F4_1 *)arg3)->unk_71.u++;

        func_8009A3D0(((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                      (((S_801715F4_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);

        table_offset = (((S_801715F4_1 *)arg3)->unk_2A.u >> 8) & 0xE;
        {
            register u8 *tp ASM_REG("$3");   /* MATCH pin: keeps a constant in a register as retail does */

            tp = (u8 *)&D_8006CCD8 + table_offset;
            ASM_KEEP_NV(tp);   /* MATCH pin: keeps a constant in a register as retail does */
            ((S_801715F4_2 *)arg2)->unk_24.at00.v += *tp;
        }
        ((S_801715F4_2 *)arg2)->unk_24.at01.v +=
            *(u8 *)((u8 *)&D_8006CCE8 + table_offset);

        func_8009A21C(((S_801715F4_2 *)arg2)->unk_24.at00.v, ((S_801715F4_2 *)arg2)->unk_24.at01.v,
                      (((S_801715F4_1 *)arg3)->unk_1C & 0x2000) ? 0x300 : 0x3000);
        goto after_loop;
    }

    if (var_s3 == 0) {
        if (*(u16 *)&D_80082EA4 != ((S_801715F4_2 *)arg2)->unk_24.at00u.v) {
            ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
            if ((s16)func_8009A180(
                    arg3,
                    (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                goto end;
            }
        }
    }

    var_s3++;
    if (var_s3 < 8) {
        goto loop;
    }

after_loop:
    if (var_s3 >= 8) {
        ((S_801715F4_1 *)arg3)->unk_71.u &= 0x7F;
        ((S_801715F4_1 *)arg3)->unk_46 &= 0x7FFF;
        func_800A9A0C(arg3);
        goto end;
    }

    ((S_801715F4_1 *)arg3)->unk_46 &= 0x7FFF;
    ((S_801715F4_8 *)arg0)->unk_9C.u = ((S_801715F4_2 *)arg2)->unk_26.u;
    ((S_801715F4_1 *)arg3)->unk_6D.u--;
    {
        u8 *counter_state = (u8 *)&D_80083460;

        ((S_801715F4_9 *)counter_state)->unk_08++;
    }
    if (((S_801715F4_1 *)arg3)->unk_6D.s != 0) {
        goto remaining_count;
    }

clear_history:
    ((S_801715F4_1 *)arg3)->unk_71.u &= 0x7F;
    goto end;

remaining_count:
    var_s3 = func_800BCB04((((S_801715F4_2 *)arg2)->unk_24.at00.v << 6) | 0x20,
                            (((S_801715F4_2 *)arg2)->unk_24.at01.v << 6) | 0x20,
                            (s16)(((S_801715F4_1 *)arg3)->unk_88 - 0x20));
    if (var_s3 < 0x200) {
        ((S_801715F4_1 *)arg3)->unk_88 = var_s3;
    }
    goto end;

end:
    return;
}

/* MECHANISM (BYTE-EXACT 537/537 @2.8.1-G0, rowbase true name func_801715F4).
   Closed from the long-standing aligned-3 plateau by THREE edits on top of the
   warm draft; the prior "maspsx real-jal move-relocation gap" verdict was wrong.

   1. THE DELAY SLOT IS A `goto zero_s3`, NOT A LOCAL `var_s3 = 0`.
      Retail's shared A0818 tail is `jal 800A0818 / move s3,zero / j <loop_setup>
      / sh v0,42(s1)`.  gcc's dbr cannot backward-fill that jal (the cross-jump
      label sits on it), and a local `var_s3 = 0` before the call is hoisted by
      sched1 to the block head, where fill_eager_delay_slots steals it into the
      two preceding branch delays -- that WAS the aligned-3 residue.  The real
      shape is that both call paths end `goto zero_s3;` with NO local zero: the
      block is [.. sw, jal, sh, j $L13], the forward scan in
      fill_simple_delay_slots breaks on the `j`, and reorg.c's post-loop
      "unconditional jump at the end" case lifts `move $19,$0` from the JUMP
      TARGET ($L13 = zero_s3) into the jal's delay slot AND redirects the jump
      past it -- which is exactly why retail's `j` lands on 0x80171B9C
      (loop_setup) rather than on the zero one word earlier.  The same edit on
      call_path_held makes both tails identical so cross-jump merges them into
      retail's `j <jal> / sw s4,16(sp)`, and it is also the SEMANTIC fix: retail
      zeroes s3 on the held path via that shared delay slot, the warm draft did
      not.
   2. That removes one var_s3 reference, which flips the allocno order
      (floor_log2(n_refs)*n_refs/live_length) and rotates the callee-saved map
      to var_s3=$17 / arg3=$18 / arg2=$19 (135 substitutions).  Pinning
      var_s3 to $19 instead lets dead-var_s3 temps coalesce into $19
      (`sll $s3,$s3,16`, in-place `addiu $s3,$s3,1`) and loses retail's
      `move s3,v0` idiom; pinning the two POINTER params is what retail's
      allocation actually looks like: `void *arg3` /
      `void *arg2` copied from arg3_p/arg2_p.
   3. The two pins alias the incoming $a2/$a3, so gcc dropped `move a2,s2` /
      `move a3,s1` at the func_80171EBC call as no-op copies; ASM_KEEP on each
      rewrites their identity and restores them.  Those keeps are volatile, so
      they also fence `var_s6 = 0`: as a declaration initializer it was pinned
      in front of them at word 3, and retail emits `move s6,zero` in the word-18
      branch delay -- assigning var_s6 AFTER the keeps releases it and closed
      the last 8 prologue words.

   Portability: strict lint 0 HARD / 0 baseline-exceed; the only macros are the
   sanctioned dungeon ASM_REG/ASM_KEEP family plus the warm draft's pre-existing
   D_80082E80_b address alias (baseline ADDR_ALIAS debt, not added here). */
