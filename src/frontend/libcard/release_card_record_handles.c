#include "frontend/libcard.h"
#include "shared/object_flags.h"
#include "engine/menu.h"
extern void set_save_heading_owner(CardHeadingDrawState *work, s32 value);
extern void func_800271C0(void *sprite, void *position, void *extra);
extern void func_80024EEC(void *object);
extern void func_80027458(void *object);
extern void func_80024184(void *object);
extern s32 D_800814A0;

void release_card_record_handles(CardHandleOwner *object) {
    void **cursor;
    s32 index;
    cursor = object->handles;
    if (object != 0) {
        index = 0;
        set_object_cleanup_flag(object->handles[0]);
        func_80024EEC(cursor[1]);
        func_80027458(cursor[2]);
        do {
            void *handle = cursor[3];
            cursor++;
            index++;
            func_80024184(handle);
        } while (index < 5);
        object->flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
