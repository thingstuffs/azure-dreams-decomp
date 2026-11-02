#include "shared/object_node.h"
#include "frontend/libcard/card_chooser.h"
#include "common.h"
#include "frontend/card/menu.h"
#include "main/data.h"


/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */

extern void forward_target_value_initcardmessageobject_parameters(void *first_ptr, void *second_ptr);

/* Narrow absolute symbol binds: these two -0x10 stores in the retail asm use
 * lui/addiu (address-of relocation form), not lui/ori (raw int), against two
 * EXE-side code addresses that are not yet named func_ symbols in this repo.
 * Bind them locally as opaque objects at their real linked addresses so the
 * store compiles to the same %hi/%lo(addiu) address computation. */

/* Chooses the next menu callback and, when needed, initializes its message and active-state flags. */
void card_boot_initialize_menu_pointer(void *ptr) {
    if (((CardChooserBody *)ptr)->unk_3C != 0) {
        ((ObjectNodeHeader *)ptr - 1)->update_callback = card_boot_handle_menu_selection_input;
        return;
    }
    ((CardChooserBody *)ptr)->unk_40 = 1;
    forward_target_value_initcardmessageobject_parameters(ptr - 0x20, ptr + 0x38);
    ((CardChooserBody *)ptr)->wait_notice_state = 1;
    ((ObjectNodeHeader *)ptr - 1)->update_callback = &D_80407F40;
}
