#! /usr/bin/python3

import argparse
import glob
import os
import subprocess


MAX_BRUTE_SIZE = 25000

EXEC_PATH = "../build/lcp_bwt"
TESTS_PATH = "./data"
TESTS_OUT_DIR = "./out"


def cmp_files(filename1, filename2):
    with open(filename1, 'r') as f:
        contents1 = f.read()

    with open(filename2, 'r') as f:
        contents2 = f.read()

    return contents1 == contents2


def generate_tests(sizes):
    print('\nGenerating test cases...')
    print('=' * 40)

    for size in sizes:
        key = 'auto-test_%s' % size
        max_id = max([int(t.rsplit('.', 2)[1]) for t in glob.glob('%s/%s.*.in' % (TESTS_PATH, key))] or [0])
        test_name = os.path.join(TESTS_PATH, '%s.%d' % (key, max_id + 1))
        test_in, test_out = test_name + '.in', test_name + '.out'

        params = ['./testgen', size, test_in, test_out]
        if int(size) > MAX_BRUTE_SIZE:
            params.append('--no-output')

        subprocess.run(params)
        print(size, '::', test_in, test_out)

    print('-' * 40)
    print('Done.\n')


def run_tests():
    print('\nRunning tests...')
    print('=' * 40)

    test_names = set(t.rsplit('.', 1)[0] for t in os.listdir(TESTS_PATH))
    results = []

    for test_name in test_names:
        test_path = os.path.join(TESTS_PATH, test_name)
        test_out = os.path.join(TESTS_OUT_DIR, test_name) + '.out'
        test_in, test_exp = test_path + '.in', test_path + '.out'
        params = [EXEC_PATH, test_in, test_out]
        subprocess.run(params, check=True)
        result = cmp_files(test_out, test_exp)
        results.append(result)
        print(test_name, "->", 'OK' if result else 'WRONG!')

    c, n = len([r for r in results if r]), len(results)
    print('-' * 40)
    print('Results: %d/%d tests passed, %d%%\n' % (c, n, 100 * (c/n if n else 1)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="LCP-BWT implementation test runner.")
    parser.add_argument('-t', '--test', action='store_true', default=False, help="Run all tests and output the results")
    parser.add_argument('-g', '--gen', nargs='+', help="Generate test cases having given sizes")
    args = parser.parse_args()

    print('LCP-BWT implementation test runner, version 0.1')

    if args.gen:
        generate_tests(args.gen)

    if not args.gen or args.test:
        run_tests()
