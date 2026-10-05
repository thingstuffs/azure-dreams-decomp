#include "common.h"

extern s32 *func_7003FC64(s32);
extern void func_7004491C(s32 *, void *);
extern s32 D_80053A88;

typedef struct { s32 words[10]; } RecordData;

/* Initializes an available record with a value and 40 bytes of data, then submits it for processing. */
void func_7FDD3C74(s32 value, void *data) {
    s32 *record;

    record = func_7003FC64(1);
    if (record != 0) {
        *(RecordData *)(record + 8) = *(RecordData *)data;
        record[4] = value;
        func_7004491C(record, &D_80053A88);
    }
}
