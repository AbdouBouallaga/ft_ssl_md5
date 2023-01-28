#/bin/bash
printf "MD5 TESTs\n\n"
echo 'is md5("salt") a salted hash? :thonking_face:' > /tmp/file
./ft_ssl md5 /tmp/file
md5 /tmp/file
openssl md5 /tmp/file

printf "\nTEST ECHO VS NORMAL\n"
echo "Magic mirror" | ./ft_ssl md5 -p
./ft_ssl md5 -s "Magic mirror"
echo "Magic mirror" | md5 -p
md5 -s "Magic mirror"


printf "\nTest -q option\n"
md5 -q /tmp/file > a
./ft_ssl md5 -q /tmp/file > b
diff a b
printf "\nHERE IS A AND B FILES\n"
cat a b
rm a b

printf "\nTest -r option\n"
md5 -r /tmp/file
./ft_ssl md5 -r /tmp/file

printf "\nTest -p option\n"
echo "Magic mirror" | md5 -p
echo "Magic mirror" | ./ft_ssl md5 -p
echo "42 is nice" | md5 -p
echo "42 is nice" | ./ft_ssl md5 -p
