#!/bin/sh

#this script was created by Mani on 10 June 2016

clear

echo "Uninstalling daemon"
echo ""

echo "Deactivating the daemon ... "
sudo launchctl unload /Library/LaunchAgents/com.ntfs_writer.plist
echo "Removing the plist file ... "
sudo rm /Library/LaunchAgents/com.ntfs_writer.plist
sudo rm -r "${1}/.ntfs_writer"
echo "Removing lines from fstab ..."
sudo sed -i.bak '/#NTFS_Writer/d' /etc/fstab

echo ""
echo "Done! If there were no errors above, the daemon has been succesfully uninstalled!"