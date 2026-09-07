#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003E1C4();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern void *func_800B063C();

extern s32 D_80012090[];
extern s16 D_8008146C;
extern M2C_UNK D_800AFAD8;
extern M2C_UNK D_800AFBFC;
extern s8 D_800DCF4C;
extern M2C_UNK D_800DEF90;

void func_800B0544(s16 arg0) {
    s8 *state;
    s32 mode;
    void *temp_a0;
    void *temp_v1;
    void *temp_v1_2;
    void *obj;

    state = &D_800DCF4C;
    if (*state != arg0) {
        func_8003E1C4(arg0);
        *state = (s8)arg0;
    }
    obj = func_8003FC64(0x12);
    if (obj != NULL) {
        M2C_FIELD(obj, M2C_UNK **, 0x10) = &D_800AFAD8;
        func_8004491C(obj, &D_800AFBFC);
        M2C_FIELD(M2C_FIELD(obj, void **, 0xC), M2C_UNK **, 8) = &D_800DEF90;
        temp_v1 = M2C_FIELD(obj, void **, 0xC);
        M2C_FIELD(temp_v1, u8 *, 0xE) = 0xE0;
        M2C_FIELD(temp_v1, u8 *, 0xD) = 0xE0;
        M2C_FIELD(temp_v1, u8 *, 0xC) = 0xE0;
        temp_v1_2 = M2C_FIELD(obj, void **, 0xC);
        M2C_FIELD(temp_v1_2, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_v1_2, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(M2C_FIELD(obj, void **, 8), s16 *, 2) = 0;
        M2C_FIELD(M2C_FIELD(obj, void **, 8), s16 *, 6) = 0;
        M2C_FIELD(M2C_FIELD(obj, void **, 8), s16 *, 0xA) = 0x4000;
        mode = *(s32 *)0x80012090;
        temp_a0 = obj + 0x20;
        if (mode == 0) {
            if (D_8008146C == 0x28) {
                M2C_FIELD(temp_a0, s16 *, 2) = 1;
                func_800B063C(temp_a0);
            }
        } else if (mode == 2) {
            M2C_FIELD(temp_a0, s16 *, 2) = (s16)mode;
        }
    }
}

/* MECHANISM: A void CFG plus split object/mode live ranges removes seven return-merge words.
   Unsigned byte fields preserve li 0xE0; the raw mode read gives maspsx base==dest v1.
   The held state page in s1 and object in s0 produce the exact 0x20 frame/save contract. */
