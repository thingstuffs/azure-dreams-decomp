#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

typedef struct {
    u32 word0;
    u32 word4;
    u32 word8;
} __attribute__((packed)) Copy12;

void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80024750;
extern Copy12 D_80025E64;
extern M2C_UNK D_80045340;

void func_818FF5B8(void **arg0, void *arg1, void *arg2) {
    register void *temp_a3 ASM_REG("$7");
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    register u8 *copy_page ASM_REG("$2");
    register Copy12 *copy_src ASM_REG("$6");
    register u32 copy0 ASM_REG("$3");
    register u32 copy4 ASM_REG("$4");
    register u32 copy8 ASM_REG("$5");

    temp_v0 = func_8003FC64(0x212);
    temp_v1 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v1, void **, 0x2C) = (void *) *arg0;
        M2C_FIELD(temp_v1, s32 *, 0x30) = (s32) M2C_FIELD(*arg0, s32 *, 0x60);
        M2C_FIELD(temp_v1, void ***, 0x34) = arg0;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80024750;
        func_8004491C(temp_v0, &D_80045340);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_a3, s16 *, 6) = 0;
        M2C_FIELD(temp_a3, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a3, u16 *, 0x14) | 0xC);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_v1_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
        temp_a3 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a3, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_a3, s16 *, 0x1C) = 0x800;
        M2C_FIELD(temp_a3, u8 *, 0xC) = (u8) M2C_FIELD(arg2, u8 *, 0xC);
        M2C_FIELD(temp_a3, u8 *, 0xD) = (u8) M2C_FIELD(arg2, u8 *, 0xD);
        M2C_FIELD(temp_a3, u8 *, 0xE) = (u8) M2C_FIELD(arg2, u8 *, 0xE);
        M2C_FIELD(temp_a3, s16 *, 0x1A) = (s16) (0x1000 - M2C_FIELD(arg2, u16 *, 0x1A));
        ASM_KEEP(temp_a3);
        copy_page = (u8 *) 0x80020000;
        ASM_KEEP(copy_page);
        copy_src = (Copy12 *) (copy_page + 0x5E64);
        copy0 = copy_src->word0;
        copy4 = copy_src->word4;
        copy8 = copy_src->word8;
        ASM_KEEP(copy_src);
        M2C_FIELD(temp_v0, Copy12 *, 0x40).word0 = copy0;
        ASM_KEEP(copy0);
        M2C_FIELD(temp_v0, Copy12 *, 0x40).word4 = copy4;
        ASM_KEEP(copy4);
        M2C_FIELD(temp_v0, Copy12 *, 0x40).word8 = copy8;
        ASM_KEEP(copy8);
        M2C_FIELD(temp_a3, void **, 8) = (void *) (temp_v0 + 0x40);
    }
}

/* MECHANISM: Reordered header stores and reused/pinned the subobject in retail $a3.
   A pinned a2/v1/a0/a1 packed copy plus ASM_KEEP seams preserves load-delay nops.
   An opaque v0-held 0x80020000 page yields retail's split lui/addiu address pair. */
