#/usr/bin/bash

echo "Running tester"
accept_count=0
reject_count=0
for i in {0..1000}
do
  ./script.rb 10 3 > out
  ./wumpus out > /dev/null
  if [ $? -eq 0 ]
  then
    accept_count=$((accept_count+1))
  else
    reject_count=$((reject_count+1))
  fi
done
echo "Accepted: " $accept_count
echo "Rejected: " $reject_count
