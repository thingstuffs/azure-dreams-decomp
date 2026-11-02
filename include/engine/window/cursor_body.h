#ifndef ENGINE_WINDOW_CURSOR_BODY_H
#define ENGINE_WINDOW_CURSOR_BODY_H
#include "common.h"
#include "records/Rec_D_80081FDC.h"
/* Prefix shared by the cursor constructors. Separate sprite views keep their
 * descriptor-pointer and descriptor-word interfaces. */
typedef struct WindowCursorBody {
    Rec_D_80081FDC *model;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 *script;
    union { s8 s; u8 u; } enabled;
    u8 pad_49;
    s16 cursor_offset;
    u8 pad_4C[0x18];
    u16 blink_frame;
    s16 variant_offset;
} WindowCursorBody;
#endif
