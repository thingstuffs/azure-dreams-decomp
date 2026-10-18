#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800478B8(void *entity);


/* Calls the handler when the object status is zero. */
void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, s32 callback_arg) {
    if (object->unk_92 == 0) {
        func_800478B8(callback_arg);
    }
}
