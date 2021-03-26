#/bin/sh
./a.out "${1}" > res1
echo ${1} > res2
if diff res1 res2; then
	printf "OK!\n"
else
	printf "ERROR!\n"
fi
rm -fr res1 res2