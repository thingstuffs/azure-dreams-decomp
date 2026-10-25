#include "frontend/libcard.h"
#include "shared/object_flags.h"
extern void set_save_heading_owner(CardHeadingDrawState *work, s32 value);
extern void func_800271C0(void *sprite, void *position, void *extra);
extern void set_object_cleanup_flag(void *object);
extern void func_80024EEC(void *object);
extern void func_80027458(void *object);
extern void func_80024184(void *object);
extern s32 D_800814A0;

void prepare_save_heading_layout(CardHeadingDrawState *work, s32 value) {
    set_save_heading_owner(work, value);
    func_800271C0(work->pad_E0, work->pad_00 + 0xB8, work->pad_00 + 0xC8);
    card_boot_initialize_save_heading_layout(work);
}
