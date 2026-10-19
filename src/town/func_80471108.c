#include "common.h"
#include "shared/town_event_buffer.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
void func_80018824(void *, s32);          /* extern */
void func_80018914(void *);                   /* extern */
extern s32 D_8001B318;

/* Prepares D_8001B218 for the active object's callback and stores its result. */
void prepare_active_object_callback(void) {
    func_80018824(D_8001B218, 0x100);
    func_80018914(D_8001B218);
    D_8001B318 = D_80016000->unk_20->callback_068(0, 1, 1, D_8001B218);
}
