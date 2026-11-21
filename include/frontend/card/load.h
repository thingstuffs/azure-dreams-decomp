#ifndef FRONTEND_CARD_LOAD_H
#define FRONTEND_CARD_LOAD_H
/* Prototypes of the functions defined in src/frontend/card/load/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct CardDevLoadSlotScreen;
struct S_func_80406AA8_0;
struct ObjectNodeHeader;

/* The load-screen information window and the five slot headers built at body offset 0x0C. */
typedef struct CardDevLoadSlotWindows {
    u8 pad_00[4];
    void *info_window;
    u8 pad_08[4];
    struct ObjectNodeHeader *windows[5];
} CardDevLoadSlotWindows;

void card_dev_build_load_slot_windows(struct CardDevLoadSlotScreen *screen);

/* card_devkit_highlight_selected_load_slot.c */
void card_devkit_highlight_selected_load_slot(void *ptr);

/* handle_menu_selection_input.c */
void handle_menu_selection_input(void *object);

/* init_save_header_buffer.c */
void init_save_header_buffer(short *dest, int index, int mode);

/* select_load_slot_callback.c */
void select_load_slot_callback(void *ptr);

/* resume_load_menu_input.c */
void resume_load_menu_input(void *ptr);

/* finish_load_slot_check.c */
void finish_load_slot_check(struct S_func_80406AA8_0 *state);

/* MAIN card server callback at 0x80406A74. Sets mode 2 and starts the default screen. */
void set_global(void);

#endif
