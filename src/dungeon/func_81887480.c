#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

#include "m2c_compat.h"



/* Creates an object, copies three source fields to its child, and runs 16 child setup steps. */
void *create_an_copies_three_source_fields_child_runs_n_16_child_setup(s32 value, void *source, s32 unused, s32 context)
{
    register u32 saved_context;
    s32 adjusted_value;
    s32 step;
    void *child;
    void *object;
    u16 counter;

    saved_context = context;
    adjusted_value = value - 0x20;
    object = func_8003FD64(2, adjusted_value);
    if (object != 0) {
        counter = D_80026324[0];
        *(M2C_UNK **)((u8 *)object + 0x10) = create_radial_effect_from_source;
        D_80026324[0] = counter + 1;
        func_8004491C(object, build_shaded_quads_adjacent_vertex_rows_adds_them_ordering_table);

        child = *(void **)((u8 *)object + 8);
        *(u16 *)((u8 *)child + 2) = *(u16 *)((u8 *)source + 2);
        step = 0;
        *(u16 *)((u8 *)child + 6) = *(u16 *)((u8 *)source + 6);
        *(u16 *)((u8 *)child + 0xA) = *(u16 *)((u8 *)source + 0xA);
        source = (void *)adjusted_value;
        *(s32 *)((u8 *)object + 0x20) = saved_context;

        do {
            create_object_offset(child, (s16)(step << 8), 0x40, -0x100, source);
            step += 1;
        } while (step < 0x10);
    }
    return object;
}
