# Usage of `generate_randoms.sh`

* This `bash` script is a wrapper around an `awk` incantation.

* The first argument is the number of random values to be generated.

* The second argument is an integer serving as the random-number
  generator's seed value (i.e., starting with the same seed value
  will always result in the same sequence of random numbers).

* The random numbers produces are between 0 and 1

* All output is to `stdout` -- so re-direct output to a file if
  you want to use such output as data to be sorted by `tester`.
