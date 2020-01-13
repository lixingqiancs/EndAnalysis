#!/bin/bash

for i in {1..22}
do
	./determine_enriched_ends 5000 /lustre/lixingqian/bed2ends/ref/hg19.size chr${i} /lustre/lixingqian/bed2ends/GM3474/${1}.chr${i}.ends.C++.bedgraph > /lustre/lixingqian/bed2ends/GM3474/${1}.chr${i}.results &
done
wait
