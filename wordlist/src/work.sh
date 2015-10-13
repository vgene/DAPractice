f1="word_utf8_1_1000.md"
f2="word_utf8_1001_2000.md"
f3="word_utf8_2001_end.md"

for a in `seq 1 3`  
do
while read line
do
	if [[ `echo $line | grep "#" `!=" " ]]
	then	
		echo ${line} | grep "#"
	fi
	f="f"$a
done < $f1
done
