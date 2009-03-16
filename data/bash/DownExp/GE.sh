#!/bin/sh

Dir=$(pwd)/data/bash/DownExp/Explain
#Dir="/usr/share/lazyword/bash/DownExp/Explain"
#echo $Dir
#1.Clean up the dir
rm $Dir/*

#2.Get the explain html and save
wget http://www.dict.cn/$1.htm -O $Dir/explain.txt

#3.Convert the GBK to UTF-8
find $Dir/ -type f -exec iconv -f GBK -t UTF-8 {} -o $Dir/convert.txt \;

#4.Take out the chinese explain to chinese.txt
grep mut_jies $Dir/convert.txt | sed -e :a -e 's/<[^>]*>//g;/</N;//ba' > $Dir/chinese.txt
