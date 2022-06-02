
out.exe : dx_Ball.cpp shapes.hpp
	g++ -Wall  -o out.exe dxBall.cpp  -I"SFML\\include" -L"SFML\\lib" -Llib -lsfml-system -lsfml-main -lsfml-window -lsfml-graphics