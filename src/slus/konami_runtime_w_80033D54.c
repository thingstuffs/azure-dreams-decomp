#include "common.h"

#include "common.h"

extern void PushMatrix(void);
extern void PopMatrix(void);
extern void TransMatrix(void *, void *);
extern void RotMatrix(void *, void *);
extern void ScaleMatrix(void *, void *);
extern void CompMatrix(void *, void *, void *);
extern void SetRotMatrix(void *);
extern void SetTransMatrix(void *);
extern void RotTransPers4(void *, void *, void *, void *, void *, void *,
                          void *, void *, void *, void *);
extern void AddPrim(void *, void *);

extern u8 D_80080994[];
extern s32 D_8008099C;
extern u8 *D_80083160_init[3] asm("D_80083160");
extern u8 *D_80083160_tail[3] asm("D_80083160");

#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

#define SCR_S16(o) (*(s16 *)(scratch + (o)))
#define SCR_U16(o) (*(u16 *)(scratch + (o)))
#define SCR_S32(o) (*(s32 *)(scratch + (o)))

s32 func_80033D54(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *scratch;
    u8 *transform;
    u8 *context;
    u8 *object;
    u8 *source;
    u8 *vertex;
    u8 *primitive;
    u8 *global_init;
    u8 **state_p;
    u8 *next;
    void *matrix;
    void *translation;
    void *work_matrix;
    u8 *node;
    void (*callback)(void *);
    s32 first_u;
    s32 first_v;
    s32 coord_value;
    s32 sum_u;
    s32 sum_v;
    s32 shifted_v;
    s32 uv_value;
    s32 visible2;
    s32 clut_base;
    s32 clut_joined;
    u16 clut_value;
    s32 tpage_base;
    u16 tpage_value;
    u16 draw_flags;
    s32 guard;

    node = arg0;
    transform = arg1;
    context = arg2;

    guard = D_8008099C;
    ASM_KEEP_NV(guard);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    state_p = D_80083160_init;
    scratch = (u8 *)0x1F800000;
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (guard != 0) {
        return 0;
    }

    matrix = (void *)0x1F800054;
    translation = (void *)0x1F800044;
    work_matrix = (void *)0x1F8000C8;

    global_init = D_80083160_init[0];
    sum_u = S32_AT(global_init, 0x8D0);
    SCR_S32(0x24) = (u32)(global_init + 0x70);
    SCR_S32(0x3C) = 0x1000;
    SCR_S32(0x4C) = 0;
    SCR_S16(0x90) = 0;
    SCR_S16(0x88) = 0;
    SCR_S16(0x80) = 0;
    SCR_S16(0x78) = 0;
    SCR_S32(0x1C) = sum_u;
    PushMatrix();

outer_loop:
    object = PTR_AT(node, 0x0);
    callback = *(void (**)(void *))(node + 0x8);
    SCR_S32(0xC4) = S32_AT(object, 0x60);
    coord_value = U16_AT(context, 0x14);
    source = PTR_AT(context, 0x8);
    SCR_U16(0x28) = coord_value;
    SCR_S32(0x34) = S32_AT(object, 0x20);
    SCR_S32(0x38) = S32_AT(object, 0x24);
    SCR_S32(0x3C) = S32_AT(object, 0x28);

    if (PTR_AT(object, 0x4) == 0) {
        SCR_S32(0x44) = S16_AT(transform, 0x2);
        SCR_S32(0x48) = S16_AT(transform, 0x6);
        SCR_S32(0x4C) = S16_AT(transform, 0xA);
        TransMatrix(matrix, translation);
        RotMatrix(object + 0x8, matrix);
        ScaleMatrix(matrix, scratch + 0x34);

        S32_AT(object, 0x40) = SCR_S32(0x54);
        S32_AT(object, 0x44) = SCR_S32(0x58);
        S32_AT(object, 0x48) = SCR_S32(0x5C);
        S32_AT(object, 0x4C) = SCR_S32(0x60);
        S32_AT(object, 0x50) = SCR_S32(0x64);
        S32_AT(object, 0x54) = SCR_S32(0x68);
        S32_AT(object, 0x58) = SCR_S32(0x6C);
        S32_AT(object, 0x5C) = SCR_S32(0x70);

        SCR_S32(0x44) = S32_AT(object, 0x10);
        SCR_S32(0x48) = S32_AT(object, 0x14);
        SCR_S32(0x4C) = S32_AT(object, 0x18);
        TransMatrix(work_matrix, translation);
    } else {
        TransMatrix(matrix, object + 0x30);
        RotMatrix(object + 0x8, matrix);
        ScaleMatrix(matrix, scratch + 0x34);
        CompMatrix(PTR_AT(object, 0x4) + 0x40, matrix, matrix);

        S32_AT(object, 0x40) = SCR_S32(0x54);
        S32_AT(object, 0x44) = SCR_S32(0x58);
        S32_AT(object, 0x48) = SCR_S32(0x5C);
        S32_AT(object, 0x4C) = SCR_S32(0x60);
        S32_AT(object, 0x50) = SCR_S32(0x64);
        S32_AT(object, 0x54) = SCR_S32(0x68);
        S32_AT(object, 0x58) = SCR_S32(0x6C);
        S32_AT(object, 0x5C) = SCR_S32(0x70);

        SCR_S32(0x44) = S32_AT(object, 0x10);
        SCR_S32(0x48) = S32_AT(object, 0x14);
        SCR_S32(0x4C) = S32_AT(object, 0x18);
        TransMatrix(work_matrix, scratch + 0x44);
    }
    RotMatrix(D_80080994, work_matrix);
    CompMatrix(matrix, work_matrix, matrix);
    SetRotMatrix(matrix);
    ASM_USE_NV(work_matrix);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    SetTransMatrix(matrix);

    if (source != 0) {
        vertex = source + 1;
inner_loop:
        primitive = (u8 *)SCR_S32(0x1C);
        SCR_S32(0x1C) = (s32)(primitive + 0x28);

        coord_value = *(volatile u8 *)(vertex + 0x7);
        first_u = U8_AT(vertex, 0x7);
        first_v = U8_AT(vertex, 0x8);
        SCR_S32(0x0C) = coord_value;
        coord_value = U8_AT(vertex, 0x8);
        SCR_S32(0x10) = coord_value;
        SCR_S32(0x14) = U8_AT(vertex, 0x9);
        SCR_S32(0x18) = U8_AT(vertex, 0xA);
        if ((first_u + U8_AT(vertex, 0x9)) >= 0x100) {
            SCR_S32(0x14) -= 1;
        }
        if ((first_v + U8_AT(vertex, 0xA)) >= 0x100) {
            SCR_S32(0x18) -= 1;
        }

        if ((U8_AT(source, 0) ^ SCR_U16(0x28)) & 1) {
            coord_value = -((s32)(U8_AT(vertex, 1) << 24) >> 23);
            SCR_S16(0x84) = coord_value;
            SCR_S16(0x74) = coord_value;
            coord_value -= SCR_U16(0x14);
        } else {
            coord_value = (s32)(U8_AT(vertex, 1) << 24) >> 23;
            SCR_S16(0x84) = coord_value;
            SCR_S16(0x74) = coord_value;
            coord_value += SCR_U16(0x14);
        }
        SCR_S16(0x8C) = coord_value;
        SCR_S16(0x7C) = coord_value;

        if ((U8_AT(source, 0) ^ SCR_U16(0x28)) & 2) {
            coord_value = -((s32)(U8_AT(vertex, 2) << 24) >> 23);
            SCR_S16(0x7E) = coord_value;
            SCR_S16(0x76) = coord_value;
            coord_value -= SCR_U16(0x18);
        } else {
            coord_value = (s32)(U8_AT(vertex, 2) << 24) >> 23;
            SCR_S16(0x7E) = coord_value;
            SCR_S16(0x76) = coord_value;
            coord_value += SCR_U16(0x18);
        }
        do {
            SCR_S16(0x8E) = coord_value;
        } while (0);
        SCR_S16(0x86) = coord_value;

        RotTransPers4(scratch + 0x74, scratch + 0x7C,
                      scratch + 0x84, scratch + 0x8C,
                      scratch + 0x9C, scratch + 0xA4,
                      scratch + 0xAC, scratch + 0xB4,
                      scratch + 0x94, scratch + 0x98);

        visible2 = 0;
        if ((u16)(SCR_U16(0x9C) + 0x20) < 0x181U) {
            visible2 = (u16)(SCR_U16(0x9E) + 0x20) < 0x121U;
        }
        tpage_base = 0;
        if ((u16)(SCR_U16(0xA4) + 0x20) < 0x181U) {
            tpage_base = (u16)(SCR_U16(0xA6) + 0x20) < 0x121U;
        }
        clut_base = 0;
        visible2 |= tpage_base;
        if ((u16)(SCR_U16(0xAC) + 0x20) < 0x181U) {
            clut_base = (u16)(SCR_U16(0xAE) + 0x20) < 0x121U;
        }
        tpage_base = 0;
        clut_joined = visible2 | clut_base;
        if ((u16)(SCR_U16(0xB4) + 0x20) < 0x181U) {
            tpage_base = (u16)(SCR_U16(0xB6) + 0x20) < 0x121U;
        }

        if ((clut_joined | tpage_base) != 0) {
            S32_AT(primitive, 0x8) = SCR_S32(0x9C);
            S32_AT(primitive, 0x10) = SCR_S32(0xA4);
            S32_AT(primitive, 0x18) = SCR_S32(0xAC);
            S32_AT(primitive, 0x20) = SCR_S32(0xB4);
            U8_AT(primitive, 0x3) = 9;
            U16_AT(context, 0x14) &= 0x7FFF;

            sum_u = SCR_S32(0x14) + SCR_S32(0x0C);
            SCR_S32(0x14) = sum_u;
            if (sum_u & 0x100) {
                SCR_S32(0x14) = sum_u - 1;
            }
            sum_v = SCR_S32(0x18) + SCR_S32(0x10);
            SCR_S32(0x18) = sum_v;
            if (sum_v & 0x100) {
                SCR_S32(0x18) = sum_v - 1;
            }

            shifted_v = SCR_S32(0x18);
            uv_value = SCR_S32(0x10);
            shifted_v <<= 8;
            SCR_S32(0x18) = shifted_v;
            uv_value <<= 8;
            SCR_S32(0x10) = uv_value;
            clut_base = U16_AT(context, 0x12);
            uv_value += SCR_S32(0x0C);
            clut_value = clut_base;
            if (clut_base == 0) {
                clut_value = U16_AT(vertex, 0x5);
            }
            uv_value += (s32)clut_value << 16;
            S32_AT(primitive, 0xC) = uv_value;

            U16_AT(primitive, 0x14) = SCR_U16(0x10) + SCR_U16(0x14);
            tpage_base = U16_AT(context, 0x10);
            if (tpage_base != 0) {
                tpage_value = tpage_base + (U16_AT(vertex, 0x3) & 0xFF9F);
            } else {
                tpage_value = U16_AT(vertex, 0x3);
            }
            U16_AT(primitive, 0x16) = tpage_value;
            visible2 = S16_AT(primitive, 0x8);
            U16_AT(primitive, 0x1C) = SCR_U16(0x18) + SCR_U16(0x0C);
            sum_u = SCR_U16(0x18);
            clut_base = SCR_U16(0x14);
            coord_value = S16_AT(primitive, 0x20);
            sum_u += clut_base;
            U16_AT(primitive, 0x24) = sum_u;

            if (coord_value < visible2) {
                U8_AT(primitive, 0x14) -= 1;
                U8_AT(primitive, 0x24) -= 1;
            }
            if (S16_AT(primitive, 0xA) > S16_AT(primitive, 0x22)) {
                U8_AT(primitive, 0x1D) -= 1;
                U8_AT(primitive, 0x25) -= 1;
            }
            if (SCR_S32(0x34) >= 0x1800) {
                U8_AT(primitive, 0x14) -= 1;
                U8_AT(primitive, 0x24) -= 1;
            }
            if (SCR_S32(0x38) >= 0x1800) {
                U8_AT(primitive, 0x1D) -= 1;
                U8_AT(primitive, 0x25) -= 1;
            }

            clut_base = U8_AT(vertex, 0x0);
            U8_AT(context, 0xF) = clut_base;
            draw_flags = SCR_U16(0x28);
            if (draw_flags & 8) {
                if (draw_flags & 4) {
                    U8_AT(context, 0xF) = clut_base | 2;
                } else {
                    U8_AT(context, 0xF) = (u8)clut_base & 0xFD;
                }
            }
            if (SCR_U16(0x28) & 0x10) {
                U8_AT(context, 0xF) &= 0xFE;
            } else {
                U8_AT(context, 0xF) |= 1;
            }

            S32_AT(primitive, 0x4) = S32_AT(context, 0xC);
            AddPrim((u8 *)SCR_S32(0x24) + (SCR_S32(0xC4) * 4), primitive);
        } else {
            U16_AT(context, 0x14) |= 0x8000;
        }

        if (S8_AT(source, 0) >= 0) {
            source += 0xC;
            vertex += 0xC;
            if (source != 0) {
                goto inner_loop;
            }
        }
    }

    S32_AT(state_p[0], 0x8D0) = SCR_S32(0x1C);
    if (callback != 0) {
        callback(node);
    }
    ASM_USE_NV(callback);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    SCR_S32(0x1C) = S32_AT(state_p[0], 0x8D0);

    next = PTR_AT(node, -8);
    node = next + 0x20;
    if (next != 0) {
        transform = PTR_AT(next, 0x8);
        context = PTR_AT(next, 0xC);
        goto outer_loop;
    }

    PopMatrix();
    S32_AT(state_p[0], 0x8D0) = SCR_S32(0x1C);
    return 0;
}
