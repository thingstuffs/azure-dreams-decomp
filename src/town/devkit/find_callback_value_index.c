#include "common.h"

typedef struct {
    u8 v[4];
} ValueList;

typedef struct {
    u8 pad[0x5C];
    s32 (*callback)(s32);
} CallbackOwner;

extern CallbackOwner *devkit_kind_callback_owner[4];
extern ValueList D_A0700100[4];

/* Returns the index of the callback value or the table's zero terminator. */
s32 find_callback_value_index(void)
{
    ValueList values;
    s32 callback_value;
    s32 index;

    values = D_A0700100[0];
    callback_value = devkit_kind_callback_owner[0]->callback(11);
    for (index = 0; values.v[index] != 0; index++) {
        if (values.v[index] == callback_value) {
            break;
        }
    }
    return index;
}
