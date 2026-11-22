#include "frontend/card/message_display.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/* Process the embedded data at offset 0x24, then the containing object. */
void init_dialog_object(CardDevDialogDisplay *object) {
    initialize_four_paired_drawing_records(object->command_buffer, object);
    position_linked_dialog_and_bind_object_data(object);
}
