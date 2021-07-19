#!/usr/bin/env python3
# -*-coding:Utf-8 -*-

# -----------------------------------------------------------------------------
# Verify if all source files have the right number of lines and function.
#
# Author:  Mathieu Zimmermann
# Contact: mathieu.zimmermann@epita.fr
# Created: 15/11/2020
# -----------------------------------------------------------------------------

import os
import subprocess
import sys
import fnmatch
import re

# Constants
# -----------------------------------------------------------------------------
MAX_LINES_PER_FUNCTION = 25
LIMIT_FUNCTION = 10
SOURCE_DIR = "./src"
TESTS_DIR = "./tests"

# Help message
# -----------------------------------------------------------------------------
HELP = """\
Check following coding-style rules for all source files:

- limit of {0} function per files
- limit of {1} lines per function

\033[33mUSAGE:\033[0m

    check_lines_nb
    check_lines_nb OPTION

\033[33mOPTIONS:\033[0m

    -v, --verbose   Display all sources files to check.
    -h, --help      Displays this help and exits.
""".format(LIMIT_FUNCTION, MAX_LINES_PER_FUNCTION)

# Short color messages
# -----------------------------------------------------------------------------
MSG_TOO_MUCH_LINES_ERROR = "\033[31m\033[1mToo much lines: \033[0m"
MSG_TOO_MUCH_FUNC_ERROR = "\033[31m\033[1mToo much functions: \033[0m"
ERROR = "\033[31m\033[1mALL ERRORS :\033[0m"
OK = "\033[32m\033[1mcheck_lines_nb: OK\033[0m"
CHECK = "\033[33mCHECK:\033[0m"

# Functions
# -----------------------------------------------------------------------------
def display_error(all_err):
    """
    Prints all error messages.
    """
    print(ERROR)
    for error in all_err:
        print(str(error[0] + ": " + error[3]
                + str(error[1]) + " at line " + str(error[2])))

def verif_file(src_file, file, err):
    """
    Get errors with lines and number of function in each files.
    """
    current_line = 0
    function_counter = 0
    current_line_in_file = 0
    for line in file:
        current_line += 1
        lines_counter = 0
        if re.match("^{$", line):
            current_line_in_file = current_line - 1
            function_counter += 1
            for func_body in file:
                current_line += 1
                if re.match("^}$", func_body):
                    break
                elif re.match("^[ ]*[{}]?$|[ ]*//.*", func_body):
                    continue
                else:
                    lines_counter += 1
            if lines_counter > MAX_LINES_PER_FUNCTION:
                err.append((src_file, lines_counter, current_line_in_file,
                    MSG_TOO_MUCH_LINES_ERROR))
    if function_counter > LIMIT_FUNCTION:
        err.append((src_file, function_counter, current_line_in_file,
            MSG_TOO_MUCH_FUNC_ERROR))



def all_src_files(patterns, start_point):
    src_files = []
    for path, _dirs, files, dirfd in os.fwalk(start_point,topdown=False):
        for filename in files:
            for pattern in patterns:
                if fnmatch.fnmatch(filename, pattern):
                    src_files.append(path + "/" + filename)
                    break
    return src_files


# Main program
# -----------------------------------------------------------------------------

args = sys.argv
VERBOSE = 0
if len(args) > 2:
    raise "Too many arguments."
if len(args) == 2:
    if (args[1] == '-v' or args[1] == "--verbose"):
        VERBOSE = 1
    elif (args[1] == '-h' or args[1] == "--help"):
        print(HELP)
        sys.exit(0)
# get all source files
all_patterns = ["*.c", "*.h"]
src_files = all_src_files(all_patterns, TESTS_DIR) + all_src_files(all_patterns, SOURCE_DIR)
clang = subprocess.run(["clang-format","-i"] + src_files, check=True)
print("Format: {}".format(clang.args))
err = []
for src_file in src_files:
    if src_file[-1] == 'c':
        with open(src_file) as file:
            src_file = src_file[2:]
            if VERBOSE:
                print(CHECK + " " + src_file)
            verif_file(src_file, file, err)
if err != []:
    display_error(err)
    sys.exit(1)
else:
    print(OK)
