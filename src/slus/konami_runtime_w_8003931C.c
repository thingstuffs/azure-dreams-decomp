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
extern ObjectBlock *ms_mot_accpt_ow(s32 arg0);
extern void func_800383D4(void);
extern void func_80038408(void);

__asm__(".set D_800C3174, 0x800C3174");
__asm__(".set D_800C321C, 0x800C321C");

/* Initializes an event-script entry or defers the command while the entry is active or unavailable. */
void func_8003931C(State *state)
{
    u8 *cursor = state->read_ptr;
    u8 *value_ptr;
    u8 index_byte = *cursor;
    s32 entry_index;
    Entry *entries;
    Entry *entry;
    AuxState *aux;
    ObjectBlock *object;
    volatile ObjectBlock *object_header;
    void *object_type;

    cursor++;
    state->read_ptr = cursor;
    entry_index = index_byte & 0xFF;
    entries = D_80082660;
    entry = entries + entry_index;
    aux = state->aux;
    if (entry->active != 0) {
        goto active;
    }
    if (entry_index == 0) {
        goto done;
    }

    do {
        object = ms_mot_accpt_ow(entry_index);
    } while (0);
    if (object == 0) {
        goto unavailable;
    }

    object_header = object - 1;
    value_ptr = state->read_ptr;
    entry->value = *value_ptr;
    value_ptr++;
    state->read_ptr = value_ptr;
    entry->active = 1;
    entry->aux_value = aux->value_48;

    if (entry_index == 1 &&
        (object_type = object_header->type) != (void *)D_800C3174 &&
        object_type != (void *)D_800C321C) {
        *(s16 *)((u8 *)object + 0x36) = aux->value_4c;
        *(s16 *)((u8 *)object + 0x38) = aux->value_50;
        goto done;
    }

    *(s16 *)((u8 *)object + 0x88) = aux->value_4c;
    *(s16 *)((u8 *)object + 0x8A) = aux->value_50;
    goto done;

unavailable:
    state->callback = func_80038408;
    state->entry_index = index_byte;
    state->timer = 0x10;
    state->read_ptr -= 2;
    goto done;

active:
    do {
        state->read_ptr = cursor - 2;
        state->entry_index = index_byte;
        state->callback = func_800383D4;
    } while (0);

done:
    return;
}
