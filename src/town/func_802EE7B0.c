#include "common.h"

extern void func_804057A8(void *, s32);
extern void initialize_menu_primitive_settings(void *, void *, void *);
extern void initialize_menu_item_positions(void *);
void initialize_menu_overlay_objects(u8 *owner, s32 value) {
    func_804057A8(owner, value);
    initialize_menu_primitive_settings(owner + 0xAF8, owner + 0xAD0, owner + 0xAE0);
    initialize_menu_item_positions(owner);
}
