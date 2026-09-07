#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u32 value;
} __attribute__((packed)) PackedWord;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_800A56E0(s32);
extern s32 func_800A7A38(void *, s32);
extern void func_800A7A7C(s32, s32, s32, void *, void *);
extern void func_800BC26C(void *, s32, s32, s32);

extern u8 D_80045340[];
extern u8 D_8006E240[9];
extern u8 D_800B80D8[];

void *func_800B8228(u32 arg0, u32 arg1, s32 arg2, void *arg3) {
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 == NULL)
        goto failure;

    {
        func_8004491C(temp_v0, D_80045340);
        FIELD(temp_v0, void *, 0x10) = D_800B80D8;
        temp_v1 = FIELD(temp_v0, void *, 8);
        FIELD(temp_v1, u16, 2) = arg0;
        FIELD(temp_v1, u16, 6) = arg1;
        FIELD(temp_v1, s16, 0xA) = arg2;
        FIELD(temp_v1, s16, 0x16) = -0x12;
        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, s32, 0xC) = 0x808080;
        FIELD(temp_s0, s16, 0x1E) = 0xC90;
        FIELD(temp_s0, s16, 0x1C) = 0xC90;
        FIELD(temp_s0, s32, 8) = func_800A7A38(arg3,
                                               FIELD(temp_s0, s32, 0xC));
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v1_2, s16, 0xB0) = arg0 >> 6;
        FIELD(temp_v1_2, s16, 0xB2) = arg1 >> 6;
        *(PackedWord *)((u8 *)temp_v0 + 0xB8) = *(PackedWord *)arg3;
        func_800BC26C(temp_v0, 0, 0, 0);
        func_800A56E0(0x51C);
    }

    goto done;

failure:
    func_800A7A7C((s32)(arg0 << 0xA) >> 0x10,
                  (s32)(arg1 << 0xA) >> 0x10,
                  (s32)(arg2 << 0x10) >> 0x10,
                  D_8006E240, arg3);

done:
    return temp_v0;
}
