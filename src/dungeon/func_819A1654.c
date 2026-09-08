#include "common.h"

typedef struct Coord {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} Coord;

typedef struct Sprite {
    u8 pad0[6];
    s16 field6;
    void *data;
    u8 r;
    u8 g;
    u8 b;
    u8 padF;
    s16 field10;
    u8 pad12[2];
    u16 flags;
    s16 field16;
    s16 field18;
    s16 field1A;
    s16 field1C;
    s16 field1E;
} Sprite;

typedef struct Effect {
    u8 pad0[0xC];
    s32 value0C;
    s32 value10;
    s32 value14;
    s32 value18;
    s32 value1C;
    s32 value20;
    s32 value24;
    s32 value28;
    u8 pad2C[0xE];
    s16 timer3A;
    s16 timer3C;
    s16 mode3E;
    s16 random40;
    u8 pad42[0x12];
    s16 path[18];
} Effect;

typedef struct Task {
    u8 pad0[8];
    Coord *coord;
    Sprite *sprite;
    void (*callback)(void);
    u8 pad14[0xC];
    Effect effect;
    u8 pad98[0x12];
    u8 data[24];
} Task;

typedef struct Entity {
    u8 pad0[4];
    u16 *header;
    u8 type;
    u8 pad9;
    s16 state;
    u8 padC[0x20];
    s16 x;
    s16 y;
    s16 z;
    s16 timer;
    u8 pad34[2];
    s16 point_index;
    u8 pad38[2];
    u16 age;
    u8 pad3C[0x18];
    s16 path[24];
    s16 base[3];
} Entity;

typedef struct World {
    u8 pad0[0x2A];
    u16 angle;
    u8 pad2C[0x34];
    void *focus;
    u8 pad64[0x32];
    s16 field96;
    u8 pad98[0xE];
    u16 fieldA6;
    u8 fieldA8;
    u8 padA9[0x4B];
    s32 fieldF4;
} World;

typedef struct GlobalState {
    s32 flags;
    s32 pad4;
    World *world;
} GlobalState;

typedef struct LookupGlobal {
    u8 pad0[6];
    s16 field6;
    void *found;
    u8 padC[8];
    u16 flags;
} LookupGlobal;

typedef struct ControlGlobal {
    u8 pad0[0xA];
    u16 count;
    s32 active;
} ControlGlobal;

typedef struct Point {
    s16 x;
    u16 y;
} Point;

typedef struct PointTable {
    Point point[8];
} PointTable;

typedef struct Blob12 {
    u8 bytes[12];
} __attribute__((packed)) Blob12;

typedef struct Blob8 {
    u8 bytes[8];
} __attribute__((packed)) Blob8;

typedef struct Blob24 {
    u8 bytes[24];
} __attribute__((packed)) Blob24;

extern GlobalState D_800814A0[];
extern World *D_800814A8[];
extern LookupGlobal D_80082E80[];
extern s16 D_80082E86[6];
extern u16 D_80082E94[6];
extern Coord D_80083780[];
extern ControlGlobal D_80083460[];
extern s16 D_800261B0[6];
extern u8 D_800DDC40[];
extern PointTable D_80024054[];
extern Blob12 D_80026180[];
extern Blob12 D_8002618C[];
extern Blob24 D_80026198[];
extern void *D_80024078[];

extern Task *func_8003FC64(s32);
extern s32 func_8003DF74(void *, void *, void *, s32);
extern void func_8004491C(Task *, void (*)(void));
extern s32 func_80069EF8(void);
extern s32 func_80053EF0(s32);
extern void func_800A56E0(s32);
extern void D_80024C50(Entity *, void *, void *, s32, s32, s32);
extern void func_8002614C(void) __attribute__((noreturn));

extern void func_80024B3C(void);
extern void func_80024BD0(void);
extern void func_80024564(void);
extern void func_800245B8(void);
extern void func_80024834(void);
extern void func_80024918(void);
extern void func_80045340(void);

#define COPY_BLOB12(dst, symbol, low) do { \
    copy_page = (u8 *)0x80020000; \
    ASM_KEEP(copy_page); \
    copy_source = copy_page + (low); \
    ASM_KEEP(copy_source); \
    *(Blob12 *)(dst) = *(Blob12 *)copy_source; \
    ASM_KEEP(copy_page); \
} while (0)

void func_80024E54(Entity *arg0, void *arg1, void *arg2) {
    PointTable points;
    Entity *e = arg0;
    void *saved_arg1 = arg1;
    void *saved_arg2 = arg2;
    register Task *task ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register Effect *effect ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register Sprite *sprite ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    Coord *coord;
    Coord *origin0;
    Coord *origin_loop;
    Coord *origin_second;
    Coord *origin_path;
    register u8 *copy_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *copy_source ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register LookupGlobal *lookup ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    World *world;
    void *focus;
    Coord *focus_coord;
    s32 i;
    s32 index;
    s32 second_index;
    s32 four;
    s32 value;
    s32 delta;
    s32 vx;
    s32 vy;
    s32 vz;
    s16 saved_timer;
    s16 saved_timer2;
    void (*loop_callback)(void);

    copy_page = (u8 *)0x80020000;
    ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(e);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    copy_source = copy_page + 0x4054;
    ASM_KEEP(copy_source);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *(Blob12 *)&points = *(Blob12 *)copy_source;
    *(Blob12 *)((u8 *)&points + 12) = *(Blob12 *)(copy_source + 12);
    *(Blob8 *)((u8 *)&points + 24) = *(Blob8 *)(copy_source + 24);
    ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    e->age++;

    {
        static void *const switch_keepalive[] = {
            &&case_0, &&case_1, &&case_2, &&switch_end, &&case_4
        };
        s32 dispatch_state;
        dispatch_state = e->state;
        if ((u32)dispatch_state >= 5) {
            goto switch_end;
        }
        goto *D_80024078[dispatch_state];

    case_0: {
        World *world0;
        World *hit_world;
        world0 = D_800814A8[0];
        world0->fieldF4 = 0;
        world0->field96 = 20;
        D_80082E86[0] = 6;
        e->state++;
        origin0 = &D_80083780[0];
        {
            Blob24 *flag_base = D_80026198;
            e->base[0] = origin0->x;
            e->base[1] = origin0->y;
            e->base[2] = origin0->z;
            *(s16 *)(flag_base->bytes + 24) = 1;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        if ((*e->header & 0x80) != 0) {
            register u8 *hit_world_page ASM_REG("$4") = (u8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
            s16 next_state;
            u16 angle;
            hit_world = *(World **)(hit_world_page + 0x14A8);
            e->timer = 33;
            hit_world->fieldA6--;
            hit_world->fieldA8 = e->type;
            hit_world = *(World **)(hit_world_page + 0x14A8);
            next_state = e->state;
            angle = hit_world->angle;
            e->state = next_state + 1;
            e->age = 0;
            e->point_index = (angle >> 9) & 7;
            return func_8002614C();
        }
        goto switch_end;
    }

    case_1:
        e->timer--;
        if (e->timer <= 0) {
            e->timer = 16;
            e->state++;
            return func_8002614C();
        }

        if (e->timer == 18) {
            i = func_80053EF0(4);
            value = 0x4300;
            if (i != 2) {
                value = 0x300;
            }
            func_800A56E0(value);
        }

        if (e->timer == 24) {
            lookup = &D_80082E80[0];
            if (func_8003DF74(lookup->found, lookup, &e->x, 0) != 0) {
                u8 *origin_loop_page;
                i = 0;
                loop_callback = func_80024B3C;
                ASM_KEEP(loop_callback);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                origin_loop_page = (u8 *)0x80080000;
                ASM_KEEP(origin_loop_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                origin_loop = (Coord *)(origin_loop_page + 0x3780);
                do {
                    task = func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        effect->random40 = (s16)((func_80069EF8() & 0xFF) + 200);
                        task->callback = loop_callback;
                        func_8004491C(task, func_80045340);
                        sprite = task->sprite;
                        sprite->field10 = 32;
                        sprite->flags |= 0xC;
                        coord = task->coord;
                        coord->x = e->x + origin_loop->x;
                        coord->y = e->y + origin_loop->y;
                        coord->z = e->z + origin_loop->z;
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                        {
                            s32 color = 0x80;
                            ASM_KEEP(color);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                            sprite->b = color;
                            sprite->g = color;
                            sprite->r = color;
                        }
                        sprite->field16 = (func_80069EF8() & 0xF) << 8;
                        sprite->field18 = (func_80069EF8() & 0xF) << 8;
                        sprite->field1A = (func_80069EF8() & 0xF) << 8;
                        COPY_BLOB12(task->data, D_80026180, 0x6180);
                        sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    }
                    ASM_KEEP(saved_arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    i++;
                } while (i < 10);
            }
        }

        if (e->timer == 24) {
            lookup = &D_80082E80[0];
            if (func_8003DF74(lookup->found, lookup, &e->x, 0) != 0) {
                task = func_8003FC64(0x212);
                effect = &task->effect;
                if (task != 0) {
                    s32 second_size;
                    u16 second_flags;
                    effect->timer3A = 20;
                    effect->timer3C = 20;
                    task->callback = func_80024BD0;
                    func_8004491C(task, func_80045340);
                    second_size = 96;
                    sprite = task->sprite;
                    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    origin_second = (Coord *)0x80080000;
                    ASM_KEEP(origin_second);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                    second_flags = sprite->flags;
                    origin_second = (Coord *)((u8 *)origin_second + 0x3780);
                    sprite->field10 = second_size;
                    sprite->flags = second_flags | 0xC;
                    coord = task->coord;
                    coord->x = e->x + origin_second->x;
                    coord->y = e->y + origin_second->y;
                    coord->z = e->z + origin_second->z;
                    sprite = task->sprite;
                    sprite->field1E = 0x1000;
                    sprite->field1C = 0x1000;
                    sprite->b = 0x80;
                    sprite->g = 0x80;
                    sprite->r = 0x80;
                    COPY_BLOB12(task->data, D_8002618C, 0x618C);
                    sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                }
            }
        }

        if (e->timer < 10) {
          if (e->timer < 6) {
            if (e->timer != 3) {
            s32 two;
            index = e->timer == 4;
            two = 2;
            four = 4;
            if (e->timer == two) {
                index = two;
            }
            if (e->timer == 1) {
                index = 3;
            }

            lookup = &D_80082E80[0];
            if (func_8003DF74(lookup->found, lookup, &e->x, 0) != 0) {
                s32 path_index2;
                register Entity *path_entity ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                register s32 path_half ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                register s32 path_saved_base ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                u8 *origin_path_page;
                path_index2 = index * 2;
                path_entity = (Entity *)((u8 *)e + (path_index2 + index) * 4);
                path_index2++;
                {
                    u32 path_bits;
                    path_bits = (u16)e->x;
                    path_saved_base = e->base[0];
                    path_bits <<= 16;
                    path_half = (s32)path_bits >> 16;
                    path_half += path_bits >> 31;
                }
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                origin_path_page = (u8 *)0x80080000;
                ASM_KEEP(origin_path_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                origin_path = (Coord *)(origin_path_page + 0x3780);
                path_half >>= 1;
                path_entity->path[0] = path_half + (origin_path->x - path_saved_base) / 2;
                path_entity->path[1] = e->y / 2 + (origin_path->y - e->base[1]) / 2;
                {
                    register u32 path_z_work ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    path_z_work = (u16)e->z;
                    path_half = e->base[2];
                    path_z_work <<= 16;
                    path_saved_base = (s32)path_z_work >> 16;
                    path_z_work >>= 31;
                    path_saved_base += path_z_work;
                    ASM_USE2(path_saved_base, path_z_work);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    path_z_work = (s32)origin_path->z - path_half;
                    path_saved_base >>= 1;
                    path_z_work = (s32)path_z_work / 2;
                    path_saved_base += (s32)path_z_work;
                    path_z_work = (path_index2 * 3) * 2;
                    path_entity->path[2] = path_saved_base;
                    path_entity = (Entity *)((u8 *)e + path_z_work);
                }
                path_entity->path[0] = e->x / 4 + (origin_path->x - e->base[0]) / 2;
                path_entity->path[1] = e->y / 4 + (origin_path->y - e->base[1]) / 2;
                path_entity->path[2] = e->z / 4 + (origin_path->z - e->base[2]) / 2;

                if (e->timer == four) {
                    task = func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        task->callback = func_80024834;
                        func_8004491C(task, func_80024564);
                        sprite = task->sprite;
                        sprite->field10 = 32;
                        sprite->flags |= 0xC;
                        effect->path[0] = e->path[6];
                        effect->path[1] = e->path[7];
                        effect->path[2] = e->path[8];
                        effect->path[3] = e->path[0];
                        effect->path[4] = e->path[1];
                        effect->path[5] = e->path[2];
                        effect->path[6] = e->path[9];
                        effect->path[7] = e->path[10];
                        effect->path[8] = e->path[11];
                        effect->path[9] = e->path[3];
                        effect->path[10] = e->path[4];
                        effect->path[11] = e->path[5];
                        coord = task->coord;
                        coord->x = e->base[0];
                        coord->y = e->base[1];
                        coord->z = e->base[2];
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        COPY_BLOB12(task->data, D_8002618C, 0x618C);
                        sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    }
                }

                if (e->timer == 2) {
                    task = func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        s32 c1;
                        register s32 c2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        c1 = 0x804020;
                        c2 = 0x201008;
                        effect->value1C = c1;
                        effect->value24 = c2;
                        effect->value28 = c2;
                        effect->value20 = c1;
                        effect->value0C = effect->value1C;
                        effect->value10 = effect->value20;
                        effect->value14 = effect->value24;
                        effect->value18 = effect->value28;
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        task->callback = func_80024834;
                        func_8004491C(task, func_80024564);
                        sprite = task->sprite;
                        sprite->field10 = 32;
                        sprite->flags |= 0xC;
                        effect->path[0] = e->path[12];
                        effect->path[1] = e->path[13];
                        effect->path[2] = e->path[14];
                        effect->path[3] = e->path[6];
                        effect->path[4] = e->path[7];
                        effect->path[5] = e->path[8];
                        effect->path[6] = e->path[15];
                        effect->path[7] = e->path[16];
                        effect->path[8] = e->path[17];
                        effect->path[9] = e->path[9];
                        effect->path[10] = e->path[10];
                        effect->path[11] = e->path[11];
                        coord = task->coord;
                        coord->x = e->base[0];
                        coord->y = e->base[1];
                        coord->z = e->base[2];
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        COPY_BLOB12(task->data, D_8002618C, 0x618C);
                        sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    }
                }

                saved_timer = e->timer;
                if (saved_timer == 1) {
                    task = func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        s32 c1;
                        register s32 c2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                        c1 = 0x804020;
                        c2 = 0x201008;
                        effect->value1C = c1;
                        effect->value24 = c2;
                        effect->value28 = c2;
                        effect->value20 = c1;
                        effect->value0C = effect->value1C;
                        effect->value10 = effect->value20;
                        effect->value14 = effect->value24;
                        effect->value18 = effect->value28;
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        task->callback = func_80024834;
                        func_8004491C(task, func_80024564);
                        sprite = task->sprite;
                        sprite->field10 = 32;
                        sprite->flags |= 0xC;
                        effect->path[0] = e->path[18];
                        effect->path[1] = e->path[19];
                        effect->path[2] = e->path[20];
                        effect->path[3] = e->path[12];
                        effect->path[4] = e->path[13];
                        effect->path[5] = e->path[14];
                        effect->path[6] = e->path[21];
                        effect->path[7] = e->path[22];
                        effect->path[8] = e->path[23];
                        effect->path[9] = e->path[15];
                        effect->path[10] = e->path[16];
                        effect->path[11] = e->path[17];
                        coord = task->coord;
                        coord->x = e->base[0];
                        coord->y = e->base[1];
                        coord->z = e->base[2];
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        COPY_BLOB12(task->data, D_8002618C, 0x618C);
                        sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                    }

                    saved_timer2 = e->timer;
                    if (saved_timer2 == saved_timer) {
                        task = func_8003FC64(0x212);
                        effect = &task->effect;
                        if (task != 0) {
                            effect->timer3A = 20;
                            effect->timer3C = 20;
                            effect->value1C = 0x10000;
                            effect->value24 = 0x804020;
                            effect->value28 = 0x804020;
                            effect->value20 = 0x10000;
                            effect->mode3E = 2;
                            effect->value0C = effect->value1C;
                            effect->value10 = effect->value20;
                            effect->value14 = effect->value24;
                            effect->value18 = effect->value28;
                            task->callback = func_80024918;
                            func_8004491C(task, func_80024564);
                            sprite = task->sprite;
                            sprite->field10 = 32;
                            sprite->flags |= 0xC;
                            effect->path[0] = e->path[12];
                            effect->path[1] = e->path[13];
                            effect->path[2] = e->path[14];
                            effect->path[3] = e->path[6];
                            effect->path[4] = e->path[7];
                            effect->path[5] = e->path[8];
                            effect->path[6] = e->path[12];
                            effect->path[7] = e->path[13];
                            effect->path[8] = e->path[14];
                            effect->path[9] = e->path[6];
                            effect->path[10] = e->path[7];
                            effect->path[11] = e->path[8];
                            effect->path[12] = points.point[e->point_index].x * 8;
                            effect->path[13] = points.point[e->point_index].y * 8;
                            effect->path[14] = 0;
                            effect->path[15] = points.point[e->point_index].x * 8;
                            effect->path[16] = points.point[e->point_index].y * 8;
                            effect->path[17] = 0;
                            coord = task->coord;
                            coord->x = e->base[0];
                            coord->y = e->base[1];
                            coord->z = e->base[2];
                            sprite = task->sprite;
                            sprite->field1E = 0x1000;
                            sprite->field1C = 0x1000;
                            sprite->b = 0x80;
                            sprite->g = 0x80;
                            sprite->r = 0x80;
                            COPY_BLOB12(task->data, D_8002618C, 0x618C);
                            sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                        }

                        saved_timer = e->timer;
                        if (saved_timer == saved_timer2) {
                            task = func_8003FC64(0x212);
                            effect = &task->effect;
                            if (task != 0) {
                                effect->timer3A = 20;
                                effect->timer3C = 20;
                                effect->value1C = 0x10000;
                                effect->value24 = 0x804020;
                                effect->value28 = 0x804020;
                                effect->value20 = 0x10000;
                                effect->mode3E = 2;
                                effect->value0C = effect->value1C;
                                effect->value10 = effect->value20;
                                effect->value14 = effect->value24;
                                effect->value18 = effect->value28;
                                task->callback = func_80024918;
                                func_8004491C(task, func_80024564);
                                sprite = task->sprite;
                                sprite->field10 = 32;
                                sprite->flags |= 0xC;
                                effect->path[0] = e->path[18];
                                effect->path[1] = e->path[19];
                                effect->path[2] = e->path[20];
                                effect->path[3] = e->path[12];
                                effect->path[4] = e->path[13];
                                effect->path[5] = e->path[14];
                                effect->path[6] = e->path[18];
                                effect->path[7] = e->path[19];
                                effect->path[8] = e->path[20];
                                effect->path[9] = e->path[12];
                                effect->path[10] = e->path[13];
                                effect->path[11] = e->path[14];
                                effect->path[12] = points.point[e->point_index].x * 8;
                                effect->path[13] = points.point[e->point_index].y * 8;
                                effect->path[14] = 0;
                                effect->path[15] = points.point[e->point_index].x * 8;
                                effect->path[16] = points.point[e->point_index].y * 8;
                                effect->path[17] = 0;
                                coord = task->coord;
                                coord->x = e->base[0];
                                coord->y = e->base[1];
                                coord->z = e->base[2];
                                sprite = task->sprite;
                                sprite->field1E = 0x1000;
                                sprite->field1C = 0x1000;
                                sprite->b = 0x80;
                                sprite->g = 0x80;
                                sprite->r = 0x80;
                                COPY_BLOB12(task->data, D_8002618C, 0x618C);
                                sprite->data = task->data;
        ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                            }

                            if (e->timer == saved_timer) {
                                register s32 interp_i ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                                register s32 interp_delta ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                                s32 interp_x;
                                register s32 interp_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                                s32 interp_z;
                                s32 interp_base;
                                register s32 interp_work ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                                register s32 out_x ASM_REG("$7");
                                interp_i = 0;
                                do {
                                    interp_base = e->path[18];
                                    interp_work = e->path[6] - interp_base;
                                    interp_delta = interp_i * 2;
                                    interp_x = interp_work * interp_delta;
                                    if (interp_x < 0) {
                                        interp_x += 15;
                                    }
                                    out_x = interp_base * 2;
                                    interp_base = e->path[19];
                                    interp_work = e->path[7] - interp_base;
                                    interp_y = interp_work * interp_delta;
                                    interp_work = interp_x >> 4;
                                    out_x += interp_work;
                                    interp_x = interp_base * 2;
                                    if (interp_y < 0) {
                                        interp_y += 15;
                                    }
                                    interp_base = e->path[20];
                                    interp_work = e->path[8] - interp_base;
                                    interp_z = interp_work * interp_delta;
                                    interp_work = interp_y >> 4;
                                    interp_work = interp_x + interp_work;
                                    interp_base = interp_base * 2;
                                    if (interp_z < 0) {
                                        interp_z += 15;
                                    }
                                    {
                                        Entity *call_e = e;
                                        void *call_arg1 = saved_arg1;
                                        void *call_arg2 = saved_arg2;
                                        ASM_KEEP4(call_e, call_arg1, call_arg2, out_x);
                                        out_x = (s16)out_x;
                                        interp_work = (s16)interp_work;
                                        D_80024C50(call_e, call_arg1, call_arg2,
                                            out_x, interp_work,
                                            (s16)({
                                                s32 arg6;
                                                arg6 = interp_base + (interp_z >> 4);
                                                arg6;
                                            }));
                                    }
                                    interp_i++;
                                } while (interp_i < 16);
                            }
                        }
                    }
                }
            }
            }
          }
        }

        world = D_800814A8[0];
        focus = world->focus;
        if (focus != 0 && e->timer == 1) {
            task = func_8003FC64(0x212);
            effect = &task->effect;
            if (task != 0) {
                register u8 *focus_data ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                effect->timer3A = 13;
                effect->timer3C = 13;
                task->callback = func_800245B8;
                func_8004491C(task, func_80045340);
                sprite = task->sprite;
                sprite->field6 = 6;
                sprite->flags &= 0xFFF3;
                focus_coord = *(Coord **)((u8 *)focus - 24);
                coord = task->coord;
                coord->x = focus_coord->x;
                coord->y = focus_coord->y;
                coord->z = focus_coord->z - (D_800DDC40[*((u8 *)focus + 19)] >> 1);
                sprite = task->sprite;
                sprite->field1E = 0x1000;
                sprite->field1C = 0x1000;
                sprite->b = 0x80;
                sprite->g = 0x80;
                sprite->r = 0x80;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                copy_page = (u8 *)0x80020000;
                ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                copy_source = copy_page + 0x6198;
                ASM_KEEP(copy_source);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                *(Blob12 *)task->data = *(Blob12 *)copy_source;
                ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                copy_page += 0x6198;
                *(Blob12 *)(task->data + 12) = *(Blob12 *)(copy_page + 12);
                ASM_KEEP(copy_page);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                ASM_KEEP(task);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                focus_data = task->data;
                sprite->data = focus_data;
                return func_8002614C();
            }
        }
        goto switch_end;

    case_2:
        if ((D_80082E94[0] & 0x8000) == 0) {
            e->timer--;
            if (e->timer >= 0) {
                goto cleanup;
            }
        }
        e->state = 4;
        /* fallthrough */

    case_4:
cleanup:
        if (D_800261B0[0] == 0) {
            D_80083460[0].active = 0;
            D_80082E86[0] = 0;
            D_80083460[0].count--;
            *((u16 *)e - 1) |= 0x8000;
            D_800814A0[0].flags |= 0x8000;
            return func_8002614C();
        }
        D_800261B0[0] = 0;
        goto switch_end;

    switch_end:
        (void)switch_keepalive;
    }
    ASM_KEEP(saved_arg2);
}
