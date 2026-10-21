#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "slus/data.h"

void initialize_script_cursor_and_defaults();                   /* extern */
extern u8 runtime_script_state[];

/* Reset graphics state and clear both image regions to black. */
void reset_graphics_state(void) {
    initialize_runtime_resource_directory();
    clear_graphics_record(&runtime_script_state);
    initialize_script_cursor_and_defaults(&runtime_script_state);
    ClearImage(&graphics_clear_rectangle_0, 0, 0, 0);
    ClearImage(&graphics_clear_rectangle_1, 0, 0, 0);
}
