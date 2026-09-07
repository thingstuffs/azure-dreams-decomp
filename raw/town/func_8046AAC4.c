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
extern s32 func_8001A79C(void);

s32 func_8001BAC4(TownObject *arg0, s32 arg1) {
    if (D_8001E950[5] == 1) {
        *(s32 *)((arg1 * 0x10) + (uptr)arg0->records + 8) =
            func_8001A79C();
        return 0;
    }
    return 1;
}
