#include "common.h"

extern s32 *func_7003FC64(s32);
extern void func_7004491C(s32 *, void *);
extern s32 D_80053A88;

typedef struct { s32 a, b, c, d; } Blk16;
typedef struct { s32 a, b; } Blk8;

/* Initializes an available record with a value and 40 bytes of data, then submits it for processing. */
void func_7FDD3C74(s32 value, void *data) {
    s32 *record;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *copy_end;

    record = func_7003FC64(1);
    if (record != 0) {
        dst = (Blk16 *)(record + 8);
        src = (Blk16 *)data;
        copy_end = src + 2;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != copy_end);
        *(Blk8 *)dst = *(Blk8 *)src;
        record[4] = value;
        func_7004491C(record, &D_80053A88);
    }
}
