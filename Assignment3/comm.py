#!/usr/bin/python

import sys
from optparse import OptionParser

def main():
    #sets version and usage messages
    version_msg = "%prog 2.0"
    usage_msg = "%prog [-123u] FILE1 FILE2"

    #handles different options []-u123] using an OptionsParser
    #access using options.[destName]
    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-u", action="store_true", dest="unsorted", default=0)
    parser.add_option("-1", action="store_true", dest="omit1", default=0)
    parser.add_option("-2", action="store_true", dest="omit2", default=0)
    parser.add_option("-3", action="store_true", dest="omit3", default=0)
    options, args = parser.parse_args(sys.argv[1:])

    if len(args)!=2:
        parser.error("Wrong number of operands")

    values1 = []
    values2 = []

    #read lines from stdin if "-" character is used
    if args[0] == "-":
        values1 = sys.stdin.readlines()
    #otherwise, gets values from args[0] into values1
    else:
        try:
            f1 = open(args[0], 'r')
            values1 = f1.readlines()
            f1.close()
        except:
            parser.error(args[0] + ": Invalid file")

    #read lines from stdin if "-" character is used
    if args[1] == "-":
        values2 = sys.stdin.readlines()
    #otherwise, gets values from args[1] into values2
    else:
        try:
            f2 = open(args[1], 'r')
            values2 = f2.readlines()
            f2.close
        except:
            parser.error(args[1] + ": Invalid file")

    #checks if inputs are sorted
    #shows error message if option and inputSorted do not match
    inputSorted = (values1 == sorted(values1)) and (values2 == sorted(values2))
    if (not inputSorted) and (options.unsorted == 0):
        parser.error("Value Error: the input file(s) are not sorted. Use "\
                    "-u if the files are unsorted.")

    #initialize two integers to iterate through values1 and values2
    iter1 = 0
    iter2 = 0

    #SORTED CASE
    if not options.unsorted:
        #keeps iterating through all values in arrays
        while iter1 < len(values1) and iter2 < len(values2):
            #checks that iter1 is in bounds
            if values1[iter1] < values2[iter2]:
                #print if not -1
                if not options.omit1:
                    sys.stdout.write(values1[iter1])
                iter1 += 1
                continue

            #checks that iter2 is in bounds
            if values2[iter2] < values1[iter1]:
                #Print if not -2
                if not options.omit2:
                    val = 8
                    if options.omit1:
                        val -= 8
                    sys.stdout.write(" " * val + values2[iter2])
                iter2 += 1
                continue

            #checks that both iter1 and iter2 are in bounds
            if values1[iter1] == values2[iter2]:
                #Print if not -3
                if not options.omit3:
                    val = 16
                    if options.omit1:
                        val -= 8
                    if options.omit2:
                        val -= 8
                    sys.stdout.write(" " * val + values1[iter1])
                iter1 += 1
                iter2 += 1
                continue

        #prints remaining values in values1
        if iter1 != len(values1):
            while iter1 < len(values1):
                if not options.omit1:
                    sys.stdout.write(values1[iter1])
                iter1 += 1
        #print remaining values in values2
        else:
            while iter2 < len(values2):
                if not options.omit2:
                    val = 8
                    if options.omit1:
                        val -= 8
                    sys.stdout.write(" " * val + values2[iter2])
                iter2 += 1

    #UNSORTED CASE
    else:
        #iterates through words in values1
        for val1 in values1:
            #nested iteration through words in values2
            for val2 in values2:
                #compares words and sees if word1 is in values2
                if val1 == val2:
                    #only prints if not -3
                    if not options.omit3:
                        val = 16
                        if options.omit1:
                            val -= 8
                        if options.omit2:
                            val -= 8
                        sys.stdout.write(" " * val + val1)
                    values2.remove(val1)
                    break
            else:
                #only prints if not -1
                if not options.omit1:
                    sys.stdout.write(val1)

        #iterates through words in values2
        for val2 in values2:
            #only prints if not -2
            if not options.omit2:
                val = 8
                if options.omit1:
                    val -= 8
                sys.stdout.write(" " * val + val2)


if __name__== "__main__":
    main()
