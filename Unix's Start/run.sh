#! /bin/bash

statusfile=$(mktemp)
tmpscript=$(mktemp)

echo $1 >> $tmpscript
echo 'echo $? > '$statusfile >> $tmpscript
echo $1

chmod 777 $tmpscript
xterm $tmpscript

status=$(cat $statusfile)
rm $statusfile
rm $tmpscript

echo "RETURN CODE: "
echo $status

exit $status
