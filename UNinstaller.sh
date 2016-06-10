#!/bin/sh

#this script was created by Mani on 10 June 2016

clear

sure=""

echo "Uninstalling daemon"
echo ""

printf "Are you sure you want to uninstall the daemon [y/n]?  "
read sure

echo ""

if [ $sure = "y" ]
then
	echo "Deactivating the daemon ... "
	sudo launchctl unload /Library/LaunchDaemons/com.ntfs_writer.plist
	echo "Removing the plist file ... "
	sudo rm /Library/LaunchDaemons/com.ntfs_writer.plist
	echo ""
	echo "Done! If there were no errors above, the daemon has been succesfully uninstalled!"
else
	echo "Abort and exit."
fi
