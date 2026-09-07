#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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
    register void *arg3 ASM_REG("$17");
    register void *arg2 ASM_REG("$18");
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
    ASM_KEEP(arg2);
    ASM_KEEP(arg3);
    var_s6 = 0;
    flags = FIELD(global, u16, 2);
    if ((flags & 0x4000) || (FIELD(arg3, s8, 0x71) >= 0)) {
        if ((FIELD(arg3, u8, 0x12) >= 2) ||
            ((s16)func_80171EBC(arg0, arg1, arg2, arg3) == 0)) {
            func_800A9A0C(arg3);
            goto end;
        }
        if (FIELD(global, void *, 0xC) == arg3) {
            FIELD(arg3, u16, 0x46) = 0xC008;
        }
        goto end;
    }

    if (!(flags & 0x2000)) {
        goto end;
    }

    func_800A19E4(arg2, arg3, 3, 6, (u8 *)arg0 + 0x9C);
    flags = FIELD(arg3, s32, 0x1C);
    if (flags & 0x410) {
        if (flags & 0x400) {
            found = func_800A02AC(arg3, FIELD(arg2, u8, 0x24),
                                  FIELD(arg2, u8, 0x25));
            if (found != 0) {
                void *other = FIELD(found, void *, -0x14);

                FIELD(arg3, u16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    FIELD(other, u8, 0x24), FIELD(other, u8, 0x25),
                    (u8 *)arg0 + 0x98);
                FIELD(arg3, u8, 0x71) &= 0x7F;
                goto end;
            }
            {
                s32 m = 0x80000000;
                register s32 t14 ASM_REG("$2");

                t14 = FIELD(arg3, s32, 0x14);
                if (t14 >= 0) {
                    t14 |= m;
                    ASM_KEEP(t14);
                    FIELD(arg3, s32, 0x14) = t14;
                    FIELD(arg3, u16, 0x2A) += (func_800A6D30() & 7) << 9;
                }
            }
            goto zero_s3;
        }

        found = func_800A04F0(arg3, FIELD(arg2, u8, 0x24),
                              FIELD(arg2, u8, 0x25),
                              FIELD(arg3, s16, 0x2A));
        if (found == 0) {
            goto zero_s3;
        }
        goto clear_history;
    }

    if (flags & 0x2000) {
        var_s3 = 0;
        if (FIELD(arg3, u16, 0x46) & 0x8000) {
            goto loop_setup;
        }

        if (flags & 0x20000) {
            {
                register u8 *o ASM_REG("$5");
                u32 offset;

                o = D_80082E80;
                offset =
                    ((FIELD(arg3, u8, 0x45) +
                      ((s32)(FIELD(D_800814A8, u16, 0x2A) << 16) >> 25)) &
                     7) *
                    2;

                t0 = o[0x24] + *(u16 *)((u8 *)&D_8006CCD8 + offset);
                t1 = o[0x25] + *(u16 *)((u8 *)&D_8006CCE8 + offset);
            }
            sp18 = t0;
            sp1A = t1;

            if ((FIELD(arg2, u8, 0x24) == (u16)t0) &&
                (FIELD(arg2, u8, 0x25) == (u16)t1)) {
                goto clear_history;
            }

            ASM_MEM_BARRIER();
            FIELD(arg3, u16, 0x2A) = func_800A0818(
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), sp18, sp1A,
                ctx_a = (u8 *)arg0 + 0x98);
            if (func_8009A66C(FIELD(arg3, s16, 0x2A), arg2, arg3, 0x20) <=
                0) {
                FIELD(arg3, u16, 0x2A) = func_800A0818(
                    FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                    D_80082E80_b[0x24], D_80082E80_b[0x25],
                    ctx_a);
            }
            {
                s16 path_ok = func_8009FD7C(FIELD(arg2, u8, 0x24),
                                             FIELD(arg2, u8, 0x25),
                                             D_80082E80_b[0x24],
                                             D_80082E80_b[0x25]);

                ASM_UNDEF(var_s3);
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
    if (FIELD(arg2, s8, 0x26) >= 0) {
        s32 index = FIELD(arg2, s8, 0x26);
        u8 *monster_table = D_800E2970;

        if (FIELD(monster_table + index * 0x14, u16, 0xC) & 2) {
            goto call_obstacle;
        }
    }

    if (FIELD(arg3, u16, 0x46) & 0x8000) {
        goto zero_s3;
    }

    found = func_800A04F0(arg3, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x2A));
    if ((found != 0) && (FIELD(found, s32, 0x1C) & 0x2000) &&
        (func_800A0134(found, arg3) < 0x81) &&
        ((s16)func_8009A540(
             ((s32)(FIELD(arg3, u16, 0x2A) << 16) >> 25) & 0xFFFF,
             FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
             (s16)(FIELD(arg3, u16, 0x88) - 0x20)) != 0)) {
        goto clear_history;
    }

    if (FIELD(arg3, s32, 0x1C) & 0x20000) {
        held_context = (u8 *)arg0 + 0x98;
        held_origin = D_80082E80;
        FIELD(arg3, u16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
            FIELD(held_origin, u8, 0x24), FIELD(held_origin, u8, 0x25),
            held_context);
        if ((s16)func_8009FD7C(FIELD(arg2, u8, 0x24),
                                FIELD(arg2, u8, 0x25),
                                FIELD(held_origin, u8, 0x24),
                                FIELD(held_origin, u8, 0x25)) == 0) {
            goto zero_s3;
        }
        if (func_800A0134(D_800814A8, arg3) >= 0x81) {
            goto zero_s3;
        }
        if ((s16)func_8009A540(
                ((s32)(FIELD(arg3, u16, 0x2A) << 16) >> 25) & 0xFFFF,
                FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                (s16)(FIELD(arg3, u16, 0x88) - 0x20)) != 0) {
            goto clear_history;
        }
        if (var_s3 == 0) {
            goto zero_s3;
        }

        dx = FIELD(arg2, u8, 0x24);
        dx -= (sx = (u16)sp18);
        if (dx < 0) {
            dx = -dx;
        }
        if (dx >= 2) {
            goto call_path_held;
        }
        {
            register s32 yv ASM_REG("$2");

            yv = FIELD(arg2, u8, 0x25);
            ASM_KEEP(yv);
            dy = yv - (u16)sp1A;
        }
        if (dy < 0) {
            dy = -dy;
        }
        if (dy < 2) {
            goto random_angle;
        }

call_path_held:
        FIELD(arg3, u16, 0x2A) = func_800A0818(
            FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), (s16)sx, sp1A,
            held_context);
        goto zero_s3;
    }

    if (var_s3 == 0) {
        goto call_obstacle;
    }
    dx = FIELD(arg2, u8, 0x24);
    dx -= (sx = (u16)sp18);
    if (dx < 0) {
        dx = -dx;
    }
    if (dx >= 2) {
        goto call_path_direct;
    }
    {
        register s32 yv ASM_REG("$2");

        yv = FIELD(arg2, u8, 0x25);
        ASM_KEEP(yv);
        dy = yv - (u16)sp1A;
    }
    if (dy < 0) {
        dy = -dy;
    }
    if (dy < 2) {
        goto random_angle;
    }

call_path_direct:
    FIELD(arg3, u16, 0x2A) = func_800A0818(
        FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25), (s16)sx, sp1A,
        (u8 *)arg0 + 0x98);
    goto zero_s3;

random_angle:
    FIELD(arg3, u16, 0x2A) = (func_800A6D30() & 7) << 9;
    var_s3 = 0;
    goto loop_setup;

call_obstacle:
    func_800A0E6C(arg2, FIELD(arg0, s8, 0x9C), arg3,
                  (u8 *)arg0 + 0x98);

zero_s3:
    var_s3 = 0;

loop_setup:
    turn_table = (s16 *)&D_8006CD00;

loop:
    {
        register s32 angle ASM_REG("$3");

        angle = FIELD(arg3, s16, 0x2A);
        if (FIELD(arg0, u16, 0x98) & 2) {
            next_angle = angle - turn_table[var_s3];
        } else {
            next_angle = angle + turn_table[var_s3];
        }
        ASM_KEEP(angle);
    }

    if (func_8009A66C((s16)next_angle, arg2, arg3, 0x20) > 0) {
        if (var_s3 >= 3) {
            register s32 c ASM_REG("$2");

            c = var_s6;
            ASM_KEEP(c);
            if (c != 0) {
                goto clear_history;
            }
        }

        FIELD(arg3, u16, 0x2A) = next_angle;
        FIELD((u8 *)arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x74) =
            FIELD(arg2, u8, 0x24);
        FIELD((u8 *)arg3 + (FIELD(arg3, u8, 0x71) & 0x7F), u8, 0x7C) =
            FIELD(arg2, u8, 0x25);
        FIELD(arg3, u8, 0x71)++;

        func_8009A3D0(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                      (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);

        table_offset = (FIELD(arg3, u16, 0x2A) >> 8) & 0xE;
        {
            register u8 *tp ASM_REG("$3");

            tp = (u8 *)&D_8006CCD8 + table_offset;
            ASM_KEEP_NV(tp);
            FIELD(arg2, u8, 0x24) += *tp;
        }
        ASM_SCHED_BARRIER();
        FIELD(arg2, u8, 0x25) +=
            *(u8 *)((u8 *)&D_8006CCE8 + table_offset);

        func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                      (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);
        goto after_loop;
    }

    if (var_s3 == 0) {
        if (*(u16 *)&D_80082EA4 != FIELD(arg2, u16, 0x24)) {
            ASM_SCHED_BARRIER();
            if ((s16)func_8009A180(
                    arg3,
                    (u8 *)FIELD(D_800814A8, void *, 0x58) + 0x20) != 0) {
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
        FIELD(arg3, u8, 0x71) &= 0x7F;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A9A0C(arg3);
        goto end;
    }

    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    FIELD(arg0, u8, 0x9C) = FIELD(arg2, u8, 0x26);
    FIELD(arg3, u8, 0x6D)--;
    {
        u8 *counter_state = (u8 *)&D_80083460;

        FIELD(counter_state, u16, 8)++;
    }
    if (FIELD(arg3, s8, 0x6D) != 0) {
        goto remaining_count;
    }

clear_history:
    FIELD(arg3, u8, 0x71) &= 0x7F;
    goto end;

remaining_count:
    var_s3 = func_800BCB04((FIELD(arg2, u8, 0x24) << 6) | 0x20,
                            (FIELD(arg2, u8, 0x25) << 6) | 0x20,
                            (s16)(FIELD(arg3, u16, 0x88) - 0x20));
    if (var_s3 < 0x200) {
        FIELD(arg3, u16, 0x88) = var_s3;
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
      allocation actually looks like: `register void *arg3 ASM_REG("$17")` /
      `register void *arg2 ASM_REG("$18")` copied from arg3_p/arg2_p.
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
