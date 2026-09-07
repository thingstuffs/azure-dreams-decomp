#include "common.h"

typedef struct UnkStruct1E {
    u8 pad[0x1E];
    u16 flags;
} UnkStruct1E;

extern int D_800814A0;

extern void func_8004F52C(UnkStruct1E *a0);
extern void func_80023A00(s32 arg0);
extern void func_80024EEC(s32 arg0);
extern void func_80024184(s32 arg0);

/* Processes the object's linked resources and five handles, then sets its and the global 0x8000 flags. */
void func_80025D34(UnkStruct1E *object)
{
    s32 handle;
    s32 handle_count;
    void *handle_cursor;

    handle_cursor = (u8 *)object + 0x20;
    if (object != 0) {
        handle_count = 0;
        func_8004F52C(*(UnkStruct1E **)((u8 *)object + 0x20));
        func_80023A00(*(s32 *)((u8 *)handle_cursor + 0x18));
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
