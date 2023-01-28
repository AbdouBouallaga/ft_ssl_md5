printf "SHA256 TESTs\n\n"
printf "\nNORMAL\n"
 ./ft_ssl sha256 -s "42 is nice"
printf "\n ECHO\n"
 echo "42 is nice" | ./ft_ssl sha256 
printf "\n ECHO -q\n"
 echo "42 is nice" | ./ft_ssl sha256 -q
printf "\n ECHO -p\n"
 echo "42 is nice" | ./ft_ssl sha256 -p
printf "\n ECHO -p\n"
 echo "42 is nice" | ./ft_ssl sha256 -p
printf "\n ECHO -p -s string\n"
 echo "42 is nice" | ./ft_ssl sha256 -p -s "42 is nice"
printf "\n ECHO -r -p -s string\n"
 echo "42 is nice" | ./ft_ssl sha256 -r -p -s "42 is nice"
printf "\n ECHO -r -p -s string -s string\n"
 echo "42 is nice" | ./ft_ssl sha256 -r -p -s "42 is nice" -s "42 is nice"
printf "\n string\n"
 ./ft_ssl sha256 -s "42 is nice"