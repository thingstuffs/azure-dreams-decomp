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
extern void dispatch_sequence_event(Entity *);
extern s32 audio_read_compact_sequence_event(Entity *);
extern s32 read_base_128_vlq(Entity *);
extern void scale_value_with_remainder(Entity *);

/* Advances active entities' tick accumulators and processes actions when their delays expire. */
s32 audio_tick_sequence_tracks(void)
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
    do {
        entity = &D_80085FA8[entity_index];
        if (entity->f2c == 0) {
            step_or_count = entity->f24;
            tick_total = entity->f3c;
            tick_total = tick_total + step_or_count;
            entity->f3c = tick_total;
            if ((unsigned int)tick_total >= 0x100) {
                delay_ticks = entity->f10;
                entity->f3c = tick_total & 0xFF;
                if (delay_ticks == 0) {
                    do {
                        if (D_800737C8[0] != 2) {
                            dispatch_sequence_event(entity);
                            if (entity->f2c != 0) {
                                break;
                            }
                            entity->f10 = read_base_128_vlq(entity);
                        } else if ((audio_read_compact_sequence_event(entity) & 0xFF) == 0) {
                            if (entity->f2c != 0) {
                                break;
                            }
                            entity->f10 = read_base_128_vlq(entity);
                        } else if (entity->f2c != 0) {
                            break;
                        }
                        if (entity->f10 != 0 && D_800737C4[0] != 0) {
                            scale_value_with_remainder(entity);
                        }
                    } while (entity->f10 == 0);
                    if (entity->f10 != 0) {
                        entity->f10 -= 1;
                    }
                } else {
                    entity->f10 = delay_ticks - 1;
                }
            }
        }
        step_or_count = D_800869B4[0];
        entity_index++;
    } while (entity_index < (unsigned int)step_or_count);
    return 0;
}
