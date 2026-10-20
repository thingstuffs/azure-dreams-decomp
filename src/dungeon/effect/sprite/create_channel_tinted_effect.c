#include "shared/object_node.h"
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

typedef struct S_818BD1C4_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BD1C4_2;


typedef struct Copy24 {
    s32 words[6];
} Copy24;

void func_8003DB94(struct Dst *state, struct Elem *entries, short index);  /* extern */
s32 register_node();           /* extern */
s32 func_80069EF8();                                /* extern */
void func_800248C0(void *state, s32 unused, Rec_D_80082E80 *primitive);
extern M2C_UNK D_80025E04;

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
    S_818BD1C4_2 *visual;
    void *object;
    S_818BD1C4_1 *state;
    s32 saved_y_offset;

    saved_y_offset = y_offset;
    object = func_8003FC64(0x212);
    if (object != NULL) {
        ((S_818BD1C4_0 *)object)->unk_10 = &func_800248C0;
        ((S_818BD1C4_0 *)object)->unk_20 = (s32) *owner_id;
        state = object + 0x20;
        state->unk_06 = 0;
        state->unk_08 = 0;
        visual = ((S_818BD1C4_0 *)object)->unk_0C;
        color_channel = color_index % 3;
        switch (color_channel) {
        case 0:
            visual->unk_0C = 0x80;
            visual->unk_0E = 0;
            visual->unk_0D = 0;
            break;
        case 1:
            visual->unk_0D = 0x80;
            visual->unk_0E = 0;
            visual->unk_0C = 0;
            break;
        case 2:
            visual->unk_0E = 0x80;
            visual->unk_0D = 0;
            visual->unk_0C = 0;
            break;
        }
        data_ptr = visual;
        visual->unk_12 = 0x7DCF;
        visual->unk_14 = (u16) (visual->unk_14 | 0xC);
        visual->unk_10 = (u16) (visual->unk_10 | 0x60);
        visual->unk_14 = (u16) (visual->unk_14 | 0x100);
        func_8003DB94(data_ptr, &D_80025E04, 0);
        phase_rounded = func_80069EF8();
        phase_value = phase_rounded;
        if (phase_value < 0) {
            phase_rounded = phase_value + 0xFFF;
        }
        visual->unk_1A = (s16) (phase_value % 4096);
        visual->unk_1E = 0x2000;
        visual->unk_1C = 0x2000;
        register_node(object, project_sprite_chain);
        transform_ptr = ((S_818BD1C4_0 *)object)->unk_08;
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
