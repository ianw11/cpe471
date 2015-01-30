#!/bin/sh
bindir=$(pwd)
cd /Users/Ian/Documents/Cal-Poly/cpe471/OpenGL-tutorial_v0014_21/misc05_picking/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/Debug/misc05_picking_slow_easy 
	else
		"/Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/Debug/misc05_picking_slow_easy"  
	fi
else
	"/Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/Debug/misc05_picking_slow_easy"  
fi
