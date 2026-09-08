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

/* Returns the index of the callback value or the table's zero terminator. */
s32 func_808B2B04(void)
{
    u8 values[4];
    s32 callback_value;
    s32 index;
    s32 result;

    *(UnalignedWord *)values = D_A0700100[0];
    callback_value = D_A0700F58[0]->callback(11);
    index = 0;
    while (values[index] != 0) {
        if (values[index] == callback_value) {
            break;
        }
        index++;
    }
    result = index;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return result;
}
