#include "common.h"

typedef union {
    s32 word;
    struct {
        u16 low;
        u16 coord;
    } half;
} CoordWord;

typedef struct {
    CoordWord x;
    CoordWord y;
    CoordWord z;
} Vec3;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[6];
    u16 top;
    u16 bottom;
} Sprite;

typedef struct {
    s32 field0;
    u8 field4;
    u8 field5;
    u8 pad6[2];
    s32 field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    u16 flags14;
    u8 pad16[6];
    u16 field1C;
    u16 field1E;
} SpawnState;

typedef struct {
    void *parent;
    u8 pad4[0x48];
    u16 field4C;
} SpawnChild;

typedef struct {
    u8 pad0[8];
    Vec3 *position;
    SpawnState *state;
    void *callback;
    u8 pad14[0xC];
    SpawnChild child;
} Spawn;

typedef struct {
    void *field0;
    u8 pad4[0x3C];
    s16 field40;
    s16 field42;
    u8 pad44[4];
    u16 counter;
    u8 pad4A[2];
    u16 state;
} Actor;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Origin;

typedef struct {
    u8 pad0[8];
    void *entry;
} EntryTable;

extern Origin D_80083780;
extern s32 D_800814A0[3];
extern EntryTable D_80082E80;
extern u8 D_80083498[];
extern u8 D_80045340[];
extern s32 D_800DEA68[];
extern s32 D_80024BB8[3];

extern void func_800478B8(Sprite *sprite);
extern void func_8002497C(void) __attribute__((noreturn));
extern void func_80024AC8(s16 a0, u16 a1, s32 a2) __attribute__((noreturn));
extern s32 func_8003DE58(void *entry, void *table, void *scratch, s32 a3);
extern Spawn *func_8003FD64(s32 id, void *template);
extern void func_8004491C(Spawn *spawn, void *callback);
extern s32 func_800644B8(s32 angle);
extern s32 func_80069EF8(void);

void func_8197CEC0(Actor *actor, Vec3 *target, Sprite *sprite) {
    u16 scratch[3];
    u16 starts[3];

    actor->counter = actor->counter + 1;
    ((u16 *)actor->field0)[0x29] = ((u16 *)actor->field0)[0x29] | 0x8000;
    func_800478B8(sprite);
    starts[0] = target->x.half.coord;
    starts[1] = target->y.half.coord;
    starts[2] = target->z.half.coord;

    switch ((s16)actor->state) {
    default:
        return func_8002497C();
    case 0:
        if ((s16)actor->counter < 8) {
            sprite->bottom = sprite->bottom + 0x78;
            sprite->top = sprite->bottom;
        }
        if (func_8003DE58(D_80082E80.entry, &D_80082E80, scratch, 0) != 0) {
            target->x.word += ((((s16)scratch[0] + D_80083780.x) - (s16)target->x.half.coord) << 14);
            target->y.word += ((((s16)scratch[1] + D_80083780.y) - (s16)target->y.half.coord) << 14);
            target->z.word += ((((s16)scratch[2] + D_80083780.z) - (s16)target->z.half.coord) << 14);
            target->z.word -= (func_800644B8(((s16)actor->counter << 11) / 10) << 9);
        }
        if ((s16)actor->counter >= 10) {
            sprite->flags = sprite->flags | 0x800;
            actor->state = actor->state + 1;
            return func_8002497C();
        }
        break;
    case 1:
        if (func_8003DE58(D_80082E80.entry, &D_80082E80, scratch, 0) != 0) {
            target->x.word += ((((s16)scratch[0] + D_80083780.x) - (s16)target->x.half.coord) << 15);
            target->y.word += ((((s16)scratch[1] + D_80083780.y) - (s16)target->y.half.coord) << 15);
            target->z.word += ((((s16)scratch[2] + D_80083780.z) - (s16)target->z.half.coord) << 15);
        }
        if ((s16)actor->counter >= 0x12) {
            sprite->flags = sprite->flags & 0xF7FF;
            sprite->bottom = sprite->bottom + 0x50;
            sprite->top = sprite->bottom;
        }
        if ((s16)actor->counter >= 0x1C) {
            register u16 actor_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            s32 global_value;
            actor_value = ((u16 *)actor)[-1];
            actor_value |= 0x8000;
            ((u16 *)actor)[-1] = actor_value;
            actor_value = actor->state;
            global_value = D_800814A0[0];
            actor_value++;
            global_value |= 0x8000;
            actor->state = actor_value;
            D_800814A0[0] = global_value;
        }
        break;
    }

    actor->field40 = (s16)(((actor->counter & 3) << 5) + 0x80);
    actor->field42 = (s16)(((((s32)(actor->counter << 16) >> 18) << 5)) + 0x80);

    {
        register s32 count ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 loop_count;
        s32 counter_lt8;
        u16 counter_range;
        counter_lt8 = (s16)actor->counter < 8;
        counter_range = *(volatile u16 *)&actor->counter;
        if (counter_lt8) {
            count = 4;
        } else {
            count = 3;
            if ((u32)(counter_range - 8) < 5U) {
                count = 0xC;
            }
        }

        loop_count = count;
        if (loop_count >= 0) {
            void *base24 = D_80024BB8;
            s32 *baseDEA = D_800DEA68;
            do {
                Spawn *spawn;
                spawn = func_8003FD64(0x312, D_80083498);
                if (spawn != 0) {
                    register s32 difference ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    s32 dx;
                    s32 random;
                    s32 z_random;
                    s32 field_c;
                    s32 base_value;
                    SpawnState *state;
                    register SpawnChild *child ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    s16 target_y;
                    s16 start_y_signed;
                    u16 start_y_unsigned;

                    spawn->callback = base24;
                    func_8004491C(spawn, D_80045340);
                    state = spawn->state;
                    difference = (s16)target->x.half.coord;
                    difference -= (s16)starts[0];
                    dx = difference;
                    if (difference < 0) {
                        dx = -dx;
                    }
                    child = &spawn->child;
                    if (dx == 0) {
                        dx = 1;
                    }
                    random = func_80069EF8() % dx;
                    spawn->position->x.half.coord = (s16)((((s16)target->x.half.coord + (s16)starts[0]) >> 1) + random - (dx >> 1));
                    target_y = (s16)target->y.half.coord;
                    start_y_signed = (s16)starts[1];
                    start_y_unsigned = starts[1];
                    difference = target_y;
                    difference += start_y_signed;
                    dx = difference;
                    if (difference < 0) {
                        dx = -dx;
                    }
                    if (dx == 0) {
                        spawn->position->y.word = target->y.word;
                        return func_80024AC8(target_y, start_y_unsigned, random);
                    }
                    ((volatile Vec3 *)spawn->position)->y.half.coord = (s16)(start_y_signed + ((target_y - start_y_signed) * random) / dx);
                    spawn->position->x.word += (((func_80069EF8() & 0x3FF) - 0x1FF) << 10);
                    spawn->position->y.word += (((func_80069EF8() & 0x3FF) - 0x1FF) << 10);
                    z_random = func_80069EF8();
                    field_c = 0xC00000;
                    spawn->position->z.word = target->z.word + (((z_random & 0x3FF) - 0x1FF) << 10);
                    state->field1E = 0x1800;
                    state->field1C = 0x1800;
                    state->field10 = 0x60;
                    state->field0 = (s32)baseDEA;
                    state->flags14 = state->flags14 | 0xC;
                    base_value = baseDEA[1];
                    field_c |= 0x6060;
                    state->field4 = 0;
                    state->field5 = 0;
                    state->fieldC = field_c;
                    state->field8 = base_value;
                    ASM_KEEP_DEP_NV(child, field_c);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
                    base_value = (s32)actor->field0;
                    child->field4C = 0;
                    child->parent = (void *)base_value;
                }
                loop_count = loop_count - 1;
            } while (loop_count >= 0);
        }
    }
}
