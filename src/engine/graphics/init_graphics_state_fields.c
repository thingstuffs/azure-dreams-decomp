#include "engine/message.h"

#include "engine/graphics.h"
#include "slus/data.h"

/* Initializes state fields and copies the global default byte. */
void init_graphics_state_fields(ScriptController *controller, s32 mode)
{
    u8 default_byte;

    *(u32 *)0x8008099C = 0;
    update_text_row_scale(controller, (u8)mode);
    controller->mode = mode;
    controller->reset_requested = 0;
    controller->camera_target_slot = 0;
    default_byte = message_mode_default_bytes[0];
    controller->field3D = 0;
    controller->pending_script = 0;
    controller->field3C = default_byte;
}
