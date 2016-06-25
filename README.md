# NTFS writer
Write files on NTFS devices with MAC OS X.
With this app you can copy files on your NTFS devices from your MAC.
You must have root privileges to let it run!

<<<<<<< HEAD
## Setup
First of all, put the app inside Applications folder. If you don't do this, the app can't start. Then, you must install the daemon to make the app works properly.
You only have to insert your admin password.

## The daemon
Every time you plug an USB device, the daemon will activate and check it. If it found some new NTFS devices, it add them to the fstab file.
From that moment, you won't see the NTFS devices on your desktop. You have to open the Volumes folder or create a link to it. You can use the app to do this.
If you'll remove the app from Applications folder without uninstalling the daemon, it will self-delete (when you plug an USB device), removing all the lines written on fstab and making visible to you all the devices associated.

## Copying files
To copy files you have to open the app, having an NTFS device plugged in and the daemon installed.
Just drag and drop all the files to copy in the app's drop area. Then, press copy.
It will alert if there are some files/folders with the same name on the device.

## Why using the app and not the Finder?
If you use the Finder to copy files (with the daemon installed), it will copy all of them on the device. And it seems to be ok, until you plug off the device.
The next time you plug it in, you'll see the files copied, but you will not able to open/copy/move them. Why? Because the Finder "forgets" to release them.
So, the OS will think that these files are in use, and it won't allow you to use them.
Using the app instead of the Finder will ensure you to correctly copy the files.

# How to build
To build this program make sure you installed all the **Qt** libraries.
Also be sure to export the _**qmake path**_ in this way:

=======
# Issues
When you write a file from a MAC to an NTFS device, you probably won't able to open/copy this file, because it's "in use from OS X". To fix it the script, when you plug in a NTFS device, run the SetFile instruction for every file in the device. This instrucion allow you to open/copy/move/delete the file.

# How to use
## Run the script manually
If you want to run the script manually, you can place in your desktop the file named **ntfs_writer.sh**.
Each time you want to run it you have to open a terminal window:
- press cmd + space;
- write "terminal" and press enter;
- write the following instructions:
>>>>>>> 5c66364150d07e9b91f888e495f035e6231cf3ad
```script
$ PATH=/users/<your_user>/Qt/<qt_version>/bin:$PATH
$ export PATH
```

First of all, download the [latest release](https://github.com/Mani-GS/NTFS_writer/releases/latest), then extract the source code in one folder. Open a terminal in that folder and execute:

```script
$ qmake -config release
$ make
```

Then right-click the app, select "Show package contents" and copy the "script" folder inside "Contents".
On a terminal, execute this:

```script
$ chmod 755 NTFS_Writer.app
```

If you want to run it on another MAC (a MAC without Qt libraries), you have to execute this:

```script
$ macdeployqt ./series.app
```

Double click the APP file, named **NTFS_Writer**, and the program will start!