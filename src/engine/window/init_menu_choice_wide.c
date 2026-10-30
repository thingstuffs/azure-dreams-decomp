#include "common.h"
#include "records/Rec_D_80081FDC.h"


typedef struct S_func_8003666C_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1A];
    void (*unk_68)(void);
    u8 pad_6C[0x8];
    void *unk_74;
} S_func_8003666C_0;

typedef struct S_func_8003666C_1 {
    u8 pad_00[0x22];
    s16 unk_22;
    u8 pad_24[0x2];
    u8 unk_26;
    u8 unk_27;
    u8 pad_28[0x58];
    void *unk_80;
} S_func_8003666C_1;

extern u8 menu_choice_display_data[0x10];
extern u8 menu_choice_cursor_storage[0x10];

extern void handle_two_column_menu_input(void);
extern void init_cursor_sprite_object(void *node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base, void *owner);

/* Copies the marker, applies the position offset, and installs the next callback. */
void init_menu_choice_wide(S_func_8003666C_0 *state) {
    S_func_8003666C_1 *layout;
    s32 center_offset;
    u8 marker;
    s32 position;
    s16 doubled_position;

    layout = (S_func_8003666C_1 *) state->unk_74;
    marker = layout->unk_27;
    position = layout->unk_22;
    center_offset = ((layout->unk_26 + 1) >> 1) - 1;
    position = (s16)(position - center_offset);
    doubled_position = (s16) (position * 2);
    state->unk_4D = marker;
    init_cursor_sprite_object(
        menu_choice_cursor_storage,
        menu_choice_display_data,
        (s32 *) state,
        1,
        doubled_position,
        ((S_func_8003666C_1 *) state->unk_74)->unk_80);
    state->unk_68 = handle_two_column_menu_input;
}
