#include "common.h"

typedef struct {
    unsigned char pad_00[0x54];
    void *unk_54;
} Struct800350B0;

extern void func_80035068(void *arg0, void *arg1);

/* Store a self-reference and pass its address to func_80035068. */
void func_800350B0(void *context, Struct800350B0 *object) {
    object->unk_54 = object;
    func_80035068(context, &object->unk_54);
}
