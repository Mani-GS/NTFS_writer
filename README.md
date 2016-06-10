# NTFS writer
Write files on NTFS devices with MAC OS X.
This simple scritp allows you to write on NTFS partitions from your MAC, without buying anithing!
You must have root privileges to let it run!

# How to use
## Run the script manually
If you want to run the script manually, you can place in your desktop the file named **ntfs_writer.sh**.
Each time you want to run it you have to open a terminal window:
- press cmd + space;
- write "terminal" and press enter;
- write the following instructions:
```script
$ cd desktop
$ sudo ./ntfs_writer.sh
[insert your admin password]
```
## Install the daemon
You can install the daemon: in this way the script will start automatically when you plug an USB device into your MAC.
To install the daemon you must:
- press cmd + space;
- write "terminal" and press enter;
- write the following instruction:
```script
$ open /users/your_user_name
```
- your home will be open in a Finder window: create a folder named "bin" and, inside it, place the three files (preferably into a subfolder;
- back in the terminal window, write this:
```script
$ cd bin
[if you created a subfolder, execute also "cd subfolder-name"]
$ sudo ./installer.sh
[insert your admin password]
```
If you don't get errors, its done!

## Uninstall the daemon
If you want to uninstall the daemon, you just have to do this:
- press cmd + space;
- write "terminal" and press enter;
- write the following instruction:
```script
$ cd bin
[if you created a subfolder, execute also "cd subfolder-name"]
$ sudo ./uninstaller.sh
[insert your admin password]
```
If you don't get errors, its done!
