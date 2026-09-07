/* TOWN func_808141B8 -- BYTE-EXACT, HELD for the owner (do NOT land from here).
 *
 * Identity : container TOWN.BIN foff 0x7941B8, size 0x458 (278 words)
 *            target sha256 12b07a072717047e47f4d36d3bfaaa919a35bc9dd40513e1cb4aa1f3053fb65d
 * Config   : 2.6.3-G0  (unmodified stock toolchain/compilers/gcc-2.6.3)
 * LINK BASE: 0x8052EDB8  -- NOT the synthetic row vram 0x808141B8.
 *
 * The row's 7 `j` words are the function's OWN local jumps in its true address
 * space, not calls to external noreturn dispatchers:
 *     j 0x8052F1E0 (x4) = `goto done`      -> function offset +0x428
 *     j 0x8052F1F0 (x2) = `return`         -> function offset +0x438 (epilogue)
 *     j 0x8052F1A0 (x1) = if/else else-skip-> function offset +0x3E8
 * All three independently solve link base 0x8052EDB8, i.e. delta 0x7FD9AC00 --
 * the delta already PROVEN for the bracketing tracked rowbase regions
 * town100_79380C (0x79380C..0x7938C0) and town100_7946C8 (0x7946C8..0x794CC4).
 * Landing needs a config/overlays/town.rowbase.jsonl record for
 * foff [0x7941B8,0x794610) with delta 0x7FD9AC00; the function is then named
 * func_8052EDB8 (true-space naming), as it is here.
 *
 * Two non-obvious spellings are load-bearing (gcc 2.6.3 sched.c alias model):
 *  1) `*(u16 *)((u8 *)arg0 + 26)` at the top of state1 instead of arg0->flags.
 *     true_dependence() drops the store->load dependence when the load is
 *     MEM_IN_STRUCT_P with a varying address and the store is a fixed-address
 *     non-struct global; a plain pointer deref clears MEM_IN_STRUCT_P and the
 *     dependence survives, so sched1 cannot hoist the load above
 *     `D_801328F8 = 0x400`.
 *  2) the address-taken `checked:` label in state0. memrefs_conflict_p proves
 *     arg0+12 (HImode store) and arg0+0 (SImode load) disjoint, so no memory
 *     dependence is possible from any C spelling; gcc's list scheduler then
 *     always picks the higher-priority load first. Taking the label's address
 *     keeps a CODE_LABEL in the RTL, which splits the basic block for
 *     schedule_insns and emits no code.
 */
#include "common.h"

typedef struct TownActor {
    u8 pad0[0x70];
    s16 field70;
    s16 field72;
    u8 pad74[2];
    s16 field76;
} TownActor;

typedef struct TownState {
    TownActor *actors[3];
    s16 state;
    s16 timer;
    s16 index;
    s16 pad12;
    s16 score;
    u16 counter;
    s16 area;
    u16 flags;
} TownState;

extern void func_8003F8A8(s32);
extern void func_8024A884(void);
extern void func_8024A900(void);
extern s32 func_80071494(void);
extern void func_8052E4C0(u32, s32, s32, s32);
extern void func_80050BFC(s32);
extern void func_80050BD8(s32);
extern void func_8003F75C(s32);

extern s16 D_8001339E;
extern s32 D_80084D5C;
extern u32 D_80095AAC;
extern u8 D_80095AAD;
extern u8 D_80095AAE;
extern u32 D_8012F140;
extern u16 D_801328F8;
extern s32 D_80132AE8[3];
extern u8 D_80530220[0x1000];
extern s32 D_805305A0;
extern s32 D_805305A4;
extern s32 D_805305A8;
extern s32 D_805305AC;
extern s32 D_805305B0;
extern s32 D_805305B4;
extern void *D_805267C8[6];

void func_8052EDB8(TownState *arg0)
{
    static void *const state_labels[7] __attribute__((used)) = {
        &&state0, &&state1, &&state2, &&state3, &&state4, &&state5, &&checked
    };
    TownActor *actor;
    s32 i;
    s32 state;
    s32 value;
    s32 color;
    s32 x;
    s32 y;

    if (D_8012F140 & 0x20) {
        arg0->counter = 0;
    }
    arg0->counter++;

    state = arg0->state;
    if ((u32)state >= 6) {
        goto done;
    }
    goto *D_805267C8[state];

state0:
        func_8003F8A8(5);
        D_805305A0 = 0x05600000;
        D_805305A4 = 0x03E00000;
        D_805305A8 = 0;
        D_805305B4 = 0;
        D_805305B0 = 0;
        D_805305AC = 0;
        func_8024A884();
        arg0->state = 1;
checked:
        if (arg0->actors[0]->field70 != 1) {
            goto done;
        }
        arg0->counter = 0;
        arg0->timer = *(u16 *)&D_80530220[arg0->area * 400 + arg0->index * 40];
        arg0->state = 2;
        goto done;

state1:
        D_801328F8 = 0x400;
        if (*(u16 *)((u8 *)arg0 + 26) & 1) {
            *(u16 *)((u8 *)arg0 + 26) &= ~1;
            arg0->index++;
            if (arg0->index >= 10) {
                arg0->state = 3;
                arg0->timer = 30;
                return;
            }
            arg0->timer = *(u16 *)&D_80530220[arg0->area * 400 + arg0->index * 40];
            return;
        }

        arg0->timer--;
        if (arg0->timer > 0) {
            goto done;
        }
        arg0->flags |= 1;
        do {
            i = 2;
            for (; i >= 0; i--) {
                arg0->actors[i]->field76 = func_80071494() % 3;
            }
        } while (arg0->actors[0]->field76 == arg0->actors[1]->field76 ||
                 arg0->actors[1]->field76 == arg0->actors[2]->field76 ||
                 arg0->actors[2]->field76 == arg0->actors[0]->field76);
        goto done;

state2:
        if (arg0->flags & 4) {
            goto done;
        }
        arg0->timer--;
        if (arg0->timer > 0) {
            goto done;
        }
        i = 2;
        value = 2;
        do {
            actor = arg0->actors[i];
            i--;
            actor->field72 = 0;
            actor->field70 = value;
        } while (i >= 0);
        func_8024A900();
        func_8024A884();
        arg0->timer = 20;
        arg0->state = 4;
        goto done;

state3:
        arg0->timer--;
        if (arg0->timer >= 0) {
            color = D_80095AAE;
            color += (0x90 - color) >> 1;
            D_80095AAE = color;
            D_80095AAD = color;
            *(u8 *)&D_80095AAC = color;

            for (i = 7; i >= 0; i--) {
                x = (((func_80071494() & 0x3F) - 0x20) << 16) + D_80132AE8[0];
                y = (((func_80071494() & 0x3F) - 0x20) << 16) + D_80132AE8[1];
                func_8052E4C0(0x00F0F0F0, x, y, 0);
            }
        }
        if (arg0->flags & 2) {
            goto done;
        }
        if (arg0->timer > 0) {
            goto done;
        }
        arg0->flags |= 8;
        arg0->state = 5;
        goto done;

state4:
        func_8024A900();
        if (D_8001339E < arg0->score) {
            D_8001339E = arg0->score;
            func_80050BFC(0xAE4);
        } else {
            func_80050BD8(0xAE4);
        }
        func_8003F75C(2);
        D_80095AAC = 0x00808080;
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
        goto done;

state5:
done:

    arg0->flags &= 0xFFF9;
}
