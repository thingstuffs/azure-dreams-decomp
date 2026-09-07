#include "common.h"

typedef struct S_8002470C_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002470C_0;   /* dst in func_8002470C */

typedef struct S_8002470C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8002470C_1;   /* sprite in func_8002470C */

typedef struct S_8002470C_2 {
    u8 pad_00[0x30];
    s16 unk_30;
    u8 pad_32[0x4];
    s16 unk_36;
} S_8002470C_2;   /* extra in func_8002470C */


typedef struct {
    u8 pad0[8];
    void *dst;
    void *sprite;
    void (*callback)(void);
} Object;

extern Object *func_8003FC64(s32);
extern void func_8004491C(Object *, void *);
extern s32 rand(void);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_800245F8(void);
extern u8 D_80045340[];
extern u8 D_80026AB0[];


void *func_8002470C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 count)
{
    Object *obj = 0;
    s16 base_angle = (s16)arg3;
    s32 iterations = count;

    while (iterations > 0) {
        obj = func_8003FC64(0x202);
        if (obj != 0) {
            s32 angle;
            s32 final_angle;
            S_8002470C_0 *dst;
            S_8002470C_1 *sprite;
            u8 *extra;

            obj->callback = func_800245F8;
            func_8004491C(obj, D_80045340);
            dst = obj->dst;
            dst->unk_02 = (s16)arg0;
            dst->unk_06 = (s16)arg1;
            dst->unk_0A = (s16)(arg2 + 0x10);

            angle = (s16)((rand() & 0x7FF) - 0x400);
            angle -= 0x800;
            final_angle = base_angle + angle;
            dst->unk_0C = func_80064584(final_angle) << 6;
            dst->unk_10 = func_800644B8(final_angle) << 6;
            dst->unk_14 =
                (rand() & 0x1FFFF) - 0x10000;

            sprite = obj->sprite;
            sprite->unk_1E = 0x1000;
            sprite->unk_1C = 0x1000;
            sprite->unk_0C = 0x808080;
            func_8003DB94(sprite, D_80026AB0, rand() & 7);

            extra = (u8 *)obj + 0x20;
            ((S_8002470C_2 *)extra)->unk_30 = (s16)((rand() & 7) + 0x10);
            ((S_8002470C_2 *)extra)->unk_36 = (s16)arg3;
        }
        iterations--;
    }
    return obj;
}
