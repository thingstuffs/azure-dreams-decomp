#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H
/* Prototypes of the functions defined in src/engine/input/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* InitPAD writes 0x22 bytes per port. The button reader decodes this prefix. */
enum ControllerReplyOffset {
    PAD_REPLY_STATUS = 0,
    PAD_REPLY_ID = 1,
    PAD_REPLY_BUTTONS_HIGH = 2,
    PAD_REPLY_BUTTONS_LOW = 3
};

enum { PAD_REPLY_LENGTH = 0x22 };
extern u8 controller_port_one_reply[];
extern u8 controller_port_two_reply[];

/* get_pad_buttons.c */
s32 get_held_pad_buttons(void);

/* get_pad_trigger_buttons.c */
s32 get_pressed_pad_buttons(void);

#endif
