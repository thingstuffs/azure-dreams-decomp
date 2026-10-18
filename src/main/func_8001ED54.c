#include "common.h"

extern s32 D_8009DDD8[];
extern void dispatch_operation_mode_context(void *, void *);
extern void initialize_card_message_object_with_code_7(void *);
extern void func_80405D2C(void);
extern void handle_object_menu_input(void);
extern void func_80405A64(void);

/* Arm the task's next callback: ready slot -> attach the sub-object, otherwise detach it. */
void func_8001ED54(void *task)
{
    s32 one;
    void *owner;
    s32 index;
    void (*callback)(void);

    owner = (u8 *)task - 0x20;
    index = *(s32 *)((u8 *)task + 0x28);
    if (D_8009DDD8[index * 0x20] != 0) {
        one = 1;
        *(s32 *)((u8 *)task + 0x3C) = one;
        dispatch_operation_mode_context(owner, (u8 *)task + 0x40);
        callback = func_80405D2C;
        *(s32 *)((u8 *)task + 0x40) = one;
    } else {
        *(void (**)(void))((u8 *)task + 0x34) = handle_object_menu_input;
        initialize_card_message_object_with_code_7(owner);
        callback = func_80405A64;
    }
    *(void (**)(void))((u8 *)task - 0x10) = callback;
}
