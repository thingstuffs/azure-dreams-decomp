#include "common.h"
#include "shared/dungeon_floor.h"

typedef struct DungeonWriteState {
    u8 pad0[4];
    u16 flags;
    u16 position;
    u8 pad8[4];
    u8 *data;
} DungeonWriteState;

extern u8 *func_8009F9E8(s32 wanted_kind, s32 wanted_flag);

/* Records an object action in the dungeon buffer, combining compatible entries. */
void func_8009F644(void *object_ptr, s32 action_code, s32 payload, s8 extra_byte) {
    u8 *object = object_ptr;
    DungeonWriteState *state = (DungeonWriteState *)0x80013710;
    u16 saved_action = action_code;
    s32 saved_payload = payload;
    s8 saved_extra = extra_byte;
    u8 *entry;
    u8 *old_entry;
    s32 compare_kind;
    s32 kind;
    u8 kind_byte;
    s32 shifted_action;
    s32 entry_action;
    u8 entry_tag;
    s32 flag_bit;
    s16 action_offset;
    u32 dispatch_index;

    if (D_800E296C & 0x10000000) {
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
    kind_byte = compare_kind;
    kind = kind_byte;

    if (entry[1] != 0) {
        if ((entry[1] & 7) != compare_kind ||
            (shifted_action = (s16)action_code,
             entry_action = entry[1],
             entry_action &= 0xF8,
             entry_action != shifted_action) ||
            entry[0] >= 0x7F) {
            state->position++;
            entry += 2;
            entry[1] = 0;
            entry[0] = 0;
        }
    }

    action_offset = (s16)(saved_action - 8);
    dispatch_index = (s16)action_offset;
    switch (dispatch_index) {
    case 0:
    case 8:
    case 16:
    case 24:
    case 32:
    case 88:
        entry[1] = saved_action | kind;
        entry[0] = entry[0] + 1;
        break;
    case 40:
    case 56:
    case 160:
        entry[1] = saved_action | kind;
        entry[0] = saved_payload | 0x80;
        break;
    case 64:
        entry[1] = saved_action | kind;
        entry[0] = saved_payload | 0x80;
        entry[2] = saved_extra;
        entry[3] = 0;
        state->position += 2;
        entry += 2;
        break;
    case 104:
    case 112:
    case 120:
    case 136:
        old_entry = entry;
        entry_tag = saved_action | kind;
        entry = func_8009F9E8(entry_tag & 0xFF, (saved_payload & 1) << 5);
        flag_bit = (saved_payload & 1) << 5;
        if (old_entry != entry) {
            state->position--;
            entry[1] = entry_tag;
            entry[0] = flag_bit | -0x80 | (saved_extra & 0x1F);
            return;
        }
                /* fall through */
    case 72:
    case 80:
    case 96:
    case 128:
    case 144:
    case 152:
        entry[1] = saved_action | kind;
        entry[0] = ((saved_payload & 1) << 5) | -0x80 | (saved_extra & 0x1F);
        break;
    default:
        break;
    }

    entry[3] = 0;
    entry[2] = 0;
}
