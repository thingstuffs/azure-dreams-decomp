#include "common.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800DAE44_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DAE44_3;




void *func_8003FD64();            /* extern */
s16 sample_terrain_surface_height();                   /* extern */
extern void spawn_scattered_timed_objects(void *source_owner, void *spawn_params);

typedef struct S_800DAE44_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800DAE44_0;


typedef struct S_800DAE44_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x36];
    s16 unk_48;
} S_800DAE44_2;

/* Create an object at the source position and initialize its data. */
void create_source_positioned_object(EntityRec *source_pos, s16 initial_value) {
    S_800DAE44_2 *object_data;
    void *object;

    object = func_8003FD64(0x312, ((M2C_UNK *)&D_80083498.next));
    if (object != NULL) {
        ((S_800DAE44_0 *)object)->unk_10 = spawn_scattered_timed_objects;
        ((MovingPosition *)(((S_800DAE44_3 *)object)->unk_08))->unk_02 = (u16) ((u16)source_pos->x.w.i);
        ((MovingPosition *)(((S_800DAE44_3 *)object)->unk_08))->unk_06 = (u16) ((u16)source_pos->y.w.i);
        object_data = object + 0x20;
        ((MovingPosition *)(((S_800DAE44_3 *)object)->unk_08))->unk_0A = (u16) ((u16)source_pos->z.w.i);
        object_data->unk_10 = sample_terrain_surface_height(((u16)source_pos->x.w.i), ((u16)source_pos->y.w.i),
            (s16) (((u16)source_pos->z.w.i) - 0x80));
        object_data->unk_48 = initial_value;
    }
}
