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

void func_801745BC(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *node ASM_REG("$16") = arg0;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    OffsetTable offsets = D_80170884;
    register void *head ASM_REG("$18") = node; /* MATCH: keep head in s2 after the shared loop tail makes it live across both arms. */
    register void *owner ASM_REG("$17") = head;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 key1 ASM_REG("$23") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register void *saved = ((S_801745BC_0_pre *)head)[-1].unk_04;
    register void *next ASM_REG("$2") = ((S_801745BC_0 *)head)->unk_5C;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *position = ((S_801745BC_0_pre *)head)[-1].unk_00;
    s32 key2;
    register s32 angle_arg ASM_REG("$7") = arg3;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 angle_base ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 lower ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 shifted ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

    ASM_KEEP(next);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    node = (u8 *)next + 0x20;
    key2 = arg2;

    if (node != head) {
        shifted = angle_arg << 16;
        angle_base = shifted >> 16;
        lower = angle_base - 0x40;
        do {
        S_801745BC_2 *data = ((S_801745BC_1_pre *)node)[-1].unk_04;
        S_801745BC_3 *node_position = ((S_801745BC_1_pre *)node)[-1].unk_00;
        s16 height;

        if ((data->unk_24 == (key1 & 0xFFFF)) &&
            (data->unk_25 == (key2 & 0xFFFF))) {
            height = node_position->unk_0A;
            if (((angle_base + 0x40) >= height) && (lower < height)) {
                if ((u32)(((S_801745BC_1 *)node)->unk_13 - 0x33) < 4U) {
                    s32 message;
                    u16 angle;
                    OffsetPair *offset;

                    ((S_801745BC_1 *)node)->unk_28 = 0;
                    ((S_801745BC_1 *)node)->unk_64 = -1;
                    func_800419EC(6, 0xC);
                    message = 0x601;
                    if (((S_801745BC_1 *)node)->unk_13 == 0x34) {
                        message = 0x80B;
                    }
                    func_800A56E0(message);

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
                    func_8009C12C(owner, saved,
                        (s16)((S_801745BC_4 *)owner)->unk_2A, 1);
                }
            }
        }
        next = ((S_801745BC_1 *)node)->unk_5C;
        node = (u8 *)next + 0x20;
        } while (node != head);
    }

       /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(saved);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(position);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(key2);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
}
