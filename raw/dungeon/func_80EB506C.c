#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_80047784();
extern void func_800478E8();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800D71A8[];
extern u8 D_800D78C0[];
extern u8 D_80170B64[];
extern u8 D_801711A4[];
extern u8 D_8017418C[];
extern u8 D_801741CC[];

void *func_8017086C(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    register void *work ASM_REG("$19");
    register s8 saved_arg1 ASM_REG("$21");
    register s8 saved_arg2 ASM_REG("$18");
    void *obj;
    void *part_a;
    void *part_b;
    void *actor;
    s32 left;
    s32 right;
    s16 saved_arg0;
    void *current;
    void *base;
    void *child_obj;
    void *elem;
    s32 count;
    register s32 i;
    register s32 elem_offset ASM_REG("$17");
    s32 child_arg;
    u16 flags;
    u16 child_flags;
    u16 elem_flags;
    register s32 call_code ASM_REG("$5");
    register s32 call_zero ASM_REG("$6");
    register u32 color ASM_REG("$8");

    work = 0;
    saved_arg2 = arg2;
    saved_arg0 = arg0;
    obj = func_8003FD64(0x112, (saved_arg1 = arg1, D_80083498));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_80170B64;
        FIELD(work, s8, 0x13) = 0x21;
        func_8004491C(obj, &D_80045340);
        actor = work;

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, void *, 0x2C) = D_8017418C;
        FIELD(part_b, s8, 0x24) = saved_arg1;
        FIELD(part_b, s8, 0x25) = saved_arg2;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto set_kind_flags;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;

set_kind_flags:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        goto call_actor_setup;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                left = func_800A6D30();
                if (left & 1) {
                    FIELD(work, s32, 0x1C) |= 0x200;
                    right = func_800A6D30();
                    func_800A48F0(work, 1, (right & 0x3F) | 0x20);
                    FIELD(part_b, void *, 0x2C) = D_801741CC;
                }
            }
        }

call_actor_setup:
        func_800A9C18(obj, part_a, part_b, saved_arg0);

        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, void *, 0x8C) = D_801711A4;
        FIELD(work, s32, 0x1C) |= 0x00040000;
        FIELD(actor, s16, 0x92) = -16;
        flags = FIELD(actor, u16, 0x98);
        FIELD(actor, u16, 0xA8) = 0;
        FIELD(actor, s16, 0x9E) = 1;
        FIELD(actor, u16, 0x98) = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = func_8003FD64(0x112, D_80083498);
            FIELD(current, void *, 0xA4) = child_obj;
            if (child_obj != 0) {
                register void *child ASM_REG("$16");

                child = (u8 *)child_obj + 0x20;

                FIELD(child, s16, 2) = 1;
                i = 0;
                base = current;
                elem_offset = 8;
                while (i < FIELD(child, s16, 2)) {
                    color = 0x00C0C0C0;
                    elem = (u8 *)child + elem_offset;
                    ASM_KEEP(elem);
                    call_code = 39;
                    ASM_KEEP_NV(call_code);
                    child_flags = FIELD(child, u16, 4);
                    ASM_KEEP(child_flags);
                    call_zero = 0;
                    ASM_KEEP_NV(call_zero);
                    FIELD(child, u16, 4) = child_flags | 0x8000;
                    child_arg = FIELD(part_b, s32, 0x28);
                    elem_flags = FIELD(elem, u16, 0x14);
                    FIELD(elem, u16, 0x10) = 96;
                    FIELD(elem, u32, 0x28) = child_arg;
                    FIELD(elem, u16, 0x14) = elem_flags | 0xC;
                    elem_offset += 48;
                    FIELD(elem, s16, 0x12) = FIELD(part_b, s16, 0x12) - 128;
                    FIELD(elem, u32, 0xC) = color;
                    FIELD(FIELD(base, void *, 0xA4), void *, 0x10) = D_800D78C0;
                    i++;
                    func_80047784(elem, call_code, call_zero, child_arg);
                    FIELD(child, u16, 6) = 0;
                    func_800478E8(part_b, D_800D71A8, 0);
                    FIELD(child, u32, 0x98) = (u8 *)obj + 30;
                }
            }
            current = (u8 *)current + 4;
            count++;
        } while (count < FIELD(actor, s16, 0x9E));
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
