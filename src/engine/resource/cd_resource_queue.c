#include "common.h"

extern void create_callback_pair_payload(int a0, int a1, int a2, int a3);

/* Forwards two values to create_callback_pair_payload with two leading zero arguments. */
void create_callback_pair_default(int value, int unused_1, int unused_2, int extra_value)
{
    int saved_value = value;
    value = 0;
    create_callback_pair_payload(value, value, saved_value, extra_value);
}


/* Fixed input buffers and the shared texture-result pointer. */
extern u8 D_80016000[0x10];
extern u8 D_80023000[0x10];
extern void *D_8008152C;

extern void queue_entity_resource_descriptor_pair(void *a0, void *a1, u16 a2);

/* Registers callbacks for the fixed buffers and returns the result-pointer slot. */
void *queue_cd_resource(s32 id)
{
    queue_entity_resource_descriptor_pair(&D_80016000, &D_80023000, (u16)id);
    return &D_8008152C;
}
