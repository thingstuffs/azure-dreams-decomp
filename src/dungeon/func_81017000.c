/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_81017000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81017000_0;   /* obj in BODY_NAME */

typedef struct S_81017000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81017000_1;   /* work in BODY_NAME */

typedef struct S_81017000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_81017000_2;   /* part_a in BODY_NAME */

typedef struct S_81017000_3 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_81017000_3;   /* part_b in BODY_NAME */

typedef struct S_81017000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_81017000_4;   /* actor in BODY_NAME */


void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8015EA78;
extern M2C_UNK D_8015F058;
extern M2C_UNK D_80162880;
extern M2C_UNK D_801628E0;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    0x8015E88C, 0x8015EA78, 0x8015F4EC, 0x8015F4EC,
    0x8015F4EC, 0x8015F518, 0x8015F498, 0x8015F498,
    0x8015F498, 0x8015F460, 0x8015F404, 0x8015F518,
    0x8015F518, 0x8015F4DC, 0x94824081, 0x8F828F82,
    0x40818B82, 0x00000000, 0x81824081, 0x81829782,
    0x44819982, 0x00000000, 0x80160950, 0x80160948,
    0x80160940, 0x80160958, 0x80160900, 0x801608F8,
    0x801608F0, 0x00000000, 0x80161EE0, 0x801620F8,
    0x80162204, 0x801624F8, 0x80162668,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 632");
#define BODY_NAME func_8015E88C
#else
#define BODY_NAME func_8015E800
#endif

void *BODY_NAME(s32, s8, s8, s16)
#ifdef __mips__
    __attribute__((section(".text.func_8015E800")))
#endif
    ;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 kind;
    s16 final_arg0;
    s32 left;
    s32 right;
    S_81017000_1 *work = NULL;
    void *obj;
    register S_81017000_2 *part_a ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_81017000_3 *part_b;
    S_81017000_4 *actor;
    register s8 saved_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 saved_arg3;
    register s8 saved_arg2 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *call_a0;
    void *call_a1;

    saved_arg1 = arg1;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    obj = func_8003FD64(0x112, &D_80083498);
    if (obj != NULL) {
        final_arg0 = arg0;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        work = obj + 0x20;
        ((S_81017000_0 *)obj)->unk_10 = &D_8015EA78;
        work->unk_13 = 0x29;
        func_8004491C(obj, &D_80045340);
        part_a = ((S_81017000_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_81017000_0 *)obj)->unk_0C;
        kind = arg0 & 3;
        part_b->unk_25 = saved_arg2;
        actor = work;
        part_b->unk_2C = &D_80162880;
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
                left = func_800A6D30();
                call_a0 = obj;
                if (!(left & 1)) {
                    goto post_kind;
                }
                    work->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = &D_801628E0;
            }
        }
post_kind:
        func_800A9C18(obj, part_a, part_b, final_arg0);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015F058;
        work->unk_1C |= 0x40000;
        actor->unk_92 = -0x18;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
