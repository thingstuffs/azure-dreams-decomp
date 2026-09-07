#include "common.h"

#include "common.h"

typedef struct Entry {
    s8 value;
    s8 active;
    u8 aux_value;
    u8 pad_03;
    void *object;
} Entry;

typedef struct ObjectBlock {
    u8 pad_00[0x10];
    void *type;
    u8 pad_14[0x0C];
} ObjectBlock;

typedef struct AuxState {
    u8 pad_00[0x48];
    u8 value_48;
    u8 pad_49[3];
    u16 value_4c;
    u8 pad_4e[2];
    u16 value_50;
} AuxState;

typedef struct State {
    u8 pad_00[0x10];
    void (*callback)(void);
    u8 pad_14[8];
    u8 *read_ptr;
    u8 pad_20[0x0F];
    u8 entry_index;
    u8 pad_30[0x50];
    AuxState *aux;
    u8 pad_84[5];
    u8 timer;
} State;

extern Entry D_80082660[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern ObjectBlock *func_800392A4(s32 arg0);
extern void func_800383D4(void);
extern void func_80038408(void);

__asm__(".set D_800C3174, 0x800C3174");
__asm__(".set D_800C321C, 0x800C321C");

void func_8003931C(State *arg0)
{
    u8 *cursor = arg0->read_ptr;
    u8 *read;
    u8 raw_index = *cursor;
    s32 index;
    Entry *base;
    Entry *entry;
    AuxState *aux;
    ObjectBlock *data;
    volatile ObjectBlock *header;
    void *type;

    cursor++;
    arg0->read_ptr = cursor;
    index = raw_index & 0xFF;
    base = D_80082660;
    entry = base + index;
    aux = arg0->aux;
    if (entry->active != 0) {
        goto active;
    }
    if (index == 0) {
        goto done;
    }

    do {
        data = func_800392A4(index);
    } while (0);
    if (data == 0) {
        goto unavailable;
    }

    header = data - 1;
    read = arg0->read_ptr;
    entry->value = *read;
    read++;
    arg0->read_ptr = read;
    entry->active = 1;
    entry->aux_value = aux->value_48;

    if (index == 1 &&
        (type = header->type) != (void *)D_800C3174 &&
        type != (void *)D_800C321C) {
        *(s16 *)((u8 *)data + 0x36) = aux->value_4c;
        *(s16 *)((u8 *)data + 0x38) = aux->value_50;
        goto done;
    }

    *(s16 *)((u8 *)data + 0x88) = aux->value_4c;
    *(s16 *)((u8 *)data + 0x8A) = aux->value_50;
    goto done;

unavailable:
    arg0->callback = func_80038408;
    arg0->entry_index = raw_index;
    arg0->timer = 0x10;
    arg0->read_ptr -= 2;
    goto done;

active:
    do {
        arg0->read_ptr = cursor - 2;
        arg0->entry_index = raw_index;
        arg0->callback = func_800383D4;
    } while (0);

done:
    return;
}
