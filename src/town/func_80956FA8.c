#include "common.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"

typedef struct EffectScaleState {
    u8 pad_00[8];
    s16 scale_enabled;
} EffectScaleState;
extern s32 D_800814A0;
void func_80023FA8(void *actor, void *unused, void *packet) {
    u16 depth;
    u16 *flags;
    ((Rec_D_80082E80 *)packet)->unk_0C.at00_s32.v += 0xFFEFEFF0U;
    if (((EffectScaleState *)actor)->scale_enabled != 0) {
        depth = (u16)(((Rec_D_80082E80 *)packet)->unk_1C.at02_u16.v + 0x120);
        depth -= ((Rec_D_80082E80 *)packet)->unk_0C.at00_u8.v >> 3;
        ((Rec_D_80082E80 *)packet)->unk_1C.at02_u16.v = depth;
        ((Rec_D_80082E80 *)packet)->unk_1C.at00_u16.v = depth;
    }
    if (((Rec_D_80082E80 *)packet)->unk_0C.at00_u8.v == 0) {
        flags = &((ObjectNodeHeader *)actor)[-1].flags;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
