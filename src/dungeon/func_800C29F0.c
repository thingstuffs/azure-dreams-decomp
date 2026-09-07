#include "common.h"

typedef struct S_800C8150_0 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x3C];
    u32 unk_54;
} S_800C8150_0;   /* arg0 in func_800C8150 */

typedef struct S_800C8150_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800C8150_1;   /* entry in func_800C8150 */

typedef struct S_800C8150_2 {
    u8 pad_00[0x54];
    u32 unk_54;
} S_800C8150_2;   /* object in func_800C8150 */



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

u32 func_800C8150(S_800C8150_0 *arg0, s16 arg1, s16 arg2, s32 arg3)
{
    s32 i;
    u8 *entry;
    void *call_arg;
    u8 *message;
    S_800C8150_2 *object;
    s32 index;
    s32 raw_index;
    s32 scaled;
    s32 state;
    s32 store_value;
    register s32 shifted_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register TablePage *table_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    i = 1;
    if (arg0->unk_14 & 0x4000) {
        u8 *page;

        page = (u8 *)0x800E0000;
        entry = *(u8 **)(page + 0x3D7C) + 4;
        arg3 = 0x40000;
loop:
        object = ((S_800C8150_1 *)entry)->unk_AC;
        if ((object != 0) && (object->unk_54 & arg3)) {
            goto marked_move;
        }
        i--;
        entry -= 4;
        if (i >= 0) {
            goto loop;
        }
        goto common;
    } else if (arg0->unk_54 & 0x40000) {
        call_arg = arg0;
        goto marked_ready;
    }

common:
    if (arg0->unk_14 & 0x4000) {
        state = arg0->unk_12;
        if ((state != 4) && (arg0->unk_13 != 0)) {
            arg0->unk_12 = state + 1;
            raw_index = func_800A1BD0(arg0);
            shifted_index = raw_index << 16;
            index = shifted_index >> 16;
            table_page = (TablePage *)0x80010000;
            if (index >= 0) {
                scaled = index * 2;
                store_value = arg0->unk_12;
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
