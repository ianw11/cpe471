#!/bin/sh
bindir=$(pwd)
cd /Users/Ian/Documents/Cal-Poly/cpe471/OpenGL-tutorial_v0014_21/tutorial11_2d_fonts/
export DYLD_LIBRARY_PATH=:$DYLD_LIBRARY_PATH

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		 -batch -command=$bindir/gdbscript  /Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/RelWithDebInfo/tutorial11_2d_fonts 
	else
		"/Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/RelWithDebInfo/tutorial11_2d_fonts"  
	fi
else
	"/Users/Ian/Documents/Cal-Poly/cpe471/CMake_binaries/RelWithDebInfo/tutorial11_2d_fonts"  
fi
