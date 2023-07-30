#!/bin/bash
declare -A memory
# Function to allocate memory using Best-Fit algorithm
allocate_memory() {
local process=$1
local size=$2
local bestFit=-1
local bestFitSize=-1
for key in "${!memory[@]}"; do
local blockSize=${memory[$key]}
if [[ $blockSize -ge $size ]]; then
if [[ $bestFit -eq -1 || $blockSize -lt $bestFitSize ]]; then
bestFit=$key
bestFitSize=$blockSize
fi
fi
done
if [[ $bestFit -eq -1 ]]; then
echo "Insufficient memory to allocate $size KB for process $process"
return
fi
local remainingSize=$((bestFitSize - size))
if [[ $remainingSize -gt 0 ]]; then
memory[$bestFit]=$remainingSize
echo "Process $process allocated $size KB of memory starting at address $bestFit"
echo "Remaining block size at address $bestFit: $remainingSize KB"
else
unset memory[$bestFit]
echo "Process $process allocated $size KB of memory starting at address $bestFit"
fi
}
# Function to deallocate memory and merge adjacent free blocks
deallocate_memory() {
local process=$1
for key in "${!memory[@]}"; do
if [[ $key == $process ]]; then
unset memory[$key]
echo "Memory for process $process deallocated"
fi
done
# Merge adjacent free blocks
local merged=0
local sorted_keys=($(echo "${!memory[@]}" | tr ' ' '\n' | sort -n))
for ((i=0; i<${#sorted_keys[@]}-1; i++)); do
local current=${sorted_keys[$i]}
local next=${sorted_keys[$i+1]}
if ((current+memory[$current] == next)); then
memory[$current]=$((memory[$current]+memory[$next]))
unset memory[$next]
merged=1
fi
done
if [[ $merged -eq 1 ]]; then
echo "Adjacent free blocks merged"
fi
}
# Example usage
memory[0]=100 # Initial memory block of size 100 KB
memory[200]=50 # Another memory block of size 50 KB
echo "Initial Memory Status:"
for key in "${!memory[@]}"; do
echo "Address $key: ${memory[$key]} KB"
done
echo "----------------------------------"
# Allocate memory for processes
allocate_memory "P1" 30
allocate_memory "P2" 80
allocate_memory "P3" 70
echo "Memory Allocation Status:"
for key in "${!memory[@]}"; do
echo "Address $key: ${memory[$key]} KB"
done
echo "----------------------------------"
# Deallocate memory for processes
deallocate_memory "P2"
echo "Memory Deallocation Status:"
for key in "${!memory[@]}"; do
echo "Address $key: ${memory[$key]} KB"
done
echo "----------------------------------"
# Allocate memory for a new process
allocate_memory "P4" 40
echo "Memory Allocation Status:"
for key in "${!memory[@]}"; do
echo "Address $key: ${memory[$key]} KB"
done
echo "----------------------------------"

