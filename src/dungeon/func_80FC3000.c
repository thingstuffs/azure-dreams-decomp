/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

typedef struct S_8015E8A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8015E8A4_0;   /* obj in func_8015E8A4 */

typedef struct S_8015E8A4_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015E8A4_1;   /* work in func_8015E8A4 */

typedef struct S_8015E8A4_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8015E8A4_2;   /* pin_part_a in func_8015E8A4 */

typedef struct S_8015E8A4_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8015E8A4_3;   /* part_b in func_8015E8A4 */

typedef struct S_8015E8A4_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_8015E8A4_4;   /* pin_actor in func_8015E8A4 */


extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_800673A0(s16 *, s32, s32);
extern void func_800A48F0(void *, s32, s32);
extern s32 func_800A6D30();
extern void func_800A9C18(void *, void *, void *, s16);
extern void func_800AA36C(void *, void *, void *, void *);
extern void func_80158A40(void) __attribute__((noreturn));
extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_8015EB40[];
extern u8 D_8015EF6C[];
extern u8 D_80163258[];
extern u8 D_80163298[];


extern void *func_8015E8A4(s32, s8, s8, s16);
static const u32 bank_words[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    (u32)func_8015E8A4, (u32)D_8015EB40, 0x8015F12C, 0x8015F198,
    0x8015F26C, 0x8015F3FC, 0x8015F444, 0x00000000,
    0x8015F794, 0x8015F794, 0x8015F794, 0x8015F7C0,
    0x8015F740, 0x8015F740, 0x8015F740, 0x8015F6D8,
    0x8015F6D8, 0x8015F7C0, 0x8015F7C0, 0x8015F784,
    0x80160F08, 0x80160F00, 0x80160EF8, 0x80160F10,
    0x80160EB8, 0x80160EB0, 0x80160EA8, 0x01000340,
    0x00800040, 0x8C824081, 0x84828582, 0x81824081,
    0x8D824081, 0x92828582, 0x99829282, 0x84824081,
    0x8E828182, 0x85828382, 0x00004481, 0x01000340,
    0x00400040,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 832");

void *func_8015E8A4(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
    __attribute__((section(".text.func_8015E800")));

void *func_8015E8A4(s32 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register void *work ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *obj;
    register s32 call_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *call_target ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    S_8015E8A4_3 *part_b;
    void *part_a;
    s16 saved_arg0;
    s32 kind;
    s32 left;
    s32 right;
    s32 index;
    s32 count;
    u16 actor_value;
    s32 double_index;
    s32 scaled_index;
    u8 *selected_entry;
    s16 *values_ptr;
    s16 values[4];
    u8 *entry;
    register s8 pin_arg1 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s16 pin_arg3;
    void *pin_part_a;
    register void *pin_actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    work = 0;
    call_id = 0x112;
    ASM_USE_NV(call_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    pin_arg1 = arg1;
    pin_arg3 = arg3;
    call_target = D_80083498;
    ASM_USE2_NV(pin_arg3, call_target);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    obj = func_8003FD64(call_id, call_target);
    saved_arg0 = (s16)arg0;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E8A4_0 *)obj)->unk_10 = D_8015EB40;
        ((S_8015E8A4_1 *)work)->unk_13 = 0x27;
        func_8004491C(obj, &D_80045340);

        pin_part_a = ((S_8015E8A4_0 *)obj)->unk_08;
        ((S_8015E8A4_2 *)pin_part_a)->unk_0A = pin_arg3;
        part_b = ((S_8015E8A4_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = arg2;
        pin_actor = work;
        part_b->unk_2C = D_80163258;
        part_b->unk_24 = pin_arg1;
        if (kind == 1) {
            left = ((S_8015E8A4_1 *)work)->unk_14 | 0x6000;
            right = ((S_8015E8A4_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }
        left = ((S_8015E8A4_1 *)work)->unk_14 | 0x2000;
        right = ((S_8015E8A4_1 *)work)->unk_1C | 0x2000;

write_kind:
        ((S_8015E8A4_1 *)work)->unk_14 = left;
        ((S_8015E8A4_1 *)work)->unk_1C = right;
        goto post_kind;

normal_kind:
        if (((arg0 & ~3) << 16) == 0) {
            if (!(((S_8015E8A4_1 *)work)->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    ((S_8015E8A4_1 *)work)->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) |
                                      0x20);
                    part_b->unk_2C = D_80163298;
                }
            }
        }

post_kind:
        func_800A9C18(obj, pin_part_a, part_b, saved_arg0);
        index = 0;
        actor_value = part_b->unk_12;
        ((S_8015E8A4_4 *)pin_actor)->unk_9A = 0xFF;
        ((S_8015E8A4_4 *)pin_actor)->unk_9C = -1;
        ((S_8015E8A4_4 *)pin_actor)->unk_8C = D_8015EF6C;
        ((S_8015E8A4_4 *)pin_actor)->unk_AE = actor_value;

        entry = part_b->unk_08;
scan_entries:
        double_index = index << 1;
        if (!(*entry & 0x20)) {
            goto scan_done;
        }
        entry += 12;
        index += 1;
        goto scan_entries;
scan_done:

        values_ptr = values;
        ASM_KEEP(values_ptr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
