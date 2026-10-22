#include "common.h"
#include "shared/object_flags.h"

typedef struct CallbackEntry CallbackEntry;
typedef void (*Callback)(CallbackEntry *);

struct CallbackEntry {
    Callback callback;
    u8 pad[20];
};

extern s32 classify_object_against_bounds(void *, void *);
extern CallbackEntry D_800D4710[];

/* Runs callbacks unless the object check triggers status clearing and flag updates. */
void run_callbacks_unless_suppressed(void *object, void *check_data)
{
    CallbackEntry *entry = D_800D4710;
    u8 *status_byte;

    if (classify_object_against_bounds(object, check_data) != 0) {
        status_byte = *(u8 **)((u8 *)object + 0x98);
        if (status_byte != 0) {
            *status_byte = 0;
        }
        *(u16 *)((u8 *)object - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    while (entry->callback != 0) {
        entry->callback(entry);
        entry++;
    }
}
