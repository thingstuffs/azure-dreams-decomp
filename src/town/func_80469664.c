#include "common.h"

typedef struct Entry {
    u32 value;
    s32 unused[2];
} Entry;

extern Entry D_8001791C[8];
extern s32 D_80017AAC[3];
extern s32 D_80017AB8[3];
extern s32 D_80017BD8[13];
extern void func_8001A1A0(void *, void *);

s32 *func_8001A664(s32 arg0) {
    s32 *value = D_80017BD8;

    value[8] = D_8001791C[arg0].value;
    func_8001A1A0(value, D_80017AAC);
    func_8001A1A0(value + 5, D_80017AB8);
    return value;
}
