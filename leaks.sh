#!/bin/bash

#add system("leaks lem-in >> leaks.txt") before return in main
#add system("leaks lem-in >> error_leaks.txt") before exit(1)

./lem-in < test_maps/augment_1.map > /dev/null
./lem-in < test_maps/valid_3hash_comment.map > /dev/null
./lem-in < test_maps/invalid_end.map > /dev/null 2>&1
./lem-in < test_maps/invalid_coord.map > /dev/null 2>&1
./lem-in < test_maps/invalid_double_ant_number.map > /dev/null 2>&1
./lem-in < test_maps/invalid_double_start.map > /dev/null 2>&1
./lem-in < test_maps/invalid_empty_line.map > /dev/null 2>&1
./lem-in < test_maps/invalid_room_name_#.map > /dev/null 2>&1
./lem-in < test_maps/invalid_room_name_with_dash.map > /dev/null 2>&1
./lem-in < test_maps/invalid_room_name_L.map > /dev/null 2>&1
wait

cat leaks.txt | grep "leaked bytes"
cat error_leaks.txt | grep "leaked bytes"