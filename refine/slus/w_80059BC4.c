#include "common.h"

#include "common.h"

typedef struct {
    s8 pad00[0x10];
    s32 f10;
    s8 pad14[0x10];
    u16 f24;
    s8 pad26[6];
    s32 f2c;
    s8 pad30[0xC];
    s32 f3c;
    s8 pad40[0x10];
} Entity;

extern s32 D_800869B4[3];
extern Entity D_80085FA8[];
extern s32 D_800737C4[4];
extern s32 D_800737C8[4];
extern void func_8005947C(Entity *);
extern s32 func_800595C0(Entity *);
extern s32 func_80058A04(Entity *);
extern void func_80059814(Entity *);

/* Advances active entities' tick accumulators and processes actions when their delays expire. */
s32 func_80059BC4(void)
{
    unsigned int entity_index;
    Entity *entity;
    s32 tick_total;
    s32 delay_ticks;
    s32 step_or_count;

    entity_index = 0;
    if (D_800869B4[0] == 0) {
        return 0;
    }
    entity = D_80085FA8;
    do {
        if (entity->f2c != 0) {
            goto next_entity;
        }
        step_or_count = entity->f24;
        tick_total = entity->f3c;
        tick_total = tick_total + step_or_count;
        entity->f3c = tick_total;
        if ((unsigned int)tick_total < 0x100) {
            goto next_entity;
        }
        delay_ticks = entity->f10;
        entity->f3c = tick_total & 0xFF;
        if (delay_ticks == 0) {

process_action:
            if (D_800737C8[0] == 2) {
                goto decode_check;
            }
            func_8005947C(entity);
            goto decode;

decode_check:
            if ((func_800595C0(entity) & 0xFF) != 0) {
                goto decode_nonzero;
            }
decode:
            if (entity->f2c != 0) {
                goto update_delay;
            }
            entity->f10 = func_80058A04(entity);
            goto post_decode;
decode_nonzero:
            if (entity->f2c != 0) {
                goto update_delay;
            }
post_decode:
            if (entity->f10 == 0) {
                goto process_action;
            }
            if (D_800737C4[0] != 0) {
                func_80059814(entity);
            }
            if (entity->f10 == 0) {
                goto process_action;
            }
update_delay:
            if (entity->f10 != 0) {
                entity->f10 -= 1;
            }
        } else {
            entity->f10 = delay_ticks - 1;
        }
next_entity:
        step_or_count = D_800869B4[0];
        entity_index++;
        entity++;
    } while (entity_index < (unsigned int)step_or_count);
    return 0;
}
