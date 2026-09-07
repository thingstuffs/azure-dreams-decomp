#include "common.h"
#include "m2c_compat.h"

M2C_UNK strcat();              /* extern */
M2C_UNK strcpy();                    /* extern */
extern u8 D_80027F18;
extern M2C_UNK D_80027F20;
extern M2C_UNK D_80027F30;
extern s32 D_800287CC;

/* Builds a string from the selected prefix, a separator, and an indexed suffix. */
void func_80021B18(s32 dest, s32 suffix_index) {
    s32 *prefix_ptr;

    prefix_ptr = &D_80027F18;
    if (D_800287CC != 0) {
        prefix_ptr = &D_80027F18 + 4;
    }
    strcpy(dest, *prefix_ptr);
    strcat(dest, &D_80027F20);
    strcat(dest, ((s32 *) &D_80027F30)[suffix_index]);
}
