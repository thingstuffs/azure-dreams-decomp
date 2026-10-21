/* Dispatch idle town actors and clear their status before target updates. */

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


void advance_sprite_animation_and_textures(void *entity);


/* Calls the handler when the object status is zero. */
extern s32 select_record_entry_and_value();
extern s32 select_sprite_entry(int, short, short);

void dispatch_object_when_idle(Rec_func_80094268_arg0 *object, s32 callback_arg) {
    if (object->unk_92 == 0) {
        advance_sprite_animation_and_textures(callback_arg);
    }
}


/* Clear the object status byte and dispatch the target update using its mode byte. */
void clear_object_status_and_dispatch_target(void *object, int target, int value, s16 flags) {
    *(s8 *)((s8 *)object + 0x92) = 0;
    if (*(u8 *)((s8 *)object + 0x93) == 0) {
        select_record_entry_and_value(target, value, flags);
        return;
    } else {
        select_sprite_entry(target, value, flags);
    }
}
