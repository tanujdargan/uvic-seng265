#!/bin/bash

# Found the 'awk' incantation at: https://bit.ly/302nrh4

AMOUNT=$1
SEED=$2

AWK=/usr/bin/awk

$AWK -v n=$AMOUNT -v seed="$SEED" \
    'BEGIN { srand(seed); for (i=0; i<n; i++) printf("%.10f\n", rand()) }'
