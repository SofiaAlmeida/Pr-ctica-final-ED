SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++
AR = ar rvs		
AR_MACOSX = libtool -static -o  
CPPFLAGS = -Wall -pedantic -g -std=c++11 -I$(INC) -c



all: $(BIN)/main $(BIN)/arboltablero_test
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

	
# ************ Compilación de módulos ************
$(BIN)/arboltablero_test: $(OBJ)/arboltablero_test.o $(OBJ)/conecta4.o $(LIB)/libtablero.a $(LIB)/libconecta4.a
	$(CXX) -o $(BIN)/arboltablero_test $(OBJ)/arboltablero_test.o $(OBJ)/conecta4.o -I$(INC) -L$(LIB) -ltablero

$(BIN)/main: $(SRC)/main.cpp $(LIB)/libconecta4.a $(LIB)/libtablero.a $(LIB)/libmando.a
	$(CXX) -std=c++11 -o $(BIN)/main $(SRC)/main.cpp -I$(INC) -L$(LIB) -lconecta4 -ltablero -lmando

$(LIB)/libtablero.a: $(OBJ)/tablero.o
	$(AR) $(LIB)/libtablero.a $(OBJ)/tablero.o

$(LIB)/libmando.a: $(OBJ)/mando.o
	$(AR)  $(LIB)/libmando.a $(OBJ)/mando.o

$(LIB)/libconecta4.a: $(OBJ)/conecta4.o
	$(AR) $(LIB)/libconecta4.a $(OBJ)/conecta4.o

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INC)/tablero.hpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/tablero.o $(SRC)/tablero.cpp -I$(INC)

$(OBJ)/arboltablero_test.o: $(SRC)/arboltablero_test.cpp $(INC)/tablero.hpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/arboltablero_test.o $(SRC)/arboltablero_test.cpp -I$(INC)

$(OBJ)/mando.o: $(SRC)/mando.cpp $(INC)/mando.hpp $(INC)/tablero.hpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/mando.o $(SRC)/mando.cpp -I$(INC)

$(OBJ)/conecta4.o: $(SRC)/conecta4.cpp $(INC)/conecta4.hpp	
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/conecta4.o $(SRC)/conecta4.cpp -I$(INC)
# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
