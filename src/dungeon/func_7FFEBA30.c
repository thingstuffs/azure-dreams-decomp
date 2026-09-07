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
extern void func_7010D810(Particle *, Entity *, Position *, s32);
extern void func_8010D440(void);
extern s32 D_80086AD8;
extern u16 D_80094422;

void func_7FFEBA30(Entity *self, Position *origin, s32 arg2) {
    s32 i;
    u16 value;
    Header *header;
    union {
        Particle *particle;
        Position *position;
    } work;

    header = self->header;
    origin->x = header->position->x + self->x;
    origin->y = header->position->y + self->y;
    origin->z = header->position->z + self->z;
    value = self->counter + 1;
    self->counter = value;
    if ((s16)value < 20) {
        i = 0;
        do {
            work.particle = func_7003CF18(0x212);
            i++;
            if (work.particle != 0) {
                func_7010D810(work.particle, self, origin, arg2);
                work.particle->size_x = 32;
                work.particle->size_y = 32;
                work.particle->callback = func_8010D440;
                work.position = work.particle->position;
                { s32 rx = func_700750E0(); s32 px = work.position->x - 31; work.position->x = px + (rx & 0x3F); }
                { s32 ry = func_700750E0(); s32 py = work.position->y - 31; work.position->y = py + (ry & 0x3F); }
                work.position->z -= func_700750E0() & 0x1F;
                work.position->velocity = -((func_700750E0() & 0xFFFF) + 0x10000) * 2;
            }
        } while (i < 4);
    }
    value = self->timer - 1;
    self->timer = value;
    if ((value << 16) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        *((u16 *)self - 1) |= 0x8000;
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}
