read n
t=1
res=1

while [ $t -le $n ]
do
    res=`expr $res \* $t`
    t=`expr $t + 1`
done

echo $res
