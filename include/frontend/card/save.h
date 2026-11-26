#ifndef FRONTEND_CARD_SAVE_H
#define FRONTEND_CARD_SAVE_H
/* Prototypes of the functions defined in src/frontend/card/save/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct ObjectNodeHeader;
struct S_func_804061C4_0;
struct CardSaveOperationBody;

/* The five window headers stored by the save-slot builder at body offset 0x04. */
typedef struct CardDevSaveSlotWindows {
    u8 pad_00[4];
    struct ObjectNodeHeader *windows[5];
} CardDevSaveSlotWindows;

/* card_dev_create_save_screen.c */
struct CardSaveScreenState;
struct ObjectNodeHeader;
struct CardSaveScreenState *card_dev_create_save_screen(struct ObjectNodeHeader *request);

/* select_save_slot_callback.c */
void select_save_slot_callback(struct CardSaveOperationBody *base);

/* card_devkit_build_save_slot_windows.c */
void card_devkit_build_save_slot_windows(struct CardSaveOperationBody *base);

/* card_devkit_refresh_save_slot_pair_highlights.c */
void card_devkit_refresh_save_slot_pair_highlights(struct CardSaveOperationBody *menu);

/* card_devkit_refresh_save_slot_selection.c */
void card_devkit_refresh_save_slot_selection(struct CardSaveOperationBody *menu);

/* finish_save_slot_check.c */
void finish_save_slot_check(void *context);

struct S_8001EC4C_0;
/* MAIN card server callback at 0x80405C4C. Selects the next action from the save body. */
void set_object_state_and_select_action(struct S_8001EC4C_0 *object);

/* Save-menu body shared by the input handler and its action dispatcher. */
typedef struct CardDevSaveMenuBody {
    u8 pad_00[0x20];
    void *unk_20;
    u8 pad_24[4];
    s32 unk_28;
    u8 pad_2C[4];
    s32 repeat_ticks;
    u8 pad_34[0x10];
    s32 callback_index;
    s32 unk_48;
} CardDevSaveMenuBody;

/* card_dev_dispatch_callback_by_index at its MAIN card server address 0x804062F4. */
void invoke_indexed_object_callback(struct CardSaveOperationBody *object);

/* handle_object_menu_input.c */
void handle_object_menu_input(struct CardSaveOperationBody *menu);

/* refresh_save_slot_selection_and_resume_menu_input.c */
void refresh_save_slot_selection_and_resume_menu_input(struct CardSaveOperationBody *menu);

/* finish_save_slot_operation.c */
void finish_save_slot_operation(struct CardSaveOperationBody *menu);

/* commit_save_and_refresh_slots.c */
void commit_save_and_refresh_slots(struct CardSaveOperationBody *menu);

/* select_slot_menu_callback.c */
void select_slot_menu_callback(struct CardSaveOperationBody *object_state);

#endif
