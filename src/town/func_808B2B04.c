#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UnalignedWord;

typedef struct {
    u8 pad[0x5C];
    s32 (*callback)(s32);
} CallbackOwner;

extern CallbackOwner *D_A0700F58[4];
extern UnalignedWord D_A0700100[4];

s32 func_808B2B04(void)
{
    u8 local[4];
    s32 needle;
    s32 i;
    s32 result;

    *(UnalignedWord *)local = D_A0700100[0];
    needle = D_A0700F58[0]->callback(11);
    i = 0;
    while (local[i] != 0) {
        if (local[i] == needle) {
            break;
        }
        i++;
    }
    result = i;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return result;
}
