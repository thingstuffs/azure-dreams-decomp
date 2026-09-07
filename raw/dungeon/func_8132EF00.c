#include "common.h"

typedef s32 M2C_UNK;
typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern s32 func_80167088();
extern M2C_UNK D_80045C34;
extern M2C_UNK D_80165AB8;
extern M2C_UNK D_80173B34[3];

void func_80165F00(void *arg0)
{
    s32 temp_coord;
    s32 temp_coord2;
    s32 temp_rand2;
    s32 temp_v1;
    register s32 temp_page ASM_REG("$5");
    void *temp_base2;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80165AB8;
        temp_v1 = rand() & 0x3F;
        temp_coord =
            M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 2) - 0x20;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 2) =
            temp_coord + temp_v1;
        temp_rand2 = rand() & 0x3F;
        ASM_SCHED_BARRIER();
        temp_base2 = M2C_FIELD(arg0, void **, 8);
        ASM_MEM_BARRIER();
        temp_page = (s32)0x80040000;
        ASM_KEEP(temp_page);
        temp_coord2 = M2C_FIELD(temp_base2, u16 *, 6) - 0x1A0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 6) =
            temp_coord2 + temp_rand2;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s16 *, 0xA) =
            (s16)(M2C_FIELD(M2C_FIELD(arg0, void **, 8), u16 *, 0xA) -
                  0x100);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v0_2, s32 *, 0x10) = 0;
        M2C_FIELD(temp_v0_2, s32 *, 0xC) = 0;
        M2C_FIELD(M2C_FIELD(temp_v0, void **, 8), s32 *, 0x14) = 0x200000;
        func_8004491C(temp_v0, (void *)(temp_page + 0x5C34));
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x14) =
            (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) & 0xFFF3);
        temp_v1 = 0x1000 / (s32)(func_80167088(5) + 6);
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0xFF;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x20;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x20;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = (s16)temp_v1;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = (s16)temp_v1;
        M2C_FIELD(temp_v0, Copy12 *, 0x56) =
            M2C_FIELD(D_80173B34, Copy12 *, 0);
        M2C_FIELD(temp_s0, void **, 8) = (void *)(temp_v0 + 0x56);
    }
}

/* MECHANISM: Dropping the cross-call destination cache gives the retail 0x20 frame and s0/s1 hold set.
   Split signed coordinate live ranges plus zero-arg RNG calls reproduce both addiu/store-delay sequences.
   A fenced, a1-pinned 0x80040000 page splits D_80045C34; u8 0xFF and packed Copy12 close G0. */
