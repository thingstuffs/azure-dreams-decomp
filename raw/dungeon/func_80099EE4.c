#include "common.h"

typedef struct DungeonWriteState {
    u8 pad0[4];
    u16 flags;
    u16 position;
    u8 pad8[4];
    u8 *data;
} DungeonWriteState;

extern s32 D_800E296C[];
extern void *D_80088D7C[];

extern u8 *func_8009F9E8(s32 arg0, s32 arg1);

void func_8009F644(void *arg0, s32 arg1, s32 arg2, s8 arg3) {
    u8 *object = arg0;
    DungeonWriteState *state = (DungeonWriteState *)0x80013710;
    register s32 saved_arg1 ASM_REG("$21") = arg1;
    s32 saved_arg2 = arg2;
    s8 saved_arg3 = arg3;
    u8 *entry;
    u8 *old_entry;
    register s32 compare_kind ASM_REG("$3");
    s32 kind;
    register s32 shifted_arg1 ASM_REG("$2");
    s32 packed;
    s32 high_bit;
    s16 action;
    u32 index;
    register s32 out_value ASM_REG("$2");

    if (D_800E296C[0] & 0x10000000) {
        return;
    }
    if (state->flags & 1) {
        return;
    }
    if (state->position >= 0xF01U) {
        return;
    }

    entry = state->data + state->position * 2;
    compare_kind = (*(u16 *)(object + 0x2A) >> 9) & 7;
    kind = compare_kind;

    if (entry[1] != 0) {
        if ((entry[1] & 7) != compare_kind) {
            goto clear_entry;
        }
        shifted_arg1 = arg1 << 16;
        ASM_SCHED_BARRIER();
        if (((*(volatile u8 *)(entry + 1)) & 0xF8) != (shifted_arg1 >> 16)) {
            goto clear_entry;
        }
        if (entry[0] < 0x7F) {
            goto entry_valid;
        }
clear_entry:
        state->position++;
        entry += 2;
        entry[1] = 0;
        entry[0] = 0;
    }

entry_valid:
    action = (s16)(saved_arg1 - 8);
    index = (s16)action;
    {
        static void *const jt_keep[] = {
            &&jt_case0, &&jt_case20, &&jt_case40,
            &&jt_case68, &&jt_case48, &&jt_default
        };
        (void)jt_keep;
    }
    if (index < 161U) {
        goto *D_80088D7C[(u32)index];
    } else {
        goto jt_default;
    }

jt_case0:
        entry[1] = saved_arg1 | kind;
        out_value = entry[0] + 1;
        goto jt_write0;

jt_case20:
        entry[1] = saved_arg1 | kind;
        out_value = saved_arg2 | 0x80;
        goto jt_write0;

jt_case40:
        entry[1] = saved_arg1 | kind;
        entry[0] = saved_arg2 | 0x80;
        entry[2] = saved_arg3;
        entry[3] = 0;
        state->position += 2;
        entry += 2;
        goto jt_default;

jt_case68:
        old_entry = entry;
        packed = saved_arg1 | kind;
        high_bit = (saved_arg2 & 1) << 5;
        entry = func_8009F9E8(packed & 0xFF, high_bit);
        if (old_entry != entry) {
            state->position--;
            entry[1] = packed;
            entry[0] = high_bit | -0x80 | (saved_arg3 & 0x1F);
            goto jt_return;
        }
        /* fall through */

jt_case48:
        entry[1] = saved_arg1 | kind;
        entry[0] = ((saved_arg2 & 1) << 5) | -0x80 | (saved_arg3 & 0x1F);
        goto jt_default;

jt_write0:
    entry[0] = out_value;

jt_default:

    entry[3] = 0;
    entry[2] = 0;

jt_return:
    ASM_KEEP(saved_arg1);
}
