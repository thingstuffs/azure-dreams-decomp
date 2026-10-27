#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80174910_6 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_6;   /* arg0 in create_three_linked_palette_objects */

   /* ((S_80174910_6 *)arg0)->unk_08 in create_three_linked_palette_objects */

typedef struct S_80174910_9 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_80174910_9;   /* ((S_80174910_6 *)arg0)->unk_0C in create_three_linked_palette_objects */

void *allocate_list_node();               /* extern */
s32 register_node(ObjectNodeHeader *entry, void *registration_id);           /* extern */
s32 LoadImage();              /* extern */
extern void D_801747B8();
extern u8 kewne_palette_colors[];

typedef struct S_80174910_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x8];
    void * unk_18;
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u16 unk_2E;
    u16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
} S_80174910_1;

typedef struct S_80174910_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80174910_2;   /* arg0 in create_three_linked_palette_objects */

typedef struct S_80174910_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80174910_4;

/* Creates three linked objects and initializes their shared palette data. */
void create_three_linked_palette_objects(S_80174910_2 *source, s32 effect_param) {
    u16 palette_rect[4];                                    /* compiler-managed */
    s16 next_palette_x;
    s32 object_index;
    u16 first_component;
    u16 second_component;
    u16 third_component;
    u16 clut_id;
    u8 entry_flags;
    u8 *texture_entry;
    ObjectNodeHeader *object;
    S_80174910_1 *object_data;
    SpriteFrameState *scale_state;
    SpriteFrameState *render_state;
    void *object_callback;

    object_index = 0;
    object_callback = &D_801747B8;
    do {
        object = allocate_list_node(0x12, source);
        object_data = ((void *)object) + 0x20;
        if (object != NULL) {
            object->update_callback = object_callback;
            object_data->unk_18 = (void *) source->unk_0C;
            object_data->unk_1C = (void *) source->unk_08;
            first_component = ((MovingPosition *)(((S_80174910_6 *)source)->unk_08))->x;
            object_data->unk_24 = first_component;
            object_data->unk_22 = first_component;
            object_data->unk_20 = first_component;
            second_component = ((MovingPosition *)(((S_80174910_6 *)source)->unk_08))->y;
            object_data->unk_2A = second_component;
            object_data->unk_28 = second_component;
            object_data->unk_26 = second_component;
            third_component = ((MovingPosition *)(((S_80174910_6 *)source)->unk_08))->z;
            object_data->unk_0C = effect_param;
            object_data->unk_34 = object_index;
            object_data->unk_30 = third_component;
            object_data->unk_2E = third_component;
            object_data->unk_2C = third_component;
            scale_state = object->sprite;
            scale_state->scale_y = 0x1000;
            scale_state->scale_x = 0x1000;
            register_node(object, project_sprite_chain);
            if (object_index == 0) {
                texture_entry = ((S_80174910_9 *)(((S_80174910_6 *)source)->unk_0C))->unk_08;
                do {
                    entry_flags = *texture_entry;
                    texture_entry += 0xC;
                    if (!(entry_flags & 0x20)) {
                        texture_entry -= 0xC;
                        break;
                    }
                } while (1);
                clut_id = ((S_80174910_4 *)texture_entry)->unk_06;
                palette_rect[3] = 1;
                palette_rect[2] = 0x10;
                palette_rect[0] = 0;
                palette_rect[1] = (s16) ((u32) (((clut_id & 0xFFC0) - 0x40) & 0xFFFF) >> 6);
                do {
                    LoadImage((s16 *) palette_rect, kewne_palette_colors);
                    next_palette_x = palette_rect[0] + 0x10;
                    palette_rect[0] = next_palette_x;
                } while (next_palette_x < 0x100);
            }
            render_state = object->sprite;
            render_state->clut = (u16) (render_state->clut - 0x40);
            object->sprite->tpage_abr = 0x20;
        }
        object_index += 1;
    } while (object_index < 3);
}

/* The external palette symbol lets the compiler keep its upper half in s3 and
   form the complete call argument in the original delay slot. */
