#include "common.h"

typedef struct {
    unsigned char pad_00[0x54];
    void *unk_54;
} Struct800350B0;

extern void func_80035068(void *arg0, void *arg1);

void func_800350B0(void *arg0, Struct800350B0 *arg1) {
    arg1->unk_54 = arg1;
    func_80035068(arg0, &arg1->unk_54);
}
