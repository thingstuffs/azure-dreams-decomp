#include "common.h"

typedef struct S_801745BC_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_801745BC_0_pre;   /* the 0x18 bytes before head in func_801745BC, addressed as head[-1] */

typedef struct S_801745BC_0 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_801745BC_0;   /* head in func_801745BC */

typedef struct S_801745BC_1_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_801745BC_1_pre;   /* the 0x18 bytes before node in func_801745BC, addressed as node[-1] */

typedef struct S_801745BC_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x14];
    s8 unk_28;
    u8 pad_29[0x33];
    void * unk_5C;
    u8 pad_60[0x4];
    s16 unk_64;
} S_801745BC_1;   /* node in func_801745BC */

typedef struct S_801745BC_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801745BC_2;   /* data in func_801745BC */

typedef struct S_801745BC_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_801745BC_3;   /* node_position in func_801745BC */

typedef struct S_801745BC_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x14];
    u16 unk_2A;
} S_801745BC_4;   /* owner in func_801745BC */

typedef struct S_801745BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801745BC_5;   /* position in func_801745BC */



typedef struct OffsetPair {
    s16 x;
    u16 y;
} OffsetPair;

typedef struct OffsetTable {
    OffsetPair entries[8];
} OffsetTable;

extern OffsetTable D_80170884;

extern void func_800419EC(u16, u32);
extern void func_80099C58(s16, s16, s16, s16, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A56E0(s32);

/* Process nodes at the target tile and height, triggering type-specific effects. */
void func_801745BC(void *source, s32 target_x, s32 target_y, s32 target_height)
{
    register void *node ASM_REG("$16") = source;
    OffsetTable offsets = D_80170884;
    void *head = node;
    register void *owner = head;
    register s32 match_x ASM_REG("$23") = target_x;
    register void *owner_data = ((S_801745BC_0_pre *)head)[-1].unk_04;
    register void *next_link ASM_REG("$2") = ((S_801745BC_0 *)head)->unk_5C;
    void *position = ((S_801745BC_0_pre *)head)[-1].unk_00;
    s32 match_y;
    u16 height_arg = target_height;
    register s32 center_height ASM_REG("$20");
    register s32 height_shifted ASM_REG("$2");

    ASM_KEEP(next_link);
    node = (u8 *)next_link + 0x20;
    match_y = target_y;

    if (node != head) {
        height_shifted = height_arg << 16;
        center_height = height_shifted >> 16;
        target_height = center_height - 0x40;
        do {
            S_801745BC_2 *node_data = ((S_801745BC_1_pre *)node)[-1].unk_04;
            S_801745BC_3 *node_position = ((S_801745BC_1_pre *)node)[-1].unk_00;
            s16 height;

            if ((node_data->unk_24 == (match_x & 0xFFFF)) &&
                (node_data->unk_25 == (match_y & 0xFFFF))) {
                height = node_position->unk_0A;
                if (((center_height + 0x40) >= height) && (target_height < height)) {
                    if ((u32)(((S_801745BC_1 *)node)->unk_13 - 0x33) < 4U) {
                        s32 message_id;
                        u16 angle;
                        OffsetPair *offset;

                        ((S_801745BC_1 *)node)->unk_28 = 0;
                        ((S_801745BC_1 *)node)->unk_64 = -1;
                        func_800419EC(6, 0xC);
                        message_id = 0x601;
                        if (((S_801745BC_1 *)node)->unk_13 == 0x34) {
                            message_id = 0x80B;
                        }
                        func_800A56E0(message_id);

                        angle = ((S_801745BC_4 *)owner)->unk_2A;
                        offset = (OffsetPair *)((u8 *)&offsets +
                            (((s16)angle >> 7) & 0x1C));
                        func_80099C58(
                            (s16)(((S_801745BC_5 *)position)->unk_02 + (offset->x * 32)),
                            (s16)(((S_801745BC_5 *)position)->unk_06 +
                                ((s32)(offset->y << 16) >> 11)),
                            (s16)(((S_801745BC_5 *)position)->unk_0A - 0x20),
                            ((S_801745BC_4 *)owner)->unk_14,
                            (s32)(s16)angle);
                    } else {
                        func_8009C12C(owner, owner_data,
                            (s16)((S_801745BC_4 *)owner)->unk_2A, 1);
                    }
                }
            }
            next_link = ((S_801745BC_1 *)node)->unk_5C;
            node = (u8 *)next_link + 0x20;
        } while (node != head);
    }

    ASM_KEEP(owner_data);
    ASM_KEEP(match_y);
}
