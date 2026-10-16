#include "common.h"

extern s32 runtimeIsRecordFieldSet(void *);
extern void townInstallStoredValueHandler(void *object, void *unused, void *update_arg);
extern void func_800C37C4(void *object, void *unusedArg, void *initializationArg);

typedef void (*FuncPtr)(void *, void *, void *);

/* Update the object's flag and dispatch its current state handler. */
void townDispatchObjectState(void *object, void *context, void *dispatch_data) {
    u8 *object_bytes = (u8 *) object;
    u8 state;

    if (runtimeIsRecordFieldSet(object) != 0) {
        object_bytes[0x15] = 1;
    }
    state = object_bytes[0x94];
    if (state == 0) {
        *(u16 *)(object_bytes + 0x72) = *(u16 *)(object_bytes + 0x6E);
        townInstallStoredValueHandler(object, context, dispatch_data);
        return;
    }
    if (state == 1) {
        func_800C37C4(object, context, dispatch_data);
        return;
    }
    (*(FuncPtr *)((((u8 *) object_bytes)[0x94] * 4) + *(s32 *)(object_bytes + 0x58) - 8))(object, context,
        dispatch_data);
}
