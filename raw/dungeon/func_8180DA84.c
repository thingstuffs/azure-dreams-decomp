#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_80026ED0();
extern s32 func_80027368();
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];

void *func_80026A84(void *arg0, void *arg1, s32 arg2, void *arg3)
{
    u16 position[3];
    s32 *callback;
    TableEntry *var_s2;
    s32 var_s1;
    s32 var_t0;
    u16 temp_v0_2;
    u16 temp_v1;
    register void *temp_a0 ASM_REG("$4");
    void *temp_a2;
    void *temp_a3;
    void *temp_v0;
    register void *var_a1 ASM_REG("$5");
    void *var_s4;

    var_s4 = NULL;
    position[0] = position[1] = 0;
    if (func_8003DE58(FIELD(arg3, s32, 8), arg3, position, 0) == 0) {
        position[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    var_s1 = 0;
    do { var_s2 = D_80028820; } while (0);
    do {
        temp_v0 = func_8003FD64(0x12, D_80083498);
        if (temp_v0 != NULL) {
            FIELD(temp_v0, s32 *, 0x10) = callback;
            func_8004491C(temp_v0, D_800CEEFC);
            temp_a2 = FIELD(temp_v0, void *, 8);
            temp_v0_2 = FIELD(arg0, u16, 2) + position[0];
            FIELD(temp_a2, u16, 2) = temp_v0_2;
            FIELD(temp_a2, u16, 0xE) = temp_v0_2;
            var_t0 = 0;
            temp_v1 = FIELD(arg0, u16, 6) + position[1];
            FIELD(temp_a2, u16, 6) = temp_v1;
            FIELD(temp_a2, u16, 0x12) = temp_v1;
            temp_a3 = temp_v0 + 0x20;
            temp_v0_2 = FIELD(arg0, u16, 0xA) + position[2];
            FIELD(temp_a2, u16, 0xA) = temp_v0_2;
            FIELD(temp_a2, u16, 0x16) = temp_v0_2;
            temp_a0 = FIELD(temp_v0, void *, 0xC);
            var_a1 = temp_a3;
            FIELD(temp_a0, s16, 0x1E) = 0x1000;
            FIELD(temp_a0, s16, 0x1C) = 0x1000;
            FIELD(temp_a0, TableEntry *, 8) = var_s2;
            FIELD(temp_a0, u16, 0x14) = FIELD(temp_a0, u16, 0x14) | 0xC;
            FIELD(temp_v0, void *, 0x20) = arg1;
            FIELD(temp_a3, s32, 4) = arg2;
            FIELD(temp_a3, s16, 0x66) = 0x20;
            FIELD(temp_a3, s16, 0x6E) = var_s1;
            do {
                FIELD(var_a1, u16, 0x24) = FIELD(temp_a2, u16, 2);
                FIELD(var_a1, u16, 0x26) = FIELD(temp_a2, u16, 6);
                var_t0 += 1;
                FIELD(var_a1, u16, 0x28) = FIELD(temp_a2, u16, 0xA);
                var_a1 += 8;
            } while (var_t0 < 8);
            FIELD(temp_a3, void *, 8) = var_s4;
            var_s4 = temp_v0;
        }
        var_s1 += 1;
        var_s2 += 1;
    } while (var_s1 < 6);
    func_80026ED0((s16)(FIELD(arg0, u16, 2) + position[0]),
                  (s16)(FIELD(arg0, u16, 6) + position[1]),
                  (s16)(FIELD(arg0, u16, 0xA) + position[2]), 0x800);
    func_80027368(FIELD(arg1, s16, 2), FIELD(arg1, s16, 6),
                  FIELD(arg1, s16, 0xA), arg2);
    return temp_v0;
}
