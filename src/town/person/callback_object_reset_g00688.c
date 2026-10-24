/* G00688: callback object reset. */
/* Original-file evidence (G00688): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CEC24. */
#include "town/person/callback_object_reset_g00688.h"

/* Prepare the context and forward the arguments to the next handler. */
void prepare_and_forward_callback(void *object, void *context, Func800CEC24Arg2 *callback_arg) {
    create_object_from_three_values(context);
    reset_object_entry_and_brighten(object, context, callback_arg);
}

/* Reset the object's table entry and brighten the packet to a clamped grayscale intensity. */
void reset_object_entry_and_brighten(void *object, void *draw_arg, Func800CEC24Arg2 *packet) {
    u32 intensity;

    initialize_object_entries((Struct800C5724 *)object, (s8 *)packet, (s32 *)D_800D6CA8);
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;

    intensity = packet->unkC;
    intensity += 0x20;
    if (intensity >= 0x100) {
        intensity = 0xFF;
    }

    packet->unkE = intensity;
    packet->unkD = intensity;
    packet->unkC = intensity;
    apply_object_setup_and_update(object, draw_arg, packet);
}
