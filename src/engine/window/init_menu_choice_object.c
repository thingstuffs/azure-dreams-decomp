#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void);

typedef struct S_func_800362D0_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1A];
    Callback unk_68;
    u8 pad_6C[0x08];
    union {
        u32 unk_74_u32;
        void *unk_74_ptr;
    } unk_74;
} S_func_800362D0_0;

typedef struct S_func_800362D0_1 {
    u8 pad_00[0x22];
    u16 unk_22;
    u8 pad_24[0x02];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x58];
    s32 unk_80;
} S_func_800362D0_1;

extern u8 menu_choice_display_data[];
extern u8 menu_choice_cursor_storage[];

extern void init_cursor_display_object(void *data_ptr_a, void *data_ptr_b, s32 *object, s16 value,
                          s16 index_offset, s32 field_value);
extern void handle_wrapping_menu_cursor_input(void);

/* Initializes the object from its child data and sets the next callback. */
void init_menu_choice_object(S_func_800362D0_0 *object) {
    u32 child_or_index;
    u8 child_byte;
    u8 index_base;
    s16 index_offset;

    child_or_index = object->unk_74.unk_74_u32;
    child_byte = ((S_func_800362D0_1 *)child_or_index)->unk_27;
    index_base = ((S_func_800362D0_1 *)child_or_index)->unk_26;
    child_or_index = ((S_func_800362D0_1 *)child_or_index)->unk_22;
    index_offset = child_or_index - (index_base - 1);
    object->unk_4D = child_byte;

    init_cursor_display_object(menu_choice_cursor_storage, menu_choice_display_data, (s32 *)object, 1, index_offset,
                  ((S_func_800362D0_1 *)object->unk_74.unk_74_ptr)->unk_80);
    object->unk_68 = handle_wrapping_menu_cursor_input;
}
