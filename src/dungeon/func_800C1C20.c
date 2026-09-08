#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    u16 z;
} DungeonCoord;

typedef struct {
    u8 pad0[8];
    void *image;
    s32 color;
    s16 width;
    s16 pad12;
    s16 blend;
    u16 blend2;
    s16 shade;
    s16 pad1A;
    s16 size;
    s16 limit;
    u16 flags;
    u16 depth;
} DungeonRender;

typedef struct {
    void *parent;
    u8 pad4[9];
    s8 angle;
    u8 pad14[2];
    s16 mode;
    s16 value;
    u8 pad20[4];
    s16 height;
    s16 frame;
    s16 speed;
    s16 limit;
} DungeonState;

typedef struct {
    s32 arg1;
    u16 arg3_low;
    s32 arg3;
    s32 arg4;
} DungeonHomes;

typedef struct {
    u8 pad0[8];
    DungeonCoord *coord;
    DungeonRender *render;
    void *callback;
    u8 pad20[12];
    DungeonState state;
} DungeonObject;

extern void func_8003DB6C(void *, void *, s32);
extern DungeonObject *func_8003FD64(s32, void *);
extern void func_8004491C(DungeonObject *, void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u8 D_80045C34[];
extern u8 D_800777E8[];
extern u8 D_80083498[];
extern u8 D_800BB0A8[];
extern u8 D_800BB14C[];
extern u8 D_800D0774[];
extern u8 D_800DF3B4[];

DungeonObject *func_800C7380(s16 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4) {
    DungeonHomes homes;
    s32 color;
    DungeonObject *temp_s4;
    DungeonObject *temp_v0;
    DungeonState *var_s2;
    register DungeonCoord *temp_s3 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    DungeonCoord *temp_s0;
    DungeonRender *temp_a2;
    void *temp_a0;
    s16 var_s7;
    s32 var_fp;
    s32 var_s6;
    register u16 held_arg2 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u32 temp_t0 ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    held_arg2 = arg2;
    ASM_KEEP_NV(held_arg2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    homes.arg1 = arg1;
    temp_t0 = arg4;
    homes.arg4 = (s32) temp_t0;
    homes.arg3 = arg3;
    temp_s4 = func_8003FD64(0x12, D_80083498);
    temp_t0 = (u16) homes.arg3;
    homes.arg3_low = (u16) temp_t0;
    if (temp_s4 != NULL) {
        s16 var_s5;
        u16 limit_v0;
        temp_s4->callback = D_800BB0A8;
        func_8004491C(temp_s4, D_80045C34);
        color = 0x404040;
        var_s2 = &temp_s4->state;
        var_fp = 0xB;
        var_s7 = -0xAA7;
        temp_s3 = temp_s4->coord;
        temp_s3->x = (s16) (((s32) (arg0 << 0x10) >> 0xA) + 0x20);
        var_s6 = 0xEA7;
        temp_t0 = homes.arg1;
        temp_s3->z = held_arg2;
        temp_s3->y = (s16) (((s32) (temp_t0 << 0x10) >> 0xA) + 0x20);
        ASM_USE(temp_t0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        temp_a2 = temp_s4->render;
        temp_a2->image = D_800777E8;
        temp_a2->limit = 0x1800;
        temp_a2->size = 0x1800;
        temp_a2->width = 0x20;
        temp_a2->depth = 0xFFFB;
        temp_a2->color = color;
        temp_a2->flags = 0xFFFF;
        temp_a2->blend = (s16) (temp_a2->blend | 0xC);
        var_s5 = 0x37;
        var_s2->mode = arg0;
        temp_t0 = (u16) homes.arg1;
        ASM_USE(temp_t0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        limit_v0 = 0x14;
        ASM_USE(limit_v0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        var_s2->value = (u16) temp_t0;
        temp_t0 = (u16) homes.arg3;
        var_s2->limit = limit_v0;
        var_s2->height = (u16) temp_t0;
        temp_t0 = (u16) homes.arg4;
        var_s2->speed = (u16) temp_t0;
        do {
            temp_v0 = func_8003FD64(0x12, temp_s4);
            if (temp_v0 != NULL) {
                register DungeonObject *call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                register void *call_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                call_a0 = temp_v0;
                call_a1 = D_800D0774;
                temp_t0 = (u32) D_800BB14C;
                ASM_KEEP(temp_t0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                temp_v0->callback = (void *) temp_t0;
                func_8004491C(call_a0, call_a1);
                temp_s0 = temp_v0->coord;
                temp_s0->x = (s16) (temp_s3->x + (func_80064584(var_s6) >> 7));
                temp_s0->y = (s16) (temp_s3->y + (func_800644B8(var_s6) >> 7));
                temp_s0->z = temp_s3->z;
                temp_a2 = temp_v0->render;
                temp_a2->blend2 = 0xFC00;
                temp_a2->shade = var_s7;
                temp_a2->size = 0x410;
                if (var_s2->height < 0) {
                    temp_a2->width = 0x40;
                }
                var_s2 = &temp_v0->state;
                temp_a0 = (void *) ((u8 *) temp_v0 + 0x24);
                temp_t0 = homes.arg3_low;
                var_s2->height = (u16) temp_t0;
                temp_a2->image = temp_a0;
                func_8003DB6C(temp_a0, D_800DF3B4, 3);
                var_s2->angle = (s8) (var_s5 & 0xBF);
                var_s2->frame = var_s5;
                var_s2->parent = temp_s4;
            }
            var_s7 += 0x155;
            var_s6 -= 0x155;
            var_fp -= 1;
            var_s5 -= 5;
        } while (var_fp > 0);
    }
    return temp_s4;
}
