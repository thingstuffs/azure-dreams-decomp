#include "common.h"

extern void func_80042B68();
extern void func_8008D330();
extern void func_80098B38();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800C4AFC();

extern u8 D_80082E80[12];
extern u8 D_80083460[12];
extern u8 D_80083780[12];
extern u16 D_800DDE84[];
extern u8 D_800E188B[];
extern void *D_800E3D7C[];

/* Updates an entity and its effects, decrementing the shared counter on completion. */
s32 func_800C4324(void *entity_arg, s32 amount_arg, s16 effect_arg)
{
    s32 amount = amount_arg;
    s32 initial_id;
    s32 selected_id;
    u8 *counter_base;

    if (entity_arg == D_800E3D7C[0]) {
        *(s32 *)((u8 *)entity_arg + 0x110) = amount;
        func_8008D330(((void *)(entity_arg)), D_80083780, D_80082E80, ((void *)(entity_arg)));
        return 0;
    }

    if ((u32)entity_arg <= 0x9FFFFFFF) {
        void *lookup_entity;
        u16 *type_table;
        s32 entity_type;

        func_800A63B8(entity_arg, amount, effect_arg);
        lookup_entity = entity_arg;
        entity_type = *((u8 *)entity_arg + 0x13);
        type_table = (u16 *)&D_800DDE84;
        if (func_800AD6FC(lookup_entity,
                         (type_table[entity_type] >> 6) & 3,
                         0) == 0) {
            func_800A5F38(entity_arg, amount);
            return 1;
        }
    }

    func_800C4AFC(*(s32 *)((u8 *)entity_arg - 0x18), 0xC02020, entity_arg);
    if (*(s32 *)((u8 *)entity_arg + 0x14) & 0x4000) {
        initial_id = func_800990FC();
        selected_id = initial_id;
        if (!(*(s32 *)((u8 *)entity_arg + 0x1C) & 0x10)) {
            selected_id = func_80099194(D_800E188B, initial_id);
        }
        func_80099290(selected_id);
        func_800A5720(initial_id);
    }
    func_80042B68(entity_arg, 3);
    func_80098B38(amount);
    counter_base = D_80083460;
    *(u16 *)(counter_base + 0xA) = *(u16 *)(counter_base + 0xA) - 1;
    return 1;
}
