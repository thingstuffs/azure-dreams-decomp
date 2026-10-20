#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[4];
    u8 flag;
} State;

extern s32 D_8008099C[];
extern void register_node_if_unregistered(void *, void *);
extern void unlink_node_if_registered(void *);
extern void draw_linked_sprites(void *, void *, void *);
extern void func_800478B8(void *);

/* Routes state processing according to the global gate and state flag. */
void update_node_registration(void *state, void *context) {
    if (D_8008099C[0] == 0) {
        if (((State *)state)->flag != 0) {
            register_node_if_unregistered(state, draw_linked_sprites);
            func_800478B8(context);
            return;
        }
    }

    unlink_node_if_registered(state);
}
