#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_80047784(void *, s32, s32);
extern void func_800478E8(void *, void *, s32);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800D78C0(void *, void *, void *, void *);
extern void *func_80170A7C(void);
extern void func_80170BB8(void *, void *, void *);
extern void func_8017140C(void *, void *, void *, void *);

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800D71A8[];
extern u8 D_8017586C[];
extern u8 D_80175894[];

void *func_8017087C(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    void *part_a;
    void *slot_base;
    void *work_copy;
    s32 base;
    register void *part_b ASM_REG("$21");
    register void *work ASM_REG("$20");
    register s8 saved_arg1 ASM_REG("$19");
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$18");
    register s32 left ASM_REG("$2");
    register s32 right;
    register void *call_a0 ASM_REG("$4");
    register s32 call_a1 ASM_REG("$5");
    register s32 call_a2 ASM_REG("$6");
    register s32 i ASM_REG("$22");
    register u8 *slot ASM_REG("$23");
    s32 j;

    work = 0;
    call_a0 = (void *)274;
    ASM_USE_NV(call_a0);
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64((s32)call_a0, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = func_80170BB8;
        FIELD(work, s8, 0x13) = 6;
        func_8004491C(obj, &D_80045340);

        part_a = FIELD(obj, void *, 8);
        FIELD(part_a, s16, 0xA) = saved_arg3;
        part_b = FIELD(obj, void *, 0xC);
        slot_base = work;
        kind = arg0 & 3;
        FIELD(part_b, void *, 0x2C) = D_8017586C;
        FIELD(part_b, s8, 0x24) = saved_arg1;
        FIELD(part_b, s8, 0x25) = saved_arg2;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            goto set_flags;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;

set_flags:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        goto post_kind;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                left = func_800A6D30();
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                FIELD(work, s32, 0x1C) |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30() & 0x3F) | 0x20);
                FIELD(part_b, void *, 0x2C) = D_80175894;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
call_a1_setup:
        func_800A9C18(obj, part_a, part_b, arg0);

        i = 0;
        base = 0x00190000;
        slot = (u8 *)slot_base;
        FIELD(slot, u8, 0x9A) = 0xFF;
        FIELD(slot_base, s8, 0x9C) = -1;
        FIELD(slot_base, void *, 0x8C) = func_8017140C;
        FIELD(work, s32, 0x1C) |= 0x40000;
        FIELD(slot_base, s16, 0x92) = -24;
        FIELD(slot_base, s16, 0x9E) = 3;
        do {
            void *new_obj;

            new_obj = func_8003FD64(274, D_80083498);
            FIELD(slot, void *, 0xA4) = new_obj;
            if (new_obj != 0) {
                register void *new_work ASM_REG("$17") = (u8 *)new_obj + 0x20;

                if (i != 0) {
                    FIELD(new_work, s16, 2) = 1;
                } else {
                    FIELD(new_work, s16, 2) = 2;
                }
                ASM_MEM_BARRIER();
                j = 0;
                if (FIELD(new_work, s16, 2) > 0) {
                    register s32 stride ASM_REG("$19");
                    s32 cur_base;

                    work_copy = slot;
                    cur_base = base;
                    stride = 8;
                    do {
                        u8 *entry = (u8 *)new_work + stride;
                        void *callback_obj;
                        register u32 color ASM_REG("$3");

                        color = 0x00C0C0C0;
                        call_a0 = entry;
                        left = FIELD(part_b, s32, 0x28);
                        call_a1 = cur_base >> 16;
                        FIELD(entry, u32, 0xC) = color;
                        FIELD(entry, s32, 0x28) = left;
                        call_a2 = 0;
                        callback_obj = FIELD(work_copy, void *, 0xA4);
                        ASM_USE(call_a2);
                        stride += 48;
                        FIELD(callback_obj, void *, 0x10) = func_800D78C0;
                        left = FIELD(entry, u16, 0x14);
                        j++;
                        left |= 0xC;
                        FIELD(entry, u16, 0x14) = left;
                        func_80047784(call_a0, call_a1, call_a2);
                        FIELD(entry, u16, 0x10) = 96;
                        FIELD(entry, u16, 0x12) = FIELD(part_b, u16, 0x12) - 128;
                        FIELD(new_work, u16, 6) = i + 1;
                        func_800478E8(part_b, D_800D71A8, FIELD(new_work, u16, 6));
                        FIELD(new_work, void *, 0x98) = (u8 *)obj + 30;
                    } while (j < FIELD(new_work, s16, 2));
                }
            }
            base += 0x10000;
            slot += 4;
        } while (++i < FIELD(slot_base, s16, 0x9E));
        FIELD(slot_base, u16, 0x98) = FIELD(slot_base, u16, 0x98) | 0x2000;
        func_800AA36C(slot_base, part_a, part_b, work);
    }
    return work;
}
