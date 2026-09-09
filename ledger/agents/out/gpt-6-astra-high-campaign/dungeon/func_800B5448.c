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
    u8 pad04[0x0A];
    s16 coord;
    u8 active;
    u8 count;
    s8 level;
};

typedef struct Scratch Scratch;

typedef struct S_800BABA8_0_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800BABA8_0_pre;   /* the 0x4 bytes before dst in func_800BABA8, addressed as dst[-1] */

typedef struct S_800BABA8_0 {
    s8 unk_00;
    u8 pad_01[0xC];
    s8 unk_0D;
    s8 unk_0E;
    s8 unk_0F;
    u8 pad_10[0x5];
    s8 unk_15;
    s8 unk_16;
    s8 unk_17;
} S_800BABA8_0;   /* dst in func_800BABA8 */

typedef struct S_800BABA8_1 {
    u8 pad_00[0x8D0];
    s32 unk_8D0;
} S_800BABA8_1;   /* *(DungeonRoot **)global_field in func_800BABA8 */

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

/* Advances particle levels and emits colored effect primitives into the dungeon display list. */
s32 func_800BABA8(DungeonObject *object, u16 *position) {
    DungeonRoot *root =
        *(DungeonRoot **)D_80083160;
    void *root_slot =
        (void *)D_80083160;
    s32 packet_cursor = root->cursor;
    Scratch *scratch;
    s16 particle = 0;
    u8 *scratch_90 = (u8 *)0x1F800090;
    u8 *scratch_94;
    void *packet;

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)root_slot + 0xB0;
    scratch->values[0] = position[1];
    scratch_94 = (u8 *)scratch;
    scratch->values[1] = position[3];
    scratch_94 = (u8 *)((u32)scratch_94 | 0x94);
    scratch->values[2] = position[5];
    packet = (void *)(packet_cursor + 7);
    do {
        {
            DungeonObject *level_entry = (DungeonObject *)((u8 *)object + (s16)particle);
            level_entry->level += 4;
            if ((s8)level_entry->level >= 48) {
                if (object->active != 0) {
                    level_entry->level = 48;
                    goto next_iteration;
                }
                level_entry->level = 0;
            }
        }
        {
            s32 particle_index = particle;
            (*(s32 *)((u8 *)packet + -3)) = 0;
            (*(s32 *)((u8 *)packet + 5)) = 0;
            scratch->x70 = scratch->values[0] +
                ((func_80064584((particle_index + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->x78 = scratch->x70;
            scratch->y72 = scratch->values[1] +
                ((func_800644B8((particle_index + (object->coord << 6)) << 7) << 4) >> 11);
            scratch->y7A = scratch->y72;
            scratch->z74 = scratch->values[2] -
                *(s8 *)((u8 *)object + particle_index + 0x12) * 2;
            scratch->z7C = scratch->z74 + 64;

            {
                s16 intensity = func_80069EF8();
                s8 particle_level = *(s8 *)((u8 *)object + particle_index + 0x12);
                if (particle_level >= 33) {
                    intensity = intensity / (particle_level - 32);
                } else if (particle_level < 16) {
                    intensity = intensity / (16 - particle_level);
                }
                ((S_800BABA8_0 *)packet)->unk_0D = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? intensity : 0;
                ((S_800BABA8_0 *)packet)->unk_15 = ((S_800BABA8_0 *)packet)->unk_0D;
                ((S_800BABA8_0 *)packet)->unk_0E = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? intensity : 0;
                ((S_800BABA8_0 *)packet)->unk_16 = ((S_800BABA8_0 *)packet)->unk_0E;
                ((S_800BABA8_0 *)packet)->unk_0F = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? intensity : 0;
                ((S_800BABA8_0 *)packet)->unk_17 = ((S_800BABA8_0 *)packet)->unk_0F;
            }

            scratch->length = func_80065420(&scratch->x70, (void *)(packet_cursor + 8),
                scratch_90, scratch_94);
            (*(s32 *)((u8 *)packet + 9)) = (*(s32 *)((u8 *)packet + 1));
            (*(u16 *)((u8 *)packet + 9)) += 4;
            scratch->length += func_80065420(&scratch->x78, (void *)(packet_cursor + 24),
                scratch_90, scratch_94);
            (*(s32 *)((u8 *)packet + 25)) = (*(s32 *)((u8 *)packet + 17));
            (*(u16 *)((u8 *)packet + 25)) += 2;
            scratch->length >>= 1;
            ((S_800BABA8_0_pre *)packet)[-1].unk_00 = 8;
            ((S_800BABA8_0 *)packet)->unk_00 = 58;
            packet = (void *)((s8 *)packet + 36);
            ASM_KEEP_NV(packet);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            packet = (void *)((s8 *)packet + 12);
            func_8006658C((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            packet_cursor += 36;
            func_80067F20((void *)packet_cursor, 0, 0, 96, 0);
            func_8006658C((void *)(scratch->base + scratch->length * 4),
                (void *)packet_cursor);
            {
                u8 drawn_count = object->count;
                packet_cursor += 12;
                object->count = drawn_count + 1;
            }
            next_iteration:
            {
                s16 next_particle = particle + 1;
                particle = next_particle;
                if (next_particle >= 32) {
                    break;
                }
            }
        }
    } while (1);
    ((S_800BABA8_1 *)(*(DungeonRoot **)root_slot))->unk_8D0 = packet_cursor;
    {
        s32 result = 0;
        ASM_KEEP_NV(result); /* MATCH: Initialize the return value before the epilogue restores. */
        return result;
    }
}
