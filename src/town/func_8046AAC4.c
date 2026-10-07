#include "shared/town_event_state.h"
#include "common.h"

typedef unsigned long uptr;

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

extern s32 func_8001A79C(void);

s32 func_8001BAC4(TownObject *object, s32 index, s32 unused2, s32 unused3) {
    if (D_8001E950->unk_05 != 1) {
        return 1;
    }
    {
                        /* MATCH: Save store operands separately so call arguments retain their incoming registers. */
        TownObject *saved_object = object;
        s32 saved_index = index;
        *(s32 *)((saved_index * 0x10) + (uptr)saved_object->records + 8) =
            func_8001A79C();
        return 0;
    }
}
