#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8009A180_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    union { s32 s; void * u; } unk_5C;
} S_8009A180_0;

typedef struct S_8009A180_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8009A180_2;

extern void func_8009A028(void *arg0);

s32 func_8009A180(void *entry, S_8009A180_0 *anchor) {
    u32 link_bits;
    u32 link_bits_2;
    s32 state_flags;
    s32 anchor_flags;
    s32 prev_link;
    S_8009A180_2 *prev_node;

    if (entry == anchor) {
        anchor_flags = anchor->unk_1C;
        anchor->unk_1C = anchor_flags | ((u32)(0x80000000));
        return 0;
    }

    state_flags = ((Rec_D_800E3D7C *)entry)->unk_1C.as_s32;
    if (state_flags < 0) {
        return 0;
    }

    prev_link = 0x80000000;
    state_flags |= prev_link;
    ((Rec_D_800E3D7C *)entry)->unk_1C.as_s32 = state_flags;
    link_bits_2 = (u32)entry;
    func_8009A028((void *)link_bits_2);

    prev_link = anchor->unk_5C.s;
    ((Rec_D_800E3D7C *)entry)->unk_5C = prev_link;
    prev_node = (void *)(prev_link + 0x20);
    link_bits = (u32)prev_node->unk_58;
    ((Rec_D_800E3D7C *)entry)->unk_58 = (void *)link_bits;
    link_bits = (u32)((u8 *)entry - 0x20);
    prev_node->unk_58 = (void *)link_bits;
    anchor->unk_5C.u = (void *)link_bits;
    return 1;
}
