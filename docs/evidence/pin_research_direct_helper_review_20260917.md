# Round46 independent direct-helper landing review

The direct `D_800DE870` argument in `dungeon/func_8132E5EC` removes its only
pin and the matching/port split. The port arm already names this same static
table. This is a genuine object address, not a literal page constraint.
The exact same object allocation, null check, callback, position field writes,
volatile middle-coordinate store and render initialization remain. The
recovered resident helper takes three arguments with a signed-short index;
this site passes zero, so correcting that prototype preserves its value.

The root independently read all67 retail words and compared all268 linked
bytes at runtime801655EC. `independent_strict.json` reports byte_exact,
zero substitutions/indels and no relocation suspicion. Final callee SHA:
`932b55b5946d52ebf55aa1fc94582460ffb66c67b7858e082a68f5b5d0297e59`.
Old source SHA: `b8c8357dace5485c4c991b849c0f18255050ae7277fe1285176fcf6ca124e09a`.

The caller `81338C4C`/runtime8016FC4C has two sites with bounded signed
coordinate offsets. Its old declaration returned M2C_UNK and took s16, while
the callee returns void and takes s32. Prototyped short parameters cause short
conversions; default-argument promotion was not the applicable explanation.
The final caller declaration is `void func_801655EC(void *, s32, s32, s32)`.
Both results are discarded. Existing explicit short conversions and masked
random offsets preserve passed values. No callee parameter or caller body is
changed. The final caller is independently linked-strict319/319 at recorded
2.8.1-G0, byte_exact and no relocation suspicion. Final caller SHA:
`3fbd470c18bdb54a21e3c9ddd6e2841f104f99f9a471a4f37ca0fc50fab808ff`.

The recipe transition qualifies for the normal automatic cell rule: old
source is exact at recorded2.7.2 and proposed2.7.2-cdk-G0; candidate is exact
atCDK but nonexact at plain2.7.2 (68/67,distance4). Retail call-delay stores
support the CDK/2.8 family; a unique historical release is not proved.

`landing_refusal` returns None for both files. For the callee arm collapse,
old/new NON_MATCHING assembly at the old recipe is identical, although textual
port views differ; this satisfies the existing port-codegen identity rule.
No new binding, asm, volatility, dead dependency, pointer narrowing or literal
address replaces the removed pin. Other inherited helper declaration debt
(e.g. the two-word registration helper's unused result/address-valued ID) is
unchanged. Final publication requires all covering caller/callee windows,
SLUS, row database and current source-hash checks.

Publication completed: both covering caller/callee windows and SLUS MATCH; row database OK. The standard cell lander accepted both hash-bound files and rechecked the original callee at CDK. Source hashes above remain current.
