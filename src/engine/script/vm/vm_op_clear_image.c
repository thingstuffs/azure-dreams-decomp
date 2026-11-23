#include "common.h"

#include "engine/script/vm.h"
#include "sdk/libgpu.h"
#include "engine/script.h"

/* Opcode 0x08: Clear the text window and reset the text cursor. */
void script_clear_text_window(MessageWindow *vm_state) {
    vm_state->column = 0;
    vm_state->row = 0;
    ClearImage(&vm_state->texture_rect, 0, 0, 0);
}
