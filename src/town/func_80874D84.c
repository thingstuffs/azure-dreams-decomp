#include "common.h"

typedef struct {
    u32 value;
} __attribute__((packed)) UnalignedWord;

typedef struct {
    u8 pad[0x5C];
    s32 (*callback)(s32);
} CallbackOwner;

extern CallbackOwner *D_80701984[4];
extern UnalignedWord D_80700BC4[4];

/* Return the index of the callback value in the byte table, or its terminator. */
s32 func_80874D84(void)
{
    u8 byte_table[4];
    s32 callback_value;
    s32 index;
#ifdef NON_MATCHING
    s32 zero = 0;
#else
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif
    s32 result;

    *(UnalignedWord *)byte_table = D_80700BC4[0];
    callback_value = D_80701984[0]->callback(zero | 11);
    index = 0;
    while (byte_table[index] != 0) {
        if (byte_table[index] == callback_value) {
            break;
        }
        index++;
    }
    result = index;
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return result;
}
