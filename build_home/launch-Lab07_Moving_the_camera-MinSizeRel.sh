#!/bin/sh
bindir=$(pwd)
cd /Users/jon/Library/CloudStorage/Dropbox/Work/2023_2024/Graphics/Git repos/Lab07_Moving_the_camera/source/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/jon/Library/CloudStorage/Dropbox/Work/2023_2024/Graphics/Git\ repos/Lab07_Moving_the_camera/build_home/MinSizeRel/Lab07_Moving_the_camera 
	else
		"/Users/jon/Library/CloudStorage/Dropbox/Work/2023_2024/Graphics/Git\ repos/Lab07_Moving_the_camera/build_home/MinSizeRel/Lab07_Moving_the_camera"  
	fi
else
	"/Users/jon/Library/CloudStorage/Dropbox/Work/2023_2024/Graphics/Git\ repos/Lab07_Moving_the_camera/build_home/MinSizeRel/Lab07_Moving_the_camera"  
fi
