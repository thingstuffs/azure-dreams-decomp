#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"

#include "records/Rec_D_80082E80.h"

typedef struct {
    s32 words[6];
} Copy24;

typedef struct {
    s32 words[4];
} Copy16;

#define MULT_HI(a, b) (0)

extern s32 D_80045C34[3];
s32 register_node();
s32 func_80069EF8();
void func_80024C48(void *effect, void *motion, Rec_D_80082E80 *visual);
extern M2C_UNK D_80025AF0;

typedef struct S_818C370C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C370C_0;

typedef struct S_818C370C_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
} S_818C370C_1;

typedef struct S_818C370C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C370C_2;   /* arg0 in create_random_variant_effect */

/* Creates an object with randomized state and initializes its rendering and data. */
s32 create_random_variant_effect(S_818C370C_2 *owner, void *source_data) {
    s32 scale;
    s32 variant_random;
    s32 angle_random;
    char color_value;
    SpriteFrameState *render_data;
    S_818C370C_1 *state;
    void *object;
    void *object_data;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        ((S_818C370C_0 *)object)->unk_10 = &func_80024C48;
        ((S_818C370C_0 *)object)->unk_20 = owner;
        state->unk_0E = 0;
        state->unk_10 = 0;
        variant_random = func_80069EF8();
        state->unk_12 = (s16)(variant_random % 7);
        color_value = 0x80;
        state->unk_14 = owner->unk_14;
        render_data = ((S_818C370C_0 *)object)->unk_0C;
        render_data->color.c.b = color_value;
        render_data->color.c.g = color_value;
        render_data->color.c.r = color_value;
        render_data->clut = 0x7DCF;
        render_data->flags = render_data->flags | 0xC;
        render_data->tpage_abr = render_data->tpage_abr | 0x20;
        render_data->flags = render_data->flags | 0x100;
        func_8003DB94(render_data, &D_80025AF0, 0);
        angle_random = func_80069EF8();
        render_data->angle_z = angle_random % 0x1000;
        scale = 0x1400 / (s16)state->unk_14;
        render_data->scale_y = scale;
        render_data->scale_x = scale;
        register_node(object, D_80045C34);
        object_data = ((S_818C370C_0 *)object)->unk_08;
        *(Copy24 *)object_data = *(Copy24 *)source_data;
        return (s32)object;
    }
    return 0;
}
