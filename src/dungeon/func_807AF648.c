#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct DungeonRoot DungeonRoot;
struct DungeonRoot {
    u8 pad[0x8D0];
    s32 cursor;
};

typedef struct DungeonObject DungeonObject;
struct DungeonObject {
    void *state;
    u8 pad04[0x08];
    s16 coord;
    u8 active;
    u8 count;
    s8 level;
};

typedef struct Scratch Scratch;

typedef struct S_807AF648_0_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_807AF648_0_pre;   /* the 0x4 bytes before dst in func_807AF648, addressed as dst[-1] */

typedef struct S_807AF648_0 {
    s8 unk_00;
    u8 pad_01[0xC];
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    u8 pad_10[0x5];
    s8 unk_15;
    s8 unk_16;
    s8 unk_17;
} S_807AF648_0;   /* dst in func_807AF648 */

typedef struct S_807AF648_1 {
    u8 pad_00[0x8D0];
    s32 unk_8D0;
} S_807AF648_1;   /* *(DungeonRoot **)global_field in func_807AF648 */

struct Scratch {
    u16 values[3];
    u8 pad06[0x1A];
    u8 *base;
    u8 pad24[0x4C];
    u16 x70;
    u16 y72;
    u16 z74;
    u8 pad76[2];
    u16 x78;
    u16 y7A;
    u16 z7C;
    u8 pad7E[0x42];
    s32 length;
};

extern u8 D_80083160[];

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s16 func_80069EF8(void);
extern void func_800F6FE0(void) __attribute__((noreturn));
extern void func_800F7148(void) __attribute__((noreturn));

/* Advances particle levels and queues colored quads in the dungeon ordering table. */
s32 func_807AF648(DungeonObject *object, u16 *origin) {
    DungeonRoot *dungeon = *(DungeonRoot **)D_80083160;
    s32 packet_cursor = dungeon->cursor;
    void *root_slot = (void *)D_80083160;
    Scratch *scratch;
    s16 particle_index = 0;
    u8 *projection_param = (u8 *)0x1F800090;
    u8 *projection_flags;
    void *quad_fields;

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)D_80083160 + 0xB0;
    scratch->values[0] = origin[1];
    projection_flags = (u8 *)scratch;
    scratch->values[1] = origin[3];
    projection_flags = (u8 *)((u32)projection_flags | 0x94);
    scratch->values[2] = origin[5];
    quad_fields = (void *)(packet_cursor + 7);
    do {
        {
            DungeonObject *particle_view = (DungeonObject *)((u8 *)object + (s16)particle_index);
            particle_view->level += 4;
            if ((s8)particle_view->level >= 48) {
                if (object->active != 0) {
                    particle_view->level = 48;
                    func_800F7148();
                }
                particle_view->level = 0;
                {
                    register u32 reset_index ASM_REG("$16") =
                        (u32)(u16)particle_index << 16;
                    ASM_KEEP(reset_index);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                }
            }
        }
        {
            s32 particle_offset = particle_index;
            (*(s32 *)((u8 *)quad_fields + -3)) = 0;
            (*(s32 *)((u8 *)quad_fields + 5)) = 0;
            scratch->x70 = scratch->values[0] +
                ((func_80064584((particle_offset + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->x78 = scratch->x70;
            scratch->y72 = scratch->values[1] +
                ((func_800644B8((particle_offset + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->y7A = scratch->y72;
            scratch->z74 = scratch->values[2] -
                *(s8 *)((u8 *)object + particle_offset + 0x10) * 2;
            scratch->z7C = scratch->z74 + 64;

            {
                s16 intensity = func_80069EF8();
                s8 level = *(s8 *)((u8 *)object + particle_offset + 0x10);
                if (level >= 33) {
                    s32 saved_intensity = intensity;
                    register s32 fade_level ASM_REG("$2") = level - 32;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    ASM_KEEP(saved_intensity);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    ASM_TAILSLOT_PIN(fade_level);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    func_800F6FE0();
                }
                if (level < 16) {
                    intensity = intensity / (16 - level);
                }
                ((S_807AF648_0 *)quad_fields)->unk_0D = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? intensity : 0;
                ((S_807AF648_0 *)quad_fields)->unk_15 = ((S_807AF648_0 *)quad_fields)->unk_0D;
                ((S_807AF648_0 *)quad_fields)->unk_0E = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? intensity : 0;
                ((S_807AF648_0 *)quad_fields)->unk_16 = ((S_807AF648_0 *)quad_fields)->unk_0E;
                ((S_807AF648_0 *)quad_fields)->unk_0F = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? intensity : 0;
                ((S_807AF648_0 *)quad_fields)->unk_17 = ((S_807AF648_0 *)quad_fields)->unk_0F;
            }

            scratch->length = func_80065420(&scratch->x70, (void *)(packet_cursor + 8),
                projection_param, projection_flags);
            (*(s32 *)((u8 *)quad_fields + 9)) = (*(s32 *)((u8 *)quad_fields + 1));
            (*(u16 *)((u8 *)quad_fields + 9)) += 4;
            scratch->length += func_80065420(&scratch->x78, (void *)(packet_cursor + 24),
                projection_param, projection_flags);
            (*(s32 *)((u8 *)quad_fields + 25)) = (*(s32 *)((u8 *)quad_fields + 17));
            (*(u16 *)((u8 *)quad_fields + 25)) += 2;
            scratch->length >>= 1;
            ((S_807AF648_0_pre *)quad_fields)[-1].unk_00 = 8;
            ((S_807AF648_0 *)quad_fields)->unk_00 = 58;
            quad_fields = (void *)((s8 *)quad_fields + 36);
            ASM_KEEP_NV(quad_fields);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            quad_fields = (void *)((s8 *)quad_fields + 12);
            {
                void *quad_packet = (void *)packet_cursor;
                packet_cursor += 36;
                func_8006658C((void *)(scratch->base + scratch->length * 4),
                    quad_packet);
            }
            func_80067F20((void *)packet_cursor, 0, 0, 96, 0);
            func_8006658C((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            {
                u8 particle_count = object->count;
                packet_cursor += 12;
                object->count = particle_count + 1;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            }
            {
                s16 next_particle = particle_index + 1;
                particle_index = next_particle;
                if (next_particle >= 32) {
                    break;
                }
            }
        }
    } while (1);
    ((S_807AF648_1 *)(*(DungeonRoot **)root_slot))->unk_8D0 = packet_cursor;
    return 0;
}
