while read w1 w2 w3 w4
do
	echo ${w2} >> wordlist.txt
done < list.txt
