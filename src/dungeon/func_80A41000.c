#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_8014C884_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_8014C884_0;   /* obj in func_8014C884 */

typedef struct S_8014C884_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8014C884_1;   /* work in func_8014C884 */

typedef struct S_8014C884_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8014C884_2;   /* part_a in func_8014C884 */

typedef struct S_8014C884_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8014C884_3;   /* part_b in func_8014C884 */

typedef struct S_8014C884_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_8014C884_4;   /* actor in func_8014C884 */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8014CA58[];
extern u8 D_80150820[];
extern u8 D_80150860[];
extern M2C_UNK D_8014CE84;

/* The carved row starts with this 33-word text-local pointer/literal bank. */
extern void *func_8014C800(s32, s8, s8, s16);
extern void *func_8014C884(s16, s16, s16, s16);
extern u8 D_8014D24C[];
extern u8 D_8014D278[];
extern u8 D_8014D1F8[];
extern u8 D_8014D1C0[];
extern u8 D_8014D23C[];
extern u8 D_8014E9EC[];
extern u8 D_8014E9E4[];
extern u8 D_8014E9DC[];
extern u8 D_8014E9F4[];
extern u8 D_8014E99C[];
extern u8 D_8014E994[];
extern u8 D_8014E98C[];

/* These text-local table entries have no catalog symbols. */
__asm__(".set D_8014D24C, 0x8014D24C");
__asm__(".set D_8014D278, 0x8014D278");
__asm__(".set D_8014D1F8, 0x8014D1F8");
__asm__(".set D_8014D1C0, 0x8014D1C0");
__asm__(".set D_8014D23C, 0x8014D23C");
__asm__(".set D_8014E9EC, 0x8014E9EC");
__asm__(".set D_8014E9E4, 0x8014E9E4");
__asm__(".set D_8014E9DC, 0x8014E9DC");
__asm__(".set D_8014E9F4, 0x8014E9F4");
__asm__(".set D_8014E99C, 0x8014E99C");
__asm__(".set D_8014E994, 0x8014E994");
__asm__(".set D_8014E98C, 0x8014E98C");

static const u32 func_8016A800_prefix[33] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
        (u32)func_8014C884,
        (u32)D_8014CA58,
        (u32)D_8014D24C,
        (u32)D_8014D24C,
        (u32)D_8014D24C,
        (u32)D_8014D278,
        (u32)D_8014D1F8,
        (u32)D_8014D1F8,
        (u32)D_8014D1F8,
        (u32)D_8014D1C0,
        (u32)D_8014D1C0,
        (u32)D_8014D278,
        (u32)D_8014D278,
        (u32)D_8014D23C,
        0x10001000,
        0x0DAC1194,
        0x10001000,
        0x12C00D48,
        0x11300ED8,
        0x10001000,
        0x0D481388,
        0x0ED81194,
        (u32)D_8014E9EC,
        (u32)D_8014E9E4,
        (u32)D_8014E9DC,
        (u32)D_8014E9F4,
        (u32)D_8014E99C,
        (u32)D_8014E994,
        (u32)D_8014E98C,
        0x01000340,
        0x00800040,
        0x01000340,
        0x00400040,
    };
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 600");

void *func_8014C884(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    S_8014C884_2 *part_a;
    S_8014C884_3 *part_b;
    S_8014C884_1 *work;
    S_8014C884_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    void *call_a0;
    void *call_a1;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8014C884_0 *)obj)->unk_10 = D_8014CA58;
        work->unk_13 = 5;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_8014C884_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8014C884_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_80150820;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = work->unk_14 | 0x2000;
        right = work->unk_1C | 0x2000;
write_kind:
        work->unk_14 = left;
        work->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                ASM_KEEP(call_a0);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80150860;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a0 = obj;
call_a1_setup:
        func_800A9C18(call_a0, part_a, part_b, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE84;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
