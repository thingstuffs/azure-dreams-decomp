#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
typedef void (*retfn)(void);

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A6D30();
extern void func_800A48F0(void *, s32, s32);
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void func_8016A984(void) __attribute__((noreturn));
extern void func_8016A9FC(void) __attribute__((noreturn));
extern void func_8016AA40(void);

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8016AB40[];
extern u8 D_8016AF6C[];
extern u8 D_8016F258[];
extern u8 D_8016F298[];

#ifdef __mips__
static const u32 bank_words[41] __asm__("func_80FB7000")
    __attribute__((section(".text.func_80FB7000"), aligned(4))) = {
    0x8016A8A4, (u32)D_8016AB40,
    0x8016B12C, 0x8016B198, 0x8016B26C, 0x8016B3FC,
    0x8016B444, 0x00000000,
    0x8016B794, 0x8016B794, 0x8016B794, 0x8016B7C0,
    0x8016B740, 0x8016B740, 0x8016B740, 0x8016B6D8,
    0x8016B6D8, 0x8016B7C0, 0x8016B7C0, 0x8016B784,
    0x8016CF08, 0x8016CF00, 0x8016CEF8, 0x8016CF10,
    0x8016CEB8, 0x8016CEB0, 0x8016CEA8,
    0x01000340, 0x00800040, 0x8C824081, 0x84828582,
    0x81824081, 0x8D824081, 0x92828582, 0x99829282,
    0x84824081, 0x8E828182, 0x85828382, 0x00004481,
    0x01000340, 0x00400040,
};
__asm__(".globl func_80FB7000\n"
        ".size func_80FB7000, 832");
#define BODY_NAME func_80FB70A4
#else
#define BODY_NAME func_80FB7000
#endif

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
#ifdef __mips__
    __attribute__((section(".text.func_80FB7000")))
#endif
    ;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register void *work ASM_REG("$16");
    void *obj;
    register s32 call_id ASM_REG("$4");
    register void *call_target ASM_REG("$5");
    void *part_b;
    void *part_a;
    s16 saved_arg0;
    s32 kind;
    s32 left;
    s32 right;
    register s32 index ASM_REG("$5");
    s32 count;
    u16 actor_value;
    register s32 double_index ASM_REG("$6");
    register s32 scaled_index ASM_REG("$2");
    register u8 *selected_entry ASM_REG("$2");
    register s16 *values_ptr ASM_REG("$4");
    s16 values[4];
    u8 *entry;
    register s8 pin_arg1 ASM_REG("$21");
    register s16 pin_arg3 ASM_REG("$18");
    register void *pin_part_a ASM_REG("$22");
    register void *pin_actor ASM_REG("$20");

    work = 0;
    call_id = 0x112;
    ASM_USE_NV(call_id);
    pin_arg1 = arg1;
    pin_arg3 = arg3;
    call_target = D_80083498;
    ASM_USE2_NV(pin_arg3, call_target);
    obj = func_8003FD64(call_id, call_target);
    saved_arg0 = (s16)arg0;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        FIELD(obj, void *, 0x10) = D_8016AB40;
        FIELD(work, s8, 0x13) = 0x27;
        func_8004491C(obj, &D_80045340);

        pin_part_a = FIELD(obj, void *, 8);
        FIELD(pin_part_a, s16, 0xA) = pin_arg3;
        part_b = FIELD(obj, void *, 0xC);
        kind = arg0 & 3;
        FIELD(part_b, s8, 0x25) = arg2;
        pin_actor = work;
        FIELD(part_b, void *, 0x2C) = D_8016F258;
        FIELD(part_b, s8, 0x24) = pin_arg1;

        if (kind == 1) {
            left = FIELD(work, s32, 0x14) | 0x6000;
            right = FIELD(work, s32, 0x1C) | 0x6000;
            ASM_KEEP(left);
            ASM_TAILSLOT_PIN(right);
            func_8016A984();
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = FIELD(work, s32, 0x14) | 0x2000;
        right = FIELD(work, s32, 0x1C) | 0x2000;

write_kind:
        FIELD(work, s32, 0x14) = left;
        FIELD(work, s32, 0x1C) = right;
        ASM_JALDELAY_PIN(right);
        func_8016A9FC();

normal_kind:
        {
            register s32 mask ASM_REG("$2");
            mask = -4;
            if (((arg0 & mask) << 16) != 0) {
                goto normal_kind_nonzero;
            }
            if (!(FIELD(work, s32, 0x14) & 0x200)) {
                if (func_800A6D30() & 1) {
                    FIELD(work, s32, 0x1C) |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) |
                                      0x20);
                    FIELD(part_b, void *, 0x2C) = D_8016F298;
                }
            }
        }

normal_kind_nonzero:

post_kind:
        func_800A9C18(obj, pin_part_a, part_b, saved_arg0);

        index = 0;
        ASM_USE_NV(index);
        actor_value = FIELD(part_b, u16, 0x12);
        FIELD(pin_actor, u8, 0x9A) = 0xFF;
        FIELD(pin_actor, s8, 0x9C) = -1;
        FIELD(pin_actor, void *, 0x8C) = D_8016AF6C;
        FIELD(pin_actor, u16, 0xAE) = actor_value;

        entry = FIELD(part_b, u8 *, 8);
    scan_entries:
        ASM_CLOBBER("$5");
        double_index = index << 1;
        if (!(*entry & 0x20)) {
            goto scan_done;
        }
        entry += 12;
        ASM_CLOBBER("$5");
        index += 1;
        ASM_KEEP(entry);
        ASM_USE_NV(index);
        ASM_KEEP(index);
        ASM_TAILSLOT_PIN(index);
        func_8016AA40();
scan_done:

        values_ptr = values;
        ASM_KEEP(values_ptr);
        scaled_index = double_index + index;
        scaled_index <<= 2;
        ASM_KEEP(scaled_index);
        selected_entry =
            (u8 *)(scaled_index + (s32)FIELD(part_b, u8 *, 8));
        count = (*(u16 *)(selected_entry + 6)) >> 6;
        values[2] = 0x100;
        values[0] = 0;
        values[3] = 1;
        values[1] = count;
        func_800673A0(values_ptr, 0, count - 1);

        values[2] = 0x10;
        values[0] = 0x30;
        values[1] -= 1;
        do {
            func_800673A0(values, values[0] - 0x30, values[1]);
            values[0] += 0x40;
        } while (values[0] < 0x100);

        func_800AA36C(pin_actor, pin_part_a, part_b, work);
    }
    return work;
}

extern void func_8016A9FC(void) __attribute__((noreturn));
#if 0
extern void func_8016AA40(void) __attribute__((noreturn));
#endif
