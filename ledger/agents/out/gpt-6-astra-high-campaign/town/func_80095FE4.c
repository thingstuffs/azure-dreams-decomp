#include "common.h"

extern u32 func_8009368C(void *arg0, s32 arg1, s32 arg2);
extern void func_80098868(void *arg0, s32 arg1, s32 arg2);

extern s32 D_800834B8;
extern s32 D_8009C340;

/* plt_carry_item_del_ext: Updates the carried object and detaches it when its type or state matches. */
void func_80093744(void) {
    u8 *base;
    void *input_values;
    s32 first_value;
    s32 second_value;
    u8 *saved_object;
    void *context;

    base = (u8 *)&D_800834B8;
    context = base;
    input_values = base - 0x20;
    first_value = *(s32 *)((u8 *)input_values + 8);
    second_value = *(s32 *)((u8 *)input_values + 0xC);
    saved_object = *(u8 **)(base + 0x2C);
    ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    if (func_8009368C(context, first_value, second_value) != 0) {
        u8 *linked_object;

        func_80098868(base, first_value, second_value);
        linked_object = *(u8 **)(base + 0x2C);
        if (linked_object != 0 && (linked_object[0x14] == 4 || linked_object[0x4D] == 0xD)) {
            *(s32 **)(saved_object + 0x50) = &D_8009C340;
            *(u8 **)(base + 0x2C) = 0;
        }
    }
}
