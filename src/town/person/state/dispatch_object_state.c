#include "common.h"

extern s32 runtime_is_record_field_set(void *);
extern void install_stored_value_handler(void *object, void *unused, void *update_arg);
extern void initialize_object_assigns_state_data(void *object, void *unusedArg, void *initializationArg);

typedef void (*FuncPtr)(void *, void *, void *);

/* Update the object's flag and dispatch its current state handler. */
void dispatch_object_state(void *object, void *context, void *dispatch_data) {
    u8 *object_bytes = (u8 *) object;
    u8 state;

    if (runtime_is_record_field_set(object) != 0) {
        object_bytes[0x15] = 1;
    }
    state = object_bytes[0x94];
    if (state == 0) {
        *(u16 *)(object_bytes + 0x72) = *(u16 *)(object_bytes + 0x6E);
        install_stored_value_handler(object, context, dispatch_data);
        return;
    }
    if (state == 1) {
        initialize_object_assigns_state_data(object, context, dispatch_data);
        return;
    }
    (*(FuncPtr *)((((u8 *) object_bytes)[0x94] * 4) + *(s32 *)(object_bytes + 0x58) - 8))(object, context,
        dispatch_data);
}
