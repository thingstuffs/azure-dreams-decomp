#include "common.h"

extern void func_8008D330();
extern void func_800A63B8();
extern s32 func_800AD6FC();
extern void func_800A5F38();
extern void func_800D4FC8();
extern void func_80042984();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern s32 func_80099734();
extern void func_80099290();
extern void func_800A5720();
extern void func_80098B38();

extern u8 *D_800E3D7C[];
extern u8 D_80083780[];
extern u8 D_80082E80[];
extern u16 D_800DDE84[];
extern u8 D_8006DE24[];
extern u8 D_800E13FB[];
extern u8 D_800E1402[];
extern u8 D_800E1411[];
extern u8 D_800E1426[];
extern u8 D_80089380[];
extern u8 D_80083460[];

/* Changes the entity's element, updates its slots, and displays the result. */
s32 func_800C0B60(u8 *target, u8 *event_data, s32 value)
{
    u8 *target_copy = target;
    register u8 *entity ASM_REG("$17") = target_copy;
    u8 *event = event_data;
    s32 message_start;
    u8 *message;
    s32 message_buffer;
    s32 message_end;
    register s32 slot_index;
    u8 *slot;

    if (entity == D_800E3D7C[0]) {
        *(u8 **)(entity + 0x110) = event;
        ASM_KEEP_NV(target_copy);
        func_8008D330(target_copy, D_80083780, D_80082E80, target_copy);
        do {
            return 0;
        } while (0);
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, event, (s16)value);
        if (func_800AD6FC(entity, (D_800DDE84[entity[0x13]] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
        *(s32 *)(entity + 0x14) &= -8;
        *(s32 *)(entity + 0x1C) &= -8;
        ASM_MEM_BARRIER();
        {
            u8 *effect_target;
            s32 color_mask;
            s32 effect_code;
            s32 entity_flags;
            s32 base_flags;
            s32 event_type;
            event_type = event[0];
            if (event_type == 5) {
                {
                    u8 *message_page;
                    message_page = (u8 *)0x800E0000;
                    ASM_KEEP_NV(message_page);
                    message = message_page + 0x13FB;
                }
                {
                    effect_target = entity - 32;
                    color_mask = 0xF0;
                    effect_code = 0x81C;
                    entity_flags = *(s32 *)(entity + 0x14) | 1;
                    base_flags = *(s32 *)(entity + 0x1C) | 1;
                }
            } else if (event_type == 6) {
                ASM_SCHED_BARRIER();
                {
                    u8 *message_page;
                    message_page = (u8 *)0x800E0000;
                    ASM_KEEP_NV(message_page);
                    message = message_page + 0x1402;
                }
                {
                    effect_target = entity - 32;
                    color_mask = 0xF00000;
                    effect_code = 0x81C;
                    entity_flags = *(s32 *)(entity + 0x14) | 2;
                    base_flags = *(s32 *)(entity + 0x1C) | 2;
                }
            } else {
                {
                    u8 *message_page;
                    message_page = (u8 *)0x800E0000;
                    ASM_KEEP_NV(message_page);
                    message = message_page + 0x140A;
                }
                effect_target = entity - 32;
                color_mask = 0xF000;
                effect_code = 0x81C;
                entity_flags = *(s32 *)(entity + 0x14) | 4;
                base_flags = *(s32 *)(entity + 0x1C) | 4;
            }
            *(s32 *)(entity + 0x14) = entity_flags;
            *(s32 *)(entity + 0x1C) = base_flags;
            func_800D4FC8(effect_target, color_mask, effect_code);
        }
        func_80042984(entity);

        slot = entity + 8;
        for (slot_index = 0; slot_index < 3; slot_index++, slot += 3) {
            if (slot[0] != 0) {
                s32 item = slot[0];
                s32 flags = *(s32 *)(entity + 0x14);

                if (((D_8006DE24[item * 20 + 16] & 7) & flags) == 0) {
                    if (flags & 1) {
                        slot[0] = ((item - 1) / 3) * 3 + 1;
                    } else if (flags & 2) {
                        slot[0] = ((item - 1) / 3) * 3 + 2;
                    } else if (flags & 4) {
                        slot[0] = ((item - 1) / 3) * 3 + 3;
                    }
                }
            }
        }

        if (*(s32 *)(entity + 0x14) & 0x4000) {
            message_buffer = func_800990FC();
            {
                register u8 *message_entity ASM_REG("$4");
                register s32 text_buffer ASM_REG("$5");
                message_entity = entity;
                text_buffer = message_buffer;
                message_start = text_buffer;
                message_end = func_80099734(message_entity, text_buffer);
            }
            message_end = func_80099194(D_800E1411, message_end);
            message_end = func_80099194(message, message_end);
            goto message_join;
        }
    } else {
        message_buffer = func_800990FC();
        {
            u8 *message_prefix;
            register s32 text_buffer ASM_REG("$5");
            message_prefix = D_800E1426;
            ASM_KEEP(message_prefix);
            text_buffer = message_buffer;
            message_start = text_buffer;
            message_end = func_80099194(message_prefix, text_buffer);
        }
        message_end = func_80099734(entity, message_end);
message_join:
        message_end = func_80099194(D_80089380, message_end);
        func_80099290(message_end);
        func_800A5720(message_start);
    }

    func_80098B38(event);
    {
        u8 *event_state;
        event_state = D_80083460;
        *(u16 *)(event_state + 0xA) -= 1;
    }
    return 1;
}
