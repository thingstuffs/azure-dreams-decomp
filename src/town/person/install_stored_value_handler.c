#include "common.h"

#include "town/person/state_updates.h"
#include "town/person/object/initialize_object_entries_api.h"
#include "town/person.h"
extern s32 D_800C34CC;

/* Updates the object using its stored value and installs its next handler. */
void install_stored_value_handler(void *object, void *unused, void *update_arg) {
    struct {
        char pad[0x50];
        void *unk50;
        char pad2[0x7C - 0x54];
        s32 **unk7C;
    } *object_fields = object;

    initialize_object_entries(object, update_arg, *object_fields->unk7C);
    object_fields->unk50 = &D_800C34CC;
}
