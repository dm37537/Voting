all:

Voting.log:
	git log > Voting.log

Doxyfile:
	doxygen -g

html: Doxyfile Voting.h Voting.c++ RunVoting.c++ TestVoting.c++
	doxygen Doxyfile

RunVoting: Voting.h Voting.c++ RunVoting.c++
	g++-4.7 -std=c++11 -Wall -Wno-sign-compare Voting.c++ RunVoting.c++ -o RunVoting

RunVoting.out: RunVoting RunVoting.in
	RunVoting < RunVoting.in > RunVoting.out

RunVoting.tmp: RunVoting RunVoting.in
	RunVoting < RunVoting.in > RunVoting.tmp
	diff RunVoting.tmp RunVoting.out

TestVoting: Voting.h Voting.c++ TestVoting.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lgtest_main -lpthread

TestVoting.out: TestVoting
	valgrind TestVoting        >  TestVoting.out 2>&1
	gcov-4.7 -b Voting.c++     >> TestVoting.out
	gcov-4.7 -b TestVoting.c++ >> TestVoting.out

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunVoting
	rm -f RunVoting.out
	rm -f RunVoting.tmp
	rm -f TestVoting
	rm -f TestVoting.out

scrub:
	make --no-print-directory clean
	rm -f Voting.log
	rm -f Doxyfile
	rm -rf html
	rm -rf latex
