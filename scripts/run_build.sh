#! /bin/bash

docker run --privileged --cpus 8 --platform linux/arm64/v8 --rm -v $(pwd):/workspace l4t_r32.5.0:2.0 bash -c "cd workspace/scripts && ./l4t_build.sh"
