#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct TablePage {
    u8 pad[0x2098];
    s16 entries[1];
} TablePage;

extern void func_80099844(void *, void *);
extern s16 func_800A1BD0(void *);
extern s16 func_800C8900();

extern u8 D_800E18F5[];
extern u8 D_800E195C[];
extern u8 *D_800E3D7C;

u32 func_800C8150(void *arg0, s16 arg1, s16 arg2, s32 arg3)
{
    s32 i;
    u8 *entry;
    void *call_arg;
    u8 *message;
    void *object;
    s32 index;
    s32 raw_index;
    s32 scaled;
    s32 state;
    s32 store_value;
    register s32 shifted_index ASM_REG("$2");
    register TablePage *table_page ASM_REG("$2");

    i = 1;
    if (FIELD(arg0, u32, 0x14) & 0x4000) {
        register u8 *page ASM_REG("$2");

        page = (u8 *)0x800E0000;
        ASM_KEEP(page);
        entry = *(u8 **)(page + 0x3D7C) + 4;
        arg3 = 0x40000;
loop:
        object = FIELD(entry, void *, 0xAC);
        if ((object != 0) && (FIELD(object, u32, 0x54) & arg3)) {
            goto marked_move;
        }
        i--;
        entry -= 4;
        if (i >= 0) {
            goto loop;
        }
        goto common;
    } else if (FIELD(arg0, u32, 0x54) & 0x40000) {
        call_arg = arg0;
        goto marked_ready;
    }

common:
    if (FIELD(arg0, u32, 0x14) & 0x4000) {
        state = FIELD(arg0, u8, 0x12);
        if ((state != 4) && (FIELD(arg0, u8, 0x13) != 0)) {
            FIELD(arg0, u8, 0x12) = state + 1;
            raw_index = func_800A1BD0(arg0);
            shifted_index = raw_index << 16;
            ASM_KEEP_NV(shifted_index);
            index = shifted_index >> 16;
            table_page = (TablePage *)0x80010000;
            if (index >= 0) {
                scaled = index * 2;
                store_value = FIELD(arg0, u8, 0x12);
                ASM_KEEP_NV(table_page);
                table_page->entries[index] = store_value;
            }
            func_80099844(arg0, D_800E195C);
            return 1;
        }
        func_800C8900(arg0, arg1, arg2);
        return 1;
    }

    goto unmarked;

marked_move:
    call_arg = arg0;
marked_ready:
    message = D_800E18F5;
    func_80099844(call_arg, message);
    return 0;

unmarked:
    return (u32)~func_800C8900(arg0, arg1, arg2) >> 31;
}

/* MECHANISM: true-space local joins are explicit gotos, so the 0x18 frame holds only
   arg0 in s0 across real calls; the two-entry pointer walk is kept as a descending base. */
