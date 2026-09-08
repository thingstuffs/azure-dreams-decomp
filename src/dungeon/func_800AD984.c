#include "common.h"

typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
} State;

typedef struct {
    u8 pad_0[0x1C];
    s32 flags_1C;
} Entity;

typedef struct {
    u8 pad_0[0x24];
    u8 field_24;
    u8 field_25;
} Source;

extern State D_80083460[];
extern s32 D_800814A0[];
extern void func_800A32A4(Entity *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_8009A028(Entity *);

/* Update an entity using source bytes and a flag-dependent mask, then set completion flags. */
void func_800B30E4(void *unused_0, void *unused_1, Source *source, Entity *entity) {
    State *state = D_80083460;
    s32 update_mask;
    u8 source_24;
    u8 source_25;

    if (state->field_10 == (s32)((u8 *)entity - 0x20)) {
        state->field_10 &= 0x7FFFFFFF;
    }
    func_800A32A4(entity);
    source_24 = source->field_24;
    source_25 = source->field_25;
    update_mask = 0x3000;
    if (entity->flags_1C & 0x2000) {
        update_mask = 0x300;
    }
    func_8009A3D0(source_24, source_25, update_mask);
    func_8009A028(entity);
    *(u16 *)((u8 *)entity - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
