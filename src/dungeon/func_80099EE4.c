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

/* Records an object action in the dungeon buffer, combining compatible entries. */
void func_8009F644(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte) {
    u8 *object = object_ptr;
    DungeonWriteState *state = (DungeonWriteState *)0x80013710;
    register s32 saved_action ASM_REG("$21") = action_code;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 saved_payload = payload;
    s8 saved_extra = extra_byte;
    u8 *entry;
    u8 *old_entry;
    register s32 compare_kind ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 kind;
    register s32 shifted_action ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 entry_tag;
    s32 flag_bit;
    s16 action_offset;
    u32 dispatch_index;

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
        shifted_action = action_code << 16;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (((*(volatile u8 *)(entry + 1)) & 0xF8) != (shifted_action >> 16)) {
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
    action_offset = (s16)(saved_action - 8);
    dispatch_index = (s16)action_offset;
    {
        static void *const dispatch_labels[] = {
            &&jt_case0, &&jt_case20, &&jt_case40,
            &&jt_case68, &&jt_case48, &&jt_default
        };
        (void)dispatch_labels;
    }
    if (dispatch_index < 161U) {
        goto *D_80088D7C[(u32)dispatch_index];
    } else {
        goto jt_default;
    }

jt_case0:
        entry[1] = saved_action | kind;
        entry[0] = entry[0] + 1;
        goto jt_default;

jt_case20:
        entry[1] = saved_action | kind;
        entry[0] = saved_payload | 0x80;
        goto jt_default;

jt_case40:
        entry[1] = saved_action | kind;
        entry[0] = saved_payload | 0x80;
        entry[2] = saved_extra;
        entry[3] = 0;
        state->position += 2;
        entry += 2;
        goto jt_default;

jt_case68:
        old_entry = entry;
        entry_tag = saved_action | kind;
        flag_bit = (saved_payload & 1) << 5;
        entry = func_8009F9E8(entry_tag & 0xFF, flag_bit);
        if (old_entry != entry) {
            state->position--;
            entry[1] = entry_tag;
            entry[0] = flag_bit | -0x80 | (saved_extra & 0x1F);
            goto jt_return;
        }
        /* fall through */

jt_case48:
        entry[1] = saved_action | kind;
        entry[0] = ((saved_payload & 1) << 5) | -0x80 | (saved_extra & 0x1F);
        goto jt_default;


jt_default:

    entry[3] = 0;
    entry[2] = 0;

jt_return:
    ASM_KEEP(saved_action);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
