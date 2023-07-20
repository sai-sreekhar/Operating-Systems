read num1
read num2

read operator

if [ $operator == "+" ] 
then
  result=$(expr $num1 + $num2)
elif [ $operator == "-" ]
then
  result=$(expr $num1 - $num2)
elif [ $operator == "*" ]
then
  result=$(expr $num1 \* $num2)
elif [ $operator == "/" ]
then
  result=$(expr $num1 / $num2)
else
  echo "Invalid operator"
  exit 1
fi

echo "The result is: $result"
