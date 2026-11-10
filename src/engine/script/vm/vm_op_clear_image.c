#include "common.h"

#include "engine/script/vm.h"
#include "sdk/libgpu.h"
#include "engine/script.h"

/* Opcode 0x08: Clear the text window and reset the text cursor. */
void script_clear_text_window(ScriptReader *vm_state) {
    *(s16 *)((u8 *)vm_state + 0x20) = 0;
    *(s16 *)((u8 *)vm_state + 0x22) = 0;
    ClearImage(vm_state, 0, 0, 0);
}
