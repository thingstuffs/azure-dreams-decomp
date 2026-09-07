#include "common.h"

typedef struct {
    char pad0[0x8D0];
    u8 *field_8D0;
} Ctx;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} S_Rect;

typedef struct {
    char pad0[0xB8];
    s16 x;
    s16 y;
    char pad_BC[4];
    u32 index;
} S_Arg1;

typedef struct {
    u16 x;
    s16 y;
    u16 w;
    u16 h;
} S_Stack;

extern u8 D_80080000[];
extern u8 D_801C9E40[16];
extern void func_80066890(u8 *dst, S_Stack *rect, s32 x, s32 y);
extern void func_8006658C(void *addr, u8 *cursor);

void func_800C96E8(S_Rect *arg0, S_Arg1 *arg1) {
    S_Stack stack;
    s16 temp_a0, temp_a2, temp_t1, temp_v1_2;
    s32 temp_a1, temp_t2, temp_v1, var_a3;
    u8 *temp_a1_2;
    u8 *var_s0;
    Ctx **temp_s3;

    temp_s3 = (Ctx **)((u8 *)&D_80080000 + 0x3160);
    var_s0 = (*(Ctx **)((u8 *)&D_80080000 + 0x3160))->field_8D0;
    temp_t2 = *(Ctx **)((u8 *)&D_80080000 + 0x3160) != (Ctx *)D_801C9E40;
    if (arg1->index < 480) {
        temp_t1 = arg1->x;
        temp_a0 = arg1->y;
        temp_v1 = temp_t1 + arg0->w;
        temp_a1 = temp_a0 + arg0->h;
        if (temp_v1 >= 0) {
            temp_a2 = arg0->x;
            if (((temp_v1 + temp_a2) < 320) && (temp_a1 >= 0)) {
                temp_v1_2 = arg0->y;
                if (((temp_a1 + temp_v1_2) < 224) && (temp_t1 >= 0) && ((temp_t1 + temp_a2) < 320) && (temp_a0 >= 0) && ((temp_a0 + temp_v1_2) < 224)) {
                    stack.x = arg1->x;
                    var_a3 = arg1->y;
                    if ((s16)temp_t2) {
                        var_a3 += 224;
                    }
                    stack.y = var_a3;
                    stack.w = arg0->x;
                    stack.h = arg0->y;
                    func_80066890(var_s0, &stack, temp_t1 + arg0->w, (s16)var_a3 + arg0->h);
                    temp_a1_2 = var_s0;
                    var_s0 += 24;
                    func_8006658C((u8 *)(*(Ctx **)((u8 *)&D_80080000 + 0x3160)) + ((arg1->index * 4) + 0xB0), temp_a1_2);
                }
            }
        }
    }
    (*temp_s3)->field_8D0 = var_s0;
}
