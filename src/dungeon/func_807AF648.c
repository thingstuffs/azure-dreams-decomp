#include "modules/dungeon_ovl_7ce800.h"
#include "common.h"
#include "shared/game_work.h"

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

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);
extern s16 func_80069EF8(void);

typedef union {
    u32 word;
    struct { u8 r, g, b, code; } bytes;
} ParticleColor;
typedef union {
    u32 word;
    struct { u16 x, y; } halves;
} ParticlePoint;
typedef union {
    u32 word;
    struct { u8 address[3], length; } bytes;
} ParticleTag;
typedef struct {
    ParticleTag tag;
    ParticleColor color0;
    ParticlePoint point0;
    ParticleColor color1;
    ParticlePoint point1;
    ParticleColor color2;
    ParticlePoint point2;
    ParticleColor color3;
    ParticlePoint point3;
} ParticleQuad;

/* Advances particle levels and queues colored quads in the dungeon ordering table. */
s32 func_800F6E48(DungeonObject *object, u16 *origin) {
    DungeonRoot *dungeon = *(DungeonRoot **)((u8 *)(&gameWork));
    s32 packet_cursor = dungeon->cursor;
    GameWork *root_slot = &gameWork;
    Scratch *scratch;
    s16 particle_index = 0;
    u8 *projection_param = (u8 *)0x1F800090;
    u8 *projection_flags;

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)((u8 *)(&gameWork)) + 0xB0;
    scratch->values[0] = origin[1];
    projection_flags = (u8 *)scratch;
    scratch->values[1] = origin[3];
    projection_flags = (u8 *)((u32)projection_flags | 0x94);
    scratch->values[2] = origin[5];
    for (; particle_index < 32; particle_index++) {
        {
            DungeonObject *particle_view = (DungeonObject *)((u8 *)object + (s16)particle_index);
            particle_view->level += 4;
            if ((s8)particle_view->level >= 48) {
                if (object->active != 0) {
                    particle_view->level = 48;
                    continue;
                }
                particle_view->level = 0;
            }
        }
        {
            s32 particle_offset = particle_index;
            ((ParticleQuad *)packet_cursor)->color0.word = 0;
            ((ParticleQuad *)packet_cursor)->color1.word = 0;
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
                    intensity = intensity / (level - 32);
                } else if (level < 16) {
                    intensity = intensity / (16 - level);
                }
                ((ParticleQuad *)packet_cursor)->color2.bytes.r = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.r = ((ParticleQuad *)packet_cursor)->color2.bytes.r;
                ((ParticleQuad *)packet_cursor)->color2.bytes.g = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.g = ((ParticleQuad *)packet_cursor)->color2.bytes.g;
                ((ParticleQuad *)packet_cursor)->color2.bytes.b = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? intensity : 0;
                ((ParticleQuad *)packet_cursor)->color3.bytes.b = ((ParticleQuad *)packet_cursor)->color2.bytes.b;
            }

            scratch->length = func_80065420(&scratch->x70, (void *)(packet_cursor + 8),
                projection_param, projection_flags);
            ((ParticleQuad *)packet_cursor)->point1.word = ((ParticleQuad *)packet_cursor)->point0.word;
            ((ParticleQuad *)packet_cursor)->point1.halves.x += 4;
            scratch->length += func_80065420(&scratch->x78, (void *)(packet_cursor + 24),
                projection_param, projection_flags);
            ((ParticleQuad *)packet_cursor)->point3.word = ((ParticleQuad *)packet_cursor)->point2.word;
            ((ParticleQuad *)packet_cursor)->point3.halves.x += 2;
            scratch->length >>= 1;
            ((ParticleQuad *)packet_cursor)->tag.bytes.length = 8;
            ((ParticleQuad *)packet_cursor)->color0.bytes.code = 58;
            {
                func_8006658C((void *)(scratch->base + scratch->length * 4),
                    (void *)packet_cursor);
                packet_cursor += 36;
            }
            func_80067F20((void *)packet_cursor, 0, 0, 96, 0);
            func_8006658C((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            {
                u8 particle_count = object->count;
                packet_cursor += 12;
                object->count = particle_count + 1;
            }
        }
    }
    ((DungeonRoot *)root_slot->unk_000)->cursor = packet_cursor;
    return 0;
}
