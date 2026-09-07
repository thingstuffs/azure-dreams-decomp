#include "common.h"

typedef void (*retfn)(void);

typedef struct S_80FB7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FB7000_0;   /* obj in BODY_NAME */

typedef struct S_80FB7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FB7000_1;   /* work in BODY_NAME */

typedef struct S_80FB7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FB7000_2;   /* pin_part_a in BODY_NAME */

typedef struct S_80FB7000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FB7000_3;   /* part_b in BODY_NAME */

typedef struct S_80FB7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FB7000_4;   /* pin_actor in BODY_NAME */


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
    register void *work ASM_REG("$16");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *obj;
    register s32 call_id ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *call_target ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    S_80FB7000_3 *part_b;
    void *part_a;
    s16 saved_arg0;
    s32 kind;
    s32 left;
    s32 right;
    register s32 index ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 count;
    u16 actor_value;
    register s32 double_index ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    register s32 scaled_index ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *selected_entry;
    s16 *values_ptr;
    s16 values[4];
    u8 *entry;
    register s8 pin_arg1 ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
    s16 pin_arg3;
    void *pin_part_a;
    register void *pin_actor ASM_REG("$20");   /* MATCH pin: load-bearing for the whole function shape */

    work = 0;
    call_id = 0x112;
    ASM_USE_NV(call_id);   /* MATCH pin: retail schedule: same instructions, different order without it */
    pin_arg1 = arg1;
    pin_arg3 = arg3;
    call_target = D_80083498;
    ASM_USE2_NV(pin_arg3, call_target);   /* MATCH pin: retail schedule: same instructions, different order without it */
    obj = func_8003FD64(call_id, call_target);
    saved_arg0 = (s16)arg0;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FB7000_0 *)obj)->unk_10 = D_8016AB40;
        ((S_80FB7000_1 *)work)->unk_13 = 0x27;
        func_8004491C(obj, &D_80045340);

        pin_part_a = ((S_80FB7000_0 *)obj)->unk_08;
        ((S_80FB7000_2 *)pin_part_a)->unk_0A = pin_arg3;
        part_b = ((S_80FB7000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = arg2;
        pin_actor = work;
        part_b->unk_2C = D_8016F258;
        part_b->unk_24 = pin_arg1;

        if (kind == 1) {
            left = ((S_80FB7000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80FB7000_1 *)work)->unk_1C | 0x6000;
            ASM_KEEP(left);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_TAILSLOT_PIN(right);   /* MATCH pin: load-bearing for the whole function shape */
            func_8016A984();
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = ((S_80FB7000_1 *)work)->unk_14 | 0x2000;
        right = ((S_80FB7000_1 *)work)->unk_1C | 0x2000;

write_kind:
        ((S_80FB7000_1 *)work)->unk_14 = left;
        ((S_80FB7000_1 *)work)->unk_1C = right;
        func_8016A9FC();

normal_kind:
        {
            s32 mask;
            mask = -4;
            if (((arg0 & mask) << 16) != 0) {
                goto normal_kind_nonzero;
            }
            if (!(((S_80FB7000_1 *)work)->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    ((S_80FB7000_1 *)work)->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) |
                                      0x20);
                    part_b->unk_2C = D_8016F298;
                }
            }
        }

normal_kind_nonzero:

post_kind:
        func_800A9C18(obj, pin_part_a, part_b, saved_arg0);

        index = 0;
        ASM_USE_NV(index);   /* MATCH pin: retail basic-block layout depends on it */
        actor_value = part_b->unk_12;
        ((S_80FB7000_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_80FB7000_4 *)pin_actor)->unk_9C = -1;
        ((S_80FB7000_4 *)pin_actor)->unk_8C = D_8016AF6C;
        ((S_80FB7000_4 *)pin_actor)->unk_AE = actor_value;

        entry = part_b->unk_08;
    scan_entries:
        ASM_CLOBBER("$5");   /* MATCH pin: retail immediate-load split depends on it */
        double_index = index << 1;
        if (!(*entry & 0x20)) {
            goto scan_done;
        }
        entry += 12;
        index += 1;
        ASM_KEEP(entry);   /* MATCH pin: retail keeps a computation the compiler would drop */
        ASM_TAILSLOT_PIN(index);   /* MATCH pin: retail delay-slot contents depend on it */
        func_8016AA40();
scan_done:

        values_ptr = values;
        ASM_KEEP(values_ptr);   /* MATCH pin: retail schedule: same instructions, different order without it */
        scaled_index = double_index + index;
        scaled_index <<= 2;
        selected_entry =
            (u8 *)(scaled_index + (s32)part_b->unk_08);
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
