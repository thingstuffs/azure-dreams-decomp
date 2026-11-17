#include "common.h"
#include "sdk/libc.h"

extern char *D_8002946C[];

/* Returns half the byte length of the indexed string. */
u32 get_indexed_string_half_length(s32 string_index) {
    return (u32)strlen(D_8002946C[string_index]) >> 1;
}
