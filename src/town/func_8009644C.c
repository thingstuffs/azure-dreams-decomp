#include "common.h"

extern s32 get_item_chk(void);
extern void func_8008B5D8(void *value, s32 code);
extern void func_800947BC(s32 object, s32 position, s32 context);
extern void func_80094774(s32 object, s32 position, s32 context);
extern s32 D_80088D44;
extern s32 D_80093D48;
extern s32 *D_800FE5D8;
extern s32 D_800FE518;

/* Select the object's next state based on slot availability. */
void func_80093BAC(s32 object, s32 position, s32 context) {
    if (get_item_chk() == -1) {
        func_8008B5D8(&D_80088D44, 0x11);
        func_800947BC(object, position, context);
        D_800FE5D8 = &D_80093D48;
        return;
    }
    func_80094774(object, position, context);
    D_800FE518 = 0;
}
