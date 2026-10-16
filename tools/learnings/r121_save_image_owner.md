# Fixed save-image ownership closes dungeon B7914

At recipe 2.7.2-cdk-G0, the original bounded two-word state object at
0x8001208C generates 180 bytes for dungeon/func_800B7914 (retail 176).
A page pointer alone would be unjustified. Independent retail witnesses instead
establish a real serialized save image at 0x80010000, exactly 0x6000 bytes.

MAIN 0x80025230 and 0x80025398 pass that complete buffer to readers/writers.
The transfer chain supplies 0xC0 units and shifts by seven: 0x6000 bytes.
The independent checksum starts at +0x208 and reads 0x177E words, ending at
exactly +0x6000. SLUS 0x80043458 forms the same base and resets +0x208C/+0x2090.
The proven MAIN rowbase and SLUS executable header fix these witnesses' addresses.

A bounded SaveImage with prefix[0x208C], s32 pending, s32 active and
suffix[0x3F6C] therefore represents an independently supported imported storage
object. The local pointer naturally lives in s0 across a real call, producing
every byte of the 176-byte retail function without pins, asm, volatile,
fake dependencies, recipe changes or a masked/truncated comparison.
The full 393216-byte dungeon engine window also matches, including the existing
CD native module. See docs/evidence/r121_hardholds/save_image_storage.json and
docs/evidence/r121_hardholds.md for the complete-binary proofs and gates.

Transferable diagnostic: when a small adjacent-field object causes an extra
base legalization, investigate its actual storage owner through pointer
passing and independently counted extents. A larger view is justified only
when those facts establish the larger object. Shared LUI pages and neighboring
C spelling alone remain insufficient. This result grants no new allocation,
initialization claim, arbitrary page abstraction or whole-program type closure.
