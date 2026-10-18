typedef signed int s32;
typedef unsigned char u8;

extern u8 D_800BB6C4[];
extern void initialize_object_state_and_appearance(void *, void *, void *);

/* Set the object handler table, initialize its state, and set its counter to 30. */
void set_handler_variant_b_with_counter_30(void *object, void *context, void *state) {
    *(void **)((u8 *)object - 0x10) = D_800BB6C4;
    initialize_object_state_and_appearance(object, context, state);
    ((s32 *)state)[2] = 30;
}
