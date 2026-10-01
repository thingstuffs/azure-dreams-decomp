#include "common.h"

typedef struct {
    u8 v[4];
} ValueList;

typedef struct {
    u8 pad[0x5C];
    s32 (*callback)(s32);
} CallbackOwner;

extern CallbackOwner *D_A0700F58[4];
extern ValueList D_A0700100[4];

/* Returns the index of the callback value or the table's zero terminator. */
s32 func_808B2B04(void)
{
    ValueList values;
    s32 callback_value;
    s32 index;

    values = D_A0700100[0];
    callback_value = D_A0700F58[0]->callback(11);
    for (index = 0; values.v[index] != 0; index++) {
        if (values.v[index] == callback_value) {
            break;
        }
    }
    return index;
}
