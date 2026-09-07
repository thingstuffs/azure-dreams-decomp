#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s32);
extern void func_800672D8(void *, void *);
extern void func_800AA36C(void *, void *, void *, void *);

extern u8 D_80083498[];
extern s32 D_80045340;
extern u8 D_80170AE8[];
extern u8 D_80176460[];
extern u8 D_80176470[];
extern u8 D_80171094[];
extern u8 D_801764B8[];

void *func_80170890(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register void *obj ASM_REG("$17");
    register void *work ASM_REG("$16") = 0;
    register void *part_a ASM_REG("$22");
    void *part_b;
    void *actor;
    s32 kind;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$21") = arg1;
    s16 saved_arg3 = arg3;
    register s8 saved_arg2 ASM_REG("$20") = arg2;

    obj = func_8003FD64(274, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_80170AE8;
        FIELD(work, s8, 0x13) = 29;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = saved_arg2;
        actor = work;
        FIELD(part_b, void *, 0x2C) = D_80176460;
        FIELD(part_b, s8, 0x24) = saved_arg1;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;
write_kind:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        goto post_kind;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                if (func_800A6D30() & 1) {
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    FIELD(part_b, void *, 0x2C) = D_80176470;
                    goto post_kind;
                }
            }
        }

post_kind:
        func_800A9C18(obj, part_a, part_b, (s16)arg0);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = D_80171094;
        FIELD(work, s32, 0x1C) |= 0x00040000;
        FIELD(actor, s16, 0x92) = -32;

        {
            u8 *cursor = FIELD(part_b, u8 **, 8);
            s32 count = 0;
            s32 index;
            u16 packet[4];
            u8 *table;
            s16 value;

scan_records:
            index = count << 1;
            if (!(*cursor & 0x20)) {
                goto scan_done;
            }
                cursor += 12;
                count += 1;
            goto scan_records;
scan_done:
            table = FIELD(part_b, u8 **, 8);
            value = (FIELD((u8 *)(((index + count) << 2) + (u32)table) + 6,
                           u16, 0) >> 6) - 1;
            packet[1] = value;
            FIELD(actor, s16, 0xB0) = value << 6;
            packet[2] = 256;
            packet[0] = 0;
            packet[3] = 1;
            func_800672D8(packet, D_801764B8);
            func_800AA36C(actor, part_a, part_b, work);
        }
    }
    return work;
}
