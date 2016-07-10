#!/bin/sh

palette="/tmp/palette.png"

filters="fps=6,scale=256:-1:flags=lanczos"

ffmpeg -v warning -i $1.mp4 -vf "$filters,palettegen" -y $palette
ffmpeg -v warning -i $1.mp4 -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse" -y $1.gif

ffmpeg -i $1.mp4 -codec:v libx264 -profile:v high -preset slow -b:v 500k -maxrate 500k -bufsize 1000k -threads 0 -pass 1 -an -f mp4 /dev/null
ffmpeg -i $1.mp4 -codec:v libx264 -profile:v high -preset slow -b:v 500k -maxrate 500k -bufsize 1000k -threads 0 -pass 2 -codec:a aac -b:a 128k -f mp4 $1-compressed.mp4
