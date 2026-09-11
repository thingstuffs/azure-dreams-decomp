#include "common.h"

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
extern void *D_80020180[];

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
    goto push_back;

/* Resolve actor collisions against zone boundaries and linked boxes. */
s32 func_8002263C(Actor *actor, s16 *zone_id, s32 *offset_x, s32 *offset_y) {
    register Box *box ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 neighbor ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 candidate;
    s32 box_id;
    register s32 old_zone ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 abs_dx;
    s32 abs_dy;
    s32 velocity;
    s32 zone_kind;
    s32 actor_x;
    s32 edge_x;
    s32 box_width;
    s32 edge_delta;
    static void *const case_labels[] = {&&diagonal_2, &&diagonal_3, &&diagonal_4, &&diagonal_5, &&clear};

    (void)case_labels;
    candidate = 0;
    neighbor = *zone_id + 1;
    while (neighbor >= *zone_id - 1) {
        candidate = (neighbor + 16) % 16;
        if (actor->x < CANDIDATE_ZONE(x)) {
            goto next_neighbor;
        }
        if (actor->y < CANDIDATE_ZONE(y)) {
            goto next_neighbor;
        }
        if (CANDIDATE_ZONE(x) + CANDIDATE_ZONE(w) < actor->x) {
            goto next_neighbor;
        }
        if (CANDIDATE_ZONE(y) + CANDIDATE_ZONE(h) < actor->y) {
            goto next_neighbor;
        }
        goto zone_found;
    next_neighbor:
        neighbor--;
    }
check_zone:
    if (candidate >= 0) {
        goto clamp_to_zone;
    }

    box_id = CURRENT_ZONE(link);
    if (box_id < 0) {
        goto check_edges;
    }
    if (actor->z < -32) {
        goto check_edges;
    }
    {
        register s32 box_offset ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        u8 *box_data;
        Box *linked_box;
        box_data = (u8 *)D_800240E0;
        do {
            box_offset = box_id << 3;
        } while (0);
        linked_box = (Box *)(box_data + box_offset);
        ASM_KEEP_NV(linked_box);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        box = linked_box;
    }
    ASM_KEEP(box);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    {
        s32 actor_x;
        s32 box_x;
        s32 actor_y;
        s32 box_y;
        actor_x = actor->x;
        box_x = box->x;
        if (actor_x < box_x) {
            goto check_edges;
        }
        actor_y = actor->y;
        box_y = box->y;
        if (actor_y < box_y) {
            goto check_edges;
        }
        if (box_x + box->w < actor_x) {
            goto check_edges;
        }
        if (box_y + box->h < actor_y) {
            goto check_edges;
        }
    }
    if (CURRENT_ZONE(kind) != 0) {
        goto clamp_x;
    }

    *offset_y -= actor->dy;
    velocity = actor->dy;
    if (velocity > 0) {
        actor->y = box->y;
        goto adjusted;
    }
    if (velocity < 0) {
        actor->y = box->y + box->h;
        goto adjusted;
    }
    {
        s32 actor_y;
        s32 edge_y;
        s32 box_height;
        s32 edge_delta;
        actor_y = actor->y;
        do {
            edge_y = box->y;
        } while (0);
        box_height = box->h;
        edge_delta = actor_y - edge_y;
        if (edge_delta < 0) {
            edge_delta = -edge_delta;
        }
        edge_y = edge_y + box_height;
        edge_y = edge_y - actor_y;
        if (edge_y < 0) {
            edge_y = -edge_y;
        }
        edge_delta = edge_delta < edge_y;
        edge_y = (u16)box->y;
        box_height = (u16)box->h;
        if (edge_delta) {
            actor->y = edge_y;
            goto adjusted;
        }
        edge_y = edge_y + box_height;
        actor->y = edge_y;
    }
    goto adjusted;

clamp_x:
    *offset_x -= actor->dx;
    velocity = actor->dx;
    if (velocity > 0) {
        edge_x = (u16)box->x;
        actor->x = edge_x;
        goto adjusted;
    }
    if (velocity < 0) {
        edge_x = (u16)box->x;
        edge_delta = (u16)box->w;
        edge_x = edge_x + edge_delta;
        goto store_x;
    }
    actor_x = actor->x;
    do {
        edge_x = box->x;
    } while (0);
    box_width = box->w;
    edge_delta = actor_x - edge_x;
    if (edge_delta < 0) {
        edge_delta = -edge_delta;
    }
    edge_x = edge_x + box_width;
    edge_x = edge_x - actor_x;
    if (edge_x < 0) {
        edge_x = -edge_x;
    }
    edge_delta = edge_delta < edge_x;
    edge_x = (u16)box->x;
    box_width = (u16)box->w;
    if (edge_delta) {
        goto store_x;
    }
    edge_x = edge_x + box_width;
store_x:
    ASM_KEEP(edge_x);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    actor->x = edge_x;
    goto adjusted;

check_edges:
    zone_kind = CURRENT_ZONE(kind);
    if ((u32)zone_kind >= 6) {
        goto push_back;
    }
    goto *D_80020180[zone_kind];
zone_found:
    *zone_id = candidate;
    candidate = -1;
    goto check_zone;

diagonal_2:
    {
        register s32 band ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register s32 zone_y ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 zone_height ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 edge_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 zone_x;
        s32 actor_y;
        s32 actor_x;
        s32 edge_y;
        s32 neg_x;
        actor_y = actor->y;
        zone_y = CURRENT_ZONE(y);
        zone_x = CURRENT_ZONE(x);
        actor_x = actor->x;
        edge_y = zone_y + 0x100;
        band = zone_x + edge_y;
        neg_x = -actor_x;
        edge_delta = neg_x + band;
        edge_delta = actor_y - edge_delta;
        edge_y = zone_y - 0x70;
        if (edge_delta < 0) {
            PUSH(0x80000, 0x80000)
        }
        edge_delta = CURRENT_ZONE(w);
        zone_height = CURRENT_ZONE(h);
        edge_delta = zone_x + edge_delta;
        edge_delta = edge_delta + edge_y;
        band = edge_delta + zone_height;
        edge_delta = neg_x + band;
        edge_delta = actor_y - edge_delta;
        if (edge_delta > 0) {
            PUSH(-0x100000, -0x100000)
        }
    }
    return 0;

diagonal_3:
    {
        register s32 edge_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 band ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register s32 current_zone ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 zone_x ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 zone_y;
        s32 actor_y;
        s32 actor_x;
        u8 *zone_data;
        zone_data = (u8 *)D_80024020;
        current_zone = *zone_id;
        ASM_KEEP(current_zone);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        actor_x = actor->x;
        actor_y = actor->y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        zone_x = ((Zone *)zone_data)[current_zone].x;
        edge_delta = ((Zone *)zone_data)[current_zone].w;
        zone_y = ((Zone *)zone_data)[current_zone].y;
        edge_delta = zone_x + edge_delta;
        edge_delta = edge_delta - 0x100;
        band = zone_y - edge_delta;
        edge_delta = actor_x + band;
        edge_delta = actor_y - edge_delta;
        zone_x = zone_x + 0x70;
        if (edge_delta < 0) {
            PUSH(0x80000, -0x80000)
        }
        edge_delta = ((Zone *)zone_data)[current_zone].h;
        edge_delta = zone_y + edge_delta;
        band = edge_delta - zone_x;
        edge_delta = actor_x + band;
        edge_delta = actor_y - edge_delta;
        if (edge_delta > 0) {
            PUSH(-0x100000, 0x100000)
        }
    }
    return 0;

diagonal_4:
    {
        register s32 edge_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 band ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register s32 current_zone ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 zone_y ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 zone_x ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register s32 edge_coord ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 actor_y;
        s32 actor_x;
        u8 *zone_data;
        zone_data = (u8 *)D_80024020;
        current_zone = *zone_id;
        ASM_KEEP(current_zone);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        actor_x = actor->x;
        actor_y = actor->y;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        zone_y = ((Zone *)zone_data)[current_zone].y;
        edge_delta = ((Zone *)zone_data)[current_zone].h;
        zone_x = ((Zone *)zone_data)[current_zone].x;
        edge_delta = zone_y + edge_delta;
        edge_coord = zone_x + 0x100;
        band = edge_delta - edge_coord;
        edge_delta = actor_x + band;
        edge_delta = actor_y - edge_delta;
        edge_coord = zone_y + 0x70;
        if (edge_delta > 0) {
            PUSH(-0x100000, 0x100000)
        }
        edge_delta = ((Zone *)zone_data)[current_zone].w;
        edge_delta = zone_x + edge_delta;
        band = edge_coord - edge_delta;
        edge_delta = actor_x + band;
        edge_delta = actor_y - edge_delta;
        if (edge_delta < 0) {
            PUSH(0x200000, -0x200000)
        }
    }
    return 0;

diagonal_5:
    {
        register s32 edge_delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register s32 band ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        register s32 zone_width ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        s32 zone_y;
        s32 zone_x;
        s32 neg_x;
        s32 actor_y;
        s32 edge_x;
        zone_y = CURRENT_ZONE(y);
        do {
            zone_width = CURRENT_ZONE(w);
        } while (0);
        zone_x = CURRENT_ZONE(x);
        edge_delta = zone_y + zone_width;
        edge_x = zone_x - 0x100;
        edge_delta = edge_delta + edge_x;
        band = edge_delta + zone_width;
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        neg_x = actor->x;
        actor_y = actor->y;
        neg_x = -neg_x;
        edge_delta = neg_x + band;
        edge_delta = actor_y - edge_delta;
        if (edge_delta > 0) {
            PUSH(-0x100000, -0x100000)
        }
        edge_delta = zone_y + zone_x;
        band = edge_delta + 0x70;
        edge_delta = neg_x + band;
        edge_delta = actor_y - edge_delta;
        if (edge_delta < 0) {
            PUSH(0x200000, 0x200000)
        }
    }
    return 0;

clear:
    return 0;
push_back:
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
        register s32 scratch ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 current_zone;
        ASM_UNDEF(scratch);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        current_zone = *zone_id;
        ASM_USE(scratch);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        neighbor = current_zone + 1;
    }
    while (neighbor >= *zone_id - 1) {
        candidate = (neighbor + 16) % 16;
        if (actor->x < CANDIDATE_ZONE(x)) {
            goto next_clamped_neighbor;
        }
        if (actor->y < CANDIDATE_ZONE(y)) {
            goto next_clamped_neighbor;
        }
        if (CANDIDATE_ZONE(x) + CANDIDATE_ZONE(w) < actor->x) {
            goto next_clamped_neighbor;
        }
        if (CANDIDATE_ZONE(y) + CANDIDATE_ZONE(h) < actor->y) {
            goto next_clamped_neighbor;
        }
        *zone_id = candidate;
    next_clamped_neighbor:
        neighbor--;
    }
adjusted:
    return 2;
}
