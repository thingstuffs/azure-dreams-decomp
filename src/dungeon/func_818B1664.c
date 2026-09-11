#include "common.h"
extern int abs(int);

typedef union FixedWord {
    s32 word;
    struct {
        u16 lo;
        s16 hi;
    } half;
} FixedWord;

typedef struct Motion {
    FixedWord x;
    FixedWord y;
    FixedWord z;
    FixedWord dx;
    FixedWord dy;
    FixedWord dz;
} Motion;

typedef struct WorkFrame {
    Motion target;
    s16 distance[3];
} WorkFrame;

typedef struct TargetInfo {
    u8 pad0[8];
    void *map;
    u8 padC[8];
    u16 flags;
    u8 pad16[14];
    u8 tileX;
    u8 tileY;
} TargetInfo;

typedef struct EntityHeader {
    u8 pad0[8];
    Motion *position;
    TargetInfo *info;
} EntityHeader;

typedef struct Child {
    u8 pad0[0x1C];
    u32 flags;
} Child;

typedef struct Entity {
    u8 pad0[0x2A];
    u16 flags2A;
    u8 pad2C[0x34];
    Child *child;
    u8 pad64[0x24];
    s16 height;
} Entity;

typedef struct EffectInner {
    u8 pad0[0xC];
    s32 value;
} EffectInner;

typedef struct Effect {
    u8 pad0[0xC];
    EffectInner *inner;
    u8 pad10[0xE];
    u16 flags;
} Effect;

typedef struct Resource {
    u16 flags;
} Resource;

typedef struct State {
    Entity *entity;
    Resource *resource;
    u8 pad8;
    u8 id;
    s16 state;
    u16 flags;
    s16 direction;
    s16 timer;
    s16 duration;
    s16 field14;
    s16 timer2;
    s16 angleStep;
    s16 angles[8];
    s16 pad2A;
    Effect *effects[10];
} State;

typedef struct DrawInfo {
    u8 pad0[0xC];
    s32 color;
} DrawInfo;

typedef struct LargeScalar {
    s32 value;
    s32 pad[2];
} LargeScalar;

extern void *D_80024028[10];
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern LargeScalar D_800814A0;
extern s32 D_8008346C[3];

extern void func_800240EC(u8 *, u8 *, DrawInfo *);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void func_8004491C(void *, void *);
extern void func_80024DF4(void);
extern s32 func_800A44E0(s32, s32, s32, s32);
extern s32 func_800BCB04(s32, s32, s32);
extern void func_800241F8(State *, Motion *);
extern void func_800A56E0(s32);
extern Effect *func_8002443C(State *, Motion *, s16, s16);
extern void func_80024050(void *, u8);

#ifdef NON_MATCHING
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3328; } while (0) ((v) = (s32)D_8006CCD8)
#define do { (v) = 0x80070000; ASM_KEEP(v); (v) -= 0x3318; } while (0) ((v) = (s32)D_8006CCE8)
#else
#define LOAD_TABLE_X_BASE(v) \
    do { (v) = 0x80070000;  (v) -= 0x3328; } while (0)
#define LOAD_TABLE_Y_BASE(v) \
    do { (v) = 0x80070000;  (v) -= 0x3318; } while (0)
#endif

/* Updates movement toward a child or terrain target and animates the associated effects. */
void func_80024E64(State *state_arg, Motion *motion_arg, DrawInfo *draw_info)
{
    WorkFrame work;
    volatile s16 saved_y;
    State *state = state_arg;
    Motion *motion = motion_arg;
    register DrawInfo *draw ASM_REG("$17") = draw_info;
    Entity *entity;
    register EntityHeader *header ASM_REG("$17");
    s32 dispatch_state;
    s32 direction;
    register s32 color ASM_REG("$3");
    u16 source_z;
    TargetInfo *target_info;
    Motion *source;
    register Motion *child_motion ASM_REG("$6");
    register u8 *angle_update ASM_REG("$5");
    u8 *angle_clear;
    u8 *angle_build;
    u8 *effect_clear;
    register Effect **effect_create ASM_REG("$18");
    Effect **effect_grow;
    Effect **effect_shrink;
    register Effect **effect_cleanup ASM_REG("$5");
    s32 index;
    register s32 child_delta ASM_REG("$2");
    register s32 motion_coord ASM_REG("$3");
    s32 next_state;
    s32 angle;
    s32 effect_angle;
    s32 effect_step;
    s32 collision_result;
    s32 terrain_height;
    Motion *target;
    s16 *target_cursor;
    s16 *distance_cursor;
    register s32 target_x ASM_REG("$5");
    register s32 target_y ASM_REG("$4");
    s32 target_z;
    u16 angle_raw;
    s32 angle_signed;
    s32 angle_adjusted;
    u16 lowered_z;
    register s16 *direction_table ASM_REG("$3");
    s32 direction_index;
    s32 axis_step;
    register s32 table_addr ASM_REG("$8");
    s32 table_offset;
    s32 update_offset;
    s16 *step_x;
    s16 *step_y;
    u16 *update_x;
    register u16 *update_y ASM_REG("$3");
    register s32 probe_height ASM_REG("$6");
    register s32 next_x ASM_REG("$4");
    s32 next_y;
    u32 table_page;
    register s32 tile_x ASM_REG("$20");
    register s32 tile_y ASM_REG("$21");
    s16 grid_x;
    s16 grid_y;
    s32 final_x;

    static void *const keepalive[] = {
        &&case_0, &&case_2, &&case_3, &&case_4,
        &&case_5, &&case_6, &&case_7, &&case_8, &&case_9
    };

    index = 7;
    angle_update = (u8 *)state + 14;
    ASM_KEEP(state);
    ASM_KEEP(motion);
    entity = state->entity;
    do {
        angle_raw = *(u16 *)(angle_update + 26) + (u16)state->angleStep;
        angle_signed = (s16)angle_raw;
        angle_adjusted = angle_signed;
        *(u16 *)(angle_update + 26) = angle_raw;
        angle_raw = angle_signed - (((angle_adjusted / 128)) << 7);
        *(u16 *)(angle_update + 26) = angle_raw;
        index--;
        angle_update -= 2;
    } while (index >= 0);
    {
        register u16 timer_value ASM_REG("$2");

        timer_value = (u16)state->timer;
        timer_value++;
        state->timer = timer_value;
        timer_value = (u16)state->timer2;
        dispatch_state = state->state;
        timer_value++;
        state->timer2 = timer_value;
    }

    if ((u32)dispatch_state >= 10) {
        goto end;
    }
    goto *D_80024028[dispatch_state];

case_0:
    state->timer = 0;
    state->timer2 = 0;
    state->angleStep = 4;
    state->state++;
    index = 7;
    angle_clear = (u8 *)state + 14;
    do {
        *(s16 *)(angle_clear + 26) = 0;
        index--;
        angle_clear -= 2;
    } while (index >= 0);
    index = 9;
    effect_clear = (u8 *)state + 36;
    do {
        *(Effect **)(effect_clear + 44) = 0;
        index--;
        effect_clear -= 4;
    } while (index >= 0);
    func_800240EC(angle_clear, angle_update, draw_info);
    color = 0x00808080;
    direction = (entity->flags2A >> 9) & 7;
    state->direction = direction;
    draw->color = color;

    header = (EntityHeader *)((u8 *)entity - 0x20);
    target_info = header->info;
    if (func_8003DE58(target_info->map, target_info, work.distance, 0) == 0) {
        if (!(header->info->flags & 0x8000)) {
            goto end;
        }
    }

    source = header->position;
    motion->x.half.hi = source->x.half.hi;
    motion->y.half.hi = source->y.half.hi;
    source_z = source->z.half.hi;
    motion->z.half.hi = source_z;
    if (!(header->info->flags & 0x8000)) {
        motion->x.half.hi += work.distance[0];
        motion->y.half.hi += work.distance[1];
        motion->z.half.hi += work.distance[2];
    } else {
        lowered_z = source_z - 64;
        motion->z.half.hi = lowered_z;
    }

    if (!(state->flags & 1)) {
        func_8004491C((u8 *)state - 0x20, func_80024DF4);
        state->flags |= 1;
    }
    if (!(state->resource->flags & 0x80)) {
        goto end;
    }

    index = 0;
    if (entity->child != 0) {
        child_motion = *(Motion **)((u8 *)entity->child - 0x18);

        motion_coord = motion->x.half.hi;
        child_delta = child_motion->x.half.hi;
        child_delta -= motion_coord;
        child_delta = abs(child_delta);
        work.distance[0] = child_delta;

        child_delta = child_motion->y.half.hi;
        motion_coord = motion->y.half.hi;
        child_delta -= motion_coord;
        child_delta = abs(child_delta);
        work.distance[1] = child_delta;

        if (entity->child->flags & 0x40000) {
            motion_coord = motion->z.half.hi - 16;
            child_delta = child_motion->z.half.hi;
            child_delta -= motion_coord;
        } else {
            child_delta = child_motion->z.half.hi;
            motion_coord = motion->z.half.hi;
            child_delta -= motion_coord;
        }
        child_delta = abs(child_delta);
        work.distance[2] = child_delta;
        ASM_SCHED_BARRIER();
        index = 1;

        state->duration = work.distance[0];
        distance_cursor = &work.target.x.half.hi;
        do {
            if (distance_cursor[12] > state->duration) {
                state->duration = (u16)distance_cursor[12];
            }
            index++;
            distance_cursor++;
        } while (index < 3);
        state->duration >>= 5;
        if (state->duration == 0) {
            state->duration = 1;
        }

        motion->dx.half.hi =
            (child_motion->x.half.hi - motion->x.half.hi) / state->duration;
        motion->dy.half.hi =
            (child_motion->y.half.hi - motion->y.half.hi) / state->duration;
        if (entity->child->flags & 0x40000) {
            motion_coord = motion->z.half.hi;
            child_delta = child_motion->z.half.hi;
            motion_coord -= 16;
            child_delta -= motion_coord;
            motion->dz.half.hi = child_delta / state->duration;
        } else {
            motion->dz.half.hi =
                (child_motion->z.half.hi - motion->z.half.hi) /
                state->duration;
        }
        next_state = (u16)state->state + 1;
        goto reset_state;
    }

    {
        TargetInfo *tile_info;

        tile_info = header->info;
        ASM_SCHED_BARRIER();
        table_page = 0x80070000;
        ASM_KEEP(table_page);
        tile_x = tile_info->tileX;
        ASM_SCHED_BARRIER();
        tile_y = tile_info->tileY;
    }
    final_x = tile_x;
    saved_y = tile_y;

    while (index < 8) {
        grid_x = (s16)tile_x;
        grid_y = (s16)tile_y;
        collision_result = func_800A44E0(
            (grid_x << 6) & 0xFFC0,
            (grid_y << 6) & 0xFFC0,
            entity->height,
            (s16)(state->direction << 9));
        if ((s16)collision_result != 0) {
            break;
        }

        (table_addr) = 0x80070000; ASM_KEEP(table_addr); (table_addr) -= 0x3328;
        table_offset = (s16)state->direction;
        probe_height = (u16)entity->height;
        table_offset *= 2;
        step_x = (s16 *)(table_offset + table_addr);
        ASM_KEEP(step_x);
        probe_height -= 32;
        probe_height = (s16)probe_height;
        (table_addr) = 0x80070000; ASM_KEEP(table_addr); (table_addr) -= 0x3318;
        step_y = (s16 *)(table_offset + table_addr);
        ASM_KEEP(step_y);
        terrain_height = func_800BCB04(
            ((grid_x + *step_x) << 6) + 32 & 0xFFE0,
            ((grid_y + *step_y) << 6) + 32 & 0xFFE0,
            probe_height);
        if ((s16)terrain_height >= 513 ||
            (s16)(terrain_height - entity->height) < -63) {
            break;
        }

        (table_addr) = 0x80070000; ASM_KEEP(table_addr); (table_addr) -= 0x3328;
        update_offset = (s16)state->direction;
        index++;
        update_offset *= 2;
        update_x = (u16 *)(update_offset + table_addr);
        (table_addr) = 0x80070000; ASM_KEEP(table_addr); (table_addr) -= 0x3318;
        update_y = (u16 *)(update_offset + table_addr);
        ASM_KEEP(update_y);
        next_x = tile_x + *update_x;
        tile_x = next_x;
        next_y = tile_y + *update_y;
        tile_y = next_y;
        saved_y = next_y;
        ASM_KEEP4_NV(next_x, next_y, tile_x, tile_y);
        final_x = next_x;
    }

    target = &work.target;
    ASM_KEEP_NV(target);
    index = 1;
    ASM_KEEP_NV(index);
    target_x = (u32)final_x << 16;
    direction_table = D_8006CCD8;
    target_x = (s32)target_x >> 10;
    direction_index = (s16)state->direction;
    ASM_KEEP(direction_index);
    target_cursor = &work.target.x.half.hi;
    axis_step = direction_table[direction_index];
    direction_table = D_8006CCE8;
    target_x = target_x + ((axis_step + 1) << 5);
    target->x.half.hi = target_x;
    target_x = (s16)target_x;
    table_addr = (u16)saved_y;
    direction_index = (s16)state->direction;
    ASM_KEEP_DEP_NV(table_addr, direction_index);
    target_y = (u32)(u16)table_addr << 16;
    axis_step = direction_table[direction_index];
    target_y = (s32)target_y >> 10;
    target_y += (axis_step + 1) << 5;
    target->y.half.hi = target_y;
    target_y = (u32)target_y << 16;
    target_z = (u16)motion->z.half.hi + 32;
    target->z.half.hi = target_z;

    {
        s32 source_coord;

        source_coord = motion->x.half.hi;
        ASM_SCHED_BARRIER();
        target_y = (s32)target_y >> 16;
        ASM_SCHED_BARRIER();
        target_x -= source_coord;
        if (target_x < 0) {
            target_x = -target_x;
        }
        work.distance[0] = target_x;

        source_coord = motion->y.half.hi;
        target_z = (u32)target_z << 16;
        target_y -= source_coord;
        target_y = abs(target_y);
        work.distance[1] = target_y;

        source_coord = motion->z.half.hi;
        target_z = (s32)target_z >> 16;
        target_z -= source_coord;
        target_z = abs(target_z);
        work.distance[2] = target_z;
    }

    state->duration = work.distance[0];
    do {
        if (target_cursor[12] > state->duration) {
            state->duration = (u16)target_cursor[12];
        }
        index++;
        target_cursor++;
    } while (index < 3);
    state->duration >>= 5;
    if (state->duration == 0) {
        state->duration = 1;
    }
    motion->dx.word = (target->x.word - motion->x.word) / state->duration;
    motion->dy.word = (target->y.word - motion->y.word) / state->duration;
    motion->dz.word = (target->z.word - motion->z.word) / state->duration;
    ASM_SCHED_BARRIER();
    next_state = 8;
    goto reset_state;

case_2:
    motion->x.half.hi += motion->dx.half.hi;
    motion->y.half.hi += motion->dy.half.hi;
    motion->z.half.hi += motion->dz.half.hi;
    func_800241F8(state, motion);
    if (state->timer < state->duration) {
        goto end;
    }
    func_800A56E0(0x300);
    goto increment_reset;

case_3:
    if (state->timer < 8) {
        goto end;
    }
    state->timer = 0;
    state->timer2 = 0;
    state->state++;
    child_motion = *(Motion **)((u8 *)entity->child - 0x18);
    motion->x.half.hi = child_motion->x.half.hi;
    motion->y.half.hi = child_motion->y.half.hi;
    if (entity->child->flags & 0x40000) {
        motion->z.half.hi = child_motion->z.half.hi + 16;
    } else {
        motion->z.half.hi = child_motion->z.half.hi;
    }

    index = 7;
    angle = 16;
    angle_build = (u8 *)state + 14;
    do {
        *(s16 *)(angle_build + 26) = angle;
        angle += 16;
        index--;
        angle_build -= 2;
    } while (index > 0);
    state->angles[0] = 0;

    index = 9;
    effect_create = (Effect **)((u8 *)state + 36);
    effect_angle = (s32)0xFF1F0000;
    do {
        effect_create[11] =
            func_8002443C(state, motion, effect_angle >> 16, index);
        effect_create--;
        effect_step = 0x190000;
        ASM_KEEP(effect_step);
        index--;
        effect_angle += effect_step;
    } while (index >= 0);
    state->field14 = 0;
    goto epilogue;

case_4: {
    Effect *effect;
    EffectInner *inner;
    s32 effect_delta;

    index = 9;
    effect_delta = 0x40404;
    effect_grow = (Effect **)((u8 *)state + 36);
    do {
        effect = effect_grow[11];
        inner = effect->inner;
        inner->value += effect_delta;
        effect_grow--;
        index--;
    } while (index >= 0);
    if (state->timer2 < 32) {
        goto end;
    }
    next_state = (u16)state->state;
    state->timer2 = 0;
    goto increment_state;
}

case_5:
    if (state->timer2 < 32) {
        goto end;
    }
    next_state = (u16)state->state;
    state->timer2 = 0;
    goto increment_state;

case_6: {
    Effect *effect;
    EffectInner *inner;
    Effect *cleanup_effect;
    register void *cleanup_base ASM_REG("$6");
    register u16 cleanup_flags ASM_REG("$2");
    s32 global_flags;
    s32 effect_delta;

    index = 9;
    effect_delta = -0x40404;
    effect_shrink = (Effect **)((u8 *)state + 36);
    do {
        effect = effect_shrink[11];
        inner = effect->inner;
        inner->value += effect_delta;
        effect_shrink--;
        index--;
    } while (index >= 0);
    if (state->timer2 < 32) {
        goto end;
    }
    cleanup_base = entity;
    ASM_KEEP(cleanup_base);
    func_80024050(((Entity *)cleanup_base)->child, state->id);
    index = 9;
    cleanup_base = (void *)0x80080000;
    next_state = (u16)state->state;
    effect_cleanup = (Effect **)((u8 *)state + 36);
    state->timer2 = 0;
    next_state++;
    state->state = next_state;
    do {
        cleanup_effect = effect_cleanup[11];
        if (cleanup_effect != 0) {
            cleanup_flags = cleanup_effect->flags;
            global_flags = *(s32 *)((u8 *)cleanup_base + 0x14A0);
            cleanup_flags |= 0x8000;
            global_flags |= 0x8000;
            cleanup_effect->flags = cleanup_flags;
            *(s32 *)((u8 *)cleanup_base + 0x14A0) = global_flags;
            effect_cleanup[11] = 0;
        }
        effect_cleanup--;
        index--;
    } while (index >= 0);
    state->field14 = 0;
    goto epilogue;
}

case_7:
    if (state->field14 != 0) {
        goto end;
    }
    D_8008346C[0] = 0;
    *(u16 *)((u8 *)state - 2) |= 0x8000;
    D_800814A0.value |= 0x8000;
    goto end;

case_8:
    motion->x.half.hi += motion->dx.half.hi;
    motion->y.half.hi += motion->dy.half.hi;
    motion->z.half.hi += motion->dz.half.hi;
    func_800241F8(state, motion);
    if (state->timer < state->duration) {
        goto end;
    }

increment_reset:
    next_state = (u16)state->state;
    state->timer = 0;
    state->timer2 = 0;
increment_state:
    next_state++;
    state->state = next_state;
    goto end;

case_9:
    if (state->timer < 8) {
        goto end;
    }
    next_state = 7;
    goto reset_state;

reset_state:
    state->state = next_state;
    state->timer = 0;
    state->timer2 = 0;

end:
    state->field14 = 0;
epilogue:
    return;
}
