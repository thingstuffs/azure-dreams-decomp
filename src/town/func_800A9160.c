#include "common.h"
#include "shared/entity_objects.h"

typedef struct {
    s8 pad00[0x50];
    void (*callback)(void *, void *, void *, s32);
} Obj;
typedef struct { u8 pad00[0x15]; u8 flag15; } State;
typedef struct { s32 x, y, z, dx, dy, dz; } VecState;

extern void initialize_object_entries(void *, s32, void *);
extern void update_target_from_previous_state(void);
extern void apply_pending_indexed_value(s32, const char *);
extern void set_flagged_entry_values(void *, const char *);
extern void update_actor_position_and_heading(void *, void *, void *, s32);
extern void *D_80100E28[];
extern u8 D_800D0D54[];
extern char D_800A630C[];
extern char D_800A62E8[];

/* Initialize object state and position, then invoke its new callback. */
void save_and_clear_entity_flag_ten(Obj *obj, State *state, VecState *motion, s32 callback_arg)
{
    s32 resource_arg;
    void *resource;

    resource_arg = callback_arg;
    state->flag15 = 0;
    resource = D_80100E28[0];
    motion->dx = 0;
    motion->dy = 0;
    motion->dz = 0;
    obj->callback = update_actor_position_and_heading;
    initialize_object_entries(obj, resource_arg, resource);
    update_target_from_previous_state();
    motion->x = D_80083780.x.v;
    motion->y = D_80083780.y.v;
    motion->z = D_80083780.z.v;
    apply_pending_indexed_value(0xE5, D_800A630C);
    set_flagged_entry_values(D_800D0D54, D_800A62E8);
    update_actor_position_and_heading(obj, state, motion, callback_arg);
}
