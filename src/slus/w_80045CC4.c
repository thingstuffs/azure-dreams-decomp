#include "common.h"
#include "shared/game_work.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80045CC4_0_pre {
    s8 unk_00;
} S_80045CC4_0_pre;   /* the 0x1 bytes before poly in func_80045CC4, addressed as poly[-1] */

typedef struct S_80045CC4_0 {
    u8 pad_00[0x4];
    union { u16 u; s16 s; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    union { s16 s16; u8 u8; } unk_10;   /* accessed as both */
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    union { struct { s16 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; } unk_18;   /* overlapping accesses */
    u8 pad_1A[0x2];
    union { u16 u; s16 s; } unk_1C;   /* accessed as both */
    union { u16 u; s16 s; } unk_1E;   /* accessed as both */
    union {
        struct { s16 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_20;   /* overlapping accesses */
} S_80045CC4_0;   /* poly in func_80045CC4 */

typedef struct S_80045CC4_1_pre {
    u16 unk_00;
    u16 unk_02;
} S_80045CC4_1_pre;   /* the 0x4 bytes before data in func_80045CC4, addressed as data[-1] */

typedef struct S_80045CC4_2 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80045CC4_2;   /* arg2 in func_80045CC4 */


#define SP_S32(offset) (*(s32 *)(scratchpad + (offset)))
#define SP_U16(offset) (*(u16 *)(scratchpad + (offset)))
#define SP_S16(offset) (*(s16 *)(scratchpad + (offset)))
#define SP_S32_VOL(offset) (*(volatile s32 *)(scratchpad + (offset)))
#define SP_S16_VOL(offset) (*(volatile s16 *)(scratchpad + (offset)))

typedef struct {
    u8 pad00[2];
    s16 unk02;
    u8 pad04[2];
    s16 unk06;
    u8 pad08[2];
    s16 unk0A;
} S_80045CC4_Arg1;

typedef struct {
    u8 pad00[8];
    u8 *unk08;
    s32 unk0C;
    u16 unk10;
    u16 unk12;
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
} S_80045CC4_Arg2;


extern void PushMatrix(void);
extern void PopMatrix(void);
extern void RotMatrix(void *r, void *m);
extern void ReadRotMatrix(void *m);
extern void CompMatrix(void *m0, void *m1, void *m2);
extern void ScaleMatrix(void *m, void *v);
extern void SetTransMatrix(void *m);
extern void SetRotMatrix(void *m);
extern s32 RotAverage4(
    void *v0, void *v1, void *v2, void *v3,
    void *sxy0, void *sxy1, void *sxy2, void *sxy3,
    void *p, void *flag);

/* Transform sprite quads, clip them to the screen, and link visible packets into the ordering table. */
void func_80045CC4(void *context, s32 position, S_80045CC4_Arg2 *sprite, s16 depth_bias)
{
    void (*callback)(void *, s32, S_80045CC4_Arg2 *, u8 *);
    s32 x;
    s32 packet_addr;
    s32 matrix_yy;
    s32 matrix_xx;
    s32 *packet;
    s32 *quad;
    s32 depth;
    s32 visible_0;
    s32 visible_1;
    s32 any_visible;
    u32 addr_mask;
    s32 visible_3;
    u8 *entry;
    u8 *payload;
    u8 *scratchpad;
    void **global_slots;
    void *global_base;
    u8 uv_edge;
    s32 visible_2;
    s16 sx;
    s16 sy;
    s16 ex;
    s16 ey;

    global_slots = ((void * *)(&gameWork));
    global_base = global_slots[0];
    scratchpad = (u8 *)0x1F800000;
    SP_S32_VOL(0x20) = (s32)((u8 *)global_base + 0xB0);
    {
        s32 translation;
        translation = ((S_80045CC4_Arg1 *)position)->unk02;
        SP_S32_VOL(0xE4) = translation;
        translation = ((S_80045CC4_Arg1 *)position)->unk06;
        SP_S32_VOL(0xE8) = translation;
        translation = ((S_80045CC4_Arg1 *)position)->unk0A;
        SP_S16_VOL(0x8C) = 0;
        SP_S16_VOL(0x84) = 0;
        SP_S16_VOL(0x7C) = 0;
        SP_S16_VOL(0x74) = 0;
        SP_S32_VOL(0xEC) = translation;
    }
    packet = *(s32 **)((u8 *)global_base + 0x8D0);
    sprite->unk14 |= 0x8000;
    addr_mask = 0xFFFFFF;
    PushMatrix();

    SP_U16(0x108) = sprite->unk20;
    SP_U16(0x10A) = sprite->unk22;
    SP_S32(0x30) = sprite->unk1C * 2;
    SP_S32(0x34) = sprite->unk1E * 2;
    SP_S32(0x38) = 0x2000;
    SP_U16(0x100) = sprite->unk16;
    SP_U16(0x104) = sprite->unk1A;
    SP_U16(0x102) = sprite->unk18;

    RotMatrix((void *)0x1F800100, (void *)0x1F8000D0);
    ReadRotMatrix((void *)0x1F80011C);
    CompMatrix((void *)0x1F80011C, (void *)0x1F8000D0, (void *)0x1F800050);
    ScaleMatrix((void *)0x1F800050, (void *)0x1F800030);
    SetTransMatrix((void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);

    quad = packet + 1;
    entry = sprite->unk08;
    payload = entry + 8;
    SP_U16(0x24) = sprite->unk14;

next_entry:
    if (!(entry[0] & 0x20)) {
        u8 u_start;
        u8 width;
        u8 v_start;
        u8 height;

        u_start = payload[0];
        SP_S32(0x08) = u_start;
        width = payload[2];
        SP_S32(0x10) = width;
        if ((u_start + width >= 0x100) || sprite->unk1A != 0) {
            SP_S32(0x10) = width - 1;
        }

        v_start = payload[1];
        SP_S32(0x0C) = v_start;
        height = payload[3];
        SP_S32(0x14) = height;
        if ((v_start + height >= 0x100) || sprite->unk1A != 0) {
            SP_S32(0x14) = height - 1;
        }

        if ((entry[0] ^ SP_U16(0x24)) & 1) {
            sx = -((s8 *)payload)[-6] - SP_U16(0x108);
            SP_S16(0x80) = sx;
            SP_S16(0x70) = sx;
            ex = sx - SP_U16(0x10);
            SP_S16(0x88) = ex;
            SP_S16(0x78) = ex;
        } else {
            sx = ((s8 *)payload)[-6] - SP_U16(0x108);
            SP_S16(0x80) = sx;
            SP_S16(0x70) = sx;
            ex = sx + SP_U16(0x10);
            SP_S16(0x88) = ex;
            SP_S16(0x78) = ex;
        }

        if ((entry[0] ^ SP_U16(0x24)) & 2) {
            sy = -((s8 *)payload)[-5] - SP_U16(0x10A);
            SP_S16(0x7A) = sy;
            SP_S16(0x72) = sy;
            ey = sy - SP_U16(0x14);
            SP_S16(0x8A) = ey;
            SP_S16(0x82) = ey;
        } else {
            sy = ((s8 *)payload)[-5] - SP_U16(0x10A);
            SP_S16(0x7A) = sy;
            SP_S16(0x72) = sy;
            ey = sy + SP_U16(0x14);
            SP_S16(0x8A) = ey;
            SP_S16(0x82) = ey;
        }

        ASM_KEEP(scratchpad);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        depth = RotAverage4(
            scratchpad + 0x70, scratchpad + 0x78,
            scratchpad + 0x80, scratchpad + 0x88,
            packet + 2, packet + 4, packet + 6, packet + 8,
            scratchpad + 0x90, scratchpad + 0x94);
        depth = depth - depth_bias - 8;
        SP_S32(0xC0) = depth;

        if ((u32)depth < 0x1E0U) {
            visible_0 = 0;
            if ((u32)((((S_80045CC4_0 *)quad)->unk_04.u + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)quad)->unk_06.u + 0x20) & 0xFFFF;
                    visible_0 = clip_y < 0x121U;
                }
            }
            visible_1 = 0;
            if ((u32)((((S_80045CC4_0 *)quad)->unk_0C + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)quad)->unk_0E + 0x20) & 0xFFFF;
                    visible_1 = clip_y < 0x121U;
                }
            }
            visible_2 = 0;
            visible_0 |= visible_1;
            if ((u32)((((S_80045CC4_0 *)quad)->unk_14 + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)quad)->unk_16 + 0x20) & 0xFFFF;
                    visible_2 = clip_y < 0x121U;
                }
            }
            visible_3 = 0;
            any_visible = visible_0 | visible_2;
            if ((u32)((((S_80045CC4_0 *)quad)->unk_1C.u + 0x20) & 0xFFFF) < 0x181U) {
                {
                    u32 clip_y = (((S_80045CC4_0 *)quad)->unk_1E.u + 0x20) & 0xFFFF;
                    visible_3 = clip_y < 0x121U;
                }
            }

            if (any_visible | visible_3) {
                ((S_80045CC4_0_pre *)quad)[-1].unk_00 = 9;
                *(u16 *)&sprite->unk14 &= 0x7FFF;

                {
                    register s32 uv_end ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                    s32 uv_start;

                    uv_end = SP_S32(0x10);
                    uv_start = SP_S32(0x08);
                    visible_2 = SP_S32(0x0C);
                    uv_end += uv_start;
                    SP_S32(0x10) = uv_end;
                    uv_start = SP_S32(0x0C);
                    uv_end = SP_S32(0x14);
                    SP_S32(0x0C) = uv_start << 8;
                    uv_end = uv_end + visible_2;
                    SP_S32_VOL(0x14) = uv_end;
                    SP_S32(0x14) = uv_end << 8;
                }

                if (SP_U16(0x24) & 0x100) {
                    ((S_80045CC4_0 *)quad)->unk_0A = sprite->unk12;
                } else {
                    ((S_80045CC4_0 *)quad)->unk_0A = sprite->unk12 + ((S_80045CC4_1_pre *)payload)[-1].unk_02;
                }

                ((S_80045CC4_0 *)quad)->unk_08 = SP_U16(0x0C) + SP_U16(0x08);
                ((S_80045CC4_0 *)quad)->unk_10.s16 = SP_U16(0x0C) + SP_U16(0x10);
                {
                    u16 tpage;
                    visible_3 = sprite->unk10;
                    if (visible_3 != 0) {
                        tpage = visible_3 + (((S_80045CC4_1_pre *)payload)[-1].unk_00 & 0xFF9F);
                        ((S_80045CC4_0 *)quad)->unk_12 = tpage;
                        ((S_80045CC4_0 *)quad)->unk_18.at00.v = SP_U16(0x14) + SP_U16(0x08);
                        ((S_80045CC4_0 *)quad)->unk_20.at00.v = SP_U16(0x14) + SP_U16(0x10);
                        matrix_xx = SP_U16(0x50);
                    } else {
                        tpage = ((S_80045CC4_1_pre *)payload)[-1].unk_00;
                        ((S_80045CC4_0 *)quad)->unk_12 = tpage;
                        ((S_80045CC4_0 *)quad)->unk_18.at00.v = SP_U16(0x14) + SP_U16(0x08);
                        ((S_80045CC4_0 *)quad)->unk_20.at00.v = SP_U16(0x14) + SP_U16(0x10);
                        matrix_xx = SP_U16(0x50);
                    }
                }
                {
                    if (((matrix_xx << 16) >> 16) >= 0x1800) {
                        uv_edge = ((S_80045CC4_0 *)quad)->unk_20.at00u.v;
                        ((S_80045CC4_0 *)quad)->unk_20.at00u.v = uv_edge + 0xFF;
                        ((S_80045CC4_0 *)quad)->unk_10.u8 = uv_edge;
                        matrix_yy = SP_U16(0x58);
                    } else {
                        matrix_yy = SP_U16(0x58);
                    }
                }
                {
                    if (((matrix_yy << 16) >> 16) >= 0x1800) {
                        uv_edge = ((S_80045CC4_0 *)quad)->unk_20.at01.v;
                        ((S_80045CC4_0 *)quad)->unk_20.at01.v = uv_edge + 0xFF;
                        ((S_80045CC4_0 *)quad)->unk_18.at01.v = uv_edge;
                    }
                }
                if (((S_80045CC4_0 *)quad)->unk_04.s > ((S_80045CC4_0 *)quad)->unk_1C.s) {
                    ((S_80045CC4_0 *)quad)->unk_10.u8--;
                    ((S_80045CC4_0 *)quad)->unk_20.at00u.v--;
                }
                if (((S_80045CC4_0 *)quad)->unk_06.s > ((S_80045CC4_0 *)quad)->unk_1E.s) {
                    ((S_80045CC4_0 *)quad)->unk_18.at01.v--;
                    ((S_80045CC4_0 *)quad)->unk_20.at01.v--;
                }

                visible_2 = payload[-7];
                ((S_80045CC4_2 *)sprite)->unk_0F = visible_2;
                visible_3 = SP_U16(0x24);
                if (visible_3 & 8) {
                    if (visible_3 & 4) {
                        x = visible_2 | 2;
                        ((S_80045CC4_2 *)sprite)->unk_0F = x;
                    } else {
                        x = visible_2 & 0xFD;
                        ((S_80045CC4_2 *)sprite)->unk_0F = x;
                    }
                    visible_0 = 0xFF000000;
                    quad[0] = sprite->unk0C;
                    packet_addr = (u32)packet & addr_mask;
                } else {
                    visible_0 = 0xFF000000;
                    quad[0] = sprite->unk0C;
                    packet_addr = (u32)packet & addr_mask;
                }

                {
                    s32 *ot_bucket;

                    quad += 10;
                    *packet = (*packet & (u32)visible_0) |
                        (*(s32 *)(SP_S32(0xC0) * 4 + SP_S32(0x20)) & addr_mask);
                    ot_bucket = (s32 *)(SP_S32(0xC0) * 4 + SP_S32(0x20));
                    packet += 10;
                    *ot_bucket = (*ot_bucket & (u32)visible_0) | packet_addr;
                }
            }
        }
    } else {
        callback = *(void (**)(void *, s32, S_80045CC4_Arg2 *, u8 *))payload;
        if (callback != NULL) {
            callback(context, position, sprite, entry);
        }
    }

    payload += 0xC;
    if ((s8)entry[0] >= 0) {
        entry += 0xC;
        goto next_entry;
    }

    PopMatrix();
    *(s32 **)((u8 *)global_slots[0] + 0x8D0) = packet;
}
