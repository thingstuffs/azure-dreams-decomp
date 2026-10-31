#include "common.h"
#include "engine/window.h"
#include "town/event.h"
#include "town/person.h"
#include "town/event/object.h"

struct EntityRec; struct Rec_D_80082E80; struct Rec_func_80094268_arg0;

/* Randomize color during an update, then reset it when the timer expires or state changes. */
void randomize_person_color(void *object, s32 context, s32 update_param, void *color_data) {
    s32 previous_state;
    s16 ticks_left;

    *((s8 *)color_data + 0xC) = scale_random_to_unsigned_halfword_limit(0x100);
    *((s8 *)color_data + 0xD) = scale_random_to_unsigned_halfword_limit(0x100);
    *((s8 *)color_data + 0xE) = scale_random_to_unsigned_halfword_limit(0x100);
    previous_state = *(s32 *)((s8 *)object + 0x50);
    update_actor_surface_motion(object, (void *)(context), (void *)(update_param), color_data);
    ticks_left = *(u16 *)((s8 *)object + 0x6C) - 1;
    *(u16 *)((s8 *)object + 0x6C) = ticks_left;
    if ((ticks_left < 0) || (*(s32 *)((s8 *)object + 0x50) != previous_state)) {
        select_object_value_by_height_band(object, (void *)(context), (struct EntityRec *)(update_param), color_data);
        *((u8 *)color_data + 0xC) = 0x80;
        *((u8 *)color_data + 0xD) = 0x80;
        *((u8 *)color_data + 0xE) = 0x80;
    }
}
