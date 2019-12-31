gradepro: main.o class.o class_util.o student.o student_util.o file_utility.o
	g++ main.o class.o class_util.o student.o student_util.o file_utility.o -o gradepro

main.o: main.cpp
	g++ -c main.cpp

class.o: class.cpp
	g++ -c class.cpp

class_util.o: class_util.cpp
	g++ -c class_util.cpp

student.o: student.cpp
	g++ -c student.cpp

student_util.o: student_util.cpp
	g++ -c student_util.cpp

file_utility.o: file_utility.cpp
	g++ -c file_utility.cpp

clean:
	rm *.o gradepro