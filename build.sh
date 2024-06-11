#!/usr/bin/bash
COMPILER=clang++
CXXFLAGS="-Ofast -pipe"
BIN="bin"
EXEC="build"
FILES=$(find ./src -type f)
if [ ! -d $BIN ]; then
    mkdir -p "$BIN"
fi

for _file in $FILES
do
    ext="${_file##*.}"
    if [ $ext = "cc" ]; then
        fn=$(basename -- "$_file")
        obj_filename="${fn%.*}.o"
        new_filename="${BIN}/${obj_filename}"
        echo "compiling $fn"
        $COMPILER $CXXFLAGS -o $new_filename -c $_file &
    fi
done
wait

object_files=$(find ./bin -type f)

echo "Linking..."

$COMPILER -Wl,-O1 -fuse-ld=mold $object_files -o $BIN/$EXEC
wait
for _obj in $object_files
do
    rm $_obj
done
