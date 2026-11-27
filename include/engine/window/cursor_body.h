#ifndef ENGINE_WINDOW_CURSOR_BODY_H
#define ENGINE_WINDOW_CURSOR_BODY_H
#include "common.h"
#include "records/Rec_D_80081FDC.h"
struct WindowCursorSource;

/* Body prefix of every node drawn by draw_linked_sprite_nodes (the six 0x11 window and cursor constructors and
 * the two town-map object initializers): its first word selects the model, the transform record made by
 * init_unit_scale_record, and its third word is 0 or the node's extra drawer, which the walker calls with the
 * node body. */
typedef struct WindowRenderPrefix {
    Rec_D_80081FDC *model;
    s32 field_04;
    void *draw_callback;
} WindowRenderPrefix;

/* Body prefix shared by the cursor constructors (node + 0x20 of a window-list node); the cursor's sprite is
 * the node's SpriteFrameState, which the update callbacks receive as their third argument. */
typedef struct WindowCursorBody {
    WindowRenderPrefix render;
    u8 pad_0C[0x38];
    struct WindowCursorSource *script;
    u8 enabled; /* nonzero while the cursor is live; unlink_cursor_when_finished tests it before checking the parent entry state */
    u8 pad_49;
    s16 cursor_offset;
    u8 pad_4C[0x18];
    u16 blink_frame;
    s16 variant_offset;
} WindowCursorBody;
#endif
