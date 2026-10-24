# Map-exit monster-load callback

TOWN +0x2AE028 (runtime 0x80018828) is a complete 56-byte wrapper. Its two
references are exit-descriptor callback fields at +0xC, not +0x10: the descriptors
start at TOWN +0x2B1730 and +0x2B194C (runtime 0x8001BF30 and 0x8001C14C).
They select area 12, rooms 10 and 44. The earlier apparent boundary was four
bytes too early. The layout exactly matches change_map's InputRecord.
Their resource pointers name the validated packed-CD records at TOWN +2B1A24
and +2B1B0C: the instance-load ledger maps these to +4CF800 and +65B000,
respectively, each loading 8,192 bytes at 0x80016000.

change_map at 0x8003BAF8 loads input +0xC at 0x8003BBE4, stores it at
map_change_state +0x24 (the alias map_change_callback[0], 0x8006AE10), and calls
it at 0x8003BC80. At the call, a0 is the RuntimeState pointer and a1 is input
+0x8, the map-data pointer. Its return address is 0x8003BC88. v0 is overwritten
at 0x8003BC8C before any read, so the result is unused. The complete 572-byte
consumer section and the entire SLUS image equal retail. The existing C type
is void (*)(RuntimeState *, void *).

The wrapper uses neither incoming carrier. It calls town service +0x1F4 with
the constant 2. The loaded-phase capture uniquely identifies that service as
the complete 12-byte reserve_tw_mon_load(s32), whose return is void. The
service table prototype is corrected to void(int); its other current source
consumer already ignores the result.

The new definition lives under town/scene/service with its declaration in
town/scene.h. RuntimeState remains opaque there. Registration uses the existing
region_2ab9c0_2b09ec owner and retires only the reviewed final eight-byte
epilogue town/func_8028E058. Complete-section and scoped-image receipts live
in the lane delivery; no guessed return value or forwarding body is used.
