#include "common.h"

typedef struct Source Source;
typedef struct Spawned Spawned;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80081484[];
extern Source *D_800814A8;
extern u8 D_800E3548[];

extern s32 func_8009A540(s32, s32, s32, s32);
extern Spawned *func_8009B25C(void *, s32, s32, s32);
extern s32 func_800A4298(Spawned *);
extern s32 func_800A70E4(s32, s32, s32);
extern Spawned *func_800A8E74(void *, s32, s32, void *, void *, s32);
extern void func_8009A3D0(s32, s32, s32);

struct Spawned {
    u8 unk00[0x13];
    u8 kind;
    s32 flags;
    u8 unk18[0x1c];
    s32 value34;
    u8 unk38[4];
    s32 value3c;
    u8 unk40[0x40];
    void *parent;
    u8 unk84[0x38];
    void *fieldbc;
};

struct Source {
    u8 unk00[0x2a];
    u16 index_field;
    u8 unk2c[0x5c];
    s16 height;
};

typedef struct Context {
    u8 unk00[8];
    s32 x;
    s32 y;
} Context;

/* Spawns an object at the target position and updates the active source state. */
void *func_8009B5AC(Source *source, s32 target_x, s32 target_y) {
    Source **active_source;
    Spawned *spawned;
    u8 *entry;
    s16 x;
    s32 y;
    s32 state_code;
    s32 probe_result;
    s32 direction;
    s32 flags34;
    s32 flags3c;
    s32 entry_value;
    register u8 *result_bytes ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 spawn_x ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u16 spawn_y ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    direction = (source->index_field >> 9) & 7;

    probe_result = func_8009A540(direction,
                                (s16)(target_x - D_8006CCD8[direction]),
                                (s16)(target_y - D_8006CCE8[direction]),
                                (s16)(source->height - 0x20));
    spawn_x = (u16)target_x;
    spawn_y = (u16)target_y;
    probe_result <<= 0x10;
    active_source = &D_800814A8;
    if (probe_result == 0) {
        goto return_null;
    }

    spawned = func_8009B25C(source, spawn_x, spawn_y,
                           source->height);
    if (spawned != (void *)0) {
        if ((spawned->flags & 0x80000) && source == *active_source) {
            D_80081484[0] = spawned->kind;
            D_80081484[1] = 0x13;
            state_code = 0x14;
            if (spawned->flags & 0x4000) {
                state_code = func_800A4298(spawned);
                if ((s16)state_code < 0) {
                    state_code = 0x14;
                }
            }
            result_bytes = D_80081484;
            result_bytes[3] = (u8)state_code;
            result_bytes[2] = 0;
            result_bytes = (u8 *)spawned;
            return result_bytes;
        }
        return spawned;
    }

    x = (s16)target_x;
    y = (s16)target_y;
    flags3c = (s16)func_800A70E4(x, y, source->height);
    if (flags3c < 0) {
        goto return_null;
    }
    entry = &D_800E3548[flags3c * 4];
    spawned = func_800A8E74(source,
                           ((Context *)((u8 *)source - 0x20))->x,
                           ((Context *)((u8 *)source - 0x20))->y,
                           source, entry, flags3c);
    if (spawned == (void *)0) {
        return (void *)1;
    }
    spawned->parent = source;
    if (source == *active_source) {
        entry_value = *(s32 *)entry;
        spawned->fieldbc = D_80081484;
        *(s32 *)D_80081484 = entry_value;
    }
    entry[1] = 0;
    entry[0] = 0;
    func_8009A3D0(x, y, 0x800);
    result_bytes = (u8 *)spawned + 0x20;
    flags34 = spawned->value34;
    flags3c = spawned->value3c;
    flags34 |= 0x80000;
    flags3c |= 0x2000;
    spawned->value34 = flags34;
    spawned->value3c = flags3c;
    return result_bytes;

return_null:
    return (void *)0;
}
