cc = g++ -std=c++11
main: main.cpp Goods.o GoodsDataController.o User.o UserDataController.o Sorter.o OperationRecorder.o
	$(cc) main.cpp Goods.o GoodsDataController.o User.o UserDataController.o Sorter.o OperationRecorder.o -o main

OperationRecorder.o: OperationRecorder.cpp
	$(cc) -c OperationRecorder.cpp

Goods.o: Goods.cpp
	$(cc) -c Goods.cpp

GoodsDataController.o: GoodsDataController.cpp
	$(cc) -c GoodsDataController.cpp

User.o: User.cpp
	$(cc) -c User.cpp

UserDataController.o: UserDataController.cpp
	$(cc) -c UserDataController.cpp
	
Sorter.o: Sorter.cpp
	$(cc) -c Sorter.cpp
	
clean:
	del *.o main.exe
	
cleano:
	del *.o