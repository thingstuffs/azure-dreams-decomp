This decoded census contains 2,154 value-returning call sites: 105 town blocks,
three resident blocks and two dungeon blocks. `sites.tsv` retains the original
identity and v15 flow evidence. Its historical return-type columns are not
trusted: the checker looks up the current registered C definitions, including
retained native fragments and their complete module owners.

Run from the repository root:

```sh
python3 tools/check_script_returns.py \
  --sites tools/fixtures/script_returns/sites.tsv \
  --services tools/fixtures/script_returns/services.tsv \
  --holds tools/fixtures/script_returns/holds.tsv
python3 -m unittest discover -s tools/tests -p test_script_returns.py -v
```

Every confirmed void callee fails, including one listed in the holds file.
Unresolved native identities and service targets need an exact site/candidate
hold with evidence. New sites, changed identities and stale holds fail. Polls
consume a result intrinsically; ignored call results and opcode 0x26 do not.
Service identities are from the captured town service table, not a claim that
all module states use the same table. The supplied m47 polls remain unresolved.

This is a regression check for a decoded census, not an exhaustive dungeon
scan. To extend coverage, regenerate the decoded table with the script decoder
and loader map, resolve new callees against their loading images, then run the
same check. Preserve unresolved cases with evidence; do not suppress confirmed
void returns. The decoder and runtime state captures are separate inputs and
are not supplied by this fixture. The 68 holds are 28 ambiguous native sites,
22 sites without a native body and 18 unresolved service polls.
