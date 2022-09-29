#!/bin/bash
# if test -f test_1.cbc
# then 
# echo "exit file test_1.cbc"
# else 
# echo "file test_1.cbc not exit"
# fi
# echo "现在是早上么，回答y or n"
# read timeofday
# if test "$timeofday" = "y"
# then
# echo "现在是早上"
# elif [ "$timeofday" = "n" ]; then 
# echo "现在是下午"
# else
# echo "请输入 y or n"
# exit 1
# fi
# exit 0
rootProjectName="$1"
commitHook="commit-msg"
hookDir=".git/hooks"
if [ -z $rootProjectName ]
then
rootProjectName="okex"
fi
rootHookDir="./$rootProjectName/$hookDir"

okTradeHookDir="./$rootProjectName/ok_trade/$hookDir"

okWidgetHookDir="./$rootProjectName/ok_widget/$hookDir"

androidLuaProjectHookDir="./$rootProjectName/android_lua_project/$hookDir"

defiWalletHookDir="./$rootProjectName/defi_wallet/$hookDir"
if [ ! -d "$rootProjectName" ]
then
echo "$rootProjectName 目录缺失"
exit 1
fi
if [  ! -f "./$commitHook" ]
then
echo "$commitHook 文件缺失"
exit 1 
fi

for dir in $rootHookDir $okTradeHookDir $okWidgetHookDir $androidLuaProjectHookDir $defiWalletHookDir
do 
if [ ! -d "$dir" ]
then 
mkdir -p "$dir"
fi
done

for dir in $rootHookDir $okTradeHookDir $okWidgetHookDir $androidLuaProjectHookDir $defiWalletHookDir
do 
cp "./$commitHook" "$dir"
done

echo "现在是早上么，回答yes or no"
read timeofday
case "$timeofday" in
[yY] | [yY][Es][Ss]) echo "现在是早上";;
[nN][Oo]) echo "现在是下午";;
*) echo "输入错误";;
esac
exit 0