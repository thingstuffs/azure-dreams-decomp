#ifndef FRONTEND_LIBCARD_SLOT_MENU_H
#define FRONTEND_LIBCARD_SLOT_MENU_H
#include "common.h"
typedef struct CardSlotMenuState {
    void *backdrop;
    struct ObjectNodeHeader *slots[5];
    struct ObjectNodeHeader *command_panel;
    struct ObjectNodeHeader *slot_details;
    struct ObjectNodeHeader *request;
    s32 mode;
    s32 unk_28;
    s32 unk_2C;
    s32 unk_30;
    void *saved_callback;
    s32 dialog_response;
    s32 countdown;
    s32 unk_40;
    s32 selected_command; /* +0x44: command row cursor, wrapped over three commands by card_boot_handle_slot_selection_input; indexes the card_boot_dispatch_selected_menu_action table */
    s32 unk_48;
    s32 unk_4C;
} CardSlotMenuState;

#endif
