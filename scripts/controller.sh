#!/bin/sh

#this script was created by Mani on 19 June 2016

cd /Applications
result=$(ls | grep "NTFS_Writer.app")

if [ -n "$result" ]
then
	echo "App found."
	sudo /Applications/NTFS_Writer.app/Contents/scripts/ntfs_writer.sh
else
	echo "App NTFS Writer not found! Uninstalling Daemons ..."
	sudo launchctl unload /Library/LaunchAgents/com.ntfs_writer.plist
	sudo rm /Library/LaunchAgents/com.ntfs_writer.plist
	echo "Removing lines from fstab ..."
	sudo sed -i.bak '/#NTFS_Writer/d' /etc/fstab
	echo "Removing controller.sh ..."
	sudo rm -r "${1}/.ntfs_writer"
fi