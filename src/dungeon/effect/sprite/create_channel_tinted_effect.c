#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

#include "records/Rec_D_80082E80.h"

struct Dst;
struct Elem;

typedef struct S_818BD1C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD1C4_0;

typedef struct S_818BD1C4_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_818BD1C4_1;

typedef struct Copy24 {
    s32 words[6];
} Copy24;

void select_record_entry_and_value(void *state, void *entries, short index);  /* extern */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
s32 rand();                                /* extern */
void func_800248C0(void *state, s32 unused, Rec_D_80082E80 *primitive);
#include "shared/sprite_source.h"
extern SpriteSourceEntry flash_sprite_entries[];

/* Creates a colored object, copies its transform, and applies a vertical offset. */
s32 create_channel_tinted_effect(s32 *owner_id, void *transform, s16 color_index, s32 y_offset) {
    s16 color_channel;
    u16 pos_y;
    s32 phase_value;
    s32 phase_rounded;
    void *data_ptr;
    void *transform_ptr;
    s32 object_result;
    void *unused_ptr;
    SpriteFrameState *visual;
    ObjectNodeHeader *object;
    S_818BD1C4_1 *state;
    s32 saved_y_offset;

    saved_y_offset = y_offset;
    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->update_callback = &func_800248C0;
        ((S_818BD1C4_0 *)object)->unk_20 = (s32) *owner_id;
        state = ((void *)object) + 0x20;
        state->unk_06 = 0;
        state->unk_08 = 0;
        visual = object->sprite;
        color_channel = color_index % 3;
        switch (color_channel) {
        case 0:
            visual->color.c.r = 0x80;
            visual->color.c.b = 0;
            visual->color.c.g = 0;
            break;
        case 1:
            visual->color.c.g = 0x80;
            visual->color.c.b = 0;
            visual->color.c.r = 0;
            break;
        case 2:
            visual->color.c.b = 0x80;
            visual->color.c.g = 0;
            visual->color.c.r = 0;
            break;
        }
        data_ptr = visual;
        visual->clut = 0x7DCF;
        visual->flags = (u16) (visual->flags | 0xC);
        visual->tpage_abr = (u16) (visual->tpage_abr | 0x60);
        visual->flags = (u16) (visual->flags | 0x100);
        select_record_entry_and_value(data_ptr, &flash_sprite_entries, 0);
        phase_rounded = rand();
        phase_value = phase_rounded;
        if (phase_value < 0) {
            phase_rounded = phase_value + 0xFFF;
        }
        visual->angle_z = (s16) (phase_value % 4096);
        visual->scale_y = 0x2000;
        visual->scale_x = 0x2000;
        register_node(object, project_sprite_chain);
        transform_ptr = object->position;
        (*(Copy24 *)((u8 *)transform_ptr + 0)) =
            (*(Copy24 *)((u8 *)transform + 0));
        pos_y = (*(u16 *)((u8 *)transform_ptr + 0xA));
        object_result = (s32) object;
        pos_y -= saved_y_offset;
        (*(u16 *)((u8 *)transform_ptr + 0xA)) = pos_y;
        return object_result;
    }
    return 0;
}
