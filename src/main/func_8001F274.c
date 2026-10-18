#include "common.h"

extern u8 D_8009DDD8[];
extern void func_8040339C(void *task, void *attached_state);
extern void initialize_card_message_object_with_code_7(void *task);
extern void process_five_object_entries(void);
extern void handle_object_menu_input(void);
extern void func_80405A64(void);

/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void func_8001F274(u8 *task) {
    u8 *owner = task - 0x20;

    if (*(s32 *)(D_8009DDD8 + (*(u32 *)(task + 0x28) << 7)) != 0) {
        *(void **)(task + 0x34) = (void *)process_five_object_entries;
        func_8040339C(owner, task + 0x38);
        *(void **)(task - 0x10) = (void *)func_80405A64;
        return;
    }
    *(void **)(task + 0x34) = (void *)handle_object_menu_input;
    initialize_card_message_object_with_code_7(owner);

    *(void **)(task - 0x10) = (void *)func_80405A64;
}
