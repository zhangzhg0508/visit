echo "yes" | ./build_visit3_2_2 --required --optional --mesagl --mpich --uintah --no-moab --no-pidx --no-visit --thirdparty-path /home/visit/third-party --makeflags -j4; python build_visit_docker_cleanup.py
