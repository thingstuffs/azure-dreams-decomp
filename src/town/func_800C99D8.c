#include "common.h"
#include "shared/object_index_slots.h"

typedef struct {
    s8 pad0[0x54];
    void *unk54;
    u8 pad58[8];
    s32 unk60;
} Obj;

typedef struct {
    u8 pad0[0x14];
    u16 unk14;
} Arg2;

extern void func_800C2E84();
extern u8 D_800C3C28[];
extern u8 D_800D5CD0[];

// Process the flagged event, clear the object's indexed flag, and reset its state pointer.
void func_800C7138(Obj *object, s32 unused, Arg2 *event) {
    if (event->unk14 & 0x6000) {
        func_800C2E84(object, event, D_800D5CD0);
        D_80082660[object->unk60].unk_00 = 0;
        object->unk54 = D_800C3C28;
    }
}
