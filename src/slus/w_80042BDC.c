#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_80042BDC {
    /* 0x00 */ u8   pad00[0x13];
    /* 0x13 */ u8   x13;
    /* 0x14 */ u32  x14;
    /* 0x18 */ u8   pad18[0x1C - 0x18];
    /* 0x1C */ u32  x1C;
    /* 0x20 */ u8   pad20[0x25 - 0x20];
    /* 0x25 */ u8   x25;
    /* 0x26 */ u8   pad26[0x60 - 0x26];
    /* 0x60 */ void *x60;
    /* 0x64 */ u8   pad64[0x71 - 0x64];
    /* 0x71 */ u8   x71;
    /* 0x72 */ u8   pad72[0x88 - 0x72];
    /* 0x88 */ s16  x88;
    /* 0x8A */ u16  x8A;
    /* 0x8C */ u8   pad8C[0x98 - 0x8C];
    /* 0x98 */ u16  x98;
    /* 0x9A */ u8   pad9A[0xA6 - 0x9A];
    /* 0xA6 */ u16  xA6;
    /* 0xA8 */ u8   xA8;
} S_80042BDC;

/* child object at *(ent - 0x14) */
typedef struct S_80042BDC_child {
    /* 0x00 */ u8  pad00[0x12];
    /* 0x12 */ s16 x12;
    /* 0x14 */ u8  pad14[0x24 - 0x14];
    /* 0x24 */ u8  x24;
    /* 0x25 */ u8  x25;
} S_80042BDC_child;



extern void *D_800E3DF0[32];

extern char D_800E1D55[];
extern char D_800E1D61[];
extern char D_800E1D80[];
extern char D_800E1D9F[];
extern char D_800E1DCF[];
extern char D_800E1DEE[];
extern char D_800E1E0D[];
extern char D_800E1E32[];
extern char D_800E1E4B[];
extern char D_800E1E6A[];
extern char D_800E1E8C[];
extern char D_800E1EC1[];
extern char D_800E1EF7[];
extern char D_800E1F1C[];
extern char D_800E1F41[];

typedef S_80042BDC *(*Ctor_80042BDC)(int a0, int a1, int a2, int a3);

extern void          *func_800990FC(void);
extern int            func_80099734(S_80042BDC *ent, void *ctx);
extern int            func_80099194(char *str, int arg);
extern int            func_80099290(int arg);
extern void           func_800A5720(void *ctx);
extern void           func_800AA53C(S_80042BDC *ent);
extern void           func_800D5460(void *p, int a1, int a2);
extern void          *func_800A1618(int a0, s16 a1);
extern void           func_8009A3D0(int a0, int a1, int a2);
extern Ctor_80042BDC  func_800A0B94(int a0, void *a1, int a2);
extern void           func_8003F320(void);
extern void           func_8004397C(S_80042BDC *ent);
extern void           func_80042710(S_80042BDC *obj, S_80042BDC *ent);
extern void           func_80042984(S_80042BDC *obj);
extern void           func_800A9A0C(S_80042BDC *obj);
extern int            func_800A1BD0(S_80042BDC *ent);
extern void           func_800AA888(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800AC82C(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800A32A4(S_80042BDC *ent);
extern void           func_8009A028(S_80042BDC *ent);
extern void           func_8009A21C(int a0, int a1, int a2);
extern void           func_800AA36C(S_80042BDC *ent, int a1, S_80042BDC_child *a2, S_80042BDC *a3);
extern void           func_80041E70(S_80042BDC *ent);

/* Dispatch entity actions, update flags, and create a replacement entity when requested. */
void func_80042BDC(S_80042BDC *ent, s16 action) {
    S_80042BDC *spawn_result;
    S_80042BDC *spawn_result_2;
    S_80042BDC *message_ctx;
    S_80042BDC_child *child;
    s32 action_index;
    action_index = (s16)(action - 1);
    switch (action_index) {
    case 0:
        ent->x1C &= ~0x200;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1D55, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 1:
        ent->x1C &= ~0x400;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1D61, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 2:
        ent->x1C &= ~0x10;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1D80, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        if (ent->x13 != 0) {
            func_800AA53C(ent);
        }
        break;
    case 3:
        ent->x1C &= ~0x20;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1D9F, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 4:
        ent->x1C &= ~0x40;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1DCF, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 5:
        ent->x1C &= ~0x80;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1DEE, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 6:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1E0D, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 7:
        ent->x1C &= ~0x800;
        break;
    case 8:
        ent->x1C &= ~0x1000;
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1E32, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 9: {
            s32 spawn_mode;
            int is_registered;
            int tile_mask;
            s16 has_owner;
            Ctor_80042BDC create_entity;
            u32 entity_flags;

            if (ent->x13 != 0x2E) {
                if (ent->x13 != 0) {
                    goto check_2E;
                }
            }
            func_800D5460((u8 *)ent - 0x20, 0x20A0A0, 0x613);
            if (ent->x13 == 0) {
                goto L_print4B;
            }
        check_2E:
            spawn_mode = 1;
            if (ent->x13 == 0x2E) {
                child = *(S_80042BDC_child **)((u8 *)ent - 0x14);
                entity_flags = ent->x14;
                ent->x13 = ent->xA8;
                if (entity_flags & 0x4000) {
                    spawn_mode = 3;
                }
                {
                    S_80042BDC *resource = func_800A1618(ent->x13, spawn_mode);
                    tile_mask = 0x3000;
                    {
                        ent->x1C |= ((u32)(0x10000));
                    }
                    spawn_result = resource;
                }
                is_registered = (ent->x14 >> 14) & 1;
                {
                    int tile_x = child->x24;
                    int tile_y = child->x25;
                    if (ent->x1C & 0x2000) {
                        tile_mask = 0x300;
                    }
                    func_8009A3D0(tile_x, tile_y, tile_mask);
                }
                func_8004397C(ent);

                create_entity = func_800A0B94(ent->x13, spawn_result, 1);
                func_8003F320();
                spawn_result_2 = create_entity(is_registered, child->x24, child->x25, ent->x88);

                spawn_result_2->x14 = 0;
                spawn_result_2->x1C = 0;
                has_owner = (ent->x1C >> 19) & 1;
                func_80042710(spawn_result_2, ent);
                func_80042984(spawn_result_2);

                if (dungeonStatus.flags & 0x1000) {
                    if (ent->x71 > (s16)ent->x8A) {
                        dungeonStatus.unk_08 -= (ent->x71 - ent->x8A);
                    }
                }
                func_800A9A0C(spawn_result_2);
                spawn_result_2->x1C &= ~0x10000;

                if (ent->x14 & 0x4000) {
                    u8 *slot_base;
                    u8 *slot_data;
                    int entity_index;
                    spawn_mode = func_800A1BD0(ent);
                    slot_base = (u8 *)((s16)spawn_mode * 4 + (u32)((u8 *)D_800E3D7C));
                    slot_data = *(u8 **)(slot_base + 0xD0);
                    entity_index = *(u8 *)(slot_data + 3) & 0x1F;
                    D_800E3DF0[entity_index] = spawn_result_2;
                    *(S_80042BDC **)(slot_base + 0xAC) = spawn_result_2;
                }

                {
                    int attach_owner = has_owner;
                    if (attach_owner) {
                        S_80042BDC *owned_ent = spawn_result_2;
                        u8 *owner_data;
                        owner_data = ((u8 *)D_800E3D7C);
                        *(S_80042BDC **)(owner_data + 0x124) = spawn_result_2;
                        spawn_result_2->x60 = owner_data;
                        spawn_result_2->x1C |= 0x80000;
                        func_800AA888(owned_ent, *(int *)((u8 *)spawn_result_2 - 0x18), *(int *)((u8 *)spawn_result_2 - 0x14), spawn_result_2);
                        func_800AC82C(spawn_result_2, *(int *)((u8 *)spawn_result_2 - 0x18), *(int *)((u8 *)spawn_result_2 - 0x14), spawn_result_2);
                    } else {
                        if (spawn_result_2->x25 == 0) {
                            dungeonStatus.unk_0A += 1;
                            spawn_result_2->x1C &= ~0x8;
                        }
                    }
                }
                ent->x14 |= 0x20000000;
                func_800A32A4(ent);
                func_8009A028(ent);
                *(u16 *)((u8 *)ent - 2) |= 0x8000;
                objectFlagBlock.flags |= 0x8000;
                ent = spawn_result_2;
            }
        L_print4B:
            if (ent->x14 & 0x4000) {
                message_ctx = func_800990FC();
                func_80099290(func_80099194(D_800E1E4B, func_80099734(ent, message_ctx)));
                func_800A5720(message_ctx);
            }
            break;
        }
    case 26:
        child = *(S_80042BDC_child **)((u8 *)ent - 0x14);
        func_8009A21C(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        func_800AA36C(ent, *(int *)((u8 *)ent - 0x18), child, ent);
        break;
    case 10:
        child = *(S_80042BDC_child **)((u8 *)ent - 0x14);
        func_8009A3D0(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        ent->x1C &= ~0x2000;
        func_8009A21C(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        break;
    case 11:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1E6A, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        child = *(S_80042BDC_child **)((u8 *)ent - 0x14);
        func_8009A3D0(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        ent->x1C |= 0x2000;
        func_8009A21C(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        break;
    case 25:
        child = *(S_80042BDC_child **)((u8 *)ent - 0x14);
        ent->x98 &= 0x7FFF;
        func_8009A3D0(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        if (ent->x98 & 0x4000) {
            ent->x1C |= 0x2000;
        }
        func_8009A21C(child->x24, child->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
        child->x12 = ent->xA6;
        break;
    case 31:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1E8C, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 20:
    case 21:
    case 22:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1EC1, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 17:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1EF7, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 18:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1F1C, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }
        break;
    case 19:
        if (ent->x14 & 0x4000) {
            message_ctx = func_800990FC();
            func_80099290(func_80099194(D_800E1F41, func_80099734(ent, message_ctx)));
            func_800A5720(message_ctx);
        }

    }

    func_80041E70(ent);
}
