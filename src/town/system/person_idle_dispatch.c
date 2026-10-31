/* Dispatch idle town actors and clear their status before target updates. */

#include "common.h"
#include "town/system/person_idle_dispatch.h"
#include "engine/graphics.h"
#include "slus.h"




/* Calls the handler when the object status is zero. */

/* Advances the supplied sprite animation only when the object halfword at offset 0x92 is zero. */
void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, void *callback_arg, s32 unused_a, s32 unused_b) {
    if (object->unk_92 == 0) {
        advance_sprite_animation_and_textures(callback_arg);
    }
}


/* Clear the object status byte and dispatch the target update using its mode byte. */
void clear_object_status_and_dispatch_target(void *object, void *target, int value, s16 flags) {
    *((s8 *)object + 0x92) = 0;
    if (*(u8 *)((s8 *)object + 0x93) == 0) {
        select_record_entry_and_value(target, value, flags);
        return;
    } else {
        select_sprite_entry(target, value, flags);
    }
}
