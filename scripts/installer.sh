#!/bin/bash

#this script was created by Mani on 10 June 2016

clear

echo "Installing daemon"
echo ""

file=""
dir=""
plist=""

#[[ $1 = /* ]] && dir="$1" || dir="$PWD/${1#./}"

file="${1}/.ntfs_writer/controller.sh"
plist="/Applications/NTFS_Writer.app/Contents/scripts/com.ntfs_writer.plist"

rm $plist
touch $plist

echo "Creating plist file ... "

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" >> $plist
echo "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">" >> $plist
echo "<plist version=\"1.0\">" >> $plist
echo "<dict>" >> $plist
echo "	<key>Label</key>" >> $plist
echo "	<string>com.ntfs_writer</string>" >> $plist
echo "	<key>ProgramArguments</key>" >> $plist
echo "	<array>" >> $plist
echo "	<string>$file</string>" >> $plist
echo "	<string>${1}</string>" >> $plist
echo "	</array>" >> $plist
echo "	<key>LaunchEvents</key>" >> $plist
echo "	<dict>" >> $plist
echo "		<key>com.apple.iokit.matching</key>" >> $plist
echo "		<dict>" >> $plist
echo "			<key>com.apple.device-attach</key>" >> $plist
echo "			<dict>" >> $plist
echo "				<key>IOProviderClass</key>" >> $plist
echo "				<string>IOUSBDevice</string>" >> $plist
echo "				<key>IOMatchLaunchStream</key>" >> $plist
echo "				<true/>" >> $plist
echo "			</dict>" >> $plist
echo "		</dict>" >> $plist
echo "	</dict>" >> $plist
echo "</dict>" >> $plist
echo "</plist>" >> $plist

#chmod 600 $plist
#chown root $plist

echo ""
echo "Copying plist file on system library folder ... "
sudo cp /Applications/NTFS_Writer.app/Contents/scripts/com.ntfs_writer.plist /Library/LaunchDaemons/
echo "Activating the daemon ... "
sudo launchctl load /Library/LaunchDaemons/com.ntfs_writer.plist

cd "${1}"
mkdir .ntfs_writer
cd .ntfs_writer

cp /Applications/NTFS_Writer.app/Contents/scripts/controller.sh "${1}/.ntfs_writer"

chmod u+x $file
chown root $file

echo ""
echo "Done! If there were no problems (no errors above) you can just plug an NTFS USB device, wait from 2 to 10 seconds and write it!"
echo "Thank you for installing :) "