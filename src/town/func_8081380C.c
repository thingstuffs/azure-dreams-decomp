#include "common.h"

typedef struct {
    u8 pad0[4];
    u16 x0;
    u16 y0;
    u16 z0;
    u16 padA;
    u16 x1;
    u16 y1;
    u16 z1;
    u8 pad12[2];
    void *unk14;
    u8 pad18[12];
    u16 flags;
} Source;

typedef struct {
    Source *source;
    u8 pad4[4];
    s16 use_first;
} Control;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Position;

typedef struct {
    u8 pad0[12];
    u32 color;
    u8 pad10[4];
    u16 flags;
} Output;

void func_8052E40C(Control *control, Position *position, Output *output) {
    Source *source = control->source;

    if (source->flags & 1) {
        output->flags |= 0x80;
    } else {
        output->flags &= ~0x80;
    }

    if (source->unk14 != 0) {
        output->color = 0xFFFFFF;
    } else {
        output->color = 0x808080;
    }

    if (control->use_first != 0) {
        position->x = source->x0;
        position->y = source->y0;
        position->z = source->z0;
    } else {
        position->x = source->x1;
        position->y = source->y1;
        position->z = source->z1;
    }
}
