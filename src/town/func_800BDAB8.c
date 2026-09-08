#include "common.h"

typedef struct S_800BB218_0 {
    u16 unk_00;
    u16 unk_02;
    u32 unk_04;
    u8 pad_08[0x8];
    u8 * unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
} S_800BB218_0;   /* scratch in func_800BB218 */

typedef struct S_800BB218_1 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800BB218_1;   /* arena in func_800BB218 */

typedef struct S_800BB218_2_pre {
    u8 * unk_00;
    u8 pad_04[0x4];
} S_800BB218_2_pre;   /* the 0x8 bytes before object in func_800BB218, addressed as object[-1] */

typedef struct S_800BB218_2 {
    u8 pad_00[0x66];
    s16 unk_66;
    u8 pad_68[0x2F];
    s8 unk_97;
} S_800BB218_2;   /* object in func_800BB218 */

typedef struct S_800BB218_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800BB218_3;   /* coords in func_800BB218 */

typedef struct S_800BB218_4 {
    u32 unk_00;
    u8 pad_04[0x4];
    u16 unk_08;
    u16 unk_0A;
} S_800BB218_4;   /* packet in func_800BB218 */

typedef struct S_800BB218_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
} S_800BB218_5;   /* next in func_800BB218 */



extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 rand(void);

typedef struct {
    void *ptr;
    u32 pad[2];
} Global83160;

extern Global83160 D_80083160;

/* Draws randomized white points around each object in the linked chain. */
s32 func_800BB218(void *first_object, void *first_coords)
{
    s16 angle;
    s32 radius_offset;
    u8 *packet;
    s32 point_index;
    u8 *scratch;
    u8 *object;
    u8 *coords;
    u32 addr_mask;
    u32 tag_mask;
    u8 *arena;
    u8 *next_node;
    s32 random_value;
    s32 x_scale;
    u32 packet_tag;
    u32 linked_tag;
    unsigned long ot_link;
    Global83160 *render_state;

    object = first_object;
    coords = first_coords;
    render_state = &D_80083160;
    scratch = (u8 *)0x1F800000;
    ((S_800BB218_0 *)scratch)->unk_10 = render_state->ptr + 0xB0;
    addr_mask = 0x00FFFFFF;
    tag_mask = 0xFF000000;

draw_object:
    point_index = 0;
    do {
        arena = render_state->ptr;
        packet = ((S_800BB218_1 *)arena)->unk_8D0;
        ((S_800BB218_1 *)arena)->unk_8D0 = packet + 0xC;
        packet[3] = 2;
        packet[7] = 0x68;
        packet[4] = 0xFF;
        packet[5] = 0xFF;
        packet[6] = 0xFF;

        random_value = rand();
        angle = (s16)(random_value % 0x1000);

        x_scale = func_800644B8(angle) >> 4;
        {
            s32 base_radius = ((S_800BB218_2 *)object)->unk_97;
            radius_offset = (point_index / 8) % 12 + 0x48;
            ((S_800BB218_0 *)scratch)->unk_14 =
                ((S_800BB218_3 *)coords)->unk_02 + ((x_scale * (base_radius + radius_offset)) >> 8);
        }

        ((S_800BB218_0 *)scratch)->unk_16 =
            ((S_800BB218_3 *)coords)->unk_06 +
            (((func_80064584(angle) >> 4) *
              (((S_800BB218_2 *)object)->unk_97 + radius_offset)) >> 8);

        ((S_800BB218_0 *)scratch)->unk_18 =
            ((S_800BB218_3 *)coords)->unk_0A -
            (((func_800644B8((point_index % 16) << 6) >> 4) *
              (((S_800BB218_2 *)object)->unk_66 + 0x10)) >> 8);

        ((S_800BB218_0 *)scratch)->unk_04 = func_80065420(
            scratch + 0x14, scratch, scratch + 8, scratch + 0xC);
        ((S_800BB218_4 *)packet)->unk_08 = ((S_800BB218_0 *)scratch)->unk_00;
        ((S_800BB218_4 *)packet)->unk_0A = ((S_800BB218_0 *)scratch)->unk_02;

        ot_link = ((S_800BB218_0 *)scratch)->unk_04;
        if (ot_link < 0x1E0) {
            ot_link <<= 2;
            ot_link += (unsigned long)((S_800BB218_0 *)scratch)->unk_10;
            packet_tag = ((S_800BB218_4 *)packet)->unk_00;
            ot_link = *(u32 *)ot_link;
            ot_link &= addr_mask;
            linked_tag = packet_tag & tag_mask;
            linked_tag |= ot_link;
            ((S_800BB218_4 *)packet)->unk_00 = linked_tag;
            *(u32 *)(((S_800BB218_0 *)scratch)->unk_10 +
                     ((S_800BB218_0 *)scratch)->unk_04 * 4) =
                (*(u32 *)(((S_800BB218_0 *)scratch)->unk_10 +
                          ((S_800BB218_0 *)scratch)->unk_04 * 4) & tag_mask) |
                ((u32)packet & addr_mask);
        }
    } while (++point_index < 0x180);

    next_node = ((S_800BB218_2_pre *)object)[-1].unk_00;
    if (next_node != 0) {
        object = next_node + 0x20;
        coords = ((S_800BB218_5 *)next_node)->unk_08;
        goto draw_object;
    }
    return 0;
}
