main : SAHC.cpp
	g++ -std=c++23 -O3 -Wall -Wextra -Wpedantic SAHC.cpp -o SAHC

run : SAHC.cpp
	g++ -std=c++23 -O3 -Wall -Wextra -Wpedantic SAHC.cpp -o SAHC && ./SAHC

debug : SAHC.cpp
	g++ -std=c++23 -g -O0 -Wall -Wextra -Wpedantic SAHC.cpp -o SAHC && ~/gf/gf2 ./SAHC

profile : SAHC.cpp
	g++ -std=c++23 -g -pg SAHC.cpp -o SAHC && ./SAHC && gprof SAHC gmon.out > outputfile.txt

clear : SAHC.cpp
	rm -q SAHC outputfile.txt gmon.out data.txt
