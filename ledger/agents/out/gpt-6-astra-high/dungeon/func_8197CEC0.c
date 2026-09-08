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

/* Advance the actor animation, move toward the entry position, and spawn trailing particles. */
void func_8197CEC0(Actor *actor, Vec3 *target, Sprite *sprite) {
    u16 entry_pos[3];
    u16 start_pos[3];

    actor->counter = actor->counter + 1;
    ((u16 *)actor->field0)[0x29] = ((u16 *)actor->field0)[0x29] | 0x8000;
    func_800478B8(sprite);
    start_pos[0] = target->x.half.coord;
    start_pos[1] = target->y.half.coord;
    start_pos[2] = target->z.half.coord;

    switch ((s16)actor->state) {
    default:
        return func_8002497C();
    case 0:
        if ((s16)actor->counter < 8) {
            sprite->bottom = sprite->bottom + 0x78;
            sprite->top = sprite->bottom;
        }
        if (func_8003DE58(D_80082E80.entry, &D_80082E80, entry_pos, 0) != 0) {
            target->x.word += ((((s16)entry_pos[0] + D_80083780.x) - (s16)target->x.half.coord) << 14);
            target->y.word += ((((s16)entry_pos[1] + D_80083780.y) - (s16)target->y.half.coord) << 14);
            target->z.word += ((((s16)entry_pos[2] + D_80083780.z) - (s16)target->z.half.coord) << 14);
            target->z.word -= (func_800644B8(((s16)actor->counter << 11) / 10) << 9);
        }
        if ((s16)actor->counter >= 10) {
            sprite->flags = sprite->flags | 0x800;
            actor->state = actor->state + 1;
            return func_8002497C();
        }
        break;
    case 1:
        if (func_8003DE58(D_80082E80.entry, &D_80082E80, entry_pos, 0) != 0) {
            target->x.word += ((((s16)entry_pos[0] + D_80083780.x) - (s16)target->x.half.coord) << 15);
            target->y.word += ((((s16)entry_pos[1] + D_80083780.y) - (s16)target->y.half.coord) << 15);
            target->z.word += ((((s16)entry_pos[2] + D_80083780.z) - (s16)target->z.half.coord) << 15);
        }
        if ((s16)actor->counter >= 0x12) {
            sprite->flags = sprite->flags & 0xF7FF;
            sprite->bottom = sprite->bottom + 0x50;
            sprite->top = sprite->bottom;
        }
        if ((s16)actor->counter >= 0x1C) {
            register u16 actor_bits ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
            s32 global_flags;
            actor_bits = ((u16 *)actor)[-1];
            actor_bits |= 0x8000;
            ((u16 *)actor)[-1] = actor_bits;
            actor_bits = actor->state;
            global_flags = D_800814A0[0];
            actor_bits++;
            global_flags |= 0x8000;
            actor->state = actor_bits;
            D_800814A0[0] = global_flags;
        }
        break;
    }

    actor->field40 = (s16)(((actor->counter & 3) << 5) + 0x80);
    actor->field42 = (s16)(((((s32)(actor->counter << 16) >> 18) << 5)) + 0x80);

    {
        register s32 spawn_limit ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
        s32 remaining;
        s32 early_frames;
        u16 frame;
        early_frames = (s16)actor->counter < 8;
        frame = *(volatile u16 *)&actor->counter;
        if (early_frames) {
            spawn_limit = 4;
        } else {
            spawn_limit = 3;
            if ((u32)(frame - 8) < 5U) {
                spawn_limit = 0xC;
            }
        }

        remaining = spawn_limit;
        if (remaining >= 0) {
            void *particle_callback = D_80024BB8;
            s32 *particle_data = D_800DEA68;
            do {
                Spawn *spawn;
                spawn = func_8003FD64(0x312, D_80083498);
                if (spawn != 0) {
                    register s32 coord_term ASM_REG("$2");   /* MATCH pin: retail schedule: same instructions, different order without it */
                    s32 coord_magnitude;
                    s32 x_offset;
                    s32 z_jitter;
                    s32 packed_color;
                    s32 data_word;
                    SpawnState *state;
                    register SpawnChild *child ASM_REG("$22");   /* MATCH pin: retail schedule: same instructions, different order without it */
                    s16 target_y;
                    s16 start_y;
                    u16 start_y_bits;

                    spawn->callback = particle_callback;
                    func_8004491C(spawn, D_80045340);
                    state = spawn->state;
                    coord_term = (s16)target->x.half.coord;
                    coord_term -= (s16)start_pos[0];
                    coord_magnitude = coord_term;
                    if (coord_term < 0) {
                        coord_magnitude = -coord_magnitude;
                    }
                    child = &spawn->child;
                    if (coord_magnitude == 0) {
                        coord_magnitude = 1;
                    }
                    x_offset = func_80069EF8() % coord_magnitude;
                    spawn->position->x.half.coord = (s16)((((s16)target->x.half.coord + (s16)start_pos[0]) >> 1) + x_offset - (coord_magnitude >> 1));
                    target_y = (s16)target->y.half.coord;
                    start_y = (s16)start_pos[1];
                    start_y_bits = start_pos[1];
                    coord_term = target_y;
                    coord_term += start_y;
                    coord_magnitude = coord_term;
                    if (coord_term < 0) {
                        coord_magnitude = -coord_magnitude;
                    }
                    if (coord_magnitude == 0) {
                        spawn->position->y.word = target->y.word;
                        return func_80024AC8(target_y, start_y_bits, x_offset);
                    }
                    ((volatile Vec3 *)spawn->position)->y.half.coord = (s16)(start_y + ((target_y - start_y) * x_offset) / coord_magnitude);
                    spawn->position->x.word += (((func_80069EF8() & 0x3FF) - 0x1FF) << 10);
                    spawn->position->y.word += (((func_80069EF8() & 0x3FF) - 0x1FF) << 10);
                    z_jitter = func_80069EF8();
                    packed_color = 0xC00000;
                    spawn->position->z.word = target->z.word + (((z_jitter & 0x3FF) - 0x1FF) << 10);
                    state->field1E = 0x1800;
                    state->field1C = 0x1800;
                    state->field10 = 0x60;
                    state->field0 = (s32)particle_data;
                    state->flags14 = state->flags14 | 0xC;
                    data_word = particle_data[1];
                    packed_color |= 0x6060;
                    state->field4 = 0;
                    state->field5 = 0;
                    state->fieldC = packed_color;
                    state->field8 = data_word;
                    ASM_KEEP_DEP_NV(child, packed_color);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
                    data_word = (s32)actor->field0;
                    child->field4C = 0;
                    child->parent = (void *)data_word;
                }
                remaining = remaining - 1;
            } while (remaining >= 0);
        }
    }
}
