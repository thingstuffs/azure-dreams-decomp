# Run thirteen: current-master replay and complete scene/effect ownership

The starting tree is current master 72dd008a. Run eleven was present; run
twelve is replayed with minimal changed-line anchors. Its existing complete
source producers, loader extents, typed records and Block pairing are kept.

Two terminal scene choices at TOWN +0x705074 and +0x71A074 contain a complete
16-byte record each. Their parent entries reference the base through +0x10.
Both existing initializers independently reference the next object, image
+0x84. Ordinary packed loader descriptors at +0x3E7B8C/+0x3E7B94 load three
sectors (0x1800 bytes) into 0x80016000. The old second link view ended at the
code return +0x150C; referenced frame data belongs to the full loaded extent.
Each record uses two argument-free zero-return callbacks, a borrowed data
pointer and two signed flag halfwords. The missing first zero-return entry
at image +0x1DC is a whole eight-byte function; the separately registered
second entry starts at +0x1E4. Both now reuse the existing item_menu_return_zero
home. Whole existing initializer TUs produce the arrays as initialized data;
no new raw row, duplicated home, cast or literal address initializer is used.

The Baloon rise-effect helper has two identical 372-byte bodies at DUNGEON
+0xD85244/+0xD8B244, loaded at 0x80170A44/0x8016AA44. The complete JAL from
the existing relocation handler and the ordinary species-25 resource-grid
loads establish the entries. Each body includes its return delay slot. The
new source preserves the allocator, complete 48-byte SpriteFrameState copy,
four-tick work state, gray sprite configuration, camera-relative direction
selection and anchor position plus height. A typed header/work composite
represents the allocation and removes the need for pointer casts. The body
is built with the existing 2.7.2-cdk -O2 -G0 recipe. Its 93 resolved words are
exact, with no masked relocation. Genuine ASPSX and final image comparison
are required independently; receipts live in the lane delivery.

The complete constructor is the shared home for the second placement.
The six species-22 views, Ghosh, casino and other descriptor/boundary leads
retain their evidence holds until complete owners are proved. The F4 offset
at TOWN +0x51E0F4 remains string data; its F8 candidate is a separate entry.

Two failed-decompilation labels at scene image +4 (469 bytes each) overlapped
the typed records. They begin in the module header and are not registered C.
The labels are retired without creating replacement raw rows; other prefix
bytes remain imported assets and add zero claimed coverage.
