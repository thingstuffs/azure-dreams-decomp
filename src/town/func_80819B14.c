#include "common.h"

typedef struct {
    void *child;
    u8 pad04[0x4C];
    s16 state;
    s16 timer;
    s16 target;
} TownObject;

typedef struct {
    s32 x;
    s32 z;
    s32 y;
    s32 dx;
    s32 dz;
    s32 dy;
} TownMotion;

typedef struct {
    u8 pad00[6];
    u16 flags;
    s16 count;
} TownChild;

typedef struct {
    u8 pad00[4];
    s32 z;
    s32 y;
} TownTarget;

extern u16 D_800135C2[];
extern s16 D_800272C8[];
extern s16 D_800272CA[];
extern s32 D_800814A0[];
extern TownTarget D_80083780[];
extern u8 D_800D0138[];

extern void func_8003F540(s32, s32, s32, s32);
extern void SD_Call(s32);
extern void func_80093CEC(void *);

/* Update object motion, scoring, and timed state transitions. */
void func_80023B14(TownObject *obj_arg, TownMotion *motion)
{
    TownObject *obj = obj_arg;
    TownChild *child;
    s16 ticks_left;
    u16 state;

    ASM_KEEP_NV(obj);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP_NV(motion);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    child = obj->child;
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->dy += motion->dz;

    ticks_left = obj->timer - 1;
    obj->timer = ticks_left;

    switch (obj->state) {
    case 0:
    case 0x40: {
        s32 y;
        u16 score;
        s16 signed_score;
        s32 next_timer;

        if (motion->dy < 0) {
            break;
        }

        y = motion->y;
        if (y > (s32)0xFFF00000) {
            if (!(child->flags & 1)) {
                SD_Call(0x506);
            }
            child->flags |= 1;
            goto set_state_ff;
        }
        if (y <= (s32)0xFFA00000) {
            break;
        }

        if (obj->state == 0 && (child->flags & 1)) {
            break;
        }
        if (D_800272CA[0] != 0) {
            break;
        }
        if (obj->target != D_800272C8[0]) {
            break;
        }

        SD_Call(0x512);
        signed_score = child->count;
        score = *(volatile u16 *)&child->count;
        if (signed_score < 9999) {
            if (obj->state != 0) {
                next_timer = 8;
                goto store_timer;
            }
            score++;
            child->count = score;
            if ((D_800135C2[0] << 16) < (score << 16)) {
                D_800135C2[0] = score;
            }
        }
        next_timer = obj->state;
        if (next_timer != 0) {
            next_timer = 8;
        } else {
            next_timer = 4;
        }
store_timer:
        obj->timer = next_timer;
        do {
            func_80093CEC(D_800D0138);
        } while (0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        obj->state = obj->state + 1;
        goto epilogue;
    }

    case 1:
        if ((ticks_left << 16) > 0) {
            break;
        }
        obj->timer = 8;
        motion->dx = ((s32)0x02A00000 - motion->x) / obj->timer;
        motion->dy = ((s32)0xFFC00000 - motion->y) / obj->timer;
        obj->state = obj->state + 1;
        goto epilogue;

    case 2:
        if ((ticks_left << 16) >= 0) {
            break;
        }
        SD_Call(0x525);
        obj->timer = 6;
        motion->dx = motion->dy = motion->dz;
        goto set_state_ff;

    case 0x20:
        if ((ticks_left << 16) > 0) {
            break;
        }
        obj->timer = 10;
        obj->state = (u16)obj->state + 1;
        goto epilogue;

    case 0x21: {
        TownTarget *target = D_80083780;
        s32 target_z = target->z;
        s32 z = motion->z;
        s32 y = motion->y;
        s32 offset_y = y + 0x600000;
        motion->z = z + ((target_z - z) >> 1);
        motion->y = y + ((target->y - offset_y) >> 1);
        if ((s16)obj->timer <= 0) {
            obj->state = 1;
        }
        break;
    }

    case 0x41: {
        s16 *best_score;

        if ((ticks_left << 16) > 0) {
            break;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        best_score = (s16 *)D_800135C2;
        ASM_CLOBBER("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        if (*best_score == child->count) {
            func_8003F540(0, 0x2C3D, 0x01000001, 0x01000271);
        } else {
            func_8003F540(0, 0x2C3D, 0, 0x01000290);
        }
        SD_Call(0x300);
        state = obj->state;
        obj->timer = 7;
        obj->state = state + 1;
        goto epilogue;
    }

        obj->state = state + 1;
        goto epilogue;

    case 0x42: {
        child->flags |= 2;
        {
            s32 x = motion->x;
            s32 z = motion->z;
            s32 y = motion->y;

            motion->x = x + (((s32)0x03800000 - x) >> 1);
            motion->z = z + (((s32)0x03C00000 - z) >> 1);
            motion->y = y + ((-y) >> 1);
            if ((s16)obj->timer > 0) {
                break;
            }
            obj->timer = 4;
            goto set_state_ff;
        }
    }

set_state_ff:
        obj->state = 0xFF;
        goto epilogue;

    case 0xFF: {
        u16 *object_flags = (u16 *)obj - 1;
        s32 *global_flags_ptr = D_800814A0;
        s32 updated_flags;

        *object_flags |= 0x8000;
        updated_flags = global_flags_ptr[0] | 0x8000;
        global_flags_ptr[0] = updated_flags;
        if ((s16)obj->timer <= 0) {
            *object_flags |= 0x8000;
            global_flags_ptr[0] = updated_flags;
        }
        break;
    }

    default:
        break;
    }

epilogue:
    return;
}
