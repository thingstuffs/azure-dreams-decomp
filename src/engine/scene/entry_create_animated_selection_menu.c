#include "shared/object_node.h"
#include "common.h"
#include "engine/graphics.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "engine/sprite.h"
#include "slus/data.h"

typedef struct S_80050BA4_s1
{
    u8 pad00[0xC];
    void *field_0xC;
    void *field_0x10;
    u8 pad14[0x1E - 0x14];
    u16 field_0x1E;
    u8 pad20[0x78 - 0x20];
    u8 field_0x78;
}
S_80050BA4_s1;

typedef struct S_80050BA4_sub
{
    u8 pad00[0x28];
    void *field_0x28;
    u8 pad2c[(0x64 - 0x28) - 4];
    void *field_0x64;
    void *field_0x68;
    u16 *field_0x6c;
    u8 pad70[0xA0 - 0x70];
    void *field_0xA0;
}
S_80050BA4_sub;

extern void *link_seventeen_indexed_entries(void *a0);
extern void init_gauge_object(void *a0, void *a1);
extern void enqueue_script_message_command(void);
extern void invoke_leading_object_callback(void *a0);

/* Retail materializes a fresh %hi(D_800814A0) for the store after the |= load
 * destroyed the address register; cdk cc1 otherwise CSEs the address across
 * load+store. The absolute-bound section alias (LEAD-24 idiom, same cohort as
 * w_80050DA8/w_80051F58, same global) forces per-access lui. */

/* Creates an owner and its companion object, flagging failed setup for cleanup. */
void *create_gauge_with_selection_menu(s32 context)
{
    void *owner;
    S_80050BA4_s1 *object;
    S_80050BA4_sub *state;
    void *resource;

    owner = allocate_flagged_object_node(0);
    if (owner == 0) {
        return 0;
    }
    object = allocate_flagged_object_node(0);
    if (object != 0) {
        state = (S_80050BA4_sub *) (((u8 *) object) + 0x20);
        state->field_0xA0 = owner;
        if (allocate_selection_menu_entry_buffers(state, 0x11) != 0) {
            object->field_0xC = &object->field_0x78;
            state->field_0x64 = link_seventeen_indexed_entries(state->field_0x68);
            init_gauge_object(state, (void *) context);
            object->field_0x10 = (void *) invoke_leading_object_callback;
            resource = create_animated_selection_menu((void *) 2);
            state->field_0x28 = resource;
            if (resource != 0) {
                enqueue_script_message_command();
                register_node(object, (void *) draw_tinted_node_sprites_scratch);
                return owner;
            }
        }
        release_null_terminated_entries(&state->field_0x6c);
        object->field_0x1E |= 0x8000;
        D_800814A0_abs |= 0x8000;
    }
    return owner;
}
