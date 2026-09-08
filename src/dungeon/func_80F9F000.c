#include "common.h"

typedef struct S_80F9F000_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80F9F000_0;   /* obj in BODY_NAME */

typedef struct S_80F9F000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F9F000_1;   /* work in BODY_NAME */

typedef struct S_80F9F000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F9F000_2;   /* part_a in BODY_NAME */

typedef struct S_80F9F000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F9F000_3;   /* part_b in BODY_NAME */

typedef struct S_80F9F000_4 {
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
} S_80F9F000_4;   /* actor in BODY_NAME */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80158A70[];
extern u8 D_8015CAD4[];
extern u8 D_8015CAFC[];
extern u8 D_80159138[];

extern void *func_80158800();

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80158800")
    __attribute__((section(".text.func_80158800"), aligned(4))) = {
    0x80158880, 0x80158A70, 0x8015956C, 0x8015956C,
    0x8015956C, 0x80159598, 0x80159518, 0x80159518,
    0x80159518, 0x801594E0, 0x801594C4, 0x80159598,
    0x80159598, 0x8015955C, 0x8015AB5C, 0x8015AB54,
    0x8015AB4C, 0x8015AB64, 0x8015AB0C, 0x8015AB04,
    0x8015AAFC, 0x92824081, 0x81828F82, 0x85829282,
    0x44818482, 0x00000000, 0x0C001000, 0x18001000,
    0x00001400, 0x18001000, 0x08001000, 0x30320C00,
};
__asm__(".globl func_80158800\n"
        ".size func_80158800, 624");
#define BODY_NAME func_80158880
#else
#define BODY_NAME func_80158800
#endif

void *BODY_NAME(s16, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80158800")))
#endif
    ;

void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    s32 kind;
    void *work = 0;
    void *obj;
    void *part_a;
    S_80F9F000_3 *part_b;
    S_80F9F000_4 *actor;
    s32 left;
    s32 right;
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    void *call_a1;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80F9F000_0 *)obj)->unk_10 = D_80158A70;
        ((S_80F9F000_1 *)work)->unk_13 = 0x26;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80F9F000_0 *)obj)->unk_08;
        ((S_80F9F000_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80F9F000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = D_8015CAD4;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = ((S_80F9F000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80F9F000_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = ((S_80F9F000_1 *)work)->unk_14 | 0x2000;
        right = ((S_80F9F000_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_80F9F000_1 *)work)->unk_14 = left;
        ((S_80F9F000_1 *)work)->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(((S_80F9F000_1 *)work)->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                ((S_80F9F000_1 *)work)->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_8015CAFC;
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
        actor->unk_8C = D_80159138;
        ((S_80F9F000_1 *)work)->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
