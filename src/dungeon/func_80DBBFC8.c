#include "common.h"


typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

extern s32 func_8003F270(void);
extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, void *);

extern u8 D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80170838[16];
extern u8 D_80170FD8[];
extern u8 D_80171284[];
extern u8 D_80171E20[];
extern u8 D_801753BC[];
extern u8 D_80175424[12];


typedef struct S_801737C8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737C8_0;   /* arg0 in func_801737C8 */

typedef struct S_801737C8_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801737C8_1_pre;   /* the 0x14 bytes before active in func_801737C8, addressed as active[-1] */

typedef struct S_801737C8_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801737C8_2;   /* linked in func_801737C8 */

typedef struct S_801737C8_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801737C8_3;   /* arg2 in func_801737C8 */

typedef struct S_801737C8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801737C8_4;   /* arg1 in func_801737C8 */

typedef struct S_801737C8_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_801737C8_5;   /* child in func_801737C8 */

typedef struct S_801737C8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801737C8_6;   /* coords in func_801737C8 */

typedef struct S_801737C8_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s32 unk_0C;
} S_801737C8_7;   /* global in func_801737C8 */

void func_801737C8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    s32 special;
    u8 state;
    void *active;

    special = 0;
    state = ((S_801737C8_0 *)arg0)->unk_9B;
    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        goto end;
    }

state_0:
    if ((*(u32 *)((u8 *)arg3 + 0x1C)) & 0x2000) {
        u32 dispatch;

        dispatch = ((*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF) - 1;
        if (dispatch >= 7) {
            goto kind_default;
        }
        (void)kind_keep;
        goto *(*(void **)((u8 *)D_80170838 + dispatch * 4));

kind_5:
        special = 1;
        goto kind_3;
kind_6:
        special = 1;
        goto kind_2;
kind_7:
        special = 1;
        goto kind_1;
    }

    {
        s32 type;

        type = (*(u16 *)((u8 *)arg3 + 0x46)) & 0x3FFF;
        if (type == 2) {
            goto kind_2;
        }
        if (type < 3) {
            selection = 0;
            if (type == 1) {
                goto normal_kind_1;
            }
            goto selection_ready;
        }
        if (type != 3) {
            selection = 0;
            goto selection_ready;
        }
    }

kind_3:
    selection = (u8 *)arg3 + 0xE;
    goto selection_ready;
kind_2:
    selection = (u8 *)arg3 + 0xB;
    goto selection_ready;
normal_kind_1:
kind_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    ((S_801737C8_0 *)arg0)->unk_98 &= 0xFF7F;
    {
        s32 special_test;

        special_test = special;
        ASM_KEEP(special_test);   /* MATCH pin: retail basic-block layout depends on it */
        if (special_test != 0) {
            active = D_800814A8;
            (*(void * *)((u8 *)arg3 + 0x60)) = active;
            goto copy_active_coords;
        }
    }

    {
        u8 *base;
        u8 item;
        u8 *row;

        base = D_8006DE24;
        item = *selection;
        row = base + item * 20;
        if (row[0x12] == 2) {
            active = (*(void * *)((u8 *)arg3 + 0x60));
            if (active != 0) {
                register u8 *linked ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

copy_active_coords:
                linked = ((S_801737C8_1_pre *)active)[-1].unk_00;
                (*(u8 *)((u8 *)arg3 + 0x72)) = ((S_801737C8_2 *)linked)->unk_24;
                (*(u8 *)((u8 *)arg3 + 0x73)) = ((S_801737C8_2 *)linked)->unk_25;
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, ((S_801737C8_3 *)arg2)->unk_24, ((S_801737C8_3 *)arg2)->unk_25,
                (*(s16 *)((u8 *)arg3 + 0x2A)), 0x10);
            (*(void * volatile *)((u8 *)arg3 + 0x60)) = active;
            ASM_KEEP(active);   /* MATCH pin: keeps a statement from moving across a call/branch */
            dx = (*(s8 *)((u8 *)arg3 + 0x72));
            dy = (*(s8 *)((u8 *)arg3 + 0x73));
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            (*(u8 *)((u8 *)arg3 + 0x72)) = dx;
            (*(u8 *)((u8 *)arg3 + 0x73)) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    ((S_801737C8_0 *)arg0)->unk_9B = ((S_801737C8_0 *)arg0)->unk_9B + 1;
    goto end;

empty_selection:
    ((S_801737C8_4 *)arg1)->unk_14 = 0;
    ((S_801737C8_4 *)arg1)->unk_10 = 0;
    ((S_801737C8_4 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_801737C8_3 *)arg2)->unk_24, ((S_801737C8_3 *)arg2)->unk_25);
    D_8008346C = 0;
    (*(u16 *)((u8 *)D_800814A8 + 0xA6))--;
    func_800A4ACC(arg3);
    (*(u8 *)((u8 *)arg3 + 0x6D))--;
    ((S_801737C8_0 *)arg0)->unk_8C = D_80171E20;
    (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
    (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
    (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        ((S_801737C8_3 *)arg2)->unk_14 |= 0x800;
        goto end;
    }
    ((S_801737C8_3 *)arg2)->unk_14 &= 0xF7FF;
    ((S_801737C8_0 *)arg0)->unk_9B++;
    func_800A56E0(0x703);

state_2:
    {
        s16 count;
        s32 small;

        count = 0;
        small = 0x20;
        do {
            arg3 = func_8003FC64(0x212);
            if (arg3 != 0) {
                u8 *aux;
                void *child;
                void *coords;
                s32 dx;
                s32 dy;
                s32 bits;

                ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a computation the compiler would drop */
                aux = (u8 *)arg3 + 0x20;
                (*(u16 *)((u8 *)aux + 0x24)) = 0x13;
                (*(u16 *)((u8 *)arg3 + 0x20)) = 0;
                (*(void * *)((u8 *)arg3 + 0x10)) = D_80171284;
                func_8004491C(arg3, D_80170FD8);

                child = (*(void * *)((u8 *)arg3 + 0x0C));
                ((S_801737C8_5 *)child)->unk_10 = small;
                ((S_801737C8_5 *)child)->unk_14 |= 0x0C;
                coords = (*(void * *)((u8 *)arg3 + 8));
                ((S_801737C8_6 *)coords)->unk_02 = ((S_801737C8_4 *)arg1)->unk_02;
                ((S_801737C8_6 *)coords)->unk_06 = ((S_801737C8_4 *)arg1)->unk_06;
                ((S_801737C8_6 *)coords)->unk_0A = ((S_801737C8_4 *)arg1)->unk_0A;

                dx = (rand() & 0x3F) - 0x20;
                dy = (rand() & 0x3F) - 0x20;
                ((S_801737C8_6 *)coords)->unk_02 += dx;
                ((S_801737C8_6 *)coords)->unk_06 += dy;
                ((S_801737C8_5 *)child)->unk_1C = 0x1000;
                ((S_801737C8_5 *)child)->unk_1E = 0x1000;

                bits = rand() & 7;
                if (bits & 1) {
                    ((S_801737C8_5 *)child)->unk_0C = 0x80;
                } else {
                    ((S_801737C8_5 *)child)->unk_0C = small;
                }
                if (bits & 2) {
                    ((S_801737C8_5 *)child)->unk_0D = 0x80;
                } else {
                    ((S_801737C8_5 *)child)->unk_0D = small;
                }
                if (bits & 4) {
                    ((S_801737C8_5 *)child)->unk_0E = 0x80;
                } else {
                    ((S_801737C8_5 *)child)->unk_0E = small;
                }
                (*(u8 *)((u8 *)aux + 2)) = ((S_801737C8_5 *)child)->unk_0C;
                (*(u8 *)((u8 *)aux + 3)) = ((S_801737C8_5 *)child)->unk_0D;
                (*(u8 *)((u8 *)aux + 4)) = ((S_801737C8_5 *)child)->unk_0E;
                ((S_801737C8_5 *)child)->unk_12 = 0x7DCF;
                ((S_801737C8_5 *)child)->unk_14 |= 0x100;
                (*(Copy12 *)((u8 *)aux + 0x34)) = *(Copy12 *)D_80175424;
                ((S_801737C8_5 *)child)->unk_08 = aux + 0x34;
                (*(u16 *)((u8 *)aux + 0x50)) = 8;
                (*(u16 *)((u8 *)aux + 0x4E)) = 4;
            }
            count++;
        } while (count < 1);
    }

    if ((((S_801737C8_3 *)arg2)->unk_04 == 6 &&
         (((S_801737C8_3 *)arg2)->unk_14 & 0x1000)) ||
        (((S_801737C8_3 *)arg2)->unk_14 & 0xE000)) {
        ((S_801737C8_0 *)arg0)->unk_98 |= 0x80;
    }
    if ((((S_801737C8_3 *)arg2)->unk_04 == 9 &&
         (((S_801737C8_3 *)arg2)->unk_14 & 0x1000)) ||
        (((S_801737C8_3 *)arg2)->unk_14 & 0xE000)) {
        ((S_801737C8_3 *)arg2)->unk_14 |= 0x800;
        ((S_801737C8_0 *)arg0)->unk_96 = 0x14;
        ((S_801737C8_0 *)arg0)->unk_9B = ((S_801737C8_0 *)arg0)->unk_9B + 1;
        goto end;
    }
    goto end;

state_3:
    {
        u8 *global;
        s16 timer;

        global = (u8 *)&D_80083460;
        if (((S_801737C8_7 *)global)->unk_0C == 0) {
            ((S_801737C8_0 *)arg0)->unk_96 = 0;
        }
        timer = ((S_801737C8_0 *)arg0)->unk_96 - 1;
        ((S_801737C8_0 *)arg0)->unk_96 = timer;
        if (timer <= 0) {
            ((S_801737C8_0 *)arg0)->unk_96 = 0;
            ((S_801737C8_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (!(((S_801737C8_3 *)arg2)->unk_14 & 0xE000)) {
            goto end;
        }
        ((S_801737C8_4 *)arg1)->unk_14 = 0;
        ((S_801737C8_4 *)arg1)->unk_10 = 0;
        ((S_801737C8_4 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_801737C8_3 *)arg2)->unk_24, ((S_801737C8_3 *)arg2)->unk_25);
        if (((S_801737C8_3 *)arg2)->unk_2C != D_801753BC) {
            u8 *table;
            s32 index;

            table = D_801753BC;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            index = ((D_80083228 + (*(s16 *)((u8 *)arg3 + 0x2A)) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
            ((S_801737C8_3 *)arg2)->unk_14 &= 0xF7FF;
        }
        if (((S_801737C8_7 *)global)->unk_0C != 0) {
            goto end;
        }
        ((S_801737C8_7 *)global)->unk_0A--;
        ((S_801737C8_0 *)arg0)->unk_8C = D_80171E20;
        func_800A4ACC(arg3);
        (*(u8 *)((u8 *)arg3 + 0x73)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x72)) = 0;
        (*(u8 *)((u8 *)arg3 + 0x6D))--;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A56E0(0xB4);
    }

end:
    return;
}

/* MECHANISM: (1) NATURAL PARAMS, NO ENTRY PINS -- once the body is exact, gcc
   allocates a0..a3 -> s6/s7/s4/s0 by itself; the inherited ASM_REG/ASM_KEEP entry
   block was the residue: a volatile asm between the prologue `sw $18` and
   `special=0` clears sched2's reg_last_uses, killing the anti-dep that hoists
   `sw s2,0x20(sp)` to word 9, and it also stops dbr's backward scan so
   `move s2,zero` cannot reach the beq delay slot. (2) ASM_SCHED_BARRIER at the
   top of the `if (obj)` loop body makes the fall-through thread ineligible, so
   gcc's dbr fills the `beqz s0` slot from the TARGET thread instead -- it copies
   the loop increment `addiu v0,fp,1` and redirects the branch past it (the
   retail "dead" word @0x80173ad8). (3) Two independent `x9B = x9B + 1` sites,
   NOT a shared next_state local: post-reload cross-jumping merges the identical
   `sb v0,0x9b(s6); j end` tails and keeps both sites tied to v0. (4) base/row
   pointer locals (`base = D_8006DE24; row = base + item*20; row[0x12]`) keep the
   +0x12 as a MEM offset -- writing D_8006DE24[item*20+0x12] folds +18 into the
   symbol at expand time and emits `lbu 0(v0)`. */
