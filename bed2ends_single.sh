#!/bin/bash

for i in {1..22}
do
	./bed2ends /lustre/lixingqian/bed2ends/ref/hg19.size chr${i} /lustre/lixingqian/bed2ends/GM3474/${1}.chr${i} /lustre/lixingqian/bed2ends/GM3474/${1}.chr${i}.bed 
done
