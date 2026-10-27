#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

struct Node; s32 append_scene_list_node(struct Node *);                      /* extern */
#include "town/scene/object/unlink_scene_list_node_api.h"                      /* extern */
#include "shared/town_state.h"
struct Actor;
struct Motion;
struct Subject;
extern void actor_moving_target_address(struct Actor *actor, struct Subject *subject, struct Motion *motion, TownMovementOutput *context);


typedef struct S_8009C0D8_1 {
    u8 pad_00[0x50];
    void (*unk_50)();
} S_8009C0D8_1;   /* arg0 in initialize_moving_object */

/* Set the object flag, assign the context handler, and run object setup. */
void initialize_moving_object(S_8009C0D8_1 *context, Rec_func_80094268_arg0 *object) {
    object->unk_15 = 1;
    context->unk_50 = &actor_moving_target_address;
    unlink_scene_list_node(object);
    append_scene_list_node((struct Node *)(object));
}
