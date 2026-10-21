#include "common.h"
#include "engine/menu.h"
#include "frontend/libcard.h"

typedef struct UnkStruct1E {
    u8 pad[0x1E];
    u16 flags;
} UnkStruct1E;

extern int D_800814A0;

extern void func_80024EEC(s32 object);
extern void func_80024184(s32 object);

/* Processes the object's linked resources and five handles, then sets its and the global 0x8000 flags. */
void card_boot_destroy_slot_selection_menu(UnkStruct1E *object)
{
    s32 handle;
    s32 handle_count;
    void *handle_cursor;

    handle_cursor = (u8 *)object + 0x20;
    if (object != 0) {
        handle_count = 0;
        set_object_cleanup_flag(*(UnkStruct1E **)((u8 *)object + 0x20));
        process_nonzero(*(s32 *)((u8 *)handle_cursor + 0x18));
        func_80024EEC(*(s32 *)((u8 *)handle_cursor + 0x1C));
        do {
            handle = *(s32 *)((u8 *)handle_cursor + 4);
            handle_cursor = (u8 *)handle_cursor + 4;
            handle_count += 1;
            func_80024184(handle);
        } while (handle_count < 5);
        object->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
