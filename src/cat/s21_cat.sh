#!/bin/bash

function TestWithOptions() {
    ./s21_cat -$1 ../../data-samples/$2 > ./results.txt
    cat -$1 ../../data-samples/$2 > ./results_cat.txt
    diff -s ./results_cat.txt ./results.txt
}

function TestWithGnu() {
    ./s21_cat -$1 ../../data-samples/$2 > ./results.txt
    cat -$3 ../../data-samples/$2 > ./results_cat.txt
    diff -s ./results_cat.txt ./results.txt
}

function SimpleTest() {
    ./s21_cat ../../data-samples/$1 > ./results.txt
    cat ../../data-samples/$1 > ./results_cat.txt
    diff -s ./results.txt ./results_cat.txt
}

# чтобы сразу тесты запускать
make rebuild

array=(b n s e t)
gnu_array=(-number-nonblank -number -squeeze-blank)
name_array=(1.txt 2.txt 3.txt)
for item in ${array[*]}
do
    for name_item in ${name_array[*]}
    do
        printf "\n\tOPTION:%c FILE:%s\n" $item $name_item
        TestWithOptions "$item" "$name_item"
    done
done

for index in ${!gnu_array[*]}
do
    for name_item in ${name_array[*]}
    do
        printf "\n\tOPTION:-%s FILE:%s\n" ${gnu_array[$index]} $name_item
        TestWithGnu "${gnu_array[$index]}" "$name_item" "${array[$index]}"
    done
done

for name_item in ${name_array[*]}
do
    printf "\n\tOPTION:none FILE:%s\n" $name_item
    SimpleTest "$name_item"
done