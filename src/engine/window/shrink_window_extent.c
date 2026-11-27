#include "common.h"

#include "engine/effect.h"
#include "engine/window.h"
#include "engine/window/message.h"

typedef struct Func80035C80Object Func80035C80Object;

struct Func80035C80Object {
    u8 pad00[0x44];
    u8 *state_table;
    u8 pad48[2];
    s16 object_id;
    u8 pad4C[4];
    u8 field50;
    u8 pad51[0x17];
    void (*field68)(struct Rec_func_80036210_arg0 *, WindowExtentEntry *);
    u8 pad6C[8];
    u8 *owner;
    u8 watched_value;
};

/* Flag the referenced record and switch callbacks when the state byte changes. */
void fade_and_shrink_window_on_value_change(Func80035C80Object *object) {
    if (object->watched_value != object->owner[1]) {
        u8 *record_base = object->state_table;
        s16 record_offset = object->object_id;
        (record_base + record_offset)[0x50] = 1;
        begin_fade_to_black();
        object->field68 = shrink_window_extent_to_minimum;
    }
}
