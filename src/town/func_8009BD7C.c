#include "common.h"
#include "shared/object_index_slots.h"

void func_80094984(void *, void *, void *);
extern s32 func_800A8184(s16, s16);
extern u8 D_80097EA0[];
extern u8 D_800D01C0[];

typedef struct {
    u8 unk0[4];
    void *unk4;
    u8 unk8[0x2E];
    s16 unk36;
    s16 unk38;
} TownObject;

/* Initialize the town object, clear its slot flags, and apply its coordinates. */
void func_800994DC(TownObject *object, void *ptr, void *ptr2) {
    func_80094984(D_800D01C0, object, ptr2);
    D_80082660[1].unk_00 = 0;
    object->unk4 = D_80097EA0;
    D_80082660[1].unk_01 = 0;
    func_800A8184(object->unk36, object->unk38);
}
