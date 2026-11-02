#include "common.h"
#include "shared/entity.h"
#include "town/scene/animation.h"

extern void func_80034A1C(void *, ...);
extern void func_8003EA54(void *);
extern void func_80050D68(void *);
extern short func_80058F88(int flags);
extern s32 func_80071494(); /* Unprototyped: JP identity rand(void); the surplus source arguments preserve the retail instruction stream. */
extern void func_8023FA58(void *, void *, ...);
extern void func_8023FB18(void *, ...);
extern s32 func_80252550();

extern u8 D_8028E568[];
extern u8 D_8028E56C[12];
extern u8 D_8028E590[];
extern u8 D_8028E600[];
extern s32 scene_object_flags;
extern u8 D_805266C0[];
extern u8 D_805266CC[];
extern u8 D_805266D8[];
extern u8 D_8053013C[];

typedef struct FallingTimedSceneObject {
    u8 pad_00[0x48];
    void * unk_48;
    u8 pad_4C[0x1C];
    s16 unk_68;
    u8 pad_6A[0x2E];
    s8 * unk_98;
    u8 pad_9C[0x4];
    s16 unk_A0;
    u16 unk_A2;
    u16 unk_A4;
    u16 unk_A6;
    u8 pad_A8[0x4];
    FallingSceneController *owner;
} FallingTimedSceneObject;   /* obj in animate_falling_timed_object */

typedef struct S_8052BCCC_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8052BCCC_3;   /* out in animate_falling_timed_object */

/* Per-frame step for the town cutscene actor: integrate its motion, then run its ten-state dispatch. */
void animate_falling_timed_object(FallingTimedSceneObject *obj, ObjectPosition *motion, void *incoming_out) {
    FallingSceneController *aux;
    S_8052BCCC_3 *out;
    u16 table[14];
    s32 a0;
    s32 a1;
    s32 value;
    s32 flag;
    s32 state;
    s16 phase_u16;
    u16 mode;
    s8 *ptr;

    aux = obj->owner;
    __builtin_memcpy(table, D_805266C0, 12);
    __builtin_memcpy(&table[8], D_805266CC, 12);

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    obj->unk_A2 = obj->unk_A2 - 1;
    aux->flags |= 1;

    state = obj->unk_68;
    out = incoming_out;
    switch (state) {
    case 0:
    {
        s32 state0_flag;
        a1 = func_80071494() & 0xF;
        if (aux->count >= 25) {
            a1 = func_80071494() & 7;
            a0 = a1 + 14;
        } else {
            if (aux->count >= 19) {
                state0_flag = a1 < 3;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 5;
            } else if (aux->count >= 7) {
                state0_flag = a1 < 4;
                if (state0_flag)
                    goto state0_small;
                state0_flag = a1 < 8;
            } else {
                state0_flag = a1 < 6;
                if (state0_flag) {
state0_small:
                    a1 = (0 - func_80071494()) & 3;
                    goto state0_finish;
                }
                state0_flag = a1 < 7;
            }
            a0 = a1 + 14;
            if (state0_flag) {
                a1 = (func_80071494(a0, a1) % 23) + 44;
state0_finish:
                a0 = a1 + 14;
            }
        }
        obj->unk_A2 = a0;
        obj->unk_A6 = a0;
        motion->velocity_y = (s32)0xFFC00000 / ((s16)(obj->unk_A2));
        if (obj->unk_A0 < 2)
            out->unk_14 |= 1;
        if (((u16)(obj->unk_A0)) & 1) {
            out->unk_06 = -256;
            motion->velocity_y = 0 - motion->velocity_y;
        } else {
            out->unk_06 = -64;
            func_80034A1C(out, D_8028E600, 0);
        }
        obj->unk_68 = 1;
        break;
    }

    case 1:
    {
        s32 case1_value;
        if (((s16)(obj->unk_A2)) <= 0) {
            motion->velocity_y = 0;
            phase_u16 = obj->unk_A6;
            case1_value = (s32)0x800000 / (s16)(phase_u16 * 2);
            obj->unk_A2 = phase_u16 * 2;
            motion->velocity_x = case1_value;
            if (obj->unk_A0 < 2)
                motion->velocity_x = 0 - case1_value;
            func_80034A1C(out, D_8028E590, 0);
            obj->unk_68 = 2;
            break;
        }
        break;
    }

    case 2:
    {
        u16 phase;
        if (((s16)(obj->unk_A2)) <= 0) {
            phase = obj->unk_A6;
            obj->unk_A2 = phase;
            mode = ((u16)(obj->unk_A0));
            value = (s32)0xFFC00000 / (s16)phase;
            if (mode & 1) {
                if ((s16)mode == 1)
                    a0 = value;
                else
                    a0 = 0 - value;
                motion->velocity_x = a0;
                motion->velocity_y = 0;
            } else {
                motion->velocity_x = 0;
                motion->velocity_y = value;
            }
            obj->unk_68 = 3;
            break;
        }
        break;
    }

    case 3:
        if (((s16)(obj->unk_A2)) <= 0) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            motion->y.v += (s32)0xFFFC0000;
            (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
            out->unk_08 = *(s32 *)D_8028E56C;
            out->unk_04 = 0;
            out->unk_05 = 0;
            if (func_80071494() & 7) {
                u16 phase3;
                /* BYTES: Redundant store retail really emits; the A6 load between the two A2 stores keeps cse from deleting the first store. */
                obj->unk_A2 = 16;
                phase3 = obj->unk_A6;
                obj->unk_A2 = phase3;
                motion->velocity_z = ((s32)0xFF900000 - motion->z.v) / ((s16)phase3);
                obj->unk_68 = 4;
            } else {
                s32 pos;
                s32 acceleration;
                obj->unk_A2 = 12;
                acceleration = (func_80071494() & 0xFF) << 12;
                pos = motion->z.v;
                a0 = 0x580000;
                pos += a0;
                a0 = ((s16)(obj->unk_A2));
                acceleration -= pos;
                acceleration /= a0;
                motion->velocity_z = acceleration;
                obj->unk_68 = 5;
            }
            break;
        }
        break;

    case 4:
        if (motion->z.v <= (s32)0xFFA80000 &&
            !(obj->unk_A4 & 2)) {
            out->unk_06 = 0;
            obj->unk_48 = D_805266D8;
            obj->unk_A4 |= 2;
            func_8023FA58(obj, motion, D_8053013C);
            aux->level.u += 1;
        }
        if (((s16)(obj->unk_A2)) == 3) {
            (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
            out->unk_08 = *(s32 *)D_8028E56C;
            out->unk_04 = 0;
            out->unk_05 = 0;
        }
        if (((s16)(obj->unk_A2)) <= 0) {
            motion->velocity_z = 0;
            obj->unk_68 = 7;
            obj->unk_A2 = ((s16)(obj->unk_A6)) * 2 + 20;
        }
        break;

    case 5:
        if (((s16)(obj->unk_A2)) <= 0) {
            obj->unk_A2 = 6;
            motion->velocity_z = ((s32)0xFFD80000 - motion->z.v) /
                obj->unk_A2;
            obj->unk_68 = 6;
        }
        break;

    case 6:
        if (((s16)(obj->unk_A2)) <= 0) {
            obj->unk_A2 = 8;
            motion->velocity_z = ((s32)0xFF900000 - motion->z.v) / (obj->unk_A2);
            obj->unk_68 = 4;
            break;
        }
        break;

    case 7:
    {
        void *call_out;
        if (((s16)(obj->unk_A2)) <= 0) {
            call_out = out;
            if (obj->unk_A0 & 1) {
                value = (s32)D_8028E590;
            } else {
                out->unk_06 = 64;
                value = (s32)D_8028E600;
            }
            func_80034A1C(call_out, (void *)value, 0);
            obj->unk_A4 &= 0xFFFD;
            aux->flags &= 0xFFFB;
            flag = ((u16)(obj->unk_A0));
            obj->unk_A2 = 8;
            a1 = -0x80000;
            if (flag & 1) {
                a0 = a1;
                if ((s16)flag != 1)
                    a0 = 0x80000;
                motion->velocity_x = a0;
                motion->velocity_y = 0;
            } else {
                motion->velocity_x = 0;
                motion->velocity_y = a1;
            }
            obj->unk_68 = 8;
        }
        break;
    }

    case 8:
        if (((s16)(obj->unk_A2)) <= 0) {
            func_8023FB18(obj);
            ptr = obj->unk_98;
            if (ptr != 0)
                *ptr = 0;
            func_80050D68(obj);
            (*(u16 *)((u8 *)(obj) + (-2))) |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        break;

    case 9:
    {
        s32 phase;
        phase = ((s16)(obj->unk_A2));
        if (phase == 1) {
            func_80058F88(0x512);
            phase = ((s16)(obj->unk_A2));
        }
        if (phase < 6) {
            out->unk_1C = table[phase];
            out->unk_1E = table[((s16)(obj->unk_A2)) + 8];
        }
        if (((s16)(obj->unk_A2)) <= 0)
            obj->unk_68 = 8;
        break;
    }
    default:
        break;
    }

    func_8003EA54(out);
    if ((obj->unk_A4 & 2) && func_80252550(D_8053013C, motion) != 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        {
            FallingSceneController *tail_aux = obj->owner;
            tail_aux->value.u += 1;
        }
        obj->unk_A4 &= 0xFFFD;
        (*(s32 *)((u8 *)(out) + (0))) = D_8028E568;
        out->unk_08 = *(s32 *)D_8028E56C;
        out->unk_04 = 0;
        out->unk_05 = 0;
        obj->unk_A2 = 14;
        obj->unk_68 = 9;
    }
    return;
#undef obj
#undef motion
#undef out
}
