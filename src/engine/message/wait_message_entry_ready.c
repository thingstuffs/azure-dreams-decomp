#include "common.h"
#include "shared/object_index_slots.h"

typedef struct Entry {
    u8 pad_0[1];
    s8 field_1;
    u8 pad_2[6];
} Entry;

typedef struct Object {
    u8 pad_0[0x10];
    void (*callback)(void);
    u8 pad_14[0x1B];
    u8 entry_index;
} Object;

extern void update_message_window(void);

/* Sets the object's callback to update_message_window when its entry's field_1 is zero. */
void wait_message_entry_ready(Object *object)
{
    if (object_index_slots[object->entry_index].unk_01 == 0) {
        object->callback = update_message_window;
    }
}
