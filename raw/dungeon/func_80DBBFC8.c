#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

void func_801737C8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_7, &&kind_6, &&kind_5
    };
    u8 *selection;
    register s32 special ASM_REG("$18");
    u8 state;
    void *active;

    special = 0;
    state = FIELD(arg0, u8, 0x9B);
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
    if (FIELD(arg3, u32, 0x1C) & 0x2000) {
        u32 dispatch;

        dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
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

        type = FIELD(arg3, u16, 0x46) & 0x3FFF;
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
    ASM_KEEP(selection);
kind_1:
    selection = (u8 *)arg3 + 8;
    goto selection_ready;
kind_default:
    selection = 0;

selection_ready:
    if (*selection == 0) {
        goto empty_selection;
    }
    FIELD(arg0, u16, 0x98) &= 0xFF7F;
    ASM_KEEP(selection);
    {
        register s32 special_test ASM_REG("$2");

        special_test = special;
        ASM_KEEP(special_test);
        if (special_test != 0) {
            active = D_800814A8;
            FIELD(arg3, void *, 0x60) = active;
            goto copy_active_coords;
        }
    }
    ASM_KEEP(selection);

    {
        u8 *base;
        u8 item;
        u8 *row;

        base = D_8006DE24;
        item = *selection;
        row = base + item * 20;
        if (row[0x12] == 2) {
            active = FIELD(arg3, void *, 0x60);
            if (active != 0) {
                register u8 *linked ASM_REG("$3");

copy_active_coords:
                linked = FIELD(active, void *, -0x14);
                ASM_KEEP(linked);
                FIELD(arg3, u8, 0x72) = FIELD(linked, u8, 0x24);
                FIELD(arg3, u8, 0x73) = FIELD(linked, u8, 0x25);
                goto invoke_item;
            }
        } else {
            s32 dx;
            s32 dy;

            active = func_800A05A4(
                arg3, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                FIELD(arg3, s16, 0x2A), 0x10);
            FIELD(arg3, void * volatile, 0x60) = active;
            ASM_KEEP(active);
            dx = FIELD(arg3, s8, 0x72);
            dy = FIELD(arg3, s8, 0x73);
            if (dx < 0) {
                dx = -dx;
            }
            if (dy < 0) {
                dy = -dy;
            }
            FIELD(arg3, u8, 0x72) = dx;
            FIELD(arg3, u8, 0x73) = dy;
        }
    }

invoke_item:
    if (func_800A94A0(arg3, selection, special, (u8 *)arg0 + 0x98) == 0) {
        goto end;
    }
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    goto end;

empty_selection:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    D_8008346C = 0;
    FIELD(D_800814A8, u16, 0xA6)--;
    func_800A4ACC(arg3);
    FIELD(arg3, u8, 0x6D)--;
    FIELD(arg0, void *, 0x8C) = D_80171E20;
    FIELD(arg3, u8, 0x73) = 0;
    FIELD(arg3, u8, 0x72) = 0;
    FIELD(arg3, u16, 0x46) &= 0x7FFF;
    goto end;

state_1:
    if (func_8003F270()) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        goto end;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u8, 0x9B)++;
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

                ASM_SCHED_BARRIER();
                aux = (u8 *)arg3 + 0x20;
                FIELD(aux, u16, 0x24) = 0x13;
                FIELD(arg3, u16, 0x20) = 0;
                FIELD(arg3, void *, 0x10) = D_80171284;
                func_8004491C(arg3, D_80170FD8);

                child = FIELD(arg3, void *, 0x0C);
                FIELD(child, u16, 0x10) = small;
                FIELD(child, u16, 0x14) |= 0x0C;
                coords = FIELD(arg3, void *, 8);
                FIELD(coords, u16, 2) = FIELD(arg1, u16, 2);
                FIELD(coords, u16, 6) = FIELD(arg1, u16, 6);
                FIELD(coords, u16, 0x0A) = FIELD(arg1, u16, 0x0A);

                dx = (rand() & 0x3F) - 0x20;
                dy = (rand() & 0x3F) - 0x20;
                FIELD(coords, u16, 2) += dx;
                FIELD(coords, u16, 6) += dy;
                FIELD(child, u16, 0x1C) = 0x1000;
                FIELD(child, u16, 0x1E) = 0x1000;

                bits = rand() & 7;
                if (bits & 1) {
                    FIELD(child, u8, 0x0C) = 0x80;
                } else {
                    FIELD(child, u8, 0x0C) = small;
                }
                if (bits & 2) {
                    FIELD(child, u8, 0x0D) = 0x80;
                } else {
                    FIELD(child, u8, 0x0D) = small;
                }
                if (bits & 4) {
                    FIELD(child, u8, 0x0E) = 0x80;
                } else {
                    FIELD(child, u8, 0x0E) = small;
                }
                FIELD(aux, u8, 2) = FIELD(child, u8, 0x0C);
                FIELD(aux, u8, 3) = FIELD(child, u8, 0x0D);
                FIELD(aux, u8, 4) = FIELD(child, u8, 0x0E);
                FIELD(child, u16, 0x12) = 0x7DCF;
                FIELD(child, u16, 0x14) |= 0x100;
                FIELD(aux, Copy12, 0x34) = *(Copy12 *)D_80175424;
                FIELD(child, void *, 8) = aux + 0x34;
                FIELD(aux, u16, 0x50) = 8;
                FIELD(aux, u16, 0x4E) = 4;
            }
            count++;
        } while (count < 1);
    }

    if ((FIELD(arg2, s8, 4) == 6 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg0, u16, 0x98) |= 0x80;
    }
    if ((FIELD(arg2, s8, 4) == 9 &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0xE000)) {
        FIELD(arg2, u16, 0x14) |= 0x800;
        FIELD(arg0, u16, 0x96) = 0x14;
        FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
        goto end;
    }
    goto end;

state_3:
    {
        u8 *global;
        s16 timer;

        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) == 0) {
            FIELD(arg0, u16, 0x96) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if (timer <= 0) {
            FIELD(arg0, u16, 0x96) = 0;
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            goto end;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        if (FIELD(arg2, u8 *, 0x2C) != D_801753BC) {
            u8 *table;
            s32 index;

            table = D_801753BC;
            FIELD(arg2, u8 *, 0x2C) = table;
            index = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(arg2, table[index], 0);
            FIELD(arg2, u16, 0x14) &= 0xF7FF;
        }
        if (FIELD(global, s32, 0x0C) != 0) {
            goto end;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg0, void *, 0x8C) = D_80171E20;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
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
