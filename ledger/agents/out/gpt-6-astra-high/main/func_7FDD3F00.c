#include "common.h"

extern s32 *func_7003FC64(s32);
extern void func_7004491C(s32 *, void *);
/* >8B so address-of uses %hi/%lo (not $gp) */
extern s32 D_80053858[4];

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Blk16;

/* Initializes a record with a value and 48 bytes of data, then submits it. */
void func_7FDD3F00(s32 value, void *data) {
    s32 *record;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *end;

    record = func_7003FC64(1);
    dst = (Blk16 *)(record + 8); /* +0x20 bytes */
    if (record != 0) {
        src = (Blk16 *)data;
        end = src + 3; /* 0x30 bytes */
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        record[4] = value;
        func_7004491C(record, &D_80053858);
    }
}
