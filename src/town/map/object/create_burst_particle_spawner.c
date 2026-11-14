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
s32 create_burst_particle_spawner(s32 *values)
{
    ObjectNodeHeader *object;
    u8 (*object_data)[16];
    ObjectNodeHeader *created_object;
    s32 *values_src;
    u8 (*init_data)[16];
    clear_resident_bit(0x97);
    init_data = ((u8 *)(&scene_object_list_anchor));
    object = allocate_list_node(0x312, init_data);
    created_object = object;
    if (created_object != 0) {
        object_data = spawn_burst_particles_around_origin;
        object->update_callback = object_data;
        ((ObjectPosition *)*(s32 * *)&object->position)->x.v = values[0];
        values_src = values;
        ((ObjectPosition *)*(s32 * *)&object->position)->y.v = values_src[1];
        ((ObjectPosition *)*(s32 * *)&object->position)->z.v = values_src[2];
    }
    if (object) {
        return 0;
    }
    else {
        return 0;
    }
}
