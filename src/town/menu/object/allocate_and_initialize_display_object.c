#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

typedef struct S_800A2000_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800A2000_0;   /* obj in allocate_and_initialize_display_object */

typedef struct S_800A2000_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
} S_800A2000_1;   /* payload in allocate_and_initialize_display_object */

extern void *allocate_list_node();

/* Allocate an object and initialize its payload, display transform, and color. */
void *allocate_and_initialize_display_object(s32 object_key, s32 payload_value, s32 payload_param, s32 payload_halfword, s32 object_param,
    s32 object_value) {
    void *obj = allocate_list_node(0x136, object_key - 0x20);
    SpriteFrameState *display;
    S_800A2000_1 *payload;

    if (obj == 0) {
        return 0;
    }
    display = ((S_800A2000_0 *)obj)->unk_0C;
    ((S_800A2000_0 *)obj)->unk_10 = object_param;
    ((S_800A2000_0 *)obj)->unk_20 = object_value;
    payload = (u8 *)obj + 0x20;
    payload->unk_10 = object_key;
    payload->unk_14 = payload_param;
    payload->unk_20 = payload_halfword;
    payload->unk_40 = payload_value;
    display->unk_20 = 0x1000;
    display->scale_y = 0x1000;
    display->scale_x = 0x1000;
    display->clut = 0;
    display->flags = 0;
    display->tpage_abr = 0;
    display->color.c.r = g_game_work.view.tint.parts.tint_r;
    display->color.c.g = g_game_work.view.tint.parts.tint_g;
    display->color.c.b = g_game_work.view.tint.parts.tint_b;
    display->flags = 0;
    return obj;
}
