#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
extern void func_801747B8(void) __attribute__((noreturn));

void func_801745BC(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    register void *node ASM_REG("$16") = arg0;
    OffsetTable offsets = D_80170884;
    register void *head ASM_REG("$18") = node;
    register void *owner ASM_REG("$17") = head;
    register s32 key1 ASM_REG("$23") = arg1;
    register void *saved = FIELD(head, void *, -0x14);
    register void *next ASM_REG("$2") = FIELD(head, void *, 0x5C);
    register void *position ASM_REG("$19") = FIELD(head, void *, -0x18);
    register s32 key2 ASM_REG("$22");
    register s32 angle_arg ASM_REG("$7") = arg3;
    register s32 angle_base ASM_REG("$20");
    register s32 lower ASM_REG("$21");
    register s32 shifted ASM_REG("$2");

    ASM_KEEP(next);
    node = (u8 *)next + 0x20;
    key2 = arg2;

    if (node != head) {
        shifted = angle_arg << 16;
        angle_base = shifted >> 16;
        lower = angle_base - 0x40;
        do {
        void *data = FIELD(node, void *, -0x14);
        void *node_position = FIELD(node, void *, -0x18);
        s16 height;

        if ((FIELD(data, u8, 0x24) == (key1 & 0xFFFF)) &&
            (FIELD(data, u8, 0x25) == (key2 & 0xFFFF))) {
            height = FIELD(node_position, s16, 0x0A);
            if (((angle_base + 0x40) >= height) && (lower < height)) {
                if ((u32)(FIELD(node, u8, 0x13) - 0x33) < 4U) {
                    s32 message;
                    u16 angle;
                    OffsetPair *offset;

                    FIELD(node, s8, 0x28) = 0;
                    FIELD(node, s16, 0x64) = -1;
                    func_800419EC(6, 0xC);
                    message = 0x601;
                    if (FIELD(node, u8, 0x13) == 0x34) {
                        message = 0x80B;
                    }
                    func_800A56E0(message);

                    angle = FIELD(owner, u16, 0x2A);
                    offset = (OffsetPair *)((u8 *)&offsets +
                        (((s16)angle >> 7) & 0x1C));
                    func_80099C58(
                        (s16)(FIELD(position, u16, 2) + (offset->x * 32)),
                        (s16)(FIELD(position, u16, 6) +
                            ((s32)(offset->y << 16) >> 11)),
                        (s16)(FIELD(position, u16, 0x0A) - 0x20),
                        FIELD(owner, s16, 0x14),
                        (s32)(s16)angle);
                    func_801747B8();
                } else {
                    func_8009C12C(owner, saved,
                        (s16)FIELD(owner, u16, 0x2A), 1);
                }
            }
        }
        next = FIELD(node, void *, 0x5C);
        ASM_KEEP(next);
        node = (u8 *)next + 0x20;
        } while (node != head);
    }

    ASM_KEEP(node);
    ASM_KEEP(head);
    ASM_KEEP(owner);
    ASM_KEEP(key1);
    ASM_KEEP(saved);
    ASM_KEEP(position);
    ASM_KEEP(key2);
    ASM_KEEP(angle_arg);
    ASM_KEEP(angle_base);
    ASM_KEEP(lower);
}
