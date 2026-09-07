#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80F45000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80F45000_0;   /* obj in BODY_NAME */

typedef struct S_80F45000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F45000_1;   /* work in BODY_NAME */

typedef struct S_80F45000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F45000_2;   /* part_a in BODY_NAME */

typedef struct S_80F45000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F45000_3;   /* part_b in BODY_NAME */

typedef struct S_80F45000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80F45000_4;   /* actor in BODY_NAME */


extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern void *func_8015E974() __attribute__((noreturn));
extern void *func_8015E9EC() __attribute__((noreturn));

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_8015EA68[];
extern M2C_UNK D_8015EE94;
extern u8 D_80162A7C[];
extern u8 D_80162AD4[];

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80F45000")
    __attribute__((section(".text.func_80F45000"), aligned(4))) = {
    0x8015E894, 0x8015EA68, 0x8015F278, 0x8015F278,
    0x8015F278, 0x8015F2A4, 0x8015F224, 0x8015F224,
    0x8015F224, 0x8015F1D0, 0x8015F208, 0x8015F2A4,
    0x8015F2A4, 0x8015F268, 0x08000000, 0x00200080,
    0x00800800, 0x08000000, 0x00000080, 0x08000020,
    0x00000040, 0x00800800, 0x00000010, 0x00000080,
    0x801608B4, 0x801609BC, 0x80160A24, 0x80160AC0,
    0x80160D90, 0x80160E14, 0x80161078, 0x80161070,
    0x80161068, 0x80161080, 0x80161028, 0x80161020,
    0x80161018,
};
__asm__(".globl func_80F45000\n"
        ".size func_80F45000,616");
#define BODY_NAME func_80F45094
#else
#define BODY_NAME func_80F45000
#endif

#ifdef __mips__
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
    __attribute__((section(".text.func_80F45000")));
#endif
void *BODY_NAME(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    void *work = 0;
    void *obj;
    void *part_a;
    register void *part_b;
    S_80F45000_4 *actor;
    register s32 kind;
    s32 probe;
    register s8 saved_arg1 ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* MATCH pin: retail schedule: same instructions, different order without it */
    void *call_a0;
    void *call_a1;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80F45000_0 *)obj)->unk_10 = D_8015EA68;
        ((S_80F45000_1 *)work)->unk_13 = 0x24;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80F45000_0 *)obj)->unk_08;
        ((S_80F45000_2 *)part_a)->unk_0A = saved_arg3;
        part_b = ((S_80F45000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        ((S_80F45000_3 *)part_b)->unk_25 = saved_arg2;
        actor = work;
        ((S_80F45000_3 *)part_b)->unk_2C = D_80162A7C;
        ((S_80F45000_3 *)part_b)->unk_24 = saved_arg1;

        if (kind == 1) {
            s32 left;
            s32 right;

            left = ((S_80F45000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80F45000_1 *)work)->unk_1C | 0x6000;
            ASM_KEEP(left);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            ASM_TAILSLOT_PIN(right);   /* MATCH pin: load-bearing for the whole function shape */
            return func_8015E974();
        }
        if (kind >= 2) {
            ((S_80F45000_1 *)work)->unk_14 |= 0x2000;
            ((S_80F45000_1 *)work)->unk_1C |= 0x2000;
            return func_8015E9EC();
        }

        call_a0 = obj;
        if (((arg0 & ~3) << 16) == 0) {
            if (!(((S_80F45000_1 *)work)->unk_14 & 0x200)) {
                call_a1 = part_a;
                probe = func_800A6D30();
                call_a0 = obj;
                if (!(probe & 1)) {
                    goto post_kind;
                }
                    ((S_80F45000_1 *)work)->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    ((S_80F45000_3 *)part_b)->unk_2C = D_80162AD4;
            }
        }

post_kind:
        func_800A9C18(obj, part_a, part_b, arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE94;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
