#include "common.h"
#include "m2c_compat.h"

typedef struct S_80F2D000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80F2D000_0;   /* object in BODY_NAME */

typedef struct S_80F2D000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80F2D000_1;   /* work in BODY_NAME */

typedef struct S_80F2D000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80F2D000_2;   /* part_a in BODY_NAME */

typedef struct S_80F2D000_3 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80F2D000_3;   /* part_b in BODY_NAME */

typedef struct S_80F2D000_4 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
    s16 unk_A6;
} S_80F2D000_4;   /* work_copy in BODY_NAME */


/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern u8 D_80045340[];
void *func_8003FD64();                 /* extern */
M2C_UNK func_8004491C();                /* extern */
M2C_UNK func_800A48F0();        /* extern */
s32 func_800A6D30();                          /* extern */
M2C_UNK func_800A9C18(); /* extern */
M2C_UNK func_800AA36C(); /* extern */
M2C_UNK func_800BC318();                      /* extern */
extern M2C_UNK D_8014CA8C;
extern M2C_UNK D_8014CF74;
extern M2C_UNK D_8014FD30;
extern M2C_UNK D_8014FD78;

#ifdef __mips__
static const u32 bank_words[] __asm__("func_8014C800")
    __attribute__((section(".text.func_8014C800"), aligned(4))) = {
    0x8014C854, 0x8014CA8C, 0x8014D358, 0x8014D358,
    0x8014D358, 0x8014D384, 0x8014D304, 0x8014D304,
    0x8014D304, 0x8014D2B0, 0x8014D2E8, 0x8014D384,
    0x8014D384, 0x8014D348, 0x8014EBC4, 0x8014EBBC,
    0x8014EBB4, 0x8014EBCC, 0x8014EB74, 0x8014EB6C,
    0x8014EB64
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 652");
#define BODY_NAME composite_body
#define BODY_STORAGE static
#define BODY_ATTR __attribute__((used, section(".text.func_8014C800")))
#else
#define BODY_NAME func_8014C800
#define BODY_STORAGE
#define BODY_ATTR
#endif

BODY_STORAGE void *BODY_NAME(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) BODY_ATTR;
/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
BODY_STORAGE void *BODY_NAME(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c) {
    s32 unksp20;
    s32 kind;
    s32 variant;
    void *obj_alt;
    S_80F2D000_3 *part_b;
    S_80F2D000_2 *part_a;
    void *work_copy;
    void *object;
    S_80F2D000_1 *work;

    unksp20 = (s32) *(s8 *)-0x149C;
    work = NULL;
    variant = 1;
    object = func_8003FD64(0x112, D_80083498);
    if (object == NULL) {
        goto done;
    } else {
        work = object + 0x20;
        ((S_80F2D000_0 *)object)->unk_10 = &D_8014CA8C;
        work->unk_13 = 0x23;
        func_8004491C(object, D_80045340);
        part_a = ((S_80F2D000_0 *)object)->unk_08;
        part_a->unk_0A = attr_c;
        part_b = ((S_80F2D000_0 *)object)->unk_0C;
        part_b->unk_25 = attr_b;
        work_copy = work;
        part_b->unk_2C = &D_8014FD30;
        kind = spawn_flags & 3;
        part_b->unk_24 = attr_a;
        if (kind == 1) {
            work->unk_14 = (s32) (work->unk_14 | 0x6000);
            work->unk_1C = (s32) (work->unk_1C | 0x6000);
        } else if (kind >= 2) {
            work->unk_14 = (s32) (work->unk_14 | 0x2000);
            work->unk_1C = (s32) (work->unk_1C | 0x2000);
        } else if (((spawn_flags & ~3) << 0x10) == 0) {
            if (work->unk_14 & 0x200) {
                goto status_done;
            }
            if (!(func_800A6D30() & 1)) {
                goto status_done;
            }
            work->unk_1C = (s32) (work->unk_1C | 0x200);
            func_800A48F0(work, 1, (func_800A6D30() & 0x3F) | 0x20);
            part_b->unk_2C = &D_8014FD78;
        status_done:
            variant = func_800A6D30() & 3;
        }
        func_800A9C18(object, part_a, part_b, spawn_flags);
        ((S_80F2D000_4 *)work_copy)->unk_9A = 0xFF;
        ((S_80F2D000_4 *)work_copy)->unk_9C = -1;
        ((S_80F2D000_4 *)work_copy)->unk_8C = &D_8014CF74;
        ((S_80F2D000_4 *)work_copy)->unk_A4 = -1;
        if (variant != 0) {
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 0;
        } else {
            obj_alt = work_copy - 0x20;
            ((S_80F2D000_4 *)work_copy)->unk_A6 = 1;
            part_b->unk_10 = 0x60;
            part_b->unk_14 = (u16) (part_b->unk_14 | 0xC);
            part_b->unk_12 = (u16) (part_b->unk_12 - 0x80);
            func_80044A50(obj_alt);
            func_800BC318(obj_alt);
        }
        func_800AA36C(work_copy, part_a, part_b, work);
        goto done;
    }
done:
    return work;
}
