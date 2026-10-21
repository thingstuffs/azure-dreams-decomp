#include "common.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void card_boot_handle_format_answer(void *object) {
    void *handler;

    if (*(s32 *)((s8 *)object + 0x3C) != 0) {
        handler = D_8002789C;
    } else {
        *(s32 *)((s8 *)object + 0x40) = 1;
        card_boot_show_formatting_progress((s8 *)object - 0x20, (s8 *)object + 0x38);
        *(s32 *)((s8 *)object + 0x38) = 1;
        handler = D_8002765C;
    }
    *(void **)((s8 *)object - 0x10) = handler;
}
