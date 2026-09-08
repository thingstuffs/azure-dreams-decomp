#include "common.h"

#include "common.h"

typedef struct {
    u32 word0;
    u32 word1;
    u8 byte8;
} __attribute__((packed)) Func80038C40Data;

extern Func80038C40Data D_8002D03C;

/* Returns whether value matches any of the nine bytes in D_8002D03C. */
s32 func_80038C40(s8 value) {
    Func80038C40Data byte_table;
    s32 byte_index;

    byte_table = D_8002D03C;
    for (byte_index = 0; byte_index < 9; byte_index++) {
        if (value == ((s8 *)&byte_table)[byte_index]) {
            return 1;
        }
    }
    return 0;
}
