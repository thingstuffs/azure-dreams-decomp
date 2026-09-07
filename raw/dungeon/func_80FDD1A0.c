#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    u32 x;
    u32 y;
    u32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} VecData;

typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} ItemData;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

extern s32 func_8003F270(void);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern s32 func_800A94A0(void *, u8 *, s32, u16 *);
extern void func_800DA840(void *, s16);

extern s32 D_80045340;
extern ItemData D_8006DE24[];
extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D7960[];
extern u8 D_80170838[16];
extern u8 D_80170EA8;
extern u8 D_80174038[];
extern u8 D_80174078[];

void func_801729A0(void *arg0, VecData *arg1, void *arg2, void *arg3)
{
    static void *const kind_keep[] = {
        &&kind_1, &&kind_2, &&kind_3, &&kind_default,
        &&kind_5, &&kind_6, &&kind_7
    };
    register s32 zero ASM_REG("$0");
    s32 alternate = 0;
    void *object = (void *)zero;
    void *active;
    u8 *choice;
    u8 *global;
    ShortVec pos;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    switch (state) {
    case 0:
        if (FIELD(arg3, u32, 0x1C) & 0x2000) {
            u32 dispatch;

            dispatch = (FIELD(arg3, u16, 0x46) & 0x3FFF) - 1;
            if (dispatch >= 7) {
                goto kind_default;
            }
            (void)kind_keep;
            goto *(((void **)D_80170838)[dispatch]);

kind_7:
            alternate = 1;
            goto kind_3;
kind_6:
            alternate = 1;
            goto kind_2;
kind_5:
            alternate = 1;
            goto kind_1;
        }

        {
            s32 type;

            type = FIELD(arg3, u16, 0x46) & 0x3FFF;
            if (type == 2) {
                goto kind_2;
            }
            if (type < 3) {
                choice = 0;
                if (type == 1) {
                    goto kind_1;
                }
                goto selection_ready;
            }
            if (type != 3) {
                choice = 0;
                goto selection_ready;
            }
        }

kind_3:
        choice = (u8 *)arg3 + 0xE;
        goto selection_ready;
kind_2:
        choice = (u8 *)arg3 + 0xB;
        goto selection_ready;
kind_1:
        choice = (u8 *)arg3 + 8;
        goto selection_ready;
kind_default:
        choice = 0;

selection_ready:
        if (*choice == 0) {
            goto empty_selection;
        }
        FIELD(arg0, u16, 0x98) &= 0xFF7F;
        {
            register s32 active_result ASM_REG("$2");

            ASM_SCHED_BARRIER();
            active_result = alternate;
            ASM_KEEP(active_result);
            if (active_result != 0) {
                active = D_800814A8;
                FIELD(arg3, void *, 0x60) = active;
                goto copy_active_coords;
            }
        }

        {
            u8 item;

            item = *choice;
            if (D_8006DE24[item].type == 2) {
                active = FIELD(arg3, void *, 0x60);
                if (active != 0) {
                    register u8 *linked ASM_REG("$3");

copy_active_coords:
                    linked = FIELD(active, u8 *, -0x14);
                    ASM_KEEP(linked);
                    FIELD(arg3, u8, 0x72) = linked[0x24];
                    FIELD(arg3, u8, 0x73) = linked[0x25];
                    goto invoke_item;
                }
            } else {
                register s32 x ASM_REG("$2");
                register s32 y ASM_REG("$3");

                active = func_800A05A4(
                    arg3,
                    FIELD(arg2, u8, 0x24),
                    FIELD(arg2, u8, 0x25),
                    FIELD(arg3, s16, 0x2A),
                    0x10);
                FIELD(arg3, void *, 0x60) = active;
                x = FIELD(arg3, s8, 0x72);
                y = FIELD(arg3, s8, 0x73);
                if (x < 0) {
                    x = -x;
                }
                if (y < 0) {
                    y = -y;
                }
                FIELD(arg3, u8, 0x72) = x;
                FIELD(arg3, u8, 0x73) = y;
                ASM_KEEP(x);
                ASM_KEEP(y);
            }
        }

invoke_item:
        pos.x = arg1->x >> 16;
        pos.y = arg1->y >> 16;
        pos.z = arg1->z >> 16;

        if (!(FIELD(arg0, u16, 0x98) & 0x2000)) {
            register void *alloc_result ASM_REG("$2");

            alloc_result = func_8003FD64(0x112, D_80083498);
            object = alloc_result;
            ASM_KEEP(alloc_result);
            FIELD(arg0, void *, 0xA8) = alloc_result;
            if (object != 0) {
                VecData *dst;

                func_8004491C(object, &D_80045340);
                FIELD(object, void *, 0x10) = D_800D7960;
                dst = FIELD(object, VecData *, 8);
                *dst = *arg1;
                FIELD(object, u8, 0xBB) = 0;
                FIELD(object, u16, 0x4A) = FIELD(arg3, u16, 0x2A);
                {
                    register s32 entity_flags ASM_REG("$3") = FIELD(arg2, s32, 0x28);
                    register void *entity ASM_REG("$4") = FIELD(object, void *, 0x0C);

                    ASM_KEEP(entity_flags);
                    ASM_KEEP(entity);
                    FIELD(entity, u16, 0x1E) = 0x1000;
                    FIELD(entity, u16, 0x1C) = 0x1000;
                    FIELD(entity, s32, 0x28) = entity_flags;
                    FIELD(entity, u16, 0x14) = FIELD(arg2, u16, 0x14);
                    FIELD(entity, u16, 0x12) = FIELD(arg2, u16, 0x12);
                    {
                        s32 entity_link = FIELD(arg2, s32, 0x0C);

                        FIELD(entity, void *, 0x2C) = D_80174078;
                        FIELD(entity, s32, 0x0C) = entity_link;
                    }
                }
            }
            FIELD(arg0, u16, 0x98) |= 0x2000;
        }

        {
            register void *entity ASM_REG("$4");
            u8 *anim;
            s32 direction;

            entity = FIELD(arg0, void *, 0xA8);
            entity = FIELD(entity, void *, 0x0C);
            anim = FIELD(entity, u8 *, 0x2C);
            direction = ((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7;
            func_80047784(entity, anim[direction], 0);
        }
        if (func_800A94A0(arg3, choice, alternate,
                          (u16 *)((u8 *)arg0 + 0x98)) == 0) {
            return;
        }
        FIELD(arg0, u16, 0x98) &= 0xDFFF;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        func_800A56E0(0x703);
        func_800DA840(&pos, (*choice - 1) % 3);
        FIELD(arg0, u8, 0x9B)++;
        return;

empty_selection:
        arg1->dz = 0;
        arg1->dy = 0;
        arg1->dx = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        D_8008346C = 0;
        FIELD(D_800814A8, u16, 0xA6)--;
        func_800A4ACC(arg3);
        FIELD(arg3, u8, 0x6D)--;
        FIELD(arg0, void *, 0x8C) = &D_80170EA8;
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        return;

    case 1:
        if (func_8003F270() != 0) {
            FIELD(arg2, u16, 0x14) |= 0x800;
            return;
        }
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, u8, 0x9B)++;
        /* fallthrough */

    case 2:
        if (FIELD(arg0, void *, 0xA8) != 0) {
            object = FIELD(arg0, void *, 0xA8);
            *FIELD(object, VecData *, 8) = *arg1;
        }
        if ((FIELD(arg2, s8, 4) != 4 ||
             !(FIELD(arg2, u16, 0x14) & 0x1000)) &&
            !(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        FIELD(arg0, u16, 0x98) |= 0x80;
        if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
            return;
        }
        if (FIELD(arg0, void *, 0xA8) != 0) {
            FIELD(object, u8, 0xBB) = 0xFF;
            FIELD(arg0, void *, 0xA8) = 0;
        }
        FIELD(arg2, void *, 0x2C) = D_80174038;
        func_80047784(
            arg2,
            D_80174038[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        arg1->dz = 0;
        arg1->dy = 0;
        arg1->dx = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
        global = (u8 *)&D_80083460;
        if (FIELD(global, s32, 0x0C) != 0) {
            return;
        }
        FIELD(global, u16, 0x0A)--;
        FIELD(arg2, u16, 0x14) &= 0xF7FF;
        FIELD(arg0, void *, 0x8C) = &D_80170EA8;
        func_800A4ACC(arg3);
        if (FIELD(arg3, s8, 0x6D) > 0) {
            FIELD(arg3, u8, 0x6D)--;
        }
        FIELD(arg3, u8, 0x73) = 0;
        FIELD(arg3, u8, 0x72) = 0;
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
        func_800A56E0(0xB4);
        return;

    default:
        return;
    }
}
