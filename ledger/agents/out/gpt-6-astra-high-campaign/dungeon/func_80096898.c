#include "common.h"

#define NULL ((void *)0)

s32 func_800A6D30(void *, void *, s32, s32);
s32 func_800A0818(u8, u8, u8, u8, void *);
void func_800B4C7C(s32, void *, s32, s32);
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
s32 func_8003AD08(s32, s32);
s32 func_80099734(void *, s32);
void func_80099290(s32);
void func_800A5720(s32);

extern u8 D_80088CAC[];
extern u8 D_800E0D51[];
extern u8 D_800E0D6D[];

/* Randomly adds a quarter of the source value to the target and reports the change. */
void func_8009BFF8(void *source, void *target, s32 passthru_2, s32 passthru_3) {
    int direction_aux;
    s32 amount;
    s16 signed_amount;
    s32 message_start;
    s32 message_end;
    u8 *type_data;
    void *source_entity;
    void *target_entity;

    type_data = *(u8 **)((s8 *)source + 0x50);
    if (type_data != NULL && *type_data == 0xB && !(func_800A6D30(source, target, passthru_2, passthru_3) & 3)) {
        amount = ((s32)(*(u16 *)((s8 *)source + 0x64) << 0x10)) >> 0x12;
        signed_amount = amount;
        *(u16 *)((s8 *)target + 0x64) += amount;
        if (signed_amount != 0) {
            source_entity = *(void **)((s8 *)source - 0x14);
            target_entity = *(void **)((s8 *)target - 0x14);
            *(void **)((s8 *)target + 0x60) = source;
            *(s16 *)((s8 *)target + 0x6A) = func_800A0818(
                *(u8 *)((s8 *)source_entity + 0x24),
                *(u8 *)((s8 *)source_entity + 0x25),
                *(u8 *)((s8 *)target_entity + 0x24),
                *(u8 *)((s8 *)target_entity + 0x25),
                &direction_aux
            );
            func_800B4C7C(3, target, -amount, 0);
            message_end = func_800990FC();
            message_start = message_end;
            message_end = func_80099194(D_800E0D51, message_start);
            message_end = func_8003AD08(-signed_amount, message_end);
            message_end = func_80099194(D_800E0D6D, message_end);
            message_end = func_80099734(target, message_end);
            message_end = func_80099194(D_80088CAC, message_end);
            func_80099290(message_end);
            func_800A5720(message_start);
        }
    }
}
