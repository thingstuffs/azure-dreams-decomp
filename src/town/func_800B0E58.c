#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Func800B0E58State;

extern void func_800AE854(void);

void func_800AE5B8(Func800B0E58State *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    func_800AE854();
    temp_v0 = arg0->unk8;
    temp_v1 = temp_v0;
    temp_v0 = temp_v0 + 1;
    arg0->unk8 = temp_v0;
    if (temp_v1 >= arg0->unk4) {
        arg0->unk0 = 0;
    }
}
