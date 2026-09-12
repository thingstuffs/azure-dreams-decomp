#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C08A4_0 {
    void * unk_00;
    u8 pad_04[0x27];
    u8 unk_2B;
    u8 pad_2C[0x34];
    u8 unk_60;
    u8 unk_61;
    u8 pad_62[0x1];
    u8 unk_63;
    u8 pad_64[0xC4];
    u8 * unk_128;
} S_800C08A4_0;   /* temp_s1 in func_800C08A4; pointer addresses record offset 0x18 */

typedef struct S_800C08A4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800C08A4_1;   /* temp_s0 in func_800C08A4 */

typedef struct S_800C08A4_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C08A4_2;   /* counter_base in func_800C08A4 */


extern u8 *D_800E3D7C;
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern s32 D_80083460[3];
M2C_UNK func_8008D344();
M2C_UNK func_80098864();
M2C_UNK func_80098B38();
s32 func_8004A658();
s32 func_800998C0();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_80099368();
s32 func_80099734();
s32 func_80099978();
M2C_UNK func_800A5720();
M2C_UNK func_800A5F38();
M2C_UNK func_800A6480();
s32 func_800A6D30();
M2C_UNK func_800A7A7C();
s32 func_800AD6FC();
extern M2C_UNK D_80089378;
extern M2C_UNK D_8008937C;
extern M2C_UNK D_800E13DA;
extern M2C_UNK D_800E13E9;

/* Applies an entity action to a target and updates the pending count. */
s32 func_800C08A4(u8 *source, u8 *target, s16 action, M2C_UNK context) {
    s32 entity_value;
    s32 event_value;
    s32 external_entity_value;
    s32 external_event_value;
    u8 *compare_ptr;
    s32 script;
    u8 *entity;
    S_800C08A4_1 *position;

    entity = source;
    if (action == 0xD) {
        if (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_2B == 0x16) {
            ASM_KEEP_NV(action); /* MATCH: retain the existing a2 value across the argument setup. */
            if ((func_800A6D30(target, target, action, context) & 1) == 0) {
                goto main_path;
            }
        }
        return func_80098864(target, context);
    }
main_path:
    compare_ptr = D_800E3D7C;
    if (entity == compare_ptr) {
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_128 = target;
        func_8008D344(entity, D_80083780, D_80082E80, entity);
        return 0;
    }
    compare_ptr = (u8 *) 0x9FFFFFFF;
    if ((u32) entity <= (u32) compare_ptr) {
        if (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_2B != 0x16) {
            func_800A6480(entity, target);
            if (func_800AD6FC(entity, (D_800DDE84[((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_2B] >> 4) & 3, 0) == 0) {
                func_800A5F38(entity, target);
                return 1;
            }
            func_80098B38(target);
            goto decrement;
        }
        position = ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_00;
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 & 0xDF);
        func_800A7A7C((u16) position->unk_02 >> 6, (u16) position->unk_06 >> 6, position->unk_0A, func_8004A658(((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_61, ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_60), entity + 0x48);
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_60 = (u8) *target;
        ((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 = (u8) (((S_800C08A4_0 *)((u8 *)entity - 0x18))->unk_63 | 0x20);
        script = func_800990FC();
        entity_value = func_80099734(entity, script);
        event_value = func_80099194(&D_800E13DA, entity_value);
        {
            s32 node;
            s32 node_offset;
            s32 saved_node;
            s32 result;

            node = func_80099978(event_value);
            saved_node = func_80099194(&D_80089378, node);
            node_offset = node - 2;
            ASM_KEEP_DEP_NV(node_offset, node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            ASM_KEEP(saved_node);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            node = saved_node;
            result = func_80099368(target, node);
            {

                entity_value = node;
                node = result;
                ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
                func_800998C0(node_offset, entity_value);
            }
            func_80099290(func_80099194(&D_8008937C, node));
        }
        func_800A5720(script);
        func_80098B38(target);
        goto decrement;
    }
    script = func_800990FC();
    external_entity_value = func_80099734(entity, script);
    external_event_value = func_80099194(&D_800E13E9, external_entity_value);
    {
        s32 node;
        s32 node_offset;
        s32 saved_node;
        s32 result;

        node = func_80099978(external_event_value);
        saved_node = func_80099194(&D_80089378, node);
        node_offset = node - 2;
        ASM_KEEP_DEP_NV(node_offset, node);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(saved_node);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        node = saved_node;
        result = func_80099368(target, node);
        {

            entity_value = node;
            node = result;
            ASM_KEEP(node);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
            func_800998C0(node_offset, entity_value);
        }
        func_80099290(func_80099194(&D_8008937C, node));
    }
    func_800A5720(script);
decrement:
    {
        u8 *counter_base = (u8 *) D_80083460;
        ((S_800C08A4_2 *)counter_base)->unk_0A = (u16) (((S_800C08A4_2 *)counter_base)->unk_0A - 1);
    }
    return 1;
}
