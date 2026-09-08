#include "common.h"

typedef struct Position {
    u16 unk0;
    u16 x;
    u16 unk4;
    u16 y;
    u16 unk8;
    u16 z;
    u8 pad_C[8];
    s32 velocity;
} Position;

typedef struct Header {
    u8 pad_0[8];
    Position *position;
} Header;

typedef struct Entity {
    u8 pad_0[0x16];
    u16 counter;
    u8 pad_18[6];
    u16 timer;
    u8 pad_20[4];
    Header *header;
    u8 pad_28[0x14];
    u16 x;
    u16 y;
    u16 z;
} Entity;

typedef struct Particle {
    u8 pad_0[8];
    Position *position;
    u8 pad_C[4];
    void (*callback)(void);
    u8 pad_14[0x2A];
    s16 size_x;
    s16 size_y;
} Particle;

extern Particle *func_7003CF18(s32);
extern s32 func_700750E0(void);
extern void func_7010B30C(Particle *, Entity *, Position *, s32);
extern void D_8010B008(void);
extern s32 D_80086AD8;
extern u16 D_80094422;

/* Emit scattered particles during the first 19 ticks and mark the entity expired when its timer ends. */
void func_7FFE8154(Entity *self, Position *origin, s32 spawn_param) {
    s32 spawn_count;
    u16 tick_count;
    Header *header;
    union {
        Particle *particle;
        Position *position;
    } spawn_data;

    header = self->header;
    origin->x = header->position->x + self->x;
    origin->y = header->position->y + self->y;
    origin->z = header->position->z + self->z;
    tick_count = self->counter + 1;
    self->counter = tick_count;
    if ((s16)tick_count < 20) {
        spawn_count = 0;
        do {
            spawn_data.particle = func_7003CF18(0x212);
            spawn_count++;
            if (spawn_data.particle != 0) {
                func_7010B30C(spawn_data.particle, self, origin, spawn_param);
                spawn_data.particle->size_x = 10;
                spawn_data.particle->size_y = 10;
                spawn_data.particle->callback = D_8010B008;
                spawn_data.position = spawn_data.particle->position;
                {
                    s32 random_x = func_700750E0();
                    s32 base_x = spawn_data.position->x - 31;
                    spawn_data.position->x = base_x + (random_x & 0x3F);
                }
                {
                    s32 random_y = func_700750E0();
                    s32 base_y = spawn_data.position->y - 31;
                    spawn_data.position->y = base_y + (random_y & 0x3F);
                }
                spawn_data.position->velocity = -((func_700750E0() & 0xFFFF) + 0x80000) * 2;
            }
        } while (spawn_count < 4);
    }
    tick_count = self->timer - 1;
    self->timer = tick_count;
    if ((tick_count << 16) <= 0) {
        u16 *active_count = &D_80094422;
        u16 remaining_count;

        *((u16 *)self - 1) |= 0x8000;
        remaining_count = *active_count - 1;
        D_80086AD8 |= 0x8000;
        *active_count = remaining_count;
    }
}
