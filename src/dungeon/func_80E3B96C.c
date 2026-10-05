#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

typedef struct {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Position;

typedef struct {
    u8 pad0[0x12];
    u16 f12;
    u8 pad14[0x10];
    u8 x;
    u8 y;
    u8 pad26[2];
    s32 f28;
} Source;

typedef struct {
    u8 pad0[0x13];
    u8 f13;
    u16 f14;
    u8 pad16[0x14];
    s16 f2A;
    u8 pad2C[0x34];
    void *f60;
} Context;

typedef struct {
    u8 pad0[8];
    Position *position;
    void *display;
    void *callback;
    void *data;
    u8 pad14[8];
    void *field20;
    u8 pad24[4];
} Object;

typedef struct {
    u8 pad0[0xC];
    u32 color;
    u8 pad10[2];
    u16 f12;
    u8 pad14[8];
    s16 f1C;
    s16 f1E;
    u8 pad20[8];
    s32 f28;
} Display;

typedef struct {
    u8 pad0[0xC];
    void *owner_minus20;
    Context *context;
    Source *source;
    Position *position;
    u8 pad1C[4];
    s16 f20;
    u8 pad22[0x10];
    s16 x;
    s16 y;
    u16 hit;
    u16 flags;
    u16 source_id;
    u16 owner_byte;
} Work;

extern s32 *D_80174CCC;
extern s8 D_801766F0[];

extern s32 func_800A1618(s32, s32);
extern s32 func_8017506C(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out);
extern Object *func_8003FD64(s32, void *);
extern void func_8003E02C(Vec3s *, Vec3s *);
extern void func_80047784(void *, s32, s32);
extern void func_8004491C(Object *, void *);

/* Find a reachable target tile and create an object with the source display and context. */
void func_8017516C(u8 *owner_data, Position *position_arg, Source *source_arg, Context *context_arg) {
    Vec3s world_offset;
    Vec3s local_offset;
    u16 hit;
    s32 direction;
    s32 trial_dir;
    s32 target_y;
    s32 target_x;
    Object *object;
    Display *display;
    Work *work;
    u8 *special_data;
    s32 offset_x_index;
    s32 owner_byte;
    s32 offset_y_index;
    u32 initial_result;

    target_y = target_x = 0;
    if (context_arg->f60 == ((u8 *)D_800E3D7C)) {
        special_data = *(u8 **)((u8 *)context_arg->f60 + 0x4C);
        if (special_data != 0) {
            if (special_data[1] == 15 && special_data[0] == 8) {
                return;
            }
        }
    }

    if (dungeonStatus.unk_1C >= 32) {
        return;
    }
    if (!func_800A1618(context_arg->f13, 1) && !func_800A1618(context_arg->f13, 3)) {
        return;
    }

    direction = (((s16)context_arg->f2A >> 9) + 4) & 7;
    initial_result = (u16)func_8017506C(source_arg->x, source_arg->y, position_arg->z, direction, &hit) << 16;
    if (initial_result == 0) {
        for (trial_dir = 0; trial_dir < 8; trial_dir++) {
            if ((s16)func_8017506C((s16)(source_arg->x + dirStepX[direction]),
                                   (s16)(source_arg->y + dirStepY[direction]),
                                   position_arg->z, (s16)trial_dir, &hit) != 0) {
                target_x = ((u16 *)dirStepX)[trial_dir] + (source_arg->x + ((u16 *)dirStepX)[direction]);
                target_y = ((u16 *)dirStepY)[trial_dir] + (source_arg->y + ((u16 *)dirStepY)[direction]);
                break;
            }
        }
        if (trial_dir >= 8) {
            return;
        }
    } else {
        target_x = source_arg->x + ((u16 *)dirStepX)[direction];
        target_y = source_arg->y + ((u16 *)dirStepY)[direction];
    }

    object = func_8003FD64(0x100, owner_data - 0x20);
    if (object == 0) {
        return;
    }

    display = object->display;
    work = (Work *)((u8 *)object + 0x20);
    object->callback = &D_80174CCC;
    work->source = source_arg;
    work->position = position_arg;

    display->f1E = 0x1000;
    display->f1C = 0x1000;
    display->color = 0x00808080;
    display->f28 = source_arg->f28;
    display->f12 = source_arg->f12;

    offset_x_index = ((gameWork.view.viewAngle + context_arg->f2A + 0x100) >> 8) & 0xE;
    local_offset.x = D_801766F0[offset_x_index];
    offset_y_index = ((gameWork.view.viewAngle + context_arg->f2A + 0x100) >> 8) & 0xE;
    local_offset.y = D_801766F0[offset_y_index + 1];
    local_offset.z = 0;
    func_8003E02C(&local_offset, &world_offset);

    object->position->x = position_arg->x + world_offset.x;
    object->position->y = position_arg->y + world_offset.y;
    object->position->z = position_arg->z + world_offset.z;
    func_80047784(display, 0x41, 0);
    func_8004491C(object, func_80045340);

    object->field20 = &context_arg->f2A;
    work->f20 = 8;
    work->x = target_x;
    work->y = target_y;
    work->hit = hit;
    work->flags = context_arg->f14 & 0x2007;
    (*(u16 *)((u8 *)work + 0x3A)) = source_arg->f12;
    owner_byte = owner_data[0xAC];
    work->owner_minus20 = (u8 *)context_arg - 0x20;
    work->context = context_arg;
    work->owner_byte = owner_byte;

    dungeonStatus.unk_0A++;

    return;
}
