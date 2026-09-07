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

void func_8017516C(u8 *arg0, Position *position_arg, Source *source_arg, Context *context_arg) {
    Vec3s transformed;
    Vec3s input;
    u16 hit;
    s32 direction;
    register s32 trial ASM_REG("$16");
    s32 final_y;
    s32 final_x;
    register Object *object ASM_REG("$18");
    Display *display;
    Work *work;
    u8 *special;
    s32 table_index;
    u16 *counter;
    s32 owner_byte;
    s32 angle_index;
    register u32 initial_test ASM_REG("$2");
    register u8 *scratch_t1 ASM_REG("$9");
    register Position *position ASM_REG("$21");
    register Source *source ASM_REG("$19");
    register Context *context ASM_REG("$20");

    position = position_arg;
    source = source_arg;
    context = context_arg;
    ASM_KEEP_NV(source);
    ASM_KEEP_NV(position);
    final_y = final_x = 0;
    if (context->f60 == D_800E3D7C) {
        special = *(u8 **)((u8 *)context->f60 + 0x4C);
        if (special != 0) {
            if (special[1] == 15 && special[0] == 8) {
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
    initial_test = (u16)func_8017506C(source->x, source->y, position->z, direction, &hit) << 16;
    if (initial_test != 0) {
        goto initial_success;
    }
    ASM_SET(initial_test);

    {
        register u16 *xbase;
        register u16 *trial_x ASM_REG("$5");
        u16 *xptr;
        u16 *yptr;
        s32 result;

        trial = 0;
        xbase = D_8006CCD8;
        ASM_USE_NV(initial_test);
        {
            register s32 failure_offset ASM_REG("$3");

            ASM_SET(failure_offset);
            failure_offset = direction << 1;
            xptr = (u16 *)(failure_offset + (s32)xbase);
            scratch_t1 = (u8 *)D_8006CCE8;
            ASM_KEEP_NV(scratch_t1);
            yptr = (u16 *)(failure_offset + (s32)scratch_t1);
        }
search:
        result = func_8017506C(
            (s16)(source->x + xptr[0]),
            (s16)(source->y + yptr[0]),
            position->z,
            (s16)trial,
            &hit);
        if ((s16)result != 0) {
            goto trial_success;
        }
        trial++;
        if (trial < 8) {
            goto search;
        }

search_done:
        if (trial >= 8) {
            goto exit;
        }
        ASM_USE_NV(trial);
        goto allocate;

trial_success:
        {
            register s32 trial_offset ASM_REG("$3");
            s32 trial_y_address;

            trial_offset = trial << 1;
            trial_x = (u16 *)(trial_offset + (s32)xbase);
            scratch_t1 = (u8 *)D_8006CCE8;
            trial_y_address = trial_offset + (s32)scratch_t1;
            ASM_KEEP(trial_x);
            ASM_KEEP(scratch_t1);
            final_x = trial_x[0] + (source->x + xptr[0]);
            final_y = *(u16 *)trial_y_address + (source->y + yptr[0]);
            goto search_done;
        }
    }

initial_success:
    {
        s32 success_base;
        s32 success_offset;
        s32 success_address;

        success_base = (s32)D_8006CCD8_success;
        success_offset = direction << 1;
        success_address = success_base + success_offset;
        ASM_USE2_NV(initial_test, success_address);
        final_x = source->x + *(u16 *)success_address;
        final_y = source->y + D_8006CCE8[direction];
    }

allocate:
    scratch_t1 = *(u8 * volatile *)&arg0;
    object = func_8003FD64(0x100, scratch_t1 - 0x20);
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

    table_index = ((D_80083228 + context->f2A + 0x100) >> 8) & 0xE;
    input.x = D_801766F0[table_index];
    ASM_KEEP(context);
    angle_index = ((D_80083228 + context->f2A + 0x100) >> 8) & 0xE;
    input.y = D_801766F0[angle_index + 1];
    input.z = 0;
    func_8003E02C(&input, &transformed);

    object->position->x = position->x + transformed.x;
    object->position->y = position->y + transformed.y;
    object->position->z = position->z + transformed.z;
    func_80047784(display, 0x41, 0);
    func_8004491C(object, &D_80045340);

    object->field20 = &context->f2A;
    work->f20 = 8;
    work->x = final_x;
    work->y = final_y;
    work->hit = hit;
    work->flags = context->f14 & 0x2007;
    work->source_id = source->f12;
    ASM_SCHED_BARRIER();
    scratch_t1 = arg0;
    owner_byte = scratch_t1[0xAC];
    work->owner_minus20 = (u8 *)context - 0x20;
    work->context = context;
    work->owner_byte = owner_byte;

    counter = (u16 *)&D_80083460;
    counter[5]++;

exit:
    return;
}
