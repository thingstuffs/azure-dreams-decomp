#include "common.h"

typedef struct S_80098CF8_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x6];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_80098CF8_0;   /* s0 in func_80098CF8 */

typedef struct S_80098CF8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
} S_80098CF8_1;   /* s2 in func_80098CF8 */

typedef struct S_80098CF8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098CF8_2;   /* primitive in func_80098CF8 */

typedef struct S_80098CF8_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80098CF8_3;   /* s5 in func_80098CF8 */

typedef struct S_80098CF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80098CF8_4;   /* s4 in func_80098CF8 */

typedef struct S_80098CF8_5 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x4];
    s32 unk_98;
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    u8 pad_AA[0x2];
    s16 unk_AC;
} S_80098CF8_5;   /* state in func_80098CF8 */

typedef struct S_80098CF8_6 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x20];
    void * unk_BC;
    u8 pad_C0[0x64];
    s32 unk_124;
} S_80098CF8_6;   /* s3 in func_80098CF8 */

typedef struct S_80098CF8_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_80098CF8_7;   /* (void *)a1 in func_80098CF8 */



extern void func_80048A44();
extern void func_800982A8();
extern void func_80098614();
extern void func_80098B38();
extern s32 func_800990FC(void *, s32, void *, void *);
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_8009929C();
extern s32 func_80099368();
extern void func_800A56E0();
extern void func_800A5720();
extern void *func_800A8608();

extern u8 D_80081484[];
extern s16 D_80083228;
extern u8 D_8008D470[];
extern u8 D_800DD0B8[8];
extern u8 D_800E08CC[];
extern u8 D_800E08E5[];
extern u8 D_800E08F1[];
extern u8 D_800E0919[];

/* Check the item, report restrictions, and create an action object for the actor and target. */
void *func_80098CF8(void *actor_arg, s32 action_id, void *target_arg, void *item_arg)
{
    register void *message ASM_REG("$4") = actor_arg;

    register void *actor ASM_REG("$19") = message;
    s32 action = action_id;
    void *target = target_arg;
    register void *item ASM_REG("$18") = item_arg;
    void *actor_state;
    register void *result;
    s32 message_id;
    void *primitive;
    void *state;
    s32 text_cursor;

    ASM_KEEP_NV(actor);
    actor_state = actor;
    result = D_80081484;
    if ((item != result) && (((S_80098CF8_0 *)result)->unk_01 != 0)) {
        message_id = func_800990FC(message, action_id, target_arg, item_arg);
        text_cursor = func_8009929C(8, message_id);
        text_cursor = func_80099368(item, text_cursor);
        text_cursor = func_80099194(D_800E08CC, text_cursor);
        text_cursor = func_80099368(result, text_cursor);
        message = D_800E08E5;
print_message:
        text_cursor = func_80099194(message, text_cursor);
        func_80099290(text_cursor);
        func_800A5720(message_id);

        ASM_KEEP(action);
        ASM_KEEP(target);
        ASM_KEEP(item);
        ASM_KEEP(actor_state);
        goto return_zero;
    }

    if (((S_80098CF8_1 *)item)->unk_00.at03.v & 0x20) {
        message_id = func_800990FC(message, action_id, target_arg, item_arg);
        result = (void *)func_8009929C(8, message_id);
        if (((S_80098CF8_1 *)item)->unk_00.at03.v & 0x40) {
            func_800A56E0(0x70A);
            text_cursor = func_80099368(item, result);
            message = D_800E08F1;
            goto print_message;
        }

        text_cursor = func_80099368(item, result);
        text_cursor = func_80099194(D_800E0919, text_cursor);
        func_80099290(text_cursor);
        func_800A5720(message_id);
        if (((S_80098CF8_1 *)item)->unk_00.at01.v == 0x11) {
            func_80098614(actor_state, item);
        } else {
            func_800982A8(actor_state, item);
        }
    }

    result = func_800A8608((u8 *)actor - 0x20, item, 0, 0, 0);
    if (result == 0) {
        goto return_zero;
    }

    {
        s32 height;

        ((S_80098CF8_0 *)result)->unk_10 = D_8008D470;
        primitive = ((S_80098CF8_0 *)result)->unk_08;
        ((S_80098CF8_2 *)primitive)->unk_02 = (((S_80098CF8_3 *)target)->unk_24 << 6) + 0x20;
        ((S_80098CF8_2 *)primitive)->unk_06 = (((S_80098CF8_3 *)target)->unk_25 << 6) + 0x20;
        height = ((S_80098CF8_4 *)actor_state)->unk_88;
        message = target;
        ((S_80098CF8_2 *)primitive)->unk_0A = height - 0x30;

        state = (u8 *)result + 0x20;
        {
            register s32 data_word ASM_REG("$5");
            s32 item_word;

            data_word = ((S_80098CF8_1 *)item)->unk_00.at00.v;
            ((S_80098CF8_5 *)state)->unk_AC = 1;
            ((S_80098CF8_5 *)state)->unk_90 = message;
            ((S_80098CF8_5 *)state)->unk_8C = action;
            ((S_80098CF8_5 *)state)->unk_A8 = 6;
            ((S_80098CF8_5 *)state)->unk_98 = data_word;
            data_word = 0x80080000;
            ASM_KEEP(data_word);
            ((S_80098CF8_6 *)actor)->unk_BC = item;
            item_word = ((S_80098CF8_1 *)item)->unk_00.at00.v;
            ((S_80098CF8_5 *)state)->unk_9C = (u8 *)data_word + 0x1484;
            ((S_80098CF8_6 *)actor)->unk_8C = 0;
            ((S_80098CF8_6 *)actor)->unk_124 = 0;
            ((S_80098CF8_7 *)((void *)data_word))->unk_1484 = item_word;
            data_word = (s32)D_800DD0B8;
            ((S_80098CF8_6 *)actor)->unk_9A = 0x1B;
            ((S_80098CF8_6 *)actor)->unk_9B = 0;
            (*(void * *)((u8 *)message + 0x2C)) = (void *)data_word;

            func_80048A44(
                message,
                ((u8 *)data_word)[((D_80083228 + ((S_80098CF8_4 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                0,
                1);
            func_800A56E0(0x511);
            ((S_80098CF8_4 *)actor_state)->unk_1C |= 0x100000;
            func_80098B38(item);
        }
    }
    return result;

return_zero:
    return 0;
}
