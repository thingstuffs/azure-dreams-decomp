#include "common.h"

typedef struct S_800C2130_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800C2130_0;   /* arg0 in func_800C2130 */


extern s32 func_8008D344();
extern s32 func_80098864();
extern void func_80098B38();
extern s32 func_800990FC();
extern s32 func_80099194();
extern void func_80099290();
extern void func_800A5720();
extern void func_800A5F38();
extern void func_800A6480();
extern s32 func_800AD6FC();
extern void func_800C4D78();

extern s32 D_80082E80;
extern s8 D_80082EA6;
extern s32 D_80083460;
extern s32 D_80083780;
extern u8 D_800DDE84[];
extern u8 D_800E1567[];
extern u8 D_800E3648[];
extern u8 *D_800E3D7C;


/* Apply an entity event or mark eligible slots, then finish the event. */
s32 func_800C2130(S_800C2130_0 *entity, s32 event, s16 event_type, s32 event_arg) {
    s32 message_arg;
    volatile u8 *slot;
    u8 *event_state;
    u16 *pending_count;
    s32 message_buf;
    s32 message_end;
    s32 slot_index;
    u8 slot_flags;

    if (event_type == 0xD) {
        return func_80098864(event, event_arg);
    }
    if (entity == D_800E3D7C) {
        entity->unk_110 = event;
        func_8008D344(entity, &D_80083780, &D_80082E80, entity);
        return 0;
    }
    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A6480(entity, event);
        if (func_800AD6FC(
                entity,
                ((u16 *)D_800DDE84)[entity->unk_13] & 3,
                event) == 0) {
            func_800A5F38(entity, event);
            return 1;
        }
        goto final;
    }

    func_800C4D78(0xC02020, 1);
    message_buf = func_800990FC();

    message_arg = message_buf;
    if (D_80082EA6 >= 0) {
        slot_index = 0;
        slot = D_800E3648;
        do {
            if (slot[1] != 0 && slot[0] != 0) {
                slot_flags = slot[3];
                if (!(slot_flags & 0x40)) {
                    slot[3] = slot_flags | 0x80;
                }
            }
            slot_index++;
            slot += 4;
        } while (slot_index < 0x20);

        func_80099290(message_arg);
    } else {
        message_end = func_80099194(D_800E1567, message_buf);
        func_80099290(message_end);
    }
    func_800A5720(message_buf);

final:
    event_state = (u8 *)&D_80083460;
    pending_count = (u16 *)(event_state + 0xA);
    *pending_count = *pending_count - 1;
    func_80098B38(event);
    return 1;
}
