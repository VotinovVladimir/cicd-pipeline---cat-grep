#!/bin/bash

SUCCESS=0
FAIL=0
DIFF_RES=""

KEYSMulti=('e' 'i' 'v' 'c' 'l' 'n' 'iv' 'ivc' 'ivcn' 'il' 'ivl' 'ivln')
Patterns=("111" "22" "abc" "AB" "Cd" "sa")
SrcFiles=("test1.txt" "test2.txt" "test3.txt")


for P in "${Patterns[@]}"; do
    for Multikey in "${KEYSMulti[@]}"; do
        for file in "${SrcFiles[@]}"; do
          grep "-$Multikey" "'$P'"  "$file" > grep_output_file.txt
          ./s21_grep  "-$Multikey" "'$P'" "$file" > my_grep_output_file.txt

          diff -s grep_output_file.txt my_grep_output_file.txt >/dev/null

          if [ $? -eq 0 ]; then
            ((SUCCESS++))
          else
          ((FAIL++))
          fi
        done
    done
done

    rm grep_output_file.txt
    rm my_grep_output_file.txt

    echo "SUCCESS" $SUCCESS
    echo "FAIL" $FAIL