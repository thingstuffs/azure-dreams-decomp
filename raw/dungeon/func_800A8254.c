#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern s16 func_8009FD40(void *, void *);
extern void func_800A9A0C(void *, void *);
extern void func_800AAA28(void *, void *);
extern void func_800ADACC(void);
extern s16 func_800B500C(u8, u8, s16);

extern u8 D_80082E80[];
extern s32 D_80083460;
extern DungeonEntry D_800E3648[];

s32 func_800AD9B4(void *arg0, void *arg1)
{
    u8 *base;
    u8 *state;
    DungeonEntry *table;
    register u8 *page ASM_REG("$2");
    register s32 index ASM_REG("$3");
    s32 result;
    s8 amount;

    if (FIELD(arg1, u16, -2) & 0x8000) {
        goto tail;
    }
    ASM_SCHED_BARRIER();
    page = (u8 *)0x80080000;
    ASM_KEEP(page);
    base = page + 0x2E80;
    ASM_KEEP(base);
    if (FIELD(base, s8, 0x26) == FIELD(arg0, s8, 0x26)) {
        goto body;
    }
    if (func_8009FD40(base, arg0) < 7) {
        goto body;
    }

tail:
    func_800ADACC();
    return 1;

body:
    if (FIELD(arg1, u8, 0x25) == 0) {
        goto tail;
    }

    index = func_800B500C(FIELD(arg0, u8, 0x24),
                          FIELD(arg0, u8, 0x25),
                          FIELD(arg1, s16, 0x88));
    ASM_KEEP(index);
    result = 1;
    if (index >= 0) {
        table = D_800E3648;
        ASM_KEEP(table);
        if (!(table[index].flags & 0x80)) {
            goto tail;
        }

        page = (u8 *)0x80080000;
        ASM_KEEP(page);
        state = page + 0x3460;
        ASM_KEEP(state);
        if (FIELD(state, u16, 2) & 0x1000) {
            amount = FIELD(arg1, s8, 0x71);
            if (amount > 0) {
                FIELD(state, u16, 8) =
                    FIELD(state, u16, 8) -
                    (amount - FIELD(arg1, u16, 0x8A));
                FIELD(arg1, s8, 0x71) = 0;
            }
        }

        func_800A9A0C(arg1, state);
        func_800AAA28(arg0, arg1);
        result = 0;
    }
    return result;
}

/* MECHANISM: The 0x20 frame follows from holding arg1 in s0 and arg0 in s1.
   Dispatcher-first CFG plus a v1 signed index fixes branch and return-value roles.
   Kept table/state bases and a v0 0x8008 page split reproduce address emission order. */
