#ifndef ENGINE_WINDOW_CURSOR_BODY_H
#define ENGINE_WINDOW_CURSOR_BODY_H
#include "common.h"
#include "records/Rec_D_80081FDC.h"
/* Body prefix shared by the cursor constructors (node + 0x20 of a window-list node); the cursor's sprite is
 * the node's SpriteFrameState, which the update callbacks receive as their third argument. */
typedef struct WindowCursorBody {
    Rec_D_80081FDC *model;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 *script;
    u8 enabled; /* nonzero while the cursor is live; unlink_cursor_when_finished tests it before checking the parent entry state */
    u8 pad_49;
    s16 cursor_offset;
    u8 pad_4C[0x18];
    u16 blink_frame;
    s16 variant_offset;
} WindowCursorBody;
#endif
