#include "common.h"

typedef struct TownState {
    s16 state;
    s16 timer;
    u16 phase;
    s16 value;
    s16 level;
    s16 count;
    u16 flags;
} TownState;

typedef struct Transform {
    s32 x;
    s32 y;
    s32 z;
} Transform;

typedef struct Part {
    u8 pad0[6];
    s16 speed;
    u8 pad8[4];
    s32 color;
    u8 pad10[12];
    s16 scale_y;
    s16 scale_x;
    s16 scale_z;
} Part;

typedef struct Object {
    u8 pad0[8];
    Transform *transform;
    Part *part;
    void *callback;
    u8 pad14[14];
    s16 lifetime;
    void *data;
    s32 color_28;
    s16 x_2c;
    s16 y_2e;
    union {
        s32 color;
        struct {
            s16 x;
            s16 y;
        } pos;
    } field_30;
    s16 x_34;
    u16 flags_36;
    u8 pad38[2];
    s16 z_3a;
    u8 pad3c[0x84];
    u16 phase;
    u8 padc2[10];
    TownState *owner;
} Object;

extern s16 D_8001339C;
extern u8 D_8003C558[16];
extern u8 D_8005860C[16];
extern u8 D_8005888C[16];
extern s32 D_80084D5C;
extern u8 D_801328C8[16];
extern s32 D_80132AEC[4];
extern u8 D_8028E628[16];
extern u8 D_80526694[16];
extern u8 D_805266A0[16];
extern u8 D_8052BC34[16];
extern u8 D_8052BC80[16];
extern u8 D_8052BCCC[16];

extern Object *func_800374FC(s32, void *);
extern void func_8003BC18(Object *, void *);
extern void func_80034A1C(Part *, void *, s32);
extern void func_8003F75C(s32);
extern void func_80050BD8(s32);
extern void func_80050BFC(s32);

/* Updates timed object spawning, result displays, and the stored best value. */
void func_8052B5A4(TownState *self) {
    void *result_data;
    s16 level_period;
    s16 spawn_period;
    s32 state;
    s32 *capped_values;
    s32 value_limit;
    Object *obj;
    Part *part;

    level_period = 42 - self->level / 6;
    spawn_period = level_period;
    result_data = D_80526694;
    if (level_period < 16) {
        spawn_period = 16;
    }
    value_limit = 0x03200000;
    capped_values = D_80132AEC;
    if (capped_values[0] > value_limit) {
        capped_values[0] = value_limit;
    }
    state = self->state;
    switch (state) {
    case 0:
        if (self->timer % spawn_period == 0) {
            if (self->count > 0 ||
                (self->state == 1 && (self->flags & 4))) {
                self->phase = (self->phase + 1) & 3;
                self->timer = 0;
                if (self->state == 0) {
                    self->count--;
                }
                obj = func_800374FC(0x136, D_801328C8);
                if (obj != 0) {
                    obj->callback = D_8052BCCC;
                    func_8003BC18(obj, D_8003C558);
                    part = obj->part;
                    obj->transform->x = 0x03200000;
                    obj->transform->y = 0x02E00000;
                    obj->transform->z = (s32)0xFFFC0000;
                    obj->phase = self->phase;
                    obj->owner = self;
                    part->scale_x = 0x1000;
                    part->scale_y = 0x1000;
                    part->speed = -0x100;
                    func_80034A1C(part, D_8028E628, 0);
                    part->color = 0x00808080;
                }
                self->flags |= 1;
            }
        }
        self->timer++;
        if (self->flags & 1) {
            break;
        }
        if (self->count > 0) {
            break;
        }
        if (self->flags & 4) {
            self->state = 2;
            goto done;
        }
        /* fall through */
    case 1:
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            obj->callback = D_8052BC34;
            func_8003BC18(obj, D_8005860C);
            obj->x_34 = 0x7C;
            obj->flags_36 = 0x78;
            obj->z_3a = 0x7C80;
            obj->field_30.color = 0x00808080;
            obj->data = result_data;
            obj->lifetime = 0x96;
        }
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            obj->callback = D_8052BC80;
            func_8003BC18(obj, D_8005888C);
            obj->x_2c = 0x74;
            obj->y_2e = 0x74;
            obj->field_30.pos.x = 0x58;
            obj->field_30.pos.y = 0x10;
            obj->color_28 = 0x00101010;
            obj->lifetime = 0x96;
            obj->flags_36 |= 1;
        }
        self->timer = 0x96;
        self->state = 3;
        goto done;

    case 2:
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            obj->callback = D_8052BC34;
            func_8003BC18(obj, D_8005860C);
            obj->x_34 = 0x80;
            obj->flags_36 = 0x78;
            obj->z_3a = 0x7C80;
            obj->data = D_805266A0;
            obj->field_30.color = 0x00808080;
            obj->lifetime = 0x96;
        }
        obj = func_800374FC(1, D_801328C8);
        if (obj != 0) {
            obj->callback = D_8052BC80;
            func_8003BC18(obj, D_8005888C);
            obj->x_2c = 0x78;
            obj->y_2e = 0x74;
            obj->field_30.pos.x = 0x50;
            obj->field_30.pos.y = 0x10;
            obj->color_28 = 0x00101010;
            obj->lifetime = 0x96;
            obj->flags_36 |= 1;
        }
        self->state = 4;
        self->timer = 0x64;
        goto done;

    case 3:
        self->timer--;
        if (self->timer >= 0) {
            break;
        }
        self->timer = 0;
        self->state = 1;
        goto done;

    case 4:
        self->timer--;
        if (self->timer >= 0) {
            break;
        }
        if (D_8001339C < self->value) {
            D_8001339C = self->value;
            func_80050BFC(0x553);
            goto sound_done;
        }
        func_80050BD8(0x553);
sound_done:
        func_8003F75C(1);
        *(u16 *)((u8 *)self - sizeof(u16)) |= 0x8000;
        self->flags |= 2;
        D_80084D5C |= 0x8000;
        break;

    default:
        break;
    }
done:
    self->flags &= 0xFFFE;
}
