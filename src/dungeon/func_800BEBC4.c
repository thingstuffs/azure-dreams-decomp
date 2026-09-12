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
    void *entry_entity = entity_arg;
    register void *entity ASM_REG("$17") = entity_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 amount = amount_arg;
    s32 initial_id;
    s32 selected_id;
    u8 *counter_base;

    if (entity == D_800E3D7C[0]) {
        *(s32 *)((u8 *)entity + 0x110) = amount;
        ASM_KEEP(entry_entity);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        func_8008D330(entry_entity, D_80083780, D_80082E80, entry_entity);
        return 0;
    }

    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if ((u32)entity <= 0x9FFFFFFF) {
        void *lookup_entity;
        u16 *type_table;
        s32 entity_type;

        func_800A63B8(entity, amount, effect_arg);
        lookup_entity = entity;
        ASM_KEEP(lookup_entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        type_table = (u16 *)0x800E0000;
        ASM_KEEP(type_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        entity_type = *((u8 *)entity + 0x13);
        ASM_KEEP(entity_type);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        type_table = (u16 *)((u8 *)type_table - 0x217C);
        ASM_KEEP(type_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        if (func_800AD6FC(lookup_entity,
                         (type_table[entity_type] >> 6) & 3,
                         0) == 0) {
            func_800A5F38(entity, amount);
            return 1;
        }
    }

    func_800C4AFC(*(s32 *)((u8 *)entity - 0x18), 0xC02020, entity);
    if (*(s32 *)((u8 *)entity + 0x14) & 0x4000) {
        initial_id = func_800990FC();
        selected_id = initial_id;
        if (!(*(s32 *)((u8 *)entity + 0x1C) & 0x10)) {
            selected_id = func_80099194(D_800E188B, initial_id);
        }
        func_80099290(selected_id);
        func_800A5720(initial_id);
    }
    func_80042B68(entity, 3);
    func_80098B38(amount);
    counter_base = D_80083460;
    *(u16 *)(counter_base + 0xA) = *(u16 *)(counter_base + 0xA) - 1;
    return 1;
}
