#ifndef TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G01134_H
#define TOWN_SHOP_POSITION_OBJECT_INITIALIZATION_G01134_H
/* position object initialization g01134. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A2ACC, CL:town/func_800A2B1C, CL:town/func_800A2CA4, CL:town/func_800A2D54, PD:town/engine:80100AA0. */

/* Position object initialization. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */
/* Position object initialization declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2ACC. */
#include "common.h"
#include "town/event/object_setup.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "records/Rec_D_800CFCB4.h"
#include "town/menu/window.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "m2c_compat.h"
#include "town/scene/list_setup.h"

typedef struct S_800A022C_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800A022C_0;

/* arg1 in start_item_object_motion */
typedef struct S_800A022C_2 {
    u8 pad_00[0x50];
    s32 * unk_50;
} S_800A022C_2;

/* arg1 in create_item_object_at */
typedef struct S_800A027C_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800A027C_3;

typedef struct S_800A027C_4 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0x38];
    s32 unk_48;
    u8 unk_4C;
    u8 unk_4D;
    u8 unk_4E;
    u8 unk_4F;
    u8 pad_50[0x43];
    s8 unk_93;
    u8 pad_94[0x4];
    s32 unk_98;
} S_800A027C_4;

typedef struct S_800A027C_5 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800A027C_5;

typedef union {
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    } bytes;
    u32 word;
} TownRecord;

/* extern */
typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;

typedef struct TownLink TownLink;

struct TownLink {
    u8 pad_00[4];
    TownLink *next;
    u8 pad_08[0xC];
    u8 type;
    u8 pad_15[0x7F];
    s8 state;
    u8 pad_95[3];
    void *object;
};

/* extern */
extern void *D_8009BC44;
void *allocate_list_node();
/* extern */
/* extern */
/* extern */
/* extern */
extern s32 item_effect_descriptor;
void dispatch_object_or_switch_alternate_state(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context);
extern u8 D_800D073C[];
extern u8 D_800D0754[];
extern u8 D_800D076C[];
extern TownRecord shop_record_queue[20];
/* Complete existing census view; the sentinel next pointer is at +4. */
extern Rec_D_800CFCB4 town_actor_control;

/* Functions defined in this translation unit. */
void start_item_object_motion(S_800A022C_2 *object, S_800A022C_0 *state, ObjectPosition *record, void *unused_render);
void *create_item_object_at(S_800A027C_5 *config, MovingPosition *position);
void clear_shop_record_queue(void);
void enqueue_shop_record(TownRecord *record);
s32 *get_shop_record_queue(void);
void dequeue_shop_record(void);
void spawn_queued_item_object(s32 check_value);
void enqueue_unlinked_item_entries(void);

#endif
