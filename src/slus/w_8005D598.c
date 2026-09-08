#include "common.h"

typedef struct { s32 value; s32 pad[2]; } S_8007997C;
extern S_8007997C D_8007997C;
typedef struct { s32 value; s32 pad[2]; } S_80079980;
extern S_80079980 D_80079980;
typedef struct { s32 value; s32 pad[2]; } S_80079984;
extern S_80079984 D_80079984;
typedef struct { s32 value; s32 pad[2]; } S_80079988;
extern S_80079988 D_80079988;
typedef struct { volatile u16 *ptr; u32 pad2[2]; } S_80079958;
extern S_80079958 D_80079958;

/* Optionally aligns a value, shifts it, and stores or returns the result. */
s32 func_8005D598(s32 index, u32 value)
{
    s32 store_index = index;
    u32 shifted_value;

    if (D_8007997C.value != 0) {
        s32 alignment = D_80079984.value;
        if (value % alignment != 0) {
            value = value + alignment;
            value = value & ~D_80079988.value;
        }
    }

    shifted_value = value >> D_80079980.value;

    if (store_index == -2) {
        goto return_value;
    }
    if (store_index != -1) {
        goto store_value;
    }
    return (u16)shifted_value;

return_value:
    return value;

store_value:
    D_80079958.ptr[store_index] = (u16)shifted_value;
    return value;
}
