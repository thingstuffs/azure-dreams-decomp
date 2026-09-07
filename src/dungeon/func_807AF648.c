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

s32 func_807AF648(DungeonObject *object, u16 *input) {
    DungeonRoot *root =
        *(DungeonRoot **)D_80083160;
    s32 cursor = root->cursor;
    void *global_field =
        (void *)D_80083160;
    Scratch *scratch;
    s16 i = 0;
    u8 *scratch_a = (u8 *)0x1F800090;
    u8 *scratch_b;
    void *dst;

    object->count = 0;
    scratch = (Scratch *)0x1F800000;
    scratch->base = *(u8 **)D_80083160 + 0xB0;
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
                    func_800F7148();
                }
                row->level = 0;
                {
                    register u32 inactive_index ASM_REG("$16") =
                        (u32)(u16)i << 16;
                    ASM_KEEP(inactive_index);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                }
            }
        }
        {
        s32 index = i;
        (*(s32 *)((u8 *)dst + -3)) = 0;
        (*(s32 *)((u8 *)dst + 5)) = 0;
        scratch->x70 = scratch->values[0] +
            ((func_80064584((index + (object->coord << 6)) << 7) << 4) >> 11);
        scratch->x78 = scratch->x70;
        scratch->y72 = scratch->values[1] +
            ((func_800644B8((index + (object->coord << 6)) << 7) << 4) >> 11);
        scratch->y7A = scratch->y72;
        scratch->z74 = scratch->values[2] -
            *(s8 *)((u8 *)object + index + 0x10) * 2;
        scratch->z7C = scratch->z74 + 64;

        {
            s16 value = func_80069EF8();
            s8 level = *(s8 *)((u8 *)object + index + 0x10);
            if (level >= 33) {
                s32 dead_value = value;
                register s32 dead_level ASM_REG("$2") = level - 32;   /* MATCH pin: load-bearing for the whole function shape */
                ASM_KEEP(dead_value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                ASM_TAILSLOT_PIN(dead_level);   /* MATCH pin: load-bearing for the whole function shape */
                func_800F6FE0();
            }
            if (level < 16) {
                value = value / (16 - level);
            }
            ((S_807AF648_0 *)dst)->unk_0D = (*(s32 *)((u8 *)object->state + 0x14) & 1) ? value : 0;
            ((S_807AF648_0 *)dst)->unk_15 = ((S_807AF648_0 *)dst)->unk_0D;
            ((S_807AF648_0 *)dst)->unk_0E = (*(s32 *)((u8 *)object->state + 0x14) & 4) ? value : 0;
            ((S_807AF648_0 *)dst)->unk_16 = ((S_807AF648_0 *)dst)->unk_0E;
            ((S_807AF648_0 *)dst)->unk_0F = (*(s32 *)((u8 *)object->state + 0x14) & 2) ? value : 0;
            ((S_807AF648_0 *)dst)->unk_17 = ((S_807AF648_0 *)dst)->unk_0F;
        }

        scratch->length = func_80065420(&scratch->x70, (void *)(cursor + 8),
            scratch_a, scratch_b);
        (*(s32 *)((u8 *)dst + 9)) = (*(s32 *)((u8 *)dst + 1));
        (*(u16 *)((u8 *)dst + 9)) += 4;
        scratch->length += func_80065420(&scratch->x78, (void *)(cursor + 24),
            scratch_a, scratch_b);
            (*(s32 *)((u8 *)dst + 25)) = (*(s32 *)((u8 *)dst + 17));
        (*(u16 *)((u8 *)dst + 25)) += 2;
        scratch->length >>= 1;
        ((S_807AF648_0_pre *)dst)[-1].unk_00 = 8;
        ((S_807AF648_0 *)dst)->unk_00 = 58;
        dst = (void *)((s8 *)dst + 36);
        ASM_KEEP_NV(dst);   /* MATCH pin: retail immediate-load split depends on it */
        dst = (void *)((s8 *)dst + 12);
        {
            void *draw_cursor = (void *)cursor;
            cursor += 36;
        func_8006658C((void *)(scratch->base + scratch->length * 4),
            draw_cursor);
        }
        func_80067F20((void *)cursor, 0, 0, 96, 0);
        func_8006658C((void *)(scratch->base + scratch->length * 4),
            (void *)cursor);
        {
            u8 count = object->count;
            cursor += 12;
            object->count = count + 1;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        }
        {
            s16 next_i = i + 1;
            i = next_i;
            if (next_i >= 32) {
                break;
            }
        }
        }
    } while (1);
    ((S_807AF648_1 *)(*(DungeonRoot **)global_field))->unk_8D0 = cursor;
    return 0;
}
