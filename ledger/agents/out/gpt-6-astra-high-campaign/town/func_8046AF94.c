#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

extern u8 *D_8001E950;
extern s32 func_8001A86C(s32);

/* Update the selected object record when the current state is 1. */
s32 func_8001BF94(TownObject *object, s32 record_index) {
    if (D_8001E950[5] == 1) {
        *(s32 *)((record_index * 0x10) + (uptr)object->records + 8) =
            func_8001A86C(0);
        return 0;
    }
    return 1;
}
