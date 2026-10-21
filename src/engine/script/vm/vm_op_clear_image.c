#include "common.h"

#include "common.h"
#include "engine/script/vm.h"
#include "sdk/libgpu.h"

/* Handles event-script image clearing by zeroing two state fields and clearing the rectangle to black. */
void vm_op_08_clear_image(void *vm_state) {
    *(s16 *)((u8 *)vm_state + 0x20) = 0;
    *(s16 *)((u8 *)vm_state + 0x22) = 0;
    ClearImage(vm_state, 0, 0, 0);
}
