#include "common.h"

typedef struct S_80170890_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170890_0;   /* obj in func_80170890 */

typedef struct S_80170890_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80170890_1;   /* work in func_80170890 */

typedef struct S_80170890_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170890_2;   /* part_a in func_80170890 */

typedef struct S_80170890_3 {
    u8 pad_00[0x8];
    u8 ** unk_08;
    u8 pad_0C[0x18];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170890_3;   /* part_b in func_80170890 */

typedef struct S_80170890_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x13];
    s16 unk_B0;
} S_80170890_4;   /* actor in func_80170890 */

typedef struct S_80170890_5 {
    u16 unk_00;
} S_80170890_5;   /* (u8 *)(((index + count) << 2) + (u32)table) + 6 in func_80170890 */



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
    void *obj;
    void *work = 0;
    void *part_a;
    S_80170890_3 *part_b;
    S_80170890_4 *actor;
    s32 kind;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$21") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 saved_arg3 = arg3;
    register s8 saved_arg2 ASM_REG("$20") = arg2;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    obj = func_8003FD64(274, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80170890_0 *)obj)->unk_10 = D_80170AE8;
        ((S_80170890_1 *)work)->unk_13 = 29;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80170890_0 *)obj)->unk_08;
        ((S_80170890_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80170890_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_80176460;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = ((S_80170890_1 *)work)->unk_14 | 0x6000;
            right = ((S_80170890_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = ((S_80170890_1 *)work)->unk_14 | 0x2000;
        right = ((S_80170890_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_80170890_1 *)work)->unk_14 = left;
        ((S_80170890_1 *)work)->unk_1C = right;
        goto post_kind;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(((S_80170890_1 *)work)->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_80176470;
                    goto post_kind;
                }
            }
        }

post_kind:
        func_800A9C18(obj, part_a, part_b, (s16)arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80171094;
        ((S_80170890_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -32;

        {
            u8 *cursor = part_b->unk_08;
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
            table = part_b->unk_08;
            value = (((S_80170890_5 *)((u8 *)(((index + count) << 2) + (u32)table) + 6))->unk_00 >> 6) - 1;
            packet[1] = value;
            actor->unk_B0 = value << 6;
            packet[2] = 256;
            packet[0] = 0;
            packet[3] = 1;
            func_800672D8(packet, D_801764B8);
            func_800AA36C(actor, part_a, part_b, work);
        }
    }
    return work;
}
