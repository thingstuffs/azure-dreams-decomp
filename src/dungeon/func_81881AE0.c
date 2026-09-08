#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800252E0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_0;   /* global in func_800252E0 */

typedef struct S_800252E0_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x12];
    void * unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x9C];
    u32 unk_C0;
} S_800252E0_1;   /* scratch in func_800252E0 */

typedef struct S_800252E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800252E0_2;   /* input in func_800252E0 */

typedef struct S_800252E0_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800252E0_3;   /* arg2use in func_800252E0 */

typedef struct S_800252E0_4 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; s8 v; } at03; } unk_04;   /* overlapping accesses */
} S_800252E0_4;   /* p in func_800252E0 */

typedef struct S_800252E0_5_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800252E0_5_pre;   /* the 0x8 bytes before arg0 in func_800252E0, addressed as arg0[-1] */

typedef struct S_800252E0_6 {
    void * unk_00;
} S_800252E0_6;   /* global_slot in func_800252E0 */

typedef struct S_800252E0_7 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800252E0_7;   /* next in func_800252E0 */

typedef struct S_800252E0_8 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800252E0_8;   /* ((S_800252E0_6 *)global_slot)->unk_00 in func_800252E0 */



extern s32 func_80025340();
extern u32 func_80065420();
extern s32 func_80066460();
extern void func_80067F20();
extern u8 D_80080000[];
extern u8 D_80083160[];

/* Queue projected point primitives from a linked list into the ordering table. */
s32 func_800252E0(void *node_data, void *position_data, void *appearance_data) {
    void *position = position_data;
    void *appearance = appearance_data;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *render_slot = D_80080000 + 0x3160;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;
    void *packet;
    s32 *ot_entry;

    {
        void *render_state = (*(void * *)((u8 *)D_80080000 + 0x3160));
        void *packet_cursor = ((S_800252E0_0 *)render_state)->unk_8D0;
        ((S_800252E0_1 *)scratch)->unk_20 = (u8 *)render_state + 0xB0;
        ((S_800252E0_1 *)scratch)->unk_18 = packet_cursor;
    }
    for (;;) {
        register u16 coord_x ASM_REG("$2") = ((S_800252E0_2 *)position)->unk_02;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_800252E0_1 *)scratch)->unk_00 = coord_x;
        ((S_800252E0_1 *)scratch)->unk_02 = ((S_800252E0_2 *)position)->unk_06;
        ((S_800252E0_1 *)scratch)->unk_04 = ((S_800252E0_2 *)position)->unk_0A;
        packet = ((S_800252E0_1 *)scratch)->unk_18;
        ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)packet + 0xC;
        ((S_800252E0_1 *)scratch)->unk_C0 = func_80065420(
            scratch, (u8 *)packet + 8, scratch + 0x90, scratch + 0x94);
        if (((S_800252E0_1 *)scratch)->unk_C0 < 0x1E0) {
            s32 color = ((S_800252E0_3 *)appearance)->unk_0C;
            ((S_800252E0_4 *)packet)->unk_00.at03.v = 2;
            ((S_800252E0_4 *)packet)->unk_04.at00.v = color;
            ((S_800252E0_4 *)packet)->unk_04.at03.v = 0x6A;
            ((S_800252E0_4 *)packet)->unk_00.at00.v = (((S_800252E0_4 *)packet)->unk_00.at00.v & length_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & addr_mask);
            {
                u32 depth_index;
                depth_index = *(volatile u32 *)(scratch + 0xC0);
                ot_entry = (s32 *)((depth_index << 2) +
                              (u32)*(void * volatile *)(scratch + 0x20));
            }
            *ot_entry = (*ot_entry & length_mask) | ((u32)packet & addr_mask);
            packet = ((S_800252E0_1 *)scratch)->unk_18;
            ((S_800252E0_1 *)scratch)->unk_18 = (u8 *)packet + 0xC;
            func_80067F20(packet, 0, 0, func_80066460(0, 1, 0, 0) & 0xFFFF, 0);
            ((S_800252E0_4 *)packet)->unk_00.at00.v = (((S_800252E0_4 *)packet)->unk_00.at00.v & length_mask) |
                (*(s32 *)((((S_800252E0_1 *)scratch)->unk_C0 << 2) +
                          (u32)((S_800252E0_1 *)scratch)->unk_20) & addr_mask);
            {
                register u32 ot_addr ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                ot_addr = *(volatile u32 *)(scratch + 0xC0);
                ot_addr = (ot_addr << 2) +
                           (u32)*(void * volatile *)(scratch + 0x20);
                packet = (void *)((u32)packet & addr_mask);
                *(s32 *)ot_addr = (*(s32 *)ot_addr & length_mask) |
                                   (u32)packet;
            }
        }
        {
            void *next_node = ((S_800252E0_5_pre *)node_data)[-1].unk_00;
            if (next_node == NULL) {
                ((S_800252E0_8 *)(((S_800252E0_6 *)render_slot)->unk_00))->unk_8D0 =
                    ((S_800252E0_1 *)scratch)->unk_18;
                return 0;
            }
            node_data = (u8 *)next_node + 0x20;
            position = ((S_800252E0_7 *)next_node)->unk_08;
            appearance = ((S_800252E0_7 *)next_node)->unk_0C;
        }
    }
}
