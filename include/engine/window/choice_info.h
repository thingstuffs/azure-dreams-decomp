#ifndef ENGINE_WINDOW_CHOICE_INFO_H
#define ENGINE_WINDOW_CHOICE_INFO_H

#include "common.h"

/* The message handler selects the menu initializer through the window's
 * +0x74 link. The cursor wraps by count and writes selection on confirm. */
typedef struct CursorInfo {
    u8 pad_00[0x22];
    u16 line;
    u8 pad_24[2];
    u8 count;
    u8 selection;
    u8 pad_28[0x58];
    void *list_head;
} CursorInfo;

struct S_80036484_0;

/* Input passes this same window to confirmation, which starts the countdown,
 * saves its selection in the message record and installs the wait callback. */
typedef struct CursorState {
    u8 pad_00[0x4D];
    u8 cursor_4D;
    u8 pad_4E[0x16];
    s16 countdown;
    u8 pad_66[2];
    void (*next_callback)(struct S_80036484_0 *);
    u8 pad_6C[8];
    CursorInfo *info_74;
} CursorState;

#endif
