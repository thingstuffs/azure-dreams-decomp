/* Dispatch idle town actors and clear their status before target updates. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800478B8(void *entity);


/* Calls the handler when the object status is zero. */
void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, s32 callback_arg) {
    if (object->unk_92 == 0) {
        func_800478B8(callback_arg);
    }
}
#include "common.h"

extern s32 func_8003DB94();
extern s32 select_sprite_entry(int, short, short);

/* Clear the object status byte and dispatch the target update using its mode byte. */
void clear_object_status_and_dispatch_target(void *object, int target, int value, s16 flags) {
    *(s8 *)((s8 *)object + 0x92) = 0;
    if (*(u8 *)((s8 *)object + 0x93) == 0) {
        func_8003DB94(target, value, flags);
        return;
    } else {
        select_sprite_entry(target, value, flags);
    }
}
