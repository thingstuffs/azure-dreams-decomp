#include "common.h"
extern int abs(int);

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 link;
    s16 kind;
} Zone;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Box;

typedef struct {
    s16 unk0;
    s16 x;
    s16 unk4;
    s16 y;
    s16 unk8;
    s16 z;
    s32 dx;
    s32 dy;
} Actor;

extern Zone D_80024020[];
extern Box D_800240E0[];

#define CURRENT_ZONE(F) (D_80024020[*zone_id].F)
#define OLD_ZONE(F) (D_80024020[old_zone].F)
#define CANDIDATE_ZONE(F) (D_80024020[candidate].F)

#define PUSH(PUSH_Y, PUSH_X)            \
    abs_dx = actor->dx;                 \
    abs_dy = actor->dy;                 \
    if (abs_dx < 0) {                   \
        abs_dx = -abs_dx;               \
    }                                   \
    if (abs_dy < 0) {                   \
        abs_dy = -abs_dy;               \
    }                                   \
    if (abs_dy < abs_dx) {              \
        *offset_y += (PUSH_Y);          \
    } else {                            \
        *offset_x += (PUSH_X);          \
    }                                   \
    break;

/* Resolve actor collisions against zone boundaries and linked boxes. */
s32 func_8002263C(Actor *actor, s16 *zone_id, s32 *offset_x, s32 *offset_y) {
    s32 candidate;
    s32 box_id;
    u32 old_zone;
    s32 abs_dx;
    s32 abs_dy;
    s32 velocity;
    s32 vz;
    s32 zone_kind;
    s32 edge_x;
    s32 box_width;
    s32 edge_delta;
    s32 edge_coord;
    s32 edge_coord_2;
    s32 zone_y_m;
    s32 actor_role_x;
    s32 actor_role_y;
    s32 height_or_box_y;
    Zone *zone_table;

    candidate = 0;
    box_id = *zone_id + 1;
    while (box_id >= *zone_id - 1) {
        candidate = (box_id + 16) % 16;
        if (actor->x >= CANDIDATE_ZONE(x)) {
            if (actor->y >= CANDIDATE_ZONE(y)) {
                if (CANDIDATE_ZONE(x) + CANDIDATE_ZONE(w) >= actor->x) {
                    if (CANDIDATE_ZONE(y) + CANDIDATE_ZONE(h) >= actor->y) {
                        goto zone_found;
                    }
                }
            }
        }
        box_id--;
    }
check_zone:
    if (candidate >= 0) {
        goto clamp_to_zone;
    }

    zone_table = D_80024020;
    zone_y_m = (s32)&zone_table[*zone_id];
    box_id = ((Zone *)zone_y_m)->link;
    if (box_id >= 0 && actor->z >= -32) {
        {
            Box *linked_box;
            velocity = (s32)((u8 *)D_800240E0);
            zone_kind = box_id << 3;
            linked_box = (Box *)(((u8 *)velocity) + zone_kind);
            candidate = (s32)linked_box;
        }
        {
            s32 box_x;
            actor_role_x = actor->x;
            box_x = ((Box *)candidate)->x;
            if (actor_role_x >= box_x) {
                actor_role_y = actor->y;
                height_or_box_y = ((Box *)candidate)->y;
                if (actor_role_y >= height_or_box_y) {
                    if (box_x + ((Box *)candidate)->w >= actor_role_x) {
                        if (height_or_box_y + ((Box *)candidate)->h >= actor_role_y) {
                            if (((Zone *)zone_y_m)->kind == 0) {
                                *offset_y -= actor->dy;
                                velocity = actor->dy;
                                if (velocity > 0) {
                                    actor->y = ((Box *)candidate)->y;
                                    goto adjusted;
                                }
                                if (velocity < 0) {
                                    actor->y = ((Box *)candidate)->y + ((Box *)candidate)->h;
                                    goto adjusted;
                                }
                                if (abs(actor->y - ((Box *)candidate)->y) < abs(((Box *)candidate)->y + ((Box *)candidate)->h - actor->y)) {
                                    actor->y = (u16)((Box *)candidate)->y;
                                    return 2;
                                }
                                actor->y = (u16)((Box *)candidate)->y + (u16)((Box *)candidate)->h;
                                return 2;
                            } else {
                                *offset_x -= actor->dx;
                                velocity = actor->dx;
                                if (velocity > 0) {
                                    edge_x = (u16)((Box *)candidate)->x;
                                    actor->x = edge_x;
                                    goto adjusted;
                                }
                                if (velocity < 0) {
                                    edge_x = (u16)((Box *)candidate)->x;
                                    edge_delta = (u16)((Box *)candidate)->w;
                                    edge_x = edge_x + edge_delta;
                                } else {
                                    edge_delta = abs(actor->x - ((Box *)candidate)->x);
                                    edge_x = abs(((Box *)candidate)->x + ((Box *)candidate)->w - actor->x);
                                    edge_delta = edge_delta < edge_x;
                                    edge_x = (u16)((Box *)candidate)->x;
                                    box_width = (u16)((Box *)candidate)->w;
                                    if (!edge_delta) {
                                        edge_x = edge_x + box_width;
                                    }
                                }
                                ASM_KEEP(edge_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                                actor->x = edge_x;
                                return 2;
                            }
                        }
                    }
                }
            }
        }
    }
    zone_kind = CURRENT_ZONE(kind);
    switch (zone_kind) {
zone_found:
    *zone_id = candidate;
    candidate = -1;
    goto check_zone;

    case 2:
    {
        s32 edge_delta;
        s32 zone_x;
        s32 actor_x;
        s32 edge_y_2;
        s32 neg_x;
        actor_role_x = actor->y;
        zone_y_m = CURRENT_ZONE(y);
        zone_x = CURRENT_ZONE(x);
        actor_x = actor->x;
        edge_y_2 = zone_y_m + 0x100;
        old_zone = zone_x + edge_y_2;
        neg_x = -actor_x;
        edge_delta = neg_x + old_zone;
        edge_delta = actor_role_x - edge_delta;
        edge_coord = zone_y_m - 0x70;
        if (edge_delta < 0) {
            PUSH(0x80000, 0x80000)
        }
        edge_delta = CURRENT_ZONE(w);
        height_or_box_y = CURRENT_ZONE(h);
        edge_delta = zone_x + edge_delta + edge_coord;
        old_zone = edge_delta + height_or_box_y;
        edge_delta = neg_x + old_zone;
        edge_delta = actor_role_x - edge_delta;
        if (edge_delta > 0) {
            PUSH(-0x100000, -0x100000)
        }
    }
    return 0;

    case 3:
    {
        s32 edge_delta;
        s32 actor_y;
        u8 *zone_data;
        zone_data = (u8 *)D_80024020;
        height_or_box_y = *zone_id;
        actor_role_y = actor->x;
        actor_y = actor->y;
        edge_coord = ((Zone *)zone_data)[height_or_box_y].x;
        edge_delta = ((Zone *)zone_data)[height_or_box_y].w;
        vz = ((Zone *)zone_data)[height_or_box_y].y;
        velocity = edge_coord + edge_delta;
        edge_delta = velocity - 0x100;
        old_zone = vz - edge_delta;
        edge_delta = actor_role_y + old_zone;
        edge_delta = actor_y - edge_delta;
        edge_coord = edge_coord + 0x70;
        if (edge_delta < 0) {
            PUSH(0x80000, -0x80000)
        }
        edge_delta = ((Zone *)zone_data)[height_or_box_y].h;
        old_zone = ((s32)(vz + edge_delta)) - edge_coord;
        edge_delta = actor_role_y + old_zone;
        edge_delta = actor_y - edge_delta;
        if (edge_delta > 0) {
            PUSH(-0x100000, 0x100000)
        }
    }
    return 0;

    case 4:
    {
        s32 current_zone;
        s32 zone_x;
        s32 actor_y;
        s32 actor_x;
        u8 *zone_data;
        s32 d4_1;
        s32 d4_2;
        s32 d4_3;
        s32 d4_4;
        zone_data = (u8 *)D_80024020;
        current_zone = *zone_id;
        actor_x = ((Actor *)actor)->x;
        actor_y = (*(s16 *)((u8 *)actor + 6));
        zone_y_m = ((Zone *)zone_data)[current_zone].y;
        zone_x = ((Zone *)zone_data)[current_zone].x;
        d4_1 = zone_y_m + ((Zone *)zone_data)[current_zone].h;
        edge_coord_2 = zone_x + 0x100;
        old_zone = d4_1 - edge_coord_2;
        d4_2 = actor_x + old_zone;
        d4_2 = actor_y - d4_2;
        edge_coord = zone_y_m + 0x70;
        if (d4_2 > 0) {
            PUSH(-0x100000, 0x100000)
        }
        d4_3 = zone_x + ((Zone *)zone_data)[current_zone].w;
        old_zone = edge_coord - d4_3;
        d4_4 = actor_x + old_zone;
        d4_4 = actor_y - d4_4;
        if (d4_4 < 0) {
            PUSH(0x200000, -0x200000)
        }
    }
    return 0;

    case 5:
    {
        s32 zone_width;
        s32 zone_y;
        s32 neg_x;
        s32 actor_y;
        s32 edge_x;
        s32 d5_1;
        s32 d5_2;
        s32 d5_3;
        s32 d5_4;
        zone_y = CURRENT_ZONE(y);
        zone_width = CURRENT_ZONE(w);
        vz = CURRENT_ZONE(x);
        d5_1 = zone_y + zone_width;
        edge_x = vz - 0x100;
        d5_1 = d5_1 + edge_x;
        old_zone = d5_1 + zone_width;
        neg_x = -actor->x;
        actor_y = actor->y;
        d5_2 = neg_x + old_zone;
        d5_2 = actor_y - d5_2;
        if (d5_2 > 0) {
            PUSH(-0x100000, -0x100000)
        }
        d5_3 = zone_y + vz;
        old_zone = d5_3 + 0x70;
        d5_4 = neg_x + old_zone;
        d5_4 = actor_y - d5_4;
        if (d5_4 < 0) {
            PUSH(0x200000, 0x200000)
        }
    }
    return 0;

    case 1:
    case 0:
        return 0;
    default:
        break;
    }
    *offset_x -= actor->dx * 3;
    *offset_y -= actor->dy * 3;
    return 1;

clamp_to_zone:
    old_zone = *zone_id;
    if (OLD_ZONE(kind) != 1) {
        s32 actor_x = actor->x;
        s32 zone_x = OLD_ZONE(x);
        if (actor_x < zone_x) {
            actor->x = OLD_ZONE(x) + 8;
        } else if (zone_x + OLD_ZONE(w) < actor_x) {
            actor->x = OLD_ZONE(x) + OLD_ZONE(w) - 8;
        }
        *offset_x -= actor->dx * 3;
    }
    if (OLD_ZONE(kind) != 0) {
        s32 actor_y = actor->y;
        s32 zone_y = OLD_ZONE(y);
        if (actor_y < zone_y) {
            actor->y = OLD_ZONE(y) + 8;
        } else if (zone_y + OLD_ZONE(h) < actor_y) {
            actor->y = OLD_ZONE(y) + OLD_ZONE(h) - 8;
        }
        *offset_y -= actor->dy * 3;
    }
    {
        s32 scratch;
        s32 current_zone;
        current_zone = *zone_id;
        box_id = current_zone + 1;
    }
    if (box_id >= *zone_id - 1) {
        zone_y_m = (s32)D_80024020;
        do {
            candidate = (box_id + 16) % 16;
            if (actor->x >= ((Zone *)zone_y_m)[candidate].x) {
                if (actor->y >= ((Zone *)zone_y_m)[candidate].y) {
                    if (((Zone *)zone_y_m)[candidate].x + ((Zone *)zone_y_m)[candidate].w >= actor->x) {
                        if (((Zone *)zone_y_m)[candidate].y + ((Zone *)zone_y_m)[candidate].h >= actor->y) {
                            *zone_id = candidate;
                        }
                    }
                }
            }
            box_id--;
        } while (box_id >= *zone_id - 1);
    }
adjusted:
    return 2;
}
