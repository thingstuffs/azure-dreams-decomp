#include "common.h"

extern void func_80047784();
extern s32 func_80047D44();
extern void func_80048088();
extern void func_8004827C();
extern void func_80099FDC();
extern void func_8009A21C();
extern s32 func_8009FB34();
extern void func_800A2B04();
extern void func_800A34BC();
extern void func_800BC26C();
extern s32 func_800BCB04();

extern u8 D_8006CCF8[];
extern u8 D_80080100[];
extern s32 D_80081488[];
extern s32 D_80083160[];
extern s8 D_800DCF4D[];
extern u8 D_800E8000[];

/* Initialize an entity sprite, its position, and direction-dependent display flags. */
void func_800A9C18(void *entity, void *position, void *sprite, s32 init_flags)
{
    s32 extra_flags;
    s32 mode;
    register s32 entity_kind ASM_REG("$3");
    u8 *entity_data;
    s16 *world_state;

    entity_data = (u8 *)entity + 0x20;
    extra_flags = init_flags & ~3;
    mode = init_flags & 3;

    if (mode == 2) {
        if ((extra_flags << 16) == 0) {
            *(s32 *)((u8 *)sprite + 0x28) =
                func_80047D44(*(u8 *)(entity_data + 0x13));
        } else {
            *(s32 *)((u8 *)sprite + 0x28) = D_80081488[0];
        }
        D_800DCF4D[0] = -1;
    } else {
        entity_kind = *(u8 *)(entity_data + 0x13);
        if (entity_kind != 0x38) {
            func_80048088(entity_kind);
        }
        func_8004827C(entity, *(u8 *)(entity_data + 0x13));
    }

    *(s8 *)((u8 *)sprite + 0x26) =
        func_8009FB34(*(u8 *)((u8 *)sprite + 0x24),
                      *(u8 *)((u8 *)sprite + 0x25));
    func_800A2B04(position,
                  *(u8 *)((u8 *)sprite + 0x24),
                  *(u8 *)((u8 *)sprite + 0x25));

    *(s16 *)(entity_data + 0x88) =
        func_800BCB04(*(u16 *)((u8 *)position + 2),
                      *(u16 *)((u8 *)position + 6),
                      (s16)(*(u16 *)((u8 *)position + 0xA) - 0x20));

    *(s16 *)((u8 *)sprite + 0x1E) = 0x1000;
    *(s16 *)((u8 *)sprite + 0x1C) = 0x1000;
    *(s32 *)((u8 *)sprite + 0xC) = 0x2C808080;
    *(u16 *)((u8 *)sprite + 0x14) |= 0x8000;

    world_state = (s16 *)D_80083160;
    func_80047784(sprite,
                  (*(u8 **)((u8 *)sprite + 0x2C))[
                      ((world_state[0x64] + *(s16 *)(entity_data + 0x2A) + 0x100) >> 9) & 7],
                  0);

    func_80099FDC(entity);
    if ((*(s32 *)(entity_data + 0x14) & 0x4000) == 0) {
        func_800A34BC(entity_data);
    }

    func_8009A21C(*(u8 *)((u8 *)sprite + 0x24),
                  *(u8 *)((u8 *)sprite + 0x25),
                  (*(s32 *)(entity_data + 0x1C) & 0x2000) ? 0x300 : 0x3000);

    *(s8 *)(entity_data + 0x71) = 0;
    *(s32 *)(entity_data + 0x1C) |= 0x40000000;
    func_800BC26C(entity, 0, (u8 *)sprite + 0x2C, entity_data + 0x2A);

    if (D_8006CCF8[
            ((world_state[0x64] + *(s16 *)(entity_data + 0x2A) + 0x100) >> 9) & 7] != 0) {
        *(u16 *)((u8 *)sprite + 0x14) |= 1;
        return;
    }
    *(u16 *)((u8 *)sprite + 0x14) &= 0xFFFE;
}
