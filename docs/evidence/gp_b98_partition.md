# B94/B98 saved-value ownership

`saved_value_b98` groups the data users at 50CAC, 50DA8 and 50E20 into a present
C owner. It is not a recovered historical translation unit. The explicit
partition moves only `func_80050CAC` from `slus/code`; both collector source files,
original row identities and remaining recipes are preserved. The destination
uses default 2.7.2-cdk, already the recipe of the two whole members. The moved
function formerly compiled in the plain 2.7.2 collector.

| Function | Observed operation | Retail words |
|---|---|---|
| 50CAC | Pass B98 when B94 is nonzero, otherwise pass zero | 12 |
| 50DA8 | Save the word at object + 0x3C into B98 while releasing an attachment | 30 |
| 50E20 | Save the same object-field view into B98 during attachment/effect cleanup | 34 |

## Storage and declarations

`D_80080B94` is `s32` initialized to 1; `D_80080B98` is `s32` initialized to zero.
They replace exactly eight bytes at offsets `0x154` and `0x158` of
`assets/54240.bin`, retail file offsets `0x54394` and `0x54398`. Their word accesses
at 50CB0, 50CC0, 50DD8 and 50E4C support these scalar views. Adjacent absolute
labels are not used to infer an object extent. The earlier bounded source audit
found direct named uses only in this group; it does not rule out indirect aliases.
The complete retail image preserves all existing accesses.

The shared header `include/slus/saved_value_b98.h` supplies these declarations
and a common prototype for `func_8004FE78`. Its parameter uses the canonical
forward-declared `struct S_8004FE78_a0`, whose definition remains with the callee.
50DA8's attachment local and 50E20's attachment field now use that pointer type.
This reconciles the previous void-pointer versus integer prototypes without
inventing a record layout. The target's actual emitted words prove the change
byte-neutral at the owner recipe.

The pre-existing 814A0 workarounds remain: DA8's absolute-symbol alias and E20's
three-word external view/literal store. They are outside this storage claim.
There are no new pins, padded declarations, volatile accesses, compiler flags or
assembler rules. This is data-ownership evidence, not an L4/L5 placement review.

## Verification

The [direct comparison](gp_b98_partition/direct_receipt.json) matches all 76
words through stock, genuine ASPSX 2.79 and the private guarded generic assembler,
with zero retail differences and zero masks. The private assembler trial is not
a global transition gate or permission to remove compatibility passes.

The [private full-link proof](gp_b98_partition/private_link_receipt.json) verifies
actual eight-byte `.sdata`, exact symbol offsets and non-absolute linkage at B94
and B98. All 870 outside physical objects remain byte-identical. There are 872
physical inputs and exactly the original 884 logical rows. The connected closure
has 154 code-remainder functions, 23 code2-remainder functions and three functions
in each of the E0 and B98 owners: all 183 functions occur exactly once.

The [multi-owner negative checks](gp_b98_partition/gate_receipt.json) edit the new
B98 part, the existing E0 part and the collector remainder separately. Every
changed image is rejected; canonical sources and retail-exact images are restored.
The [production ownership receipt](gp_b98_partition/ownership_receipt.json)
requires a direct genuine proof of the complete physical owner, not just either
member's subset. The full image equals retail SHA-1
`e6bfbb95ff6676899e077481221d73ddd4d3bf52`.

The [fresh row records](gp_b98_partition/live_rows.json) preserve the collectors'
unrelated GP/model discrepancies. Only the two whole-member dependency entries
are removed. E0 and the runtime-directory placement certificates are refreshed
because the connected build inputs changed; neither collector receives placement.
See [activation review](gp_b98_partition/activation_review.json) for current hashes,
counts and checks. Private reproducers are in `work/native_lane/gp_b98_partition/`:
`direct_probe.py`, `build_probe.py`, `prove.py`, and `gate_probe.py`.
