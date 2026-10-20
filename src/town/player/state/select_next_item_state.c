#include "common.h"

extern s32 get_item_chk(void);
extern void write_resource_command(void *value, s32 code);
extern void set_item_selection_data_pointer(s32 object, s32 position, s32 context);
extern void func_80094774(s32 object, s32 position, s32 context);
extern s32 D_80088D44;
extern s32 D_80093D48;
extern s32 *D_800FE5D8;
extern s32 D_800FE518;

/* Select the object's next state based on slot availability. */
void select_next_item_state(s32 object, s32 position, s32 context) {
    if (get_item_chk() == -1) {
        write_resource_command(&D_80088D44, 0x11);
        set_item_selection_data_pointer(object, position, context);
        D_800FE5D8 = &D_80093D48;
        return;
    }
    func_80094774(object, position, context);
    D_800FE518 = 0;
}
