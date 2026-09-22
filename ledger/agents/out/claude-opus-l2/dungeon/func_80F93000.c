#include "common.h"

typedef struct S_80F93000_0 {
    u8 pad_00[0x8];
    void ** unk_08;
    void ** unk_0C;
    void * unk_10;
} S_80F93000_0;   /* obj in BODY_NAME */

typedef struct S_80F93000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F93000_1;   /* work in BODY_NAME */

typedef struct S_80F93000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F93000_2;   /* part_a in BODY_NAME */

typedef struct S_80F93000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80F93000_3;   /* part_b in BODY_NAME */

typedef struct S_80F93000_4 {
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
} S_80F93000_4;   /* actor in BODY_NAME */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();

extern u8 D_80045340[];
extern u8 D_80083498[];
extern u8 D_80164A70[];
extern u8 D_80168AD4[];
extern u8 D_80168AFC[];
extern u8 D_80165138[];

extern void *func_80164800();

#ifdef __mips__
static const u32 bank_words[] __asm__("func_80164800")
    __attribute__((section(".text.func_80164800"), aligned(4))) = {
    0x80164880, 0x80164A70, 0x8016556C, 0x8016556C,
    0x8016556C, 0x80165598, 0x80165518, 0x80165518,
    0x80165518, 0x801654E0, 0x801654C4, 0x80165598,
    0x80165598, 0x8016555C, 0x80166B5C, 0x80166B54,
    0x80166B4C, 0x80166B64, 0x80166B0C, 0x80166B04,
    0x80166AFC, 0x92824081, 0x81828F82, 0x85829282,
    0x44818482, 0x00000000, 0x0C001000, 0x18001000,
    0x00001400, 0x18001000, 0x08001000, 0x0A0D0C00,
};
__asm__(".globl func_80164800\n"
        ".size func_80164800, 624");
#define BODY_NAME func_80164880
#else
#define BODY_NAME func_80164800
#endif

void *BODY_NAME(s16, s16, s16, s16)
#ifdef __mips__
    __attribute__((section(".text.func_80164800")))
#endif
    ;

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *BODY_NAME(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *work = 0;
    void *obj;
    void *part_a;
    S_80F93000_3 *part_b;
    S_80F93000_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = func_8003FD64(0x112, D_80083498);
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80F93000_0 *)obj)->unk_10 = D_80164A70;
        ((S_80F93000_1 *)work)->unk_13 = 0x26;
        func_8004491C(obj, &D_80045340);

        part_a = ((S_80F93000_0 *)obj)->unk_08;
        ((S_80F93000_2 *)part_a)->unk_0A = saved_spawn;
        part_b = ((S_80F93000_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = D_80168AD4;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            left = ((S_80F93000_1 *)work)->unk_14 | 0x6000;
            right = ((S_80F93000_1 *)work)->unk_1C | 0x6000;
            goto write_kind;
        }
        if (kind < 2) {
            goto normal_kind;
        }

        left = ((S_80F93000_1 *)work)->unk_14 | 0x2000;
        right = ((S_80F93000_1 *)work)->unk_1C | 0x2000;
write_kind:
        ((S_80F93000_1 *)work)->unk_14 = left;
        ((S_80F93000_1 *)work)->unk_1C = right;
        goto post_kind;

normal_kind:
        call_a1 = obj;
        if (((flags & ~3) << 16) == 0) {
            if (!(((S_80F93000_1 *)work)->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = func_800A6D30();
                call_a1 = obj;
                if (!(left & 1)) {
                    goto call_a1_setup;
                }
                ((S_80F93000_1 *)work)->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30(obj) & 0x3F) | 0x20);
                part_b->unk_2C = D_80168AFC;
                goto post_kind;
            }
        }
        goto call_a1_setup;

post_kind:
        call_a1 = obj;
call_a1_setup:
        func_800A9C18(call_a1, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = D_80165138;
        ((S_80F93000_1 *)work)->unk_1C |= 0x40000;
        actor->unk_A0 = 0;
        actor->unk_92 = -0x30;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
