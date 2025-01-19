#! /bin/bash

docker run -i -v $(pwd):/workspace l4t_r32.5.0:latest bash -c "cd workspace/scripts && ./l4t_build.sh"
