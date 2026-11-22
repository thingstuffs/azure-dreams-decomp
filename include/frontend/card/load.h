#ifndef FRONTEND_CARD_LOAD_H
#define FRONTEND_CARD_LOAD_H
struct CardDevSaveWork;
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

#include "shared/object_node.h"

struct ObjectNodeHeader;
struct CardDevSlotWindow;

/* Body of the devkit load screen's slot-window builder object (offsets of the server build). */
typedef struct CardDevLoadSlotScreen {
    struct ObjectNodeHeader *background;
    struct ObjectNodeHeader *information;
    struct ObjectNodeHeader *slot_display;
    struct CardDevSlotWindow *windows[5];
    struct ObjectNodeHeader *request;
    s32 mode;
    s32 window_count;
    s32 selection;
    s32 repeat_ticks;
    void *state_callback;
    s32 dialog_answer;
    s32 countdown;
    s32 operation_state;
} CardDevLoadSlotScreen;

typedef struct CardDevLoadNode {
    ObjectNodeHeader node;
    CardDevLoadSlotScreen body;
} CardDevLoadNode;
struct CardDevLoadNode *card_dev_create_load_screen(struct ObjectNodeHeader *request, s32 mode);
struct CardDevLoadNode *allocate_initializes(struct ObjectNodeHeader *request, s32 mode);

void card_dev_release_load_screen_parts(CardDevLoadNode *screen);
void card_dev_build_load_slot_windows(struct CardDevLoadSlotScreen *screen);

/* card_devkit_highlight_selected_load_slot.c */
void card_devkit_highlight_selected_load_slot(CardDevLoadSlotScreen *screen);

/* handle_menu_selection_input.c */
void handle_menu_selection_input(CardDevLoadSlotScreen *screen);

/* init_save_header_buffer.c */
void init_save_header_buffer(struct CardDevSaveWork *save, int index, int mode);

/* select_load_slot_callback.c */
void select_load_slot_callback(CardDevLoadSlotScreen *screen);

/* resume_load_menu_input.c */
void resume_load_menu_input(CardDevLoadSlotScreen *screen);

/* finish_load_slot_check.c */
void finish_load_slot_check(CardDevLoadSlotScreen *screen);

/* MAIN card server callback at 0x80406A74. Sets mode 2 and starts the default screen. */
void set_global(void);

#endif
