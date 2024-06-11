#!/usr/bin/bash
COMPILER=clang++
CXXFLAGS="-O1 -pipe"
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
        #echo $_file
        fn=$(basename -- "$_file")
        obj_filename="${fn%.*}.o"
        #new_filename=$(echo $obj_filename | awk '{gsub("src","bin"); print}')
        new_filename="${BIN}/${obj_filename}"
        echo "compiling $fn"
        $COMPILER $CXXFLAGS -o $new_filename -c $_file
    fi
done

object_files=$(find ./bin -type f)

echo "Linking..."

$COMPILER -Wl,-O1 -fuse-ld=mold $object_files -o $BIN/$EXEC
