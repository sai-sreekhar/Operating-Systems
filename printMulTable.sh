read number

# Print the table header
echo "Multiplication Table for $number"

# Print the table body
for i in {1..10}; do
  echo "$number * $i = $((number * i))"
done

