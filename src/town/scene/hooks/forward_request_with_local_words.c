#include "common.h"
#include "town/scene/entry_requests.h"

typedef struct {
    s32 words[4];
} UnkStruct80476358;

extern UnkStruct80476358 D_80017124;
extern u8 D_800170D0[];
extern void func_80018FC8(UnkStruct80476358 *, u8 *, s32, s32);

/* Pass a local copy of the word template and fixed data to the handler. */
void dispatch_scene_request_with_local_words(s32 request, s32 unused, s32 value) {
    UnkStruct80476358 local_words = D_80017124;

    func_80018FC8(&local_words, D_800170D0, request, value);
}
