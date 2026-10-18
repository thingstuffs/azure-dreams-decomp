#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800B1BEC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x34];
    void * unk_44;
} S_800B1BEC_0;   /* part in create_dual_buffer_object */

typedef struct S_800B1BEC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800B1BEC_1;   /* object in create_dual_buffer_object */


extern void *func_8004B404(s32);
extern void func_8004B1A4(void *);
extern void initialize_four_anchored_nodes(void *);
extern void *process_context_with_selector_4(void *);
extern void build_owned_floating_number_widget(void *, s32, s32, s32);
extern void func_8004491C(void *, void *);
extern void lower_value_toward_target(void);

extern u8 D_8004CAA0[];

/* Create an object with two buffers and initialize its state and position. */
void *create_dual_buffer_object(s32 setup_value, s32 x, s32 y)
{
    void *object;
    S_800B1BEC_0 *part;
    void *second_buffer;
    u16 object_flags;
    u32 global_flags;

    object = func_8003FC64(0);
    if (object != 0) {
        part = (u8 *)object + 0x20;
        part->unk_08 = func_8004B404(0xCC);
        second_buffer = func_8004B404(0xCC);
        part->unk_0C = second_buffer;

        if (part->unk_08 != 0 && second_buffer != 0) {
            ((S_800B1BEC_1 *)object)->unk_0C = (u8 *)object + 0x58;
            initialize_four_anchored_nodes(part);
            part->unk_44 = process_context_with_selector_4((u8 *)object + 0x68);
            build_owned_floating_number_widget(part, setup_value, x, y);
            func_8004491C(object, D_8004CAA0);
            ((S_800B1BEC_1 *)object)->unk_10 = lower_value_toward_target;
        } else {
            func_8004B1A4(part->unk_08);
            func_8004B1A4(part->unk_0C);
            object_flags = ((S_800B1BEC_1 *)object)->unk_1E | 0x8000;
            global_flags = ((u32)object_flag_block.flags) | 0x8000;
            ((S_800B1BEC_1 *)object)->unk_1E = object_flags;
            object_flag_block.flags = global_flags;
        }
    }
    return object;
}
