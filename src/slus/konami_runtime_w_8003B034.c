#include "common.h"

#include "common.h"

void clear_alternate_texture_regions(s16 use_alt_rect);
s32 func_80048D20();                                /* extern */
extern s32 D_80080A80;

/* Save the result of func_80048D20 and transfer both image variants through the scratch buffer. */
void func_8003B034(void) {
    D_80080A80 = func_80048D20();
    clear_alternate_texture_regions(1);
    clear_alternate_texture_regions(0);
}
