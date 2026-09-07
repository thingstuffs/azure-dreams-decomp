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
extern s32 func_800BAD40(s8);
extern s32 func_800BAEA8(void);

s32 func_800BABA8(DungeonObject *object, u16 *input) {
    register DungeonRoot *root ASM_REG("$3") =
        *(DungeonRoot **)D_80083160;
    void *global_field =
        (void *)D_80083160;
    s32 cursor = root->cursor;
    Scratch *scratch;
    register s16 i ASM_REG("$21") = 0;
    register u8 *scratch_a ASM_REG("$23") = (u8 *)0x1F800090;
    register u8 *scratch_b ASM_REG("$22");
    register void *dst ASM_REG("$17");

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)global_field + 0xB0;
    scratch->values[0] = input[1];
    scratch_b = (u8 *)scratch;
    scratch->values[1] = input[3];
    scratch_b = (u8 *)((u32)scratch_b | 0x94);
    scratch->values[2] = input[5];
    dst = (void *)(cursor + 7);
    do {
        {
            DungeonObject *row = (DungeonObject *)((u8 *)object + (s16)i);
            row->level += 4;
            if ((s8)row->level >= 48) {
                if (object->active != 0) {
                    row->level = 48;
                    return func_800BAEA8();
                }
                row->level = 0;
            }
        }
        {
        s32 index = i;
        M2C_FIELD(dst, s32 *, -3) = 0;
        M2C_FIELD(dst, s32 *, 5) = 0;
        scratch->x70 = scratch->values[0] +
            ((func_80064584((index + (object->coord << 6)) << 7) << 4) >> 11);
        scratch->x78 = scratch->x70;
        scratch->y72 = scratch->values[1] +
            ((func_800644B8((index + (object->coord << 6)) << 7) << 4) >> 11);
        scratch->y7A = scratch->y72;
        scratch->z74 = scratch->values[2] -
            *(s8 *)((u8 *)object + index + 0x12) * 2;
        scratch->z7C = scratch->z74 + 64;

        {
            s16 value = func_80069EF8();
            s8 level = *(s8 *)((u8 *)object + index + 0x12);
            if (level >= 33) {
                s32 dead_value = value;
                register s32 dead_level ASM_REG("$2") = level - 32;
                ASM_KEEP(dead_value);
                ASM_TAILSLOT_PIN(dead_level);
                return func_800BAD40(level);
            }
            if (level < 16) {
                value = value / (16 - level);
            }
            M2C_FIELD(dst, s8 *, 13) = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? value : 0;
            M2C_FIELD(dst, s8 *, 21) = M2C_FIELD(dst, s8 *, 13);
            M2C_FIELD(dst, s8 *, 14) = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? value : 0;
            M2C_FIELD(dst, s8 *, 22) = M2C_FIELD(dst, s8 *, 14);
            M2C_FIELD(dst, s8 *, 15) = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? value : 0;
            M2C_FIELD(dst, s8 *, 23) = M2C_FIELD(dst, s8 *, 15);
        }

        scratch->length = func_80065420(&scratch->x70, (void *)(cursor + 8),
            scratch_a, scratch_b);
        M2C_FIELD(dst, s32 *, 9) = M2C_FIELD(dst, s32 *, 1);
        M2C_FIELD(dst, u16 *, 9) += 4;
        scratch->length += func_80065420(&scratch->x78, (void *)(cursor + 24),
            scratch_a, scratch_b);
        M2C_FIELD(dst, s32 *, 25) = M2C_FIELD(dst, s32 *, 17);
        M2C_FIELD(dst, u16 *, 25) += 2;
        scratch->length >>= 1;
        M2C_FIELD(dst, s8 *, -4) = 8;
        M2C_FIELD(dst, s8 *, 0) = 58;
        dst = (void *)((s8 *)dst + 36);
        ASM_KEEP_NV(dst);
        dst = (void *)((s8 *)dst + 12);
        func_8006658C((void *)(scratch->base + scratch->length * 4),
            (void *)cursor);
        cursor += 36;
        func_80067F20((void *)cursor, 0, 0, 96, 0);
        func_8006658C((void *)(scratch->base + scratch->length * 4),
            (void *)cursor);
        {
            u8 count = object->count;
            ASM_MEM_BARRIER();
            cursor += 12;
            ASM_SCHED_BARRIER();
            object->count = count + 1;
            ASM_SCHED_BARRIER();
        }
        {
            register s16 next_i ASM_REG("$2") = i + 1;
            ASM_KEEP_NV(next_i);
            i = next_i;
            if (next_i >= 32) {
                break;
            }
        }
        }
    } while (1);
    M2C_FIELD(*(DungeonRoot **)global_field, s32 *, 0x8D0) = cursor;
    return 0;
}
