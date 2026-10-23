#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/vector.h"
#include "town/minigame.h"
#include "engine/runtime.h"
#include "slus.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800224E0_0 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    union {
        struct { void * v; } at00;
        struct { s16 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_20;   /* overlapping accesses */
    u8 pad_24[0x4];
    s16 unk_28;
} S_800224E0_0;   /* obj in create_minigame_display_objects */

   /* prim in create_minigame_display_objects */

typedef struct S_800224E0_2 {
    u8 pad_00[0x48];
    void * unk_48;
} S_800224E0_2;   /* parent in create_minigame_display_objects */

typedef struct S_800224E0_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
} S_800224E0_3;   /* slot in create_minigame_display_objects */

extern u8 D_80020224[];
extern u8 D_80022768[];
extern u8 D_80023404[];
extern u8 D_80023DE0[];
extern u8 D_80023EB0[];
extern u8 D_8002415C[];
extern u8 D_80024470[];
extern u8 D_800244A0[];
extern s32 pickup_reward_total[];
extern u8 minigame_palette_backup[];
extern u8 minigame_image_backup[];
extern u8 D_800246E0[];
extern u8 lit_mesh_renderer_address[];

extern void register_node();
extern void StoreImage();
extern void configure_the_set_mode_n_3();

/* Creates parent and child display objects and uploads their graphics data. */
void create_minigame_display_objects(void)
{
    s16 upload_rect[4];
    s32 child_index;
    u8 *obj;
    u8 *parent_state;
    u8 *child_slot;
    u8 *callback;
    IntVector3 *prim;
    SpriteFrameState *draw_state;
    u8 *object_state;
    u8 *child_script;
    u32 neutral_color;
    u8 *render_state;

    parent_state = NULL;
    callback = D_80020224;
    noop_display_setup_hook();
    pickup_reward_total[0] = 0;
    initialize_minigame_display(D_800246E0);
    set_resident_bit(0xA4);

    obj = allocate_flagged_object_node(0x32);
    if (obj != NULL) {
        parent_state = obj + 0x20;
        prim = *(u8 * *)&((ObjectNodeHeader *)obj)->position;
        ((ObjectNodeHeader *)obj)->update_callback = D_80022768;
        prim->x = 0x04600000;
        prim->y = 0x03600000;
        ((S_800224E0_2 *)parent_state)->unk_48 = callback;
        configure_the_set_mode_n_3(parent_state, prim, D_80024470);
    }

    child_index = 2;
    child_script = D_80023404;
    child_slot = parent_state + 8;
    do {
        obj = allocate_flagged_object_node(2);
        ((S_800224E0_3 *)child_slot)->unk_4C = obj;
        if (obj != NULL) {
            ((ObjectNodeHeader *)obj)->update_callback = child_script;
            ((S_800224E0_0 *)obj)->unk_28 = child_index;
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
        }
        child_index--;
        child_slot -= 4;
    } while (child_index >= 0);

    obj = allocate_flagged_object_node(0x136);
    if (obj != NULL) {
        render_state = obj + 0x28;
        register_node(obj, lit_mesh_renderer_address);
        neutral_color = 0x00808080;
        ((ObjectNodeHeader *)obj)->update_callback = D_80023DE0;
        prim = *(u8 * *)&((ObjectNodeHeader *)obj)->position;
        draw_state = *(u8 * *)&((ObjectNodeHeader *)obj)->sprite;
        ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
        draw_state->scale_x = 0x1000;
        draw_state->scale_y = 0x1000;
        draw_state->offset_x = 0x1000;
        draw_state->source = 0x2C;
        draw_state->clut = 0;
        draw_state->flags = 0;
        draw_state->tpage_abr = 0;
        draw_state->angle_x = 0;
        draw_state->angle_y = 0;
        draw_state->angle_z = 0;
        draw_state->unk_00 = 0;
        draw_state->unk_04 = 0;
        draw_state->frame_ticks = 0;
        draw_state = (u8 *)&draw_state->color.word;
        draw_state->unk_00 = neutral_color;
        prim->x = 0x04400000;
        prim->y = 0x02C00000;
        object_state = obj + 0x20;
        prim->z = 0;
        (*(void * volatile *)((u8 *)object_state + 0x50)) = callback;
        configure_the_set_mode_n_3(render_state, *(u8 * *)&((ObjectNodeHeader *)obj)->position, D_800244A0);
    }

    child_index = 4;
    do {
        obj = allocate_flagged_object_node(0x100);
        if (obj != NULL) {
            register_node(obj, D_8002415C);
            ((S_800224E0_0 *)obj)->unk_20.at00.v = parent_state;
            ((ObjectNodeHeader *)obj)->update_callback = D_80023EB0;
            obj += 0x20;
            ((S_800224E0_0 *)obj)->unk_20.at02.v = child_index;
            switch (child_index) {
            case 0:
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = 1;
                break;
            case 1:
            case 2:
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = 2;
                break;
            case 3:
            case 4:
                ((S_800224E0_0 *)obj)->unk_20.at00u.v = 3;
                break;
            default:
                break;
            }
        }
        child_index--;
    } while (child_index >= 0);

    upload_rect[0] = 0x40;
    upload_rect[1] = 0x1D0;
    upload_rect[2] = 0x20;
    upload_rect[3] = 1;
    StoreImage(upload_rect, minigame_palette_backup);
    upload_rect[0] = 0xC0;
    upload_rect[1] = 0x1F8;
    upload_rect[2] = 0x30;
    upload_rect[3] = 1;
    StoreImage(upload_rect, minigame_image_backup);
}
