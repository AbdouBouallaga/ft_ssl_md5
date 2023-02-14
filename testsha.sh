printf 'echo "42 is nice" | openssl sha256\n'
echo "42 is nice" | openssl sha256
printf '\necho "42 is nice" | ./ft_ssl sha256\n'
echo "42 is nice" | ./ft_ssl sha256
printf '\necho "42 is nice" | ./ft_ssl sha256 -p\n'
echo "42 is nice" | ./ft_ssl sha256 -p
printf '\necho "Pity the living." | ./ft_ssl sha256 -q -r\n'
echo "Pity the living." | ./ft_ssl sha256 -q -r
printf '\necho "And above all," > file\n'
echo "And above all," > file
printf '\n./ft_ssl sha256 file\n'
./ft_ssl sha256 file
printf '\n./ft_ssl sha256 -r file\n'
./ft_ssl sha256 -r file
printf '\n./ft_ssl sha256 -s "pity those that aren'"'"'t following baerista on spotify."\n'
./ft_ssl sha256 -s "pity those that aren't following baerista on spotify."
printf '\necho "be sure to handle edge cases carefully" | ./ft_ssl sha256 -p file\n'
echo "be sure to handle edge cases carefully" | ./ft_ssl sha256 -p file
printf '\n echo "some of this will not make sense at first" | ./ft_ssl sha256 file\n'
echo "some of this will not make sense at first" | ./ft_ssl sha256 file
printf '\necho "but eventually you will understand" | ./ft_ssl sha256 -p -r file\n'
echo "but eventually you will understand" | ./ft_ssl sha256 -p -r file
printf '\necho "GL HF let'"'"'s go" | ./ft_ssl sha256 -p -s "foo" file\n'
echo "GL HF let's go" | ./ft_ssl sha256 -p -s "foo" file
printf '\necho "one more thing" | ./ft_ssl sha256 -r -p -s "foo" file -s "bar"\n'
echo "one more thing" | ./ft_ssl sha256 -r -p -s "foo" file -s "bar"
printf '\necho "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" file\n'
echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" file
rm file
printf '\n'
