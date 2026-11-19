#include "frontend/libcard.h"
#include "shared/object_flags.h"
extern void set_save_heading_owner(ObjectNodeHeader **dest, ObjectNodeHeader *owner);
extern void func_800271C0(void *sprite, void *position, void *extra);

void prepare_save_heading_layout(CardHeadingDrawState *work, ObjectNodeHeader *owner) {
    set_save_heading_owner(&work->owner, owner);
    func_800271C0(work->pad_E0, &work->display_block, &work->display_vector);
    card_boot_initialize_save_heading_layout(work);
}
