"""ledger_public: lane-local strings in public ledgers (census patterns, scrub, fail-new check).

    python3 -m unittest tools.lint.test_ledger_public
"""
from contextlib import redirect_stdout
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import ledger_public as P  # noqa: E402
import ledger_integrity as I  # noqa: E402


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True, capture_output=True, text=True).stdout.strip()


def tokens(text):
    return sorted(t for (_, t) in P.count_tokens(text))


class PatternTests(unittest.TestCase):
    def test_lane_names(self):
        self.assertEqual(tokens('"decided": "r121w_typesA-final"'), ['r121w_typesA-final'])
        self.assertEqual(tokens('by r121-opus_entity2 and c182_tools'), ['c182_tools', 'r121-opus_entity2'])
        self.assertEqual(tokens('8bdcec820+opus_entity2; sol61_w12; r93_sonnet_vb7'),
                         ['opus_entity2', 'r93_sonnet_vb7', 'sol61_w12'])
        self.assertEqual(tokens('see _batchAC140 and batchAC141'), ['_batchAC140', 'batchAC141'])

    def test_paths(self):
        self.assertEqual(tokens('evidence work/native_' 'lane/r121_census2/a.tsv'),
                         ['work/native_' 'lane/r121_census2/a.tsv'])  # the lane inside the path is not counted again
        self.assertEqual(tokens('r121w_entity1 out/field_roles.tsv'), ['out/field_roles.tsv', 'r121w_entity1'])
        self.assertEqual(len(tokens('/tmp/' 'claude-1000/x/scratchpad/a.c')), 1)

    def test_not_lane_local(self):
        # repo paths, identifiers, JSON keys, prose and the extracted-disc tree
        for text in ('docs/evidence/r121_remnants.md', 'src/town/minigame/update_gym_lane_selection.c',
                     '"r86_census": {"verdict": 1}', 'r86-era rows', 'r84 run 345', 'sol9_copy8#1',
                     'work/disc/containers/MAIN_MAIN.BIN', 'tools/lanes/r121_sdk/recover.py', 'checkout/x',
                     'r120: retired'):
            self.assertEqual(tokens(text), [], text)


class ScrubTests(unittest.TestCase):
    def test_values_phrases_and_generic(self):
        row = {'decided': 'r121w_typesA-final', 'census_base': '8bdcec820+opus_entity2',
               'evidence': [{'source': 'r121w_entity1 out/field_roles.tsv + naming_decisions.tsv'}],
               'note': 'r118_opus_o7 tried; see work/native_' 'lane/r93_opus_fp1/held/dungeon/func_81910A9C.c',
               'path': 'docs/evidence/r121_remnants.receipt.json', 'lane': 'r121_remnants', 'n': 3}
        line = json.dumps(row)
        out = P.scrub_text(line)
        new = json.loads(out)
        self.assertEqual(new['decided'], 'r121 B21 types census, final pass')
        self.assertEqual(new['census_base'], '8bdcec820+EntityRec split patch')
        self.assertEqual(new['evidence'][0]['source'], 'field-role census and naming decisions (r121 TYPES landing)')
        self.assertEqual(new['note'], 'a round-118 Opus lane tried; see candidate func_81910A9C.c (not published)')
        self.assertEqual(new['path'], row['path'])  # a published file keeps its name
        self.assertEqual(new['lane'], 'r121 remnants census')
        self.assertEqual(new['n'], 3)
        self.assertEqual(P.count_tokens(out), {})
        self.assertEqual(P.scrub_text(out), out)  # idempotent

    def test_untouched_bytes_stay(self):
        line = '{"a":"x","lane":"r95_opus_H","b":[1,2]}'  # compact JSON keeps its spelling
        self.assertEqual(P.scrub_text(line), '{"a":"x","lane":"a round-95 Opus lane","b":[1,2]}')

    def test_phrases(self):
        self.assertEqual(P.lane_phrase('r78_types_phase9'), 'type consolidation phase 9')
        self.assertEqual(P.lane_phrase('opus_goto4'), 'an Opus lane')
        self.assertEqual(P.lane_phrase('c181_followups3'), 'an accuracy lane')
        self.assertEqual(P.lane_phrase('batchAC140'), 'the ACCURACY 140 batch')
        self.assertEqual(P.path_phrase('work/native_' 'lane/lac_hard/REPORT.md'), 'agent report REPORT.md (not published)')
        self.assertEqual(P.path_phrase('work/native_' 'lane/r95_opus_H/cand'), 'working data (not published)')


class CheckTests(unittest.TestCase):
    def setUp(self):
        self.root = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, self.root)
        (self.root / 'ledger').mkdir()
        (self.root / 'tools/lint').mkdir(parents=True)
        (self.root / 'ledger/unions.jsonl').write_text('')
        (self.root / 'ledger/fields.jsonl').write_text('{"decided": "r121w_typesA-final"}\n')
        (self.root / 'ledger/sweeps').mkdir()
        git(self.root, 'init', '-q')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'base')

    def run_check(self):
        buf = io.StringIO()
        n = P.check(self.root, 'HEAD', out=buf)
        return n, buf.getvalue()

    def test_existing_strings_pass_new_fail(self):
        f = self.root / 'ledger/fields.jsonl'
        f.write_text(f.read_text() + '{"decided": "r121w_typesA-final", "x": 1}\n')  # a second copy is new
        n, text = self.run_check()
        self.assertEqual(n, 1)
        self.assertIn("NEW lane ledger/fields.jsonl: 'r121w_typesA-final' (+1)", text)
        f.write_text('{"decided": "r121 B21 types census, final pass"}\n')
        self.assertEqual(self.run_check()[0], 0)

    def test_new_files_and_scope(self):
        (self.root / 'ledger/new.jsonl').write_text('{"evidence": "work/native_' 'lane/x/REPORT.md"}\n')
        (self.root / 'ledger/sweeps/old.jsonl').write_text('{"lane": "r79_sonnet_g13"}\n')  # not a public file
        (self.root / 'tools/lint/debt_baseline.json').write_text('{"note": "c182_tools"}')
        n, text = self.run_check()
        self.assertEqual(n, 2, text)

    def test_ledger_integrity_fails_new(self):
        (self.root / 'ledger/fields.jsonl').write_text('{"decided": "r124w_fields1"}\n')
        buf = io.StringIO()
        with redirect_stdout(buf):
            rc = I.main(['HEAD', '--root', str(self.root), '--fail-new', '--no-layouts'])
        self.assertEqual(rc, 1, buf.getvalue())
        self.assertIn('public ledgers: 1 new lane-local strings', buf.getvalue())
        with redirect_stdout(io.StringIO()):
            self.assertEqual(I.main(['HEAD', '--root', str(self.root), '--no-layouts']), 0)  # report mode


class TreeHashTests(unittest.TestCase):
    """A prototype-floor row's "tree" must name a commit in public history (an ancestor of HEAD or a public ref)."""

    def setUp(self):
        self.root = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, self.root)
        (self.root / 'ledger').mkdir()
        git(self.root, 'init', '-q')
        (self.root / 'a.txt').write_text('a')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'public')
        self.public = git(self.root, 'rev-parse', 'HEAD')
        # a private commit on a side branch: an object of the repository, but not an ancestor of HEAD
        git(self.root, 'checkout', '-qb', 'lane')
        (self.root / 'a.txt').write_text('b')
        git(self.root, 'commit', '-qam', 'private')
        self.private = git(self.root, 'rev-parse', 'HEAD')
        git(self.root, 'checkout', '-q', '-')
        git(self.root, 'branch', '-qD', 'lane')
        (self.root / 'ledger/unions.jsonl').write_text('')
        self.floors = self.root / 'ledger/prototype_floors.jsonl'
        self.floors.write_text(json.dumps({'name': 'f', 'tree': self.public}) + '\n')
        git(self.root, 'add', '-A')
        git(self.root, 'commit', '-qm', 'base')

    def run_check(self, **kw):
        buf = io.StringIO()
        return P.check(self.root, 'HEAD', out=buf, **kw), buf.getvalue()

    def add_row(self, tree):
        self.floors.write_text(self.floors.read_text() + json.dumps({'name': 'g', 'tree': tree}) + '\n')

    def test_public_ancestor_passes(self):
        self.add_row(self.public)
        self.assertEqual(self.run_check()[0], 0)

    def test_new_private_hash_fails(self):
        self.add_row(self.private)
        n, text = self.run_check()
        self.assertEqual(n, 1, text)
        self.assertIn(f'NEW tree ledger/prototype_floors.jsonl: {self.private} (+1)', text)
        # unknown hashes (not even an object here) count as outside public history too
        self.floors.write_text(self.floors.read_text().replace(self.private, '0' * 40))
        self.assertEqual(self.run_check()[0], 1)

    def test_existing_private_hash_is_not_new(self):
        self.add_row(self.private)
        git(self.root, 'commit', '-qam', 'row with a private hash')
        self.floors.write_text(self.floors.read_text() + json.dumps({'name': 'h', 'tree': None}) + '\n')
        self.assertEqual(self.run_check()[0], 0)  # on BASE already: census reports it, check does not fail
        found = P.unreachable_trees(self.root, self.floors.read_text(), P.public_refs(self.root))
        self.assertEqual(dict(found), {self.private: 1})

    def test_lane_root_public_ref(self):
        # a lane root made from master: its history has no master commits, so master hashes need --public-ref
        lane = Path(tempfile.mkdtemp())
        self.addCleanup(shutil.rmtree, lane)
        git(lane, 'init', '-q')
        (lane / 'objects').write_text('')
        (lane / '.git/objects/info/alternates').write_text(str(self.root / '.git/objects') + '\n')
        (lane / 'ledger').mkdir()
        (lane / 'ledger/prototype_floors.jsonl').write_text('')
        git(lane, 'add', '-A')
        git(lane, 'commit', '-qm', 'base')
        (lane / 'ledger/prototype_floors.jsonl').write_text(json.dumps({'name': 'g', 'tree': self.public}) + '\n')
        buf = io.StringIO()
        self.assertEqual(P.check(lane, 'HEAD', out=buf), 1)
        self.assertEqual(P.check(lane, 'HEAD', out=io.StringIO(), public_ref=[self.public]), 0)
        os.environ['LEDGER_PUBLIC_REF'] = self.public
        try:
            self.assertEqual(P.check(lane, 'HEAD', out=io.StringIO()), 0)
        finally:
            del os.environ['LEDGER_PUBLIC_REF']

    def test_ledger_integrity_fails_new_tree(self):
        self.add_row(self.private)
        buf = io.StringIO()
        with redirect_stdout(buf):
            rc = I.main(['HEAD', '--root', str(self.root), '--fail-new', '--no-layouts'])
        self.assertEqual(rc, 1, buf.getvalue())
        self.assertIn('1 new private commit hashes', buf.getvalue())


if __name__ == '__main__':
    unittest.main()
