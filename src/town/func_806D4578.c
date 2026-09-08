#include "common.h"

typedef struct {
    s32 values[3];
} ValueTable;

extern ValueTable D_8001601C;
extern s32 func_80018868(s32, s32);

/* Select a value from the table using the result of query 0x990. */
s32 func_806D4578(void) {
    ValueTable table = D_8001601C;

    return table.values[func_80018868(0x990, 2)];
}
