#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800CB4C0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800CB4C0_6;   /* arg0 in create_source_linked_fading_effect */

   /* ((S_800CB4C0_6 *)arg0)->unk_08 in create_source_linked_fading_effect */

void select_record_entry_and_value();  /* extern */
void *allocate_list_node();               /* extern */
s32 register_node();           /* extern */
extern M2C_UNK D_800CB374;
extern M2C_UNK D_800E02CC;

typedef struct S_800CB4C0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CB4C0_0;

typedef struct S_800CB4C0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB4C0_2;   /* arg0 in create_source_linked_fading_effect */

typedef struct S_800CB4C0_5 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB4C0_5;

/* Creates an object with shared or copied source coordinates and initializes its display state. */
void *create_source_linked_fading_effect(void *source, s16 copy_position) {
    s32 display_value;
    SpriteFrameState *display;
    void *object;
    S_800CB4C0_5 *state;
    SpriteFrameState *source_display;
    MovingPosition *position;

    object = allocate_list_node(0x100, source);
    if (object != NULL) {
        ((S_800CB4C0_0 *)object)->unk_10 = &D_800CB374;
        register_node(object, project_sprite_chain);
        display = ((S_800CB4C0_0 *)object)->unk_0C;
        select_record_entry_and_value(display, &D_800E02CC, 0);
        display->scale_y = 0x1400;
        display->scale_x = 0x1400;
        display->tpage_abr = 0x20;
        display->flags = (u16) (display->flags | 0xC);
        if ((copy_position << 0x10) == 0) {
            ((S_800CB4C0_0 *)object)->unk_08 = ((S_800CB4C0_2 *)source)->unk_08;
        } else {
            position = ((S_800CB4C0_0 *)object)->unk_08;
            position->unk_02 = (u16) ((MovingPosition *)(((S_800CB4C0_6 *)source)->unk_08))->unk_02;
            position->unk_06 = (u16) ((MovingPosition *)(((S_800CB4C0_6 *)source)->unk_08))->unk_06;
            position->unk_0A = (u16) ((MovingPosition *)(((S_800CB4C0_6 *)source)->unk_08))->unk_0A;
            source_display = ((S_800CB4C0_2 *)source)->unk_0C;
            display_value = source_display->color.word;
            display->tpage_abr = 0x60;
            display->color.word = display_value;
        }

        display->unk_06 = -1;
        state = object + 0x20;
        state->unk_A8 = source;
        state->unk_B4 = copy_position;
        state->unk_96 = 8;
    }
    return object;
}
