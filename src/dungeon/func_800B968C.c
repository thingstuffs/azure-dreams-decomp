#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 fieldA;
} D_80083460_t;

extern s32 func_8008D344();
extern s32 func_8008D368();
extern s32 func_80098864(u8 *, s32);
extern s32 func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099368();
extern s32 func_8009955C();
extern s32 func_800997FC();
extern s32 func_800998C0();
extern s32 func_80099978();
extern s32 func_800A5720();
extern s32 func_800A5F38();
extern s32 func_800A6480();
extern s32 func_800AD6FC();

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_8008936C[];
extern u8 D_80089370[];
extern u8 D_800DD158[];
extern u16 D_800DDE84[];
extern u8 D_800E118C[];
extern u8 D_800E11AB[];
extern u8 D_800E11D7[];
extern u8 *D_800E3D7C[];

/* Applies an item effect to its target and prepares the resulting message. */
s32 func_800BEDEC(u32 target_addr, u8 *used_item, s16 effect_type, s32 effect_value) {
    register u8 *actor ASM_REG("$4");
    register u32 target ASM_REG("$16") = target_addr;
    register s32 text_cursor;
    u8 *linked_item;
    register s32 text_start;
    u8 *item = used_item;

    ASM_KEEP_NV(target);

    if (effect_type == 0xD) {
        do {
            return func_80098864(item, effect_value);
        } while (0);
    }

    actor = D_800E3D7C[0];
    if ((u8 *)target == actor) {
        u8 item_flags;
        s32 result;

        ASM_KEEP(actor);
        *(u8 **)(actor + 0x110) = item;
        func_8008D344(actor, D_80083780, D_80082E80, actor);
        item_flags = item[3];
        result = 0;
        item[3] = item_flags & 0xDF;
        return result;
    }

    if (target <= 0x9FFFFFFF) {
        func_800A6480(target, item, effect_type);
        if (func_800AD6FC(target, D_800DDE84[*(u8 *)(target + 0x13)] & 3, 0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
        D_80083460.fieldA--;
        func_80098B38(item);
        return 1;
    }

    linked_item = *(u8 **)(actor + 0x50);
    if (linked_item != 0) {
        if (!(item[3] & 0x20)) {
            u8 item_flags;
            register s32 result;

            *(s32 *)(actor + 0x114) = 0x802020;
            func_8008D368(actor, D_80083780, D_80082E80, D_800DD158, 0);
            item_flags = item[3];
            result = 0;
            item[3] = item_flags | 0x20;
            return result;
        }

        {
            s32 text_end;
            register u8 *message_text ASM_REG("$4");
            register s32 message_end ASM_REG("$5");

            if (!(linked_item[3] & 0x40)) {
                s32 next_cursor;
                s32 saved_cursor;

                text_start = func_800990FC();
                text_cursor = func_8009955C(linked_item, text_start);
                if (*(s8 *)(linked_item + 2) < 0x63) {
                    linked_item[2] = linked_item[2] + 1;
                }
                text_cursor = func_80099978(func_80099194(D_800E118C, text_cursor));
                next_cursor = func_80099194(D_8008936C, text_cursor);
                target = text_cursor - 2;
                text_cursor = next_cursor;
                next_cursor = func_80099368(linked_item, text_cursor);
                saved_cursor = text_cursor;
                text_cursor = next_cursor;
                func_800998C0(target, saved_cursor);
                message_text = D_80089370;
                message_end = text_cursor;
            } else {
                text_start = func_800990FC();

                text_end = func_80099368(linked_item, text_start);
                message_text = D_800E11AB;
                message_end = text_end;
            }
            func_80099290(func_80099194(message_text, message_end));
        }
        func_800A5720(text_start);
    } else {
        func_800997FC(D_800E11D7, effect_value, effect_type);
    }
    D_80083460.fieldA--;
    func_80098B38(item);
    return 1;
}
