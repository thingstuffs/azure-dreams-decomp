#include "common.h"

#include "common.h"

typedef struct {
    u32 word0;
    u32 word1;
    u8 byte8;
} __attribute__((packed)) Func80038C40Data;

extern Func80038C40Data D_8002D03C;

s32 func_80038C40(s8 value) {
    Func80038C40Data data;
    s32 i;

    data = D_8002D03C;
    for (i = 0; i < 9; i++) {
        if (value == ((s8 *)&data)[i]) {
            return 1;
        }
    }
    return 0;
}
