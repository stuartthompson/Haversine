all:
	g++ -o haversine.exe haversine.cpp -std=c++11 -static-libgcc -static-libstdc++ -Ic:/stu/deps/include 

clean:
	rm *.exe
