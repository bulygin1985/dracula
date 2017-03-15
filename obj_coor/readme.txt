1) location.txt, seas.txt, sea.centers.txt : all coordinates are part of map [0,1] x [0,1]
2) Land locations are enumerated in Russian lexicographical rule. Exception : st_joseph 
3) Sea location  - in Russian lexicographical rule from number 61
4) Russian game land location cards number = location_index + 1,sea location = location_index + 61
5) Graph is represented as adjacency list : first number is vertex number, another in row are neighbours
6) land_param.txt - west/east = 1/0, city/town = 1/0, port/not = 1/0