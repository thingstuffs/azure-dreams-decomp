#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s16 active;
    u8 pad4A[2];
    u16 timer;
} DungeonState;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 height;
} DungeonOrigin;

typedef struct {
    u8 pad0[0x10];
    u8 red;
    u8 green;
    u8 blue;
} FadeColor;

typedef struct {
    void *ptr;
    u8 pad[8];
} DungeonPage;

extern u16 D_80027330;
extern u8 D_80027334[];
extern FadeColor D_80027398;
extern u16 D_8002745C[];
extern void *D_8002732C;
extern u8 D_800273BE;
extern s32 D_800273C0;
extern DungeonPage D_800E3D7C;
extern s32 D_800814A0;

extern void func_80024C08(void) __attribute__((noreturn));
extern void func_8002592C(s16, s16, s16, s16, s32);
extern void func_80026BA8(s32, s32, DungeonOrigin *);
extern void func_800419EC(s32, s32);
extern s32 func_80069EF8(void);
extern s16 func_800A07D0(s32, s32, s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8009B4B0();

void func_8195F0BC(DungeonState *state, DungeonOrigin *origin) {
    register FadeColor *var_a1 ASM_REG("$5");
    register s32 var_s1 ASM_REG("$17");
    register s32 var_s3 ASM_REG("$19");
    register s32 temp_s4 ASM_REG("$20");
    register s32 temp_s5 ASM_REG("$21");
    s32 var_s1_2;
    register s32 var_s2_2 ASM_REG("$18");
    register s32 var_v0 ASM_REG("$2");
    register u16 *var_s2 ASM_REG("$18");
    register u16 *var_s6 ASM_REG("$22");
    register void *temp_v0 ASM_REG("$16");
    s32 temp_a3;
    u16 timer;
    register s32 arg_x ASM_REG("$5");
    register s32 arg_y ASM_REG("$6");
    register void *page ASM_REG("$4");
    u8 *row;
    register u8 cell ASM_REG("$3");
    register s32 hard_zero ASM_REG("$0");

#ifdef NON_MATCHING
    hard_zero = 0;
#endif

    D_80027330++;
    if (state->active == 0) {
        var_a1 = (FadeColor *)0x80020000;
        if (!(state->timer & 3)) {
            func_800419EC(8, 16);
            var_a1 = (FadeColor *)0x80020000;
        }
        var_a1 = (FadeColor *)((u8 *)var_a1 + 0x7398);
        var_a1->red += (0xF0 - var_a1->red) / (s16)state->timer;
        var_a1->green += (0x40 - var_a1->green) / (s16)state->timer;
        var_a1->blue += (0x20 - var_a1->blue) / (s16)state->timer;

        var_s3 = 1;
        var_v0 = (s32)D_8002745C;
        var_s6 = (u16 *)var_v0 + 8;
        do {
            var_s1 = 1;
            var_s2 = var_s6 + 1;
            var_v0 = (u16)origin->y >> 6;
            var_v0 -= 3;
            temp_s5 = var_v0 + var_s3;
            do {
                var_v0 = (u16)origin->x >> 6;
                var_v0 -= 3;
                temp_s4 = var_v0 + var_s1;
                var_v0 = func_80069EF8();
                arg_x = temp_s4 & 0xFFFF;
                ASM_KEEP(arg_x);
                arg_y = temp_s5 & 0xFFFF;
                ASM_KEEP(arg_y);
                row = D_80027334 + (var_s3 << 3);
                row += var_s1;
                ASM_KEEP_DEP_NV(var_v0, row);
                page = (void *)0x800e0000;
                ASM_KEEP(page);
                var_v0 &= 7;
                ASM_KEEP(var_v0);
                cell = *row;
                ASM_MEM_BARRIER();
                page = *(void **)((u8 *)page + 0x3D7C);
                ASM_KEEP_NV(cell);
                temp_a3 = *var_s2;
                ASM_KEEP(temp_a3);
                temp_a3 += (s8)cell - var_v0;
                *var_s2 = temp_a3;
                temp_v0 = func_8009B4B0(page, arg_x, arg_y, temp_a3);
                if (temp_v0 != 0 && temp_v0 != D_8002732C) {
                    *(u16 *)(*(u8 **)((u8 *)temp_v0 - 0x18) + 0xA) =
                        *var_s2 + origin->height;
                }
                if (!(func_80069EF8() & 7)) {
                    func_8002592C((s16)(temp_s4 << 6), (s16)(temp_s5 << 6),
                                   *(s16 *)var_s2, (s16)var_s1,
                                   (s16)var_s3);
                }
                var_s1++;
                var_s2++;
            } while (var_s1 < 7);
            var_s3++;
            var_s6 += 8;
        } while (var_s3 < 7);

        timer = state->timer - 1;
        state->timer = timer;
        var_s3 = 0;
        if ((timer << 16) <= 0) {
            temp_s5 = (s32)0x800e0000;
            ASM_KEEP(temp_s5);
            var_s1 = hard_zero;
            ASM_KEEP(var_s1);
            do {
                temp_s4 = var_s3 << 16;
                var_s2_2 = var_s1;
                do {
                    var_v0 = var_s1 - 3;
                    arg_x = (u16)origin->x;
                    page = *(void **)((u8 *)temp_s5 + 0x3D7C);
                    ASM_KEEP_DEP_NV(page, arg_x);
                    arg_y = (u16)origin->y;
                    arg_x = (((u32)arg_x >> 6) + var_v0) & 0xFFFF;
                    arg_y >>= 6;
                    var_v0 = var_s3 - 3;
                    ASM_KEEP(var_v0);
                    arg_y += var_v0;
                    arg_y &= 0xFFFF;
                    temp_v0 = func_8009B4B0(page, arg_x, arg_y);
                    if (temp_v0 != 0 && temp_v0 != D_8002732C) {
                        func_8009CE1C(
                            temp_v0, 16, D_800273BE, 9,
                            (s16)func_800A07D0(var_s2_2 >> 16,
                                               temp_s4 >> 16, 3, 3),
                            D_800273C0, 2);
                        *(s32 *)((u8 *)temp_v0 + 0x14) &= 0xFFEFFFFF;
                    }
                    func_80026BA8(var_s2_2 >> 16, temp_s4 >> 16, origin);
                    var_s2_2 += 0x10000;
                    var_s1++;
                } while (var_s1 < 7);
                var_s3++;
                var_s1 = 0;
            } while (var_s3 < 7);
            state->timer = 8;
            state->active++;
            func_80024C08();
        }
    } else {
        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
