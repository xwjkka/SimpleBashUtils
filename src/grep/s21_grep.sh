#!/bin/bash

function TestWithOptions() {
    ./s21_grep -$1 $2 ../../data-samples/$3> ./results.txt
    grep -$1 $2 ../../data-samples/$3> ./results_grep.txt
    diff -s ./results.txt ./results_grep.txt
}

function SimpleTest() {
    ./s21_grep $1 ../../data-samples/$2 > ./results.txt
    grep $1 ../../data-samples/$2 > ./results_grep.txt
    diff -s ./results.txt ./results_grep.txt
}

make rebuild

array=(i v c l n h s o)
array2=(v c l n h s o i)
name_array=(1.txt 2.txt 3.txt)
pattern="ne"
pattern2="^[a-z]"
file=../../data-samples/pattern.txt

for item in ${array[*]}
do
    for name_item in ${name_array[*]}
    do
        printf "\n\tOPTION:%c FILE:%s\n" $item $name_item
        TestWithOptions "$item" "$pattern" "$name_item"
    done
done

for item in ${array[*]}
do
    for sec_item in ${array2[*]}
    do
        printf "\n\tOPTION:%c %c FILE:2.txt\n" $item $sec_item
        ./s21_grep -$item -$sec_item iNt s21_grep.c s21_grep.h> ./results.txt
        grep -$item -$sec_item iNt s21_grep.c s21_grep.h> ./results_grep.txt 
        diff -s ./results.txt ./results_grep.txt

        printf "\n\tOPTION:%c%c FILE:2.txt\n" $item $sec_item
        ./s21_grep -$item$sec_item iNt s21_grep.c s21_grep.h> ./results.txt
        grep -$item$sec_item iNt s21_grep.c s21_grep.h> ./results_grep.txt 
        diff -s ./results.txt ./results_grep.txt
    done
done

for name_item in ${name_array[*]}
do
    printf "\n\tOPTION:e FILE:%s\n" $name_item
    ./s21_grep -e $pattern -e $pattern2 ../../data-samples/$name_item> ./results.txt
    grep -e $pattern -e $pattern2 ../../data-samples/$name_item> ./results_grep.txt
    diff -s ./results.txt ./results_grep.txt
done

for name_item in ${name_array[*]}
do
    printf "\n\tOPTION:f FILE:%s\n" $name_item
    ./s21_grep -f $file ../../data-samples/$name_item> ./results.txt
    grep -f $file ../../data-samples/$name_item> ./results_grep.txt
    diff -s ./results.txt ./results_grep.txt
done

for name_item in ${name_array[*]}
do
    printf "\n\tOPTION:none FILE:%s\n" $name_item
    SimpleTest "da" "$name_item"
done

printf "\n\tOPTION:fff\n"
./s21_grep -v -e k s21_grep.c s21_grep.h -i -e for> ./results.txt
grep -v -e k s21_grep.c s21_grep.h -i -e for> ./results_grep.txt 
diff -s ./results.txt ./results_grep.txt