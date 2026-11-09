"""ledger_integrity: union ledger loads, retired_to_cast sites and their re-derivation.

    python3 -m unittest tools.lint.test_ledger_integrity
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
import ledger_integrity as I  # noqa: E402


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME='t', GIT_AUTHOR_EMAIL='t@invalid',
               GIT_COMMITTER_NAME='t', GIT_COMMITTER_EMAIL='t@invalid')
    return subprocess.run(['git', *args], cwd=root, env=env, check=True,
                          capture_output=True, text=True).stdout.strip()


def loads(**members):
    zero = dict(lb=0, lbu=0, lh=0, lhu=0, lw=0, sb=0, sh=0, sw=0, unmapped=0)
    return {name: dict(zero, **counts) for name, counts in members.items()}


def row(rid, sites=(), status='retired', path='f', member_loads=None):
    return dict(id=rid, status=status, path=path, members=[dict(name='s', type='s16'), dict(name='u', type='u16')],
                retired_to_cast=list(sites), loads=member_loads or loads(s={}, u={}))


class ParseTests(unittest.TestCase):
    def test_forms(self):
        p = I.parse_entry('src/a.c:12 (s16)')
        self.assertEqual((p['kind'], p['line'], p['second'], p['cast']), ('site', 12, None, '(s16)'))
        p = I.parse_entry('src/a.c:289,291 *(u8 *)& width casts of x and y')
        self.assertEqual((p['line'], p['second'], I.squash(p['cast'])), (289, 291, '*(u8*)&'))
        p = I.parse_entry('src/a.c:226,3 (u16)')
        self.assertEqual((p['second'], p['extra']), (None, 3))
        self.assertEqual(I.parse_entry('src/a.c:9 (S_8017_0 *)')['cast'], '(S_8017_0 *)')
        self.assertEqual(I.parse_entry('src/a.c:9 (u8 *)&effect->x')['cast'], '(u8 *)')
        self.assertEqual(I.parse_entry('src/a.c (former member sites)')['kind'], 'note')
        self.assertEqual(I.parse_entry('src/a.c (u16) (cast gone)')['kind'], 'note')
        self.assertEqual(I.parse_entry('src/a.c:46')['kind'], 'nocast')
        p = I.parse_entry(dict(site='src/a.c:5', cast='(Handler)run', to='handler'))
        self.assertEqual((p['kind'], p['line'], p['cast']), ('site', 5, '(Handler)'))

    def test_cast_fields(self):
        self.assertEqual(I.cast_fields('x = (s16)p->a + (s16)q.b;', '(s16)'), {'a', 'b'})
        self.assertEqual(I.cast_fields('((S_1 *)p)->unk_96 = 0;', '(S_1*)'), {'unk_96'})


class SiteTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'src').mkdir()
        (self.root / 'src/a.c').write_text('int a;\nx = (s16)p->f;\ny = *(u8 *)&p->g;\nz = *(u8 *)&p->h;\n')
        self.texts = I.Texts(self.root)

    def test_check_entry(self):
        check = lambda e: I.check_entry(e, self.texts)  # noqa: E731
        self.assertEqual(check('src/a.c:2 (s16)'), 'ok')
        self.assertEqual(check('src/a.c:2 ( s16 ) value cast'), 'ok')
        self.assertEqual(check('src/a.c:1 (s16)'), 'stale')
        self.assertEqual(check('src/a.c:9 (s16)'), 'noline')
        self.assertEqual(check('src/b.c:1 (s16)'), 'nofile')
        self.assertEqual(check('src/a.c:3,4 *(u8 *)& both'), 'ok')
        self.assertEqual(check('src/a.c:2,4 *(u8 *)& both'), 'stale')     # second line checked too
        self.assertEqual(check('src/a.c:2,1 (s16)'), 'ok')                # small n is a count
        self.assertEqual(check('src/a.c:4'), 'ok')
        self.assertEqual(check('src/a.c (former member sites)'), 'note')


class LoadsTests(unittest.TestCase):
    def test_zeroed_rows_and_count_drop_fail(self):
        base = [row('a', member_loads=loads(s=dict(lh=3), u=dict(lhu=1))), row('b')]
        head = [row('a'), row('b')]                      # the AC131 B2 shape: regenerated all-zero
        result = I.check_loads(base, head)
        self.assertEqual(result['zeroed'], ['a'])
        self.assertEqual(len(result['problems']), 2)

    def test_missing_loads_key_counts_as_zero(self):
        base = [dict(id='a', status='retired')]
        head = [row('a', member_loads=loads(s=dict(lh=2)))]
        self.assertEqual(I.check_loads(base, head)['problems'], [])

    def test_weak_evidence_counts_loads_not_stores(self):
        rows = [row('a', member_loads=loads(s=dict(lh=1, sh=9))),
                row('b', member_loads=loads(s=dict(lh=4), u=dict(lhu=3))),
                row('c', member_loads=loads(s=dict(lh=2), u=dict(lhu=2))),
                row('d'), row('e', status='unproven', member_loads=loads(s=dict(lh=1)))]
        weak = I.weak_evidence(rows, [row('c')])
        self.assertEqual(weak['all'], dict(rows=3, under5=2, one=1))
        self.assertEqual(weak['no_load_data'], 1)
        self.assertEqual(weak['newly_retired'], dict(rows=2, under5=1, one=1))


class EvidenceLoadTests(unittest.TestCase):
    def test_prose_numbers_are_compared_with_the_loads_field(self):
        agree = row('a', member_loads=loads(s=dict(lh=2), u=dict(lhu=4, unmapped=1)))
        agree['evidence'] = 'u16: retail loads 2 lh versus 4 lhu, 1 unmapped; signed reads take (s16) casts.'
        wrong = row('b', member_loads=loads(s=dict(lh=9), u=dict(lhu=1)))
        wrong['evidence'] = 'Its mapped retail loads are 9 lh and 3 lhu, with two other reads unmapped.'
        no_loads_word = row('c', member_loads=loads(s={}, u={}))
        no_loads_word['evidence'] = 'Scoped object comparison was byte-equal for 33 recipes and 4 lh sites.'
        no_field = dict(id='d', evidence='retail loads 2 lh', status='retired')
        self.assertEqual(I.evidence_load_mismatches([agree, wrong, no_loads_word, no_field]),
                         [('b', 'lhu', [3], 1)])
        # either of two quoted numbers may be the current one (BASE and HEAD both quoted)
        agree['evidence'] = 'loads were 2 lh and 3 lhu, now 2 lh and 4 lhu'
        self.assertEqual(I.evidence_load_mismatches([agree]), [])


class RepoTests(unittest.TestCase):
    """BASE/HEAD comparisons and re-derivation through the file's history."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        root = self.root = Path(self.tmp.name)
        (root / 'src').mkdir()
        (root / 'ledger').mkdir()
        self.source = root / 'src/a.c'
        self.source.write_text('void f(S *p)\n{\n    x = (s16)p->f;\n    y = (u16)p->g;\n}\n')
        rows = [row('r1', ['src/a.c:3 (s16)'], path='f'),
                row('r2', ['src/a.c:4 (u16)', 'src/a.c:1 (u16) stale already'], path='g')]
        self.write(rows)
        git(root, 'init', '-q')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')

    def write(self, rows):
        (self.root / I.LEDGER).write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in rows))

    def run_main(self, *args):
        with redirect_stdout(io.StringIO()) as out:
            code = I.main(['HEAD', '--root', str(self.root), *args])
        return code, out.getvalue()

    def test_fail_new_ignores_entries_already_stale_on_base(self):
        self.source.write_text('/* moved */\n' + self.source.read_text())
        code, out = self.run_main('--fail-new')
        self.assertEqual(code, 1)
        self.assertIn('NEW STALE r1: src/a.c:3 (s16)', out)
        self.assertNotIn('stale already', out)
        code, out = self.run_main('--fail-all')
        self.assertIn('stale already', out)
        self.assertEqual(self.run_main()[0], 0)          # report-only by default

    def test_loads_regression_always_fails(self):
        rows = [row('r1', ['src/a.c:3 (s16)'], path='f', member_loads=loads(s=dict(lh=2)))]
        self.write(rows)
        git(self.root, 'commit', '-qam', 'loads')
        self.write([row('r1', ['src/a.c:3 (s16)'], path='f')])
        code, out = self.run_main()
        self.assertEqual(code, 1)
        self.assertIn('LOADS loads zeroed: r1', out)

    def test_rederive_follows_history_and_marks_gone(self):
        self.source.write_text('/* header */\n#include "x.h"\n' +
                               self.source.read_text().replace('    y = (u16)p->g;\n', '    y = p->g;\n'))
        git(self.root, 'commit', '-qam', 'edit')
        code, out = self.run_main('--rederive', '--write')
        self.assertEqual(code, 0, out)
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        self.assertEqual(rows[0]['retired_to_cast'], ['src/a.c:5 (s16)'])
        self.assertEqual(rows[1]['retired_to_cast'][0], 'src/a.c (u16) (cast gone)')
        self.assertIn('history', out)
        self.assertEqual(self.run_main('--fail-all')[0], 0)

    def test_rederive_without_history_needs_the_rows_field(self):
        self.source.write_text('void f(S *p)\n{\n    w = (u16)p->other;\n    x = (s16)p->f;\n    y = (u16)p->g;\n}\n')
        rows = [row('r2', ['src/a.c:2 (u16) branch line'], path='g')]   # never true on any commit
        self.write(rows)
        self.run_main('--rederive', '--write')
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        self.assertEqual(rows[0]['retired_to_cast'], ['src/a.c:5 (u16) branch line'])

    def test_git_opcodes_track_hunk_offsets(self):
        old = ['a', 'b', 'c', 'd', 'e', 'f']
        new = ['a', 'c', 'x', 'y', 'e', 'f', 'g']
        ops = I.git_opcodes(old, new)
        self.assertEqual(ops[0], ('equal', 0, 1, 0, 1))
        self.assertEqual(I.map_line(ops, new, 3, 'c', lambda n: 'field'), (2, 2, 'field'))   # b deleted: c moves up
        self.assertEqual(I.map_line(ops, new, 6, 'f', lambda n: 'field')[0], 6)
        self.assertEqual(I.git_opcodes(['a'], ['a']), [('equal', 0, 1, 0, 1)])

    def test_rederive_offsets_through_deletions_not_nearest_text(self):
        # The entry's field never held on a commit (the cited cast read another member), seven lines
        # then go before it and the member is corrected.  A later cast of the same field and spelling
        # sits nearer the old number than the moved line; the git offset still picks the moved one.
        body = ''.join(f'    pad{n} = {n};\n' for n in range(7))
        original = ('void f(S *p)\n{\n' + body + '    x = (s16)p->g;\n' + ''.join(f'    q{n} = 0;\n' for n in range(4))
                    + '    y = (s16)p->f;\n}\n')
        self.source.write_text(original)
        git(self.root, 'commit', '-qam', 'long')
        self.write([row('r1', ['src/a.c:10 (s16)'], path='f')])
        self.source.write_text(original.replace(body, '').replace('p->g', 'p->f'))
        git(self.root, 'commit', '-qam', 'shrink')
        self.run_main('--rederive', '--write')
        out = I.read_ledger((self.root / I.LEDGER).read_text())[0]
        self.assertEqual(out['retired_to_cast'], ['src/a.c:3 (s16)'])

    def test_duplicates_share_a_line_and_status_is_untouched(self):
        self.source.write_text('\n\n' + self.source.read_text())
        rows = [row('r1', ['src/a.c:3 (s16)', 'src/a.c:3 (s16)'], path='f')]
        rows[0]['evidence'] = 'prose stays'
        self.write(rows)
        self.run_main('--rederive', '--write')
        out = I.read_ledger((self.root / I.LEDGER).read_text())[0]
        self.assertEqual(out['retired_to_cast'], ['src/a.c:5 (s16)', 'src/a.c:5 (s16)'])
        self.assertEqual((out['status'], out['evidence']), ('retired', 'prose stays'))


TYPES = 'typedef signed char s8;\ntypedef unsigned char u8;\ntypedef short s16;\n' \
        'typedef unsigned short u16;\ntypedef int s32;\n'


def frow(path, owner='S', members=('s', 'u'), file='src/a.c'):
    return dict(id=f'{file}::{owner}.{path}', owner=owner, path=path, file=file, status='retired',
                members=[dict(name=m) for m in members], retired_to_cast=[])


class FieldRuleTests(unittest.TestCase):
    """The cited span must reference the row's field; built from real ledger cases."""

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        (self.root / 'src').mkdir()
        (self.root / 'include').mkdir()

    def classify(self, row, entry, source, layouts=False):
        (self.root / 'src/a.c').write_text(source)
        return I.field_class(row, entry, I.Texts(self.root), I.Layouts(self.root, layouts))

    def test_ac133_rederived_line_holding_another_field_is_wrong(self):
        # FadingSpriteSequenceBody.unk_58 re-derived onto the line that casts unk_7C.
        source = ('void f(FadingSpriteSequenceBody *effect, S *effect_data, P *position)\n{\n'
                  '    effect_data->unk_4C = (u16)effect->unk_58;\n'
                  '    position->x.w.i = (u16)effect->unk_7C;\n'
                  '    spawn_x = (s16)(((u16)effect->unk_58 +\n'
                  '              (effect->unk_4C - effect->unk_58) * step / 6);\n}\n')
        row = frow('unk_58', 'FadingSpriteSequenceBody')
        self.assertEqual(self.classify(row, 'src/a.c:4 (u16)', source), 'wrong')
        self.assertEqual(self.classify(row, 'src/a.c:3 (u16)', source), 'field')
        self.assertEqual(self.classify(row, 'src/a.c:5 (u16)', source), 'field')

    def test_ac134_misses_are_wrong(self):
        star = ('    effect_data->unk_5A = effect_data->unk_5E =\n        (u16)effect_data->unk_20;\n'
                '    effect_data->unk_62 = effect_data->unk_66 =\n        (u16)effect_data->unk_22;\n')
        row = frow('unk_20', 'StarEdgeEffectBody')
        self.assertEqual(self.classify(row, 'src/a.c:2 (u16)', star), 'field')
        self.assertEqual(self.classify(row, 'src/a.c:4 (u16)', star), 'wrong')
        route = ('            entity->unk_02 = 0;\n            entity->unk_00 = (u16)entity->unk_00 + 1;\n'
                 '            entity->unk_04 = (u16)entity->unk_02 + 1;\n')
        row = frow('unk_00', 'B32_818CF0E8_S_818CF0E8_0')
        self.assertEqual(self.classify(row, 'src/a.c:2 (u16)', route), 'field')
        self.assertEqual(self.classify(row, 'src/a.c:3 (u16)', route), 'wrong')
        menu = ('    ((FivePointEffectBody *)effect)->unk_4A = (s16) ((u16) ((FivePointEffectBody *)effect)->unk_4A + 1);\n'
                '    next_phase = (u16)((FivePointEffectBody *)effect)->unk_50 + 1;\n')
        row = frow('unk_4A', 'S_800BB55C_0')          # owner retyped; the field name still checks
        self.assertEqual(self.classify(row, 'src/a.c:1 (u16)', menu), 'field')
        self.assertEqual(self.classify(row, 'src/a.c:2 (u16)', menu), 'wrong')

    def test_span_lines_and_shifted_span(self):
        # `,n` is a span of n lines; a one-line shift onto the neighbour's cast is wrong.
        source = ('                if (effect->unk_26 == 1) {\n'
                  '                    (*(s16 *)&effect->unk_16) = 10;\n'
                  '                    (*(s16 *)&effect->unk_1E) = 0;\n'
                  '                    motion->velocity_y = 0;\n'
                  '    if (find_first_entry_matching_keys(owner, (u16)(s8)((u8)effect->unk_4C),\n'
                  '                      (u16)(s8)((u8)effect->unk_4D),\n'
                  '                      motion->z.w.i) != 0) {\n')
        row16, row1e = frow('unk_16', 'S_func_810332A4_1'), frow('unk_1E', 'S_func_810332A4_1')
        self.assertEqual(self.classify(row16, 'src/a.c:2,2 *(s16 *)&', source), 'field')
        self.assertEqual(self.classify(row1e, 'src/a.c:2,2 *(s16 *)&', source), 'field')
        self.assertEqual(self.classify(row16, 'src/a.c:3,2 *(s16 *)&', source), 'wrong')
        row4c, row4d = frow('unk_4C', 'S_func_810332A4_1'), frow('unk_4D', 'S_func_810332A4_1')
        self.assertEqual(self.classify(row4d, 'src/a.c:5,2 (u8)', source), 'field')   # field on line 2 of span
        self.assertEqual(self.classify(row4c, 'src/a.c:6,2 (u8)', source), 'wrong')

    def test_owner_pointer_cast_same_or_next_line(self):
        source = ('    ((S_80175594_1 *)scratch)->unk_104 =\n'
                  '        (render->unk_1A - (*(u16 *)&((S_80175594_1 *)scratch)->unk_34));\n'
                  '    view_angle = ((*(u16 *)&((S_80175594_1 *)scratch)->unk_38) + 0x100) & 0x1FF;\n'
                  '    angle_offset = render->unk_18 - 0x100;\n'
                  '    ((S_80175594_1 *)scratch)->unk_102 = view_angle + angle_offset;\n')
        row = frow('unk_34', 'S_80175594_1', ('s32', 'u16'))
        self.assertEqual(self.classify(row, 'src/a.c:2,2 (S_80175594_1 *)', source), 'field')
        self.assertEqual(self.classify(row, 'src/a.c:3,2 (S_80175594_1 *)', source), 'wrong')  # the master case
        split = '    angle = (S_80175594_1 *)scratch\n        ->unk_34;\n'
        self.assertEqual(self.classify(row, 'src/a.c:1 (S_80175594_1 *)', split), 'field')   # next line
        row = frow('unk_96', 'S_807B040C_1')
        line = ('((S_807B040C_1 *)entity)->unk_88 = (s16)sample(*(u16 *)&((ObjectPosition *)motion)->x.w.i,\n'
                '    *(u16 *)&((ObjectPosition *)motion)->y.w.i, -0x400);\n')
        self.assertEqual(self.classify(row, 'src/a.c:1,2 (S_807B040C_1 *)', line), 'wrong')

    def test_member_and_declarator_aliases(self):
        grid = ('    *(u8 *)&((GridPoint *)((u8 *)base + (motion->unk_34 << 2)))->x;\n'
                '    coord = (u16)step->y;\n    k = (u16)tile->n;\n')
        self.assertEqual(self.classify(frow('unk_00', 'GridPoint', ('x', 'unk_00')), 'src/a.c:1 *(u8 *)&', grid),
                         'alias')
        self.assertEqual(self.classify(frow('unk_02', 'GridPoint', ('y', 'unk_02')), 'src/a.c:2 (u16)', grid),
                         'alias')
        self.assertEqual(self.classify(frow('unk_10', 'Tile', ('n', 'v')), 'src/a.c:3 (u16)', grid), 'alias')
        # Signedness member names are not aliases; an unproven named member is only reported.
        self.assertEqual(self.classify(frow('unk_10', 'Tile', ('s', 'u')), 'src/a.c:3 (u16)', grid), 'renamed?')
        decl = ('typedef struct FollowingColorEffect {\n    u8 pad_00[8];\n    u16 angle_x, angle_y, angle_z;\n'
                '    s16 target_x, target_y, target_z;\n} FollowingColorEffect;\n'
                'void f(FollowingColorEffect *state) {\n    v = (s16)state->angle_y;\n'
                '    w = (u16)state->target_z;\n}\n')
        angle = frow('angle_x', 'FollowingColorEffect')
        self.assertEqual(self.classify(angle, 'src/a.c:7 (s16)', decl), 'alias')
        self.assertEqual(self.classify(angle, 'src/a.c:8 (u16)', decl), 'wrong')
        self.assertEqual(self.classify(frow('target_x', 'FollowingColorEffect'), 'src/a.c:8 (u16)', decl), 'alias')

    def test_entry_text_names_the_member(self):
        source = '    coord = (u16)step->y;\n    if ((s16)effect->ticks_left <= 0) {\n'
        grid = frow('unk_00', 'GridPoint', ('x', 'unk_00'))
        self.assertEqual(self.classify(grid, 'src/a.c:1 (u16) value cast of y', source), 'named')
        self.assertEqual(self.classify(grid, 'src/a.c:1 (u16) value cast', source), 'renamed?')
        row = frow('unk_96', 'S_80975170_0')
        self.assertEqual(self.classify(row, 'src/a.c:2 (s16)effect->ticks_left', source), 'named')
        handler = dict(site='src/a.c:1', cast='(u16)step', to='y')
        self.assertEqual(self.classify(frow('unk_8C', 'ActorRecord'), handler, source), 'named')

    def test_typedef_and_variable_rows(self):
        source = ('    offset = (s16)town_display_offset;\n    offset_bits = (u16)town_display_offset;\n'
                  '    extent = (u16)object->extent - 6;\n')
        row = frow('town_display_offset', 'town_display_offset')
        self.assertEqual(self.classify(row, 'src/a.c:2 (u16)', source), 'typedef')
        self.assertEqual(self.classify(frow('TownExtent', 'TownExtent'), 'src/a.c:3 (u16)', source), 'typedef?')

    def test_nofield_is_reported_not_failing(self):
        source = '    (s16)(origin->field_25 + (u16)dir_step_y[offset >> 1]),\n'
        self.assertEqual(self.classify(frow('field_2A', 'ActorBytesFieldView_80E91000'), 'src/a.c:1 (u16)', source),
                         'nofield')

    @unittest.skipUnless(shutil.which('clang'), 'clang not installed')
    def test_renamed_field_proven_by_record_layout(self):
        source = TYPES + ('typedef struct PositionedGraphicEffectBody {\n    u8 pad_00[0x4];\n    s32 unk_04;\n'
                          '    u8 pad_08[0x5C];\n    s16 phase;\n    s16 frames_left;\n} PositionedGraphicEffectBody;\n'
                          'typedef struct Other { u8 pad[0x60]; s16 phase; } Other;\n'
                          'void f(PositionedGraphicEffectBody *effect, Other *o) {\n'
                          '    effect->phase = (u16)effect->phase + 1;\n    o->phase = (u16)o->phase + 1;\n}\n')
        n = source.count('\n') - 2
        self.assertEqual(self.classify(frow('unk_64', 'S_80026FB0_0'), f'src/a.c:{n} (u16)', source, True),
                         'renamed')
        self.assertEqual(self.classify(frow('unk_64', 'S_80026FB0_0'), f'src/a.c:{n} (u16)', source), 'renamed?')
        # A member found only at another offset is not this row's field.
        self.assertEqual(self.classify(frow('unk_62', 'S_80026FB0_0'), f'src/a.c:{n} (u16)', source, True),
                         'wrong')
        self.assertEqual(self.classify(frow('unk_60', 'S_80026FB0_0'), f'src/a.c:{n + 1} (u16)', source, True),
                         'renamed')

    @unittest.skipUnless(shutil.which('clang'), 'clang not installed')
    def test_typedef_member_from_record_layout(self):
        source = TYPES + ('typedef u16 TownExtent;\ntypedef struct O { s16 x; TownExtent extent; } O;\n'
                          'void f(O *object) {\n    extent = (u16)object->extent - 6;\n    x = (u16)object->x;\n}\n')
        n = source.count('\n') - 2
        row = frow('TownExtent', 'TownExtent')
        self.assertEqual(self.classify(row, f'src/a.c:{n} (u16)', source, True), 'typedef')
        self.assertEqual(self.classify(row, f'src/a.c:{n + 1} (u16)', source, True), 'typedef?')


class FieldRuleRepoTests(unittest.TestCase):
    """--fail-new / --fail-all and --rederive under the field rule."""

    SOURCE = ('/* header */\nvoid f(Body *effect, S *effect_data, P *position)\n{\n'
              '    effect_data->unk_4C = (u16)effect->unk_58;\n'
              '    effect_data->unk_4E = (u16)effect->unk_7C;\n'
              '                    (*(s16 *)&effect->unk_16) = 10;\n'
              '                    (*(s16 *)&effect->unk_1E) = 0;\n'
              '    z = (u16)dir_step_y[d];\n}\n')

    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        root = self.root = Path(self.tmp.name)
        (root / 'src').mkdir()
        (root / 'ledger').mkdir()
        self.source = root / 'src/a.c'
        self.source.write_text(self.SOURCE)
        rows = [frow('unk_58', 'Body'), frow('unk_16', 'Body')]
        rows[0]['retired_to_cast'] = ['src/a.c:4 (u16)']
        rows[1]['retired_to_cast'] = ['src/a.c:6,2 *(s16 *)&']
        self.write(rows)
        git(root, 'init', '-q')
        git(root, 'add', '-A')
        git(root, 'commit', '-qm', 'base')

    def write(self, rows):
        (self.root / I.LEDGER).write_text(''.join(json.dumps(r, sort_keys=True) + '\n' for r in rows))

    def run_main(self, *args):
        with redirect_stdout(io.StringIO()) as out:
            code = I.main(['HEAD', '--root', str(self.root), '--no-layouts', *args])
        return code, out.getvalue()

    def drop_header(self):
        # One line removed above: both cited lines still hold the cast spelling, now
        # applied to the neighbouring field (the shape the old token check passed).
        self.source.write_text(self.SOURCE.replace('/* header */\n', ''))

    def test_wrong_field_fails_new_but_not_when_already_wrong_on_base(self):
        self.assertEqual(self.run_main('--fail-all')[0], 0)
        self.drop_header()
        code, out = self.run_main('--fail-new')
        self.assertEqual(code, 1, out)
        self.assertIn('NEW WRONG src/a.c::Body.unk_58: src/a.c:4 (u16)', out)
        self.assertIn('NEW WRONG src/a.c::Body.unk_16: src/a.c:6,2 *(s16 *)&', out)
        self.assertIn('stale 0', out)
        self.assertIn('wrong 2', out)
        git(self.root, 'commit', '-qam', 'moved')
        self.assertEqual(self.run_main('--fail-new')[0], 0)           # already wrong on BASE
        self.assertEqual(self.run_main('--fail-all')[0], 1)

    def test_report_only_classes_never_fail(self):
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        rows.append(dict(frow('unk_2A', 'Body'), retired_to_cast=['src/a.c:8 (u16)']))
        self.write(rows)
        code, out = self.run_main('--fail-all', '--list')
        self.assertEqual(code, 0, out)
        self.assertIn('nofield 1', out)

    def test_rederive_moves_wrong_entries_onto_their_field(self):
        self.drop_header()
        git(self.root, 'commit', '-qam', 'moved')
        code, out = self.run_main('--rederive', '--write')
        self.assertEqual(code, 0, out)
        rows = I.read_ledger((self.root / I.LEDGER).read_text())
        self.assertEqual(rows[0]['retired_to_cast'], ['src/a.c:3 (u16)'])
        self.assertEqual(rows[1]['retired_to_cast'], ['src/a.c:5,2 *(s16 *)&'])
        self.assertEqual(self.run_main('--fail-all')[0], 0)

    def test_rederive_never_lands_on_another_fields_cast(self):
        # The AC133 shape: the row's own cast is retyped away and the cited line now
        # holds the same cast spelling on a neighbouring field.
        self.source.write_text('/* header */\nvoid f(Body *effect, S *effect_data, P *position)\n{\n'
                               '    effect_data->unk_4E = (u16)effect->unk_7C;\n'
                               '    effect_data->unk_4C = effect->unk_58;\n}\n')
        git(self.root, 'commit', '-qam', 'retype')
        rows = I.read_ledger((self.root / I.LEDGER).read_text())[:1]
        self.write(rows)
        self.assertEqual(I.field_class(rows[0], 'src/a.c:4 (u16)', I.Texts(self.root)), 'wrong')
        self.run_main('--rederive', '--write')
        out = I.read_ledger((self.root / I.LEDGER).read_text())[0]
        self.assertEqual(out['retired_to_cast'], ['src/a.c (u16) (cast gone)'])

    def test_rederive_does_not_harvest_the_next_lines_field(self):
        # The AC133 mechanism: the row's cast goes (the entry is token-stale), the next line
        # keeps `(u16)effect->unk_7C`; history once harvested unk_7C from the anchor's next
        # line and moved the entry onto it.
        rows = I.read_ledger((self.root / I.LEDGER).read_text())[:1]
        self.source.write_text(self.SOURCE.replace('    effect_data->unk_4C = (u16)effect->unk_58;\n',
                                                   '    effect_data->unk_4C = effect->unk_58;\n'))
        git(self.root, 'commit', '-qam', 'retype')
        self.write(rows)
        self.assertEqual(I.check_entry('src/a.c:4 (u16)', I.Texts(self.root)), 'stale')
        code, out = self.run_main('--rederive', '--write')
        self.assertEqual(code, 0, out)
        out = I.read_ledger((self.root / I.LEDGER).read_text())[0]
        self.assertEqual(out['retired_to_cast'], ['src/a.c (u16) (cast gone)'])


if __name__ == '__main__':
    unittest.main()
