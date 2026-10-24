#include "common.h"
#include "shared/object_flags.h"

typedef struct S_func_800A9F90 S_func_800A9F90;

struct S_func_800A9F90 {
    u8 pad00[0x50];
    void (*callback)(S_func_800A9F90 *self);
    u8 pad54[0x6C - 0x54];
    u16 counter;
};

extern void unlink_node_if_registered(S_func_800A9F90 *);

/* Decrement the counter and handle expiry or invoke the callback. */
void decrement_callback_object_timer(S_func_800A9F90 *self, s32 expiry_arg)
{
    void (*callback)(S_func_800A9F90 *self);
    u16 counter;

    counter = self->counter - 1;
    self->counter = counter;
    if ((counter << 16) <= 0) {
        unlink_node_if_registered(self);
        *(u16 *)((u8 *)self - 2) =
            (u16)(*(u16 *)((u8 *)self - 2) | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    callback = self->callback;
    if (callback != 0) {
        callback(self);
    }
}
