#include "common.h"

#include "common.h"

s32 ClearImage(void *, u8, u8, u8);
void clear_graphics_record();                   /* extern */
void initialize_script_cursor_and_defaults();                   /* extern */
void initialize_runtime_resource_directory();                            /* extern */
extern u8 graphics_clear_rectangle_0[];
extern u8 graphics_clear_rectangle_1[];
extern u8 D_80082A38[];

/* Reset graphics state and clear both image regions to black. */
void reset_graphics_state(void) {
    initialize_runtime_resource_directory();
    clear_graphics_record(&D_80082A38);
    initialize_script_cursor_and_defaults(&D_80082A38);
    ClearImage(&graphics_clear_rectangle_0, 0, 0, 0);
    ClearImage(&graphics_clear_rectangle_1, 0, 0, 0);
}
