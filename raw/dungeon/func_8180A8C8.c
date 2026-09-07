#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct ResidentPage {
    u8 pad0[0x2094];
    u16 table[1];
} ResidentPage;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

void func_800260C8(void *arg0, s16 arg1) {
    s16 temp_a0;
    s32 temp_v0;
    s32 temp_v1_2;
    void *temp_a0_2;
    void *temp_a0_3;
    void *temp_a2;
    void *temp_v1;
    ResidentPage *temp_page;

    temp_a2 = arg0 + 0x20;
    temp_a0 = M2C_FIELD(temp_a2, s16 *, 0x26);
    if (temp_a0 != arg1) {
        temp_v1 = M2C_FIELD(arg0, void **, 0x20);
        if (temp_v1 != NULL) {
            M2C_FIELD(M2C_FIELD(((temp_a0 * 4) + temp_v1), void **, 0xC), s16 *, 0xB6) = 4;
            temp_page = (ResidentPage *)0x80010000;
            temp_v0 = M2C_FIELD(temp_a2, s16 *, 0x26);
            temp_a0_2 = M2C_FIELD(M2C_FIELD(((temp_v0 * 4) + M2C_FIELD(arg0, void **, 0x20)), void **, 0xC), void **, 0xC);
            temp_v1_2 = (temp_page->table[temp_v0] + 2) & 7;
            M2C_FIELD(temp_a0_2, s8 *, 0x24) = (s8) (D_8006CCD8[temp_v1_2] + 1);
            M2C_FIELD(temp_a0_2, s8 *, 0x25) = (s8) (D_8006CCE8[temp_v1_2] + 1);
        }
        M2C_FIELD(temp_a2, s16 *, 0x26) = arg1;
        temp_a0_3 = M2C_FIELD(arg0, void **, 0x20);
        if (temp_a0_3 != NULL) {
            M2C_FIELD(temp_a0_3, s16 *, 0x26) = arg1;
        }
    }
}
