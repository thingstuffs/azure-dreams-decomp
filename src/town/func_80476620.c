#include "common.h"

typedef struct {
    s32 value;
    s32 unk4;
    s32 unk8;
} Entry;

typedef struct {
    s32 unk0[8];
    s32 value;
} Destination;

extern Entry D_80016470[];
extern Destination D_800164D0;

Destination *func_80017620(s32 index) {
    Destination *destination = &D_800164D0;

    destination->value = D_80016470[index].value;
    return destination;
}
