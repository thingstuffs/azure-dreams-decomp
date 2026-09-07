#include "common.h"

extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern u8 D_801328C8[];
extern u8 D_8005860C[];

typedef struct FourWords {
    s32 word[4];
} FourWords;

/* Allocates a record, stores a value and three data blocks, and passes it to func_8003BC18. */
void func_8080BFFC(s32 record_value, FourWords *data_blocks) {
    u8 *record;
    FourWords *src_block;
    FourWords *dst_block;
    FourWords *src_end;

    record = func_800374FC(1, D_801328C8);
    dst_block = (FourWords *)(record + 0x20);
    if (record != 0) {
        src_block = data_blocks;
        src_end = src_block + 3;
        do {
            *dst_block++ = *src_block++;
        } while (src_block != src_end);
        *(s32 *)(record + 0x10) = record_value;
        func_8003BC18(record, D_8005860C);
    }
}
