#include "common.h"

extern u32 strlen(s32 value);
extern s32 D_8002946C[];

/* Returns half the byte length of the indexed string. */
u32 get_half_byte_length(s32 string_index) {
    return strlen(D_8002946C[string_index]) >> 1;
}
