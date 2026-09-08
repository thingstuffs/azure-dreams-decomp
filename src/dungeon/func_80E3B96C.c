#include "common.h"

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

extern s32 D_80045340;
extern u16 D_8006CCD8[];
extern u16 D_8006CCD8_success[] __asm__("D_8006CCD8");
extern u16 D_8006CCE8[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s16 D_8008347C;
extern u8 *D_800E3D7C;
extern s32 *D_80174CCC;
extern s8 D_801766F0[];

extern s32 func_800A1618(s32, s32);
extern s32 func_8017506C(s32, s32, s32, s32, u16 *);
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
    register s32 trial_dir ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 target_y;
    s32 target_x;
    Object *object;
    Display *display;
    Work *work;
    u8 *special_data;
    s32 offset_x_index;
    u16 *object_counts;
    s32 owner_byte;
    s32 offset_y_index;
    u32 initial_result;
    register u8 *table_or_owner ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    Position *position;
    Source *source;
    Context *context;

    position = position_arg;
    source = source_arg;
    context = context_arg;
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(position);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    target_y = target_x = 0;
    if (context->f60 == D_800E3D7C) {
        special_data = *(u8 **)((u8 *)context->f60 + 0x4C);
        if (special_data != 0) {
            if (special_data[1] == 15 && special_data[0] == 8) {
                goto exit;
            }
        }
    }

    if (D_8008347C >= 32) {
        goto exit;
    }
    if (!func_800A1618(context->f13, 1) && !func_800A1618(context->f13, 3)) {
        goto exit;
    }

    direction = (((s16)context->f2A >> 9) + 4) & 7;
    initial_result = (u16)func_8017506C(source->x, source->y, position->z, direction, &hit) << 16;
    if (initial_result != 0) {
        goto initial_success;
    }

    {
        register u16 *x_steps;
        register u16 *trial_x_step ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u16 *first_x_step;
        u16 *first_y_step;
        s32 trial_result;

        trial_dir = 0;
        x_steps = D_8006CCD8;
        {
            register s32 direction_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ASM_SET(direction_offset);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            direction_offset = direction << 1;
            first_x_step = (u16 *)(direction_offset + (s32)x_steps);
            table_or_owner = (u8 *)D_8006CCE8;
            first_y_step = (u16 *)(direction_offset + (s32)table_or_owner);
        }
search:
        trial_result = func_8017506C(
            (s16)(source->x + first_x_step[0]),
            (s16)(source->y + first_y_step[0]),
            position->z,
            (s16)trial_dir,
            &hit);
        if ((s16)trial_result != 0) {
            goto trial_success;
        }
        trial_dir++;
        if (trial_dir < 8) {
            goto search;
        }

search_done:
        if (trial_dir >= 8) {
            goto exit;
        }
        ASM_USE_NV(trial_dir);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        goto allocate;

trial_success:
        {
            register s32 trial_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            s32 trial_y_address;

            trial_offset = trial_dir << 1;
            trial_x_step = (u16 *)(trial_offset + (s32)x_steps);
            table_or_owner = (u8 *)D_8006CCE8;
            trial_y_address = trial_offset + (s32)table_or_owner;
            ASM_KEEP(trial_x_step);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            target_x = trial_x_step[0] + (source->x + first_x_step[0]);
            target_y = *(u16 *)trial_y_address + (source->y + first_y_step[0]);
            goto search_done;
        }
    }

initial_success:
    {
        s32 x_steps_address;
        s32 direction_offset;
        s32 x_step_address;

        x_steps_address = (s32)D_8006CCD8_success;
        direction_offset = direction << 1;
        x_step_address = x_steps_address + direction_offset;
        target_x = source->x + *(u16 *)x_step_address;
        target_y = source->y + D_8006CCE8[direction];
    }

allocate:
    table_or_owner = *(u8 * volatile *)&owner_data;
    object = func_8003FD64(0x100, table_or_owner - 0x20);
    if (object == 0) {
        goto exit;
    }

    display = object->display;
    work = (Work *)((u8 *)object + 0x20);
    object->callback = &D_80174CCC;
    work->source = source;
    work->position = position;

    display->f1E = 0x1000;
    display->f1C = 0x1000;
    display->color = 0x00808080;
    display->f28 = source->f28;
    display->f12 = source->f12;

    offset_x_index = ((D_80083228 + context->f2A + 0x100) >> 8) & 0xE;
    local_offset.x = D_801766F0[offset_x_index];
    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    offset_y_index = ((D_80083228 + context->f2A + 0x100) >> 8) & 0xE;
    local_offset.y = D_801766F0[offset_y_index + 1];
    local_offset.z = 0;
    func_8003E02C(&local_offset, &world_offset);

    object->position->x = position->x + world_offset.x;
    object->position->y = position->y + world_offset.y;
    object->position->z = position->z + world_offset.z;
    func_80047784(display, 0x41, 0);
    func_8004491C(object, &D_80045340);

    object->field20 = &context->f2A;
    work->f20 = 8;
    work->x = target_x;
    work->y = target_y;
    work->hit = hit;
    work->flags = context->f14 & 0x2007;
    work->source_id = source->f12;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    table_or_owner = owner_data;
    owner_byte = table_or_owner[0xAC];
    work->owner_minus20 = (u8 *)context - 0x20;
    work->context = context;
    work->owner_byte = owner_byte;

    object_counts = (u16 *)&D_80083460;
    object_counts[5]++;

exit:
    return;
}
