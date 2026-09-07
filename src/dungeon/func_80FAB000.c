#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80FAB000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FAB000_0;   /* obj in BODY_NAME */

typedef struct S_80FAB000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FAB000_1;   /* work in BODY_NAME */

typedef struct S_80FAB000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FAB000_2;   /* part_a in BODY_NAME */

typedef struct S_80FAB000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80FAB000_3;   /* part_b in BODY_NAME */

typedef struct S_80FAB000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x3];
    s16 unk_A0;
} S_80FAB000_4;   /* actor in BODY_NAME */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern void *func_8014C800();

extern s32 D_80045340;
extern s32 D_80083498;
extern u8 D_8014CA70[];
extern M2C_UNK D_8015D138;
extern u8 D_80150AD4[];
extern u8 D_80150AFC[];

#ifdef __mips__
__asm__(".set D_8015D138, 0x8014D138");
#endif

#ifdef __mips__
static const u32 prefix_words[] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
    0x8014C880, 0x8014CA70, 0x8014D56C, 0x8014D56C,
    0x8014D56C, 0x8014D598, 0x8014D518, 0x8014D518,
    0x8014D518, 0x8014D4E0, 0x8014D4C4, 0x8014D598,
    0x8014D598, 0x8014D55C, 0x8014EB5C, 0x8014EB54,
    0x8014EB4C, 0x8014EB64, 0x8014EB0C, 0x8014EB04,
    0x8014EAFC, 0x92824081, 0x81828F82, 0x85829282,
    0x44818482, 0x00000000, 0x0C001000, 0x18001000,
    0x00001400, 0x18001000, 0x08001000, 0x27BD0C00,
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 624");
#define BODY_NAME func_8014C880
#else
#define BODY_NAME func_8014C800
#endif

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
    __attribute__((section(".text.func_8014C800")));
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *obj;
    S_80FAB000_2 *part_a;
    S_80FAB000_3 *part_b;
    S_80FAB000_1 *work;
    S_80FAB000_4 *actor;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_a0;
    void *call_a1;

    work = 0;
    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, &D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80FAB000_0 *)obj)->unk_10 = D_8014CA70;
        work->unk_13 = 0x26;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80FAB000_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_80FAB000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        actor = work;
        part_b->unk_2C = D_80150AD4;
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
                ASM_KEEP(call_a0);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80150AFC;
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
        actor->unk_8C = &D_8015D138;
        work->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
