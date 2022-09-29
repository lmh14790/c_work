#!/bin/bash
# for file in $(ls *.c)
# do
# echo "$file"
# done
# exit 0
#====================
# echo "输入密码"
# read pwd
# until [ "$pwd" = "110" ]
# do
# echo "密码错误,请重新输入"
# read pwd
# done
# exit 0
#====================
# echo "输入密码"
# read pwd
# when [ "$pwd" != "110" ]
# do
# echo "密码错误,请重新输入"
# read pwd
# done
# exit 0
until who | grep "$1" > /dev/null
do 
sleep 60
done 
echo -e '\a'
echo "********** $1 has just log in *********"
exit 0
