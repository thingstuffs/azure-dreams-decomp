#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8009A180_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    union { s32 s; void * u; } unk_5C;   /* accessed as both */
} S_8009A180_0;   /* arg1 in func_8009A180 */


typedef struct S_8009A180_2 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8009A180_2;   /* node in func_8009A180 */


extern void func_8009A028(void *arg0);


/* Marks an entry, relinking newly marked entries beside a distinct anchor. */
s32 func_8009A180(void *entry, S_8009A180_0 *anchor) {
    register u32 link_bits ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 anchor_flags;
    s32 prev_link;
    S_8009A180_2 *prev_node;
    u32 marked_bit;

    if (entry == anchor) {
        result = 0;
        anchor_flags = anchor->unk_1C;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        link_bits = 0x80000000;
        anchor->unk_1C = anchor_flags | link_bits;
        return;
    }

    marked_bit = 0x80000000;
    result = ((Rec_D_800E3D7C *)entry)->unk_1C.as_s32;
    if (result >= 0) {
        result |= marked_bit;
        ((Rec_D_800E3D7C *)entry)->unk_1C.as_s32 = result;
        link_bits = (u32)entry;
        func_8009A028((void *)link_bits);

        prev_link = anchor->unk_5C.s;
        ((Rec_D_800E3D7C *)entry)->unk_5C = prev_link;
        ASM_KEEP(prev_link);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        prev_node = (void *)(prev_link + 0x20);
        ASM_KEEP(prev_node);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        link_bits = (u32)prev_node->unk_58;
        ASM_KEEP(link_bits);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        result = 1;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((Rec_D_800E3D7C *)entry)->unk_58 = (void *)link_bits;
        link_bits = (u32)((u8 *)entry - 0x20);
        prev_node->unk_58 = (void *)link_bits;
        anchor->unk_5C.u = (void *)link_bits;
        return;
    }

    return 0;
}
