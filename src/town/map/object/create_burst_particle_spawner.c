#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "town/map/spawn_burst_particles_around_origin_api.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern void clear_resident_bit(s16 flag_id);
extern void *allocate_list_node(s32 flags, void *list_head);

/* Creates an object and initializes its data pointer and three input values. */
s32 create_burst_particle_spawner(struct ObjectPosition *origin)
{
    ObjectNodeHeader *object;
    u8 (*object_data)[16];
    ObjectNodeHeader *created_object;
    u8 (*init_data)[16];
    clear_resident_bit(0x97);
    init_data = ((u8 *)(&scene_object_list_anchor));
    object = allocate_list_node(0x312, init_data);
    created_object = object;
    if (created_object != 0) {
        object_data = spawn_burst_particles_around_origin;
        object->update_callback = object_data;
        object->position->x.v = origin->x.v;
        object->position->y.v = origin->y.v;
        object->position->z.v = origin->z.v;
    }
    if (object) {
        return 0;
    }
    else {
        return 0;
    }
}
