#!/bin/sh

#this script was created by Mani on 09 June 2016

clear

echo "Welcome!"
echo ""
echo "NTFS devices found:"
diskutil list | grep NTFS | awk '{print $3}'
echo ""

ET=($(diskutil list | grep NTFS | awk '{print $3}'))
input="/etc/fstab"
label=1
read_fstab=1

#if fstab doesn't exists, I'll create it and I'll write an empty line
#I must write an empty line otherwise this script can't correctly read the file
if [ -f $input ]
then
	echo "Found fstab"
else
	touch $input
	echo "" | sudo tee -a $input
	echo "fstab didn't exist, it's been created"
fi

echo ""

#if fstab exists and it's empty, I'll add an empty line (see comment above)
while IFS= read -r line
do
	read_fstab=0
	break
done < $input

if [ "$read_fstab" = 1 ]
then
	echo "" | sudo tee -a $input
fi

#check NTFS devices, if they're not present in fstab I'll add them
#also solve a little problem on the files

for var in "${ET[@]}"
do
	label=1
	while IFS= read -r line
	do
		if [ "$line" = "LABEL=${var} none ntfs rw,auto,nobrowse" ]
		then
			label=0
			break
		fi
	done < $input
	
	if [ "$label" = 0 ]
	then
		echo "${var} already in fstab"
	else
		echo "${var} must be added"
		echo "LABEL=${var} none ntfs rw,auto,nobrowse" >> $input
		echo "Unmounting ${var} ..."
		diskutil umount ${var}
		echo "Re-mounting ${var} ..."
		diskutil mount ${var}
	fi
	
	cd /Volumes/${var}
	
	SAVEIFS=$IFS
	IFS=$(echo -en "\n\b")

	for f in *
	do
  		setfile -c "" -t "" "$f"
  		echo "File $var/$f controlled"
	done
	
	IFS=$SAVEIFS
done

echo ""
echo "Done! Open Volumes folder writing: "
echo ""
echo "open /Volumes"
echo ""
echo "and you will able to write on NTFS devices."