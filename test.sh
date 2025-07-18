set -eu
set -o pipefail

mkdir -p build/
verify() {
 if ! "$CC" -std=c23 "$1" -I "$2" -o build/run; then
   echo "compile failed: $CC -std=c23 $1 -I $2"
   exit 1
 fi
 if ! build/run | md5sum | grep -q "$3"; then
   echo "run failed: $1 $2"
   exit 1
 fi
}

verify brute_force.c 12x12_simple 4fa4c109fbe377d4314b191b7a508f4a
verify brute_force.c 16x16_embed 2cf4c7aecbcd621395471be3a140d66e

verify graph_color.c 12x12_simple 4fa4c109fbe377d4314b191b7a508f4a
verify graph_color.c 16x16_embed 2cf4c7aecbcd621395471be3a140d66e
verify graph_color.c 9x9_antibrute 990e2d99fface43030c1246a820db879
verify graph_color.c 9x9_tdoku d89988b8b41f9c9485de73894a203b2e

verify brute_force_c2y.c 12x12_simple 4fa4c109fbe377d4314b191b7a508f4a
verify brute_force_c2y.c 16x16_embed 2cf4c7aecbcd621395471be3a140d66e

verify graph_color_c2y.c 12x12_simple 4fa4c109fbe377d4314b191b7a508f4a
verify graph_color_c2y.c 16x16_embed 2cf4c7aecbcd621395471be3a140d66e
verify graph_color_c2y.c 9x9_antibrute 990e2d99fface43030c1246a820db879
verify graph_color_c2y.c 9x9_tdoku d89988b8b41f9c9485de73894a203b2e
