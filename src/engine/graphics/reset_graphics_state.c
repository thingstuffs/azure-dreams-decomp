#include "common.h"

#include "common.h"

s32 ClearImage(void *, u8, u8, u8);
void clear_graphics_record();                   /* extern */
void func_80034EC4();                   /* extern */
void func_8003C920();                            /* extern */
extern u8 D_800809A8[];
extern u8 D_800809B0[];
extern u8 D_80082A38[];

/* Reset graphics state and clear both image regions to black. */
void reset_graphics_state(void) {
    func_8003C920();
    clear_graphics_record(&D_80082A38);
    func_80034EC4(&D_80082A38);
    ClearImage(&D_800809A8, 0, 0, 0);
    ClearImage(&D_800809B0, 0, 0, 0);
}
