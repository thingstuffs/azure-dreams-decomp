#include "common.h"
#include "engine/effect.h"
#include "engine/resource.h"
#include "engine/scene.h"

typedef struct S_8004ED5C {
    void (*unk18)(void *);
} S_8004ED5C;

/* Registers the object's input handler and installs its update callback on success. */
void schedule_deferred_resource_transition(void *object)
{
    void *handler_object = object;

    if (create_deferred_resource_transition_task(1, 0x1E, (void *)dispatch_after_controller_release, handler_object) != 0) {
        ((S_8004ED5C *)((u8 *)handler_object - 0x10))->unk18 = load_transition_image_and_begin_data_read;
    }
}
