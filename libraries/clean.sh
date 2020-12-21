#!/bin/sh
for i in `find . -type d -name .git -print | sed 's#/.git##'`; do 
echo $i
rm -rf $i/.git
git rm --cached $i
git add $i
done
