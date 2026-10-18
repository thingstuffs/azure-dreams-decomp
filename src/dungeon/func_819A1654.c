#include "modules/dungeon_ovl_19c088c.h"

void advance_entity_effect_sequence(Row_819A1654_Entity *entity, void *saved_context, void *saved_data) {
    Row_819A1654_PointTable points;
    Row_819A1654_Task *task;
    Row_819A1654_Effect *effect;
    Row_819A1654_Sprite *sprite;
    Row_819A1654_Coord *coord;
    Row_819A1654_Coord *start_origin;
    Row_819A1654_Coord *origin_loop;
    EntityRec *origin_second;
    Row_819A1654_Coord *origin_path;
    u8 *copy_page;
    EntityRec *world;
    void *focus;
    Row_819A1654_Coord *focus_coord;
    s32 spawn_index;
    s32 path_pair;
    s32 first_path_timer;
    s32 sound_id;
    s32 saved_timer;
    s16 rechecked_timer;
    EntityRec *start_world;
    Row_819A1654_World *hit_world;
    void (*particle_callback)(void);

    *(Row_819A1654_PointTable *)&points = *(Row_819A1654_PointTable *)&D_80024054;

    entity->age++;

    {
        s32 dispatch_state;
        s32 interp_work;
        dispatch_state = entity->state;
        switch (dispatch_state) {
        case 0:
        start_world = D_800814A8;
        start_world->unk_F4 = 0;
        start_world->unk_96 = 20;
        D_80082E86[0] = 6;
        entity->state++;
        start_origin = &D_80083780[0];
        {
            Row_819A1654_Blob24 *flag_base = D_80026198;
            entity->base[0] = start_origin->x;
            entity->base[1] = start_origin->y;
            entity->base[2] = start_origin->z;
            *(s16 *)(flag_base->bytes + 24) = 1;
        }
    case 1:
        if ((*entity->header & 0x80) != 0) {
            u8 *hit_world_page = (u8 *)0x80080000;
            s16 next_state;
            u16 angle;
            hit_world = *(Row_819A1654_World **)(hit_world_page + 0x14A8);
            entity->timer = 33;
            hit_world->fieldA6--;
            hit_world->fieldA8 = entity->type;
            next_state = entity->state;
            angle = (*(Row_819A1654_World **)(hit_world_page + 0x14A8))->angle;
            entity->state = next_state + 1;
            entity->age = 0;
            entity->point_index = (angle >> 9) & 7;
            break;
        }
        break;

        case 2:
            entity->timer--;
            if (entity->timer <= 0) {
                entity->timer = 16;
                entity->state++;
                break;
            }

            if (entity->timer == 18) {
                spawn_index = func_80053EF0(4);
                sound_id = 0x4300;
                if (spawn_index != 2) {
                    sound_id = 0x300;
                }
                play_sound_if_enabled(sound_id);
            }

            if (entity->timer == 24) {
                if (func_8003DF74((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                    spawn_index = 0;
                    particle_callback = choose_random_sign;
                    origin_loop = D_80083780;
                    do {
                        task = (Row_819A1654_Task *)func_8003FC64(0x212);
                        effect = &task->effect;
                        if (task != 0) {
                            effect->timer3A = 20;
                            effect->timer3C = 20;
                            effect->random40 = (s16)((func_80069EF8() & 0xFF) + 200);
                            task->callback = particle_callback;
                            func_8004491C(task, func_80045340);
                            sprite = task->sprite;
                            sprite->field10 = 32;
                            sprite->flags |= 0xC;
                            coord = task->coord;
                            coord->x = entity->x + origin_loop->x;
                            coord->y = entity->y + origin_loop->y;
                            coord->z = entity->z + origin_loop->z;
                            sprite = task->sprite;
                            interp_work = 0x1000;
                            sprite->field1E = interp_work;
                            sprite->field1C = interp_work;
                            interp_work = 0x80;
                            sprite->b = interp_work;
                            sprite->g = interp_work;
                            sprite->r = interp_work;
                            sprite->field16 = (func_80069EF8() & 0xF) << 8;
                            sprite->field18 = (func_80069EF8() & 0xF) << 8;
                            sprite->field1A = (func_80069EF8() & 0xF) << 8;
                            *(Row_819A1654_Blob12 *)(task->data) = D_80026180[0];
                            sprite->data = task->data;
                        }
                        spawn_index++;
                    } while (spawn_index < 10);
                }
            }

            if (entity->timer == 24) {
                if (func_8003DF74((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                    task = (Row_819A1654_Task *)func_8003FC64(0x212);
                    effect = &task->effect;
                    if (task != 0) {
                        s32 burst_size;
                        u16 burst_flags;
                        effect->timer3A = 20;
                        effect->timer3C = 20;
                        task->callback = func_80024BD0;
                        func_8004491C(task, func_80045340);
                        burst_size = 96;
                        sprite = task->sprite;
                        burst_flags = sprite->flags;
                        origin_second = &D_80083780;
                        sprite->field10 = burst_size;
                        sprite->flags = burst_flags | 0xC;
                        coord = task->coord;
                        coord->x = entity->x + origin_second->x.w.i;
                        coord->y = entity->y + origin_second->y.w.i;
                        coord->z = entity->z + origin_second->z.w.i;
                        sprite = task->sprite;
                        sprite->field1E = 0x1000;
                        sprite->field1C = 0x1000;
                        sprite->b = 0x80;
                        sprite->g = 0x80;
                        sprite->r = 0x80;
                        *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                        (*(void **)((u8 *)sprite + 8)) = task->data;
                    }
                }
            }

            if (entity->timer < 10) {
                if (entity->timer < 6) {
                    if (entity->timer != 3) {
                        s32 second_path_timer;
                        path_pair = entity->timer == 4;
                        second_path_timer = 2;
                        first_path_timer = 4;
                        if (entity->timer == second_path_timer) {
                            path_pair = second_path_timer;
                        }
                        if (entity->timer == 1) {
                            path_pair = 3;
                        }

                        if (func_8003DF74((&D_80082E80[0])->found, &D_80082E80[0], &entity->x, 0) != 0) {
                            s32 path_point;
                            Row_819A1654_Entity *path_entity;
                            Row_819A1654_Entity *next_entity;
                            s32 path_half;
                            u32 dim_color;
                            path_point = path_pair * 2;
                            path_entity = (Row_819A1654_Entity *)((u8 *)entity + (path_point + path_pair) * 4);
                            path_point++;
                            path_half = entity->x / 2;
                            origin_path = D_80083780;
                            path_entity->path[0] = path_half + (origin_path->x - entity->base[0]) / 2;
                            path_entity->path[1] = entity->y / 2 + (origin_path->y - entity->base[1]) / 2;
                            path_entity->path[2] = entity->z / 2 + (origin_path->z - entity->base[2]) / 2;
                            next_entity = (Row_819A1654_Entity *)((u8 *)entity + path_point * 3 * 2);
                            next_entity->path[0] = entity->x / 4 + (origin_path->x - entity->base[0]) / 2;
                            next_entity->path[1] = entity->y / 4 + (origin_path->y - entity->base[1]) / 2;
                            next_entity->path[2] = entity->z / 4 + (origin_path->z - entity->base[2]) / 2;

                            if (entity->timer == first_path_timer) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    func_8004491C(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[6];
                                    effect->path[1] = entity->path[7];
                                    effect->path[2] = entity->path[8];
                                    effect->path[3] = entity->path[0];
                                    effect->path[4] = entity->path[1];
                                    effect->path[5] = entity->path[2];
                                    effect->path[6] = entity->path[9];
                                    effect->path[7] = entity->path[10];
                                    effect->path[8] = entity->path[11];
                                    effect->path[9] = entity->path[3];
                                    effect->path[10] = entity->path[4];
                                    effect->path[11] = entity->path[5];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }
                            }

                            if (entity->timer == 2) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    s32 bright_color;
                                    bright_color = 0x804020;
                                    dim_color = 0x201008;
                                    effect->value1C = bright_color;
                                    effect->value24 = dim_color;
                                    effect->value28 = dim_color;
                                    effect->value20 = bright_color;
                                    effect->value0C = effect->value1C;
                                    effect->value10 = effect->value20;
                                    effect->value14 = effect->value24;
                                    effect->value18 = effect->value28;
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    func_8004491C(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[12];
                                    effect->path[1] = entity->path[13];
                                    effect->path[2] = entity->path[14];
                                    effect->path[3] = entity->path[6];
                                    effect->path[4] = entity->path[7];
                                    effect->path[5] = entity->path[8];
                                    effect->path[6] = entity->path[15];
                                    effect->path[7] = entity->path[16];
                                    effect->path[8] = entity->path[17];
                                    effect->path[9] = entity->path[9];
                                    effect->path[10] = entity->path[10];
                                    effect->path[11] = entity->path[11];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }
                            }

                            saved_timer = entity->timer;
                            if (saved_timer == 1) {
                                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                                effect = &task->effect;
                                if (task != 0) {
                                    s32 bright_color;
                                    bright_color = 0x804020;
                                    dim_color = 0x201008;
                                    effect->value1C = bright_color;
                                    effect->value24 = dim_color;
                                    effect->value28 = dim_color;
                                    effect->value20 = bright_color;
                                    effect->value0C = effect->value1C;
                                    effect->value10 = effect->value20;
                                    effect->value14 = effect->value24;
                                    effect->value18 = effect->value28;
                                    effect->timer3A = 20;
                                    effect->timer3C = 20;
                                    task->callback = func_80024834;
                                    func_8004491C(task, draw_linked_effect_chain);
                                    sprite = task->sprite;
                                    sprite->field10 = 32;
                                    sprite->flags |= 0xC;
                                    effect->path[0] = entity->path[18];
                                    effect->path[1] = entity->path[19];
                                    effect->path[2] = entity->path[20];
                                    effect->path[3] = entity->path[12];
                                    effect->path[4] = entity->path[13];
                                    effect->path[5] = entity->path[14];
                                    effect->path[6] = entity->path[21];
                                    effect->path[7] = entity->path[22];
                                    effect->path[8] = entity->path[23];
                                    effect->path[9] = entity->path[15];
                                    effect->path[10] = entity->path[16];
                                    effect->path[11] = entity->path[17];
                                    coord = task->coord;
                                    coord->x = entity->base[0];
                                    coord->y = entity->base[1];
                                    coord->z = entity->base[2];
                                    sprite = task->sprite;
                                    sprite->field1E = 0x1000;
                                    sprite->field1C = 0x1000;
                                    sprite->b = 0x80;
                                    sprite->g = 0x80;
                                    sprite->r = 0x80;
                                    *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                    (*(void **)((u8 *)sprite + 8)) = task->data;
                                }

                                rechecked_timer = entity->timer;
                                if (rechecked_timer == saved_timer) {
                                    task = (Row_819A1654_Task *)func_8003FC64(0x212);
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
                                        task->callback = advance_object_motion_and_animation;
                                        func_8004491C(task, draw_linked_effect_chain);
                                        sprite = task->sprite;
                                        sprite->field10 = 32;
                                        sprite->flags |= 0xC;
                                        effect->path[0] = entity->path[12];
                                        effect->path[1] = entity->path[13];
                                        effect->path[2] = entity->path[14];
                                        effect->path[3] = entity->path[6];
                                        effect->path[4] = entity->path[7];
                                        effect->path[5] = entity->path[8];
                                        effect->path[6] = entity->path[12];
                                        effect->path[7] = entity->path[13];
                                        effect->path[8] = entity->path[14];
                                        effect->path[9] = entity->path[6];
                                        effect->path[10] = entity->path[7];
                                        effect->path[11] = entity->path[8];
                                        effect->path[12] = points.point[entity->point_index].x * 8;
                                        effect->path[13] = points.point[entity->point_index].y * 8;
                                        effect->path[14] = 0;
                                        effect->path[15] = points.point[entity->point_index].x * 8;
                                        effect->path[16] = points.point[entity->point_index].y * 8;
                                        effect->path[17] = 0;
                                        coord = task->coord;
                                        coord->x = entity->base[0];
                                        coord->y = entity->base[1];
                                        coord->z = entity->base[2];
                                        sprite = task->sprite;
                                        sprite->field1E = 0x1000;
                                        sprite->field1C = 0x1000;
                                        sprite->b = 0x80;
                                        sprite->g = 0x80;
                                        sprite->r = 0x80;
                                        *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                        (*(void **)((u8 *)sprite + 8)) = task->data;
                                    }

                                    saved_timer = entity->timer;
                                    if (saved_timer == rechecked_timer) {
                                        task = (Row_819A1654_Task *)func_8003FC64(0x212);
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
                                            task->callback = advance_object_motion_and_animation;
                                            func_8004491C(task, draw_linked_effect_chain);
                                            sprite = task->sprite;
                                            sprite->field10 = 32;
                                            sprite->flags |= 0xC;
                                            effect->path[0] = entity->path[18];
                                            effect->path[1] = entity->path[19];
                                            effect->path[2] = entity->path[20];
                                            effect->path[3] = entity->path[12];
                                            effect->path[4] = entity->path[13];
                                            effect->path[5] = entity->path[14];
                                            effect->path[6] = entity->path[18];
                                            effect->path[7] = entity->path[19];
                                            effect->path[8] = entity->path[20];
                                            effect->path[9] = entity->path[12];
                                            effect->path[10] = entity->path[13];
                                            effect->path[11] = entity->path[14];
                                            effect->path[12] = points.point[entity->point_index].x * 8;
                                            effect->path[13] = points.point[entity->point_index].y * 8;
                                            effect->path[14] = 0;
                                            effect->path[15] = points.point[entity->point_index].x * 8;
                                            effect->path[16] = points.point[entity->point_index].y * 8;
                                            effect->path[17] = 0;
                                            coord = task->coord;
                                            coord->x = entity->base[0];
                                            coord->y = entity->base[1];
                                            coord->z = entity->base[2];
                                            sprite = task->sprite;
                                            sprite->field1E = 0x1000;
                                            sprite->field1C = 0x1000;
                                            sprite->b = 0x80;
                                            sprite->g = 0x80;
                                            sprite->r = 0x80;
                                            *(Row_819A1654_Blob12 *)(task->data) = D_8002618C[0];
                                            (*(void **)((u8 *)sprite + 8)) = task->data;
                                        }

                                        if (entity->timer == saved_timer) {
                                            s32 trail_fraction;
                                            s32 interp_x;
                                            s32 interp_z;
                                            s32 interp_base;
                                            s32 out_x;
                                            saved_timer = 0;
loop_1:
                                            {
                                                interp_base = entity->path[18];
                                                interp_work = entity->path[6] - interp_base;
                                                trail_fraction = saved_timer << 1;
                                                interp_x = interp_work * trail_fraction;
                                                if (interp_x < 0) {
                                                    interp_x += 15;
                                                }
                                                out_x = interp_base * 2;
                                                interp_base = entity->path[19];
                                                interp_work = entity->path[7] - interp_base;
                                                next_entity = (Row_819A1654_Entity *)(interp_work * trail_fraction);
                                                interp_work = interp_x >> 4;
                                                out_x += interp_work;
                                                interp_x = interp_base * 2;
                                                if ((s32)next_entity < 0) {
                                                    next_entity = (Row_819A1654_Entity *)((s32)next_entity + 15);
                                                }
                                                interp_base = entity->path[20];
                                                interp_work = entity->path[8] - interp_base;
                                                interp_z = interp_work * trail_fraction;
                                                interp_work = (s32)next_entity >> 4;
                                                {
                                                    s32 interp_y = interp_x + interp_work;
                                                    interp_work = interp_y;
                                                }
                                                interp_base = interp_base * 2;
                                                if (interp_z < 0) {
                                                    interp_z += 15;
                                                }
                                                D_80024C50(entity, saved_context, saved_data,
                                                    (s16)out_x, (s16)interp_work,
                                                    (s16)(interp_base + (interp_z >> 4)));
                                                saved_timer++;
                                            }
                                            if (saved_timer < 16)
                                                goto loop_1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            world = D_800814A8;
            focus = world->target;
            if (focus != 0 && entity->timer == 1) {
                task = (Row_819A1654_Task *)func_8003FC64(0x212);
                effect = &task->effect;
                if (task != 0) {
                    effect->timer3A = 13;
                    effect->timer3C = 13;
                    task->callback = update_effect_countdown_fields;
                    func_8004491C(task, func_80045340);
                    sprite = task->sprite;
                    sprite->field6 = 6;
                    sprite->flags &= 0xFFF3;
                    focus_coord = *(Row_819A1654_Coord **)((u8 *)focus - 24);
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
                    *(Row_819A1654_Blob12 *)task->data = *(Row_819A1654_Blob12 *)D_80026198;
                    copy_page = (u8 *)D_80026198;
                    *(Row_819A1654_Blob12 *)(task->data + 12) = *(Row_819A1654_Blob12 *)(copy_page + 12);
                    sprite->data = task->data;
                    break;
                }
            }
            break;

        case 3:
            if ((D_80082E94[0] & 0x8000) != 0 || --entity->timer < 0) {
                entity->state = 4;
            }
            /* fallthrough */

        case 4:
            if (((s16 *)D_800261B0)[0] == 0) {
                ((Row_819A1654_ControlGlobal *)&g_dungeon_status)[0].active = 0;
                D_80082E86[0] = 0;
                ((Row_819A1654_ControlGlobal *)&g_dungeon_status)[0].count--;
                *((u16 *)entity - 1) |= 0x8000;
                D_800814A0[0].flags |= 0x8000;
                break;
            }
            ((s16 *)D_800261B0)[0] = 0;
            break;

        default:
            break;
        }
    }
}
