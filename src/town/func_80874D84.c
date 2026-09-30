#include "common.h"

typedef struct {
    u8 bytes[4];
} ByteTable;

typedef struct {
    u8 pad[0x5C];
    s32 (*callback)(s32);
} CallbackOwner;

extern CallbackOwner *D_80701984[4];
extern ByteTable D_80700BC4;

/* Return the index of the callback value in the byte table, or its terminator. */
s32 func_80874D84(void)
{
    ByteTable byte_table;
    s32 callback_value;
    s32 index;

    byte_table = D_80700BC4;
    callback_value = D_80701984[0]->callback(11);
    index = 0;
    while (byte_table.bytes[index] != 0) {
        if (byte_table.bytes[index] == callback_value) {
            break;
        }
        index++;
    }
    return index;
}
