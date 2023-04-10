SRC_PATH := src
INP_FILE_LIST := main.cpp SinhVien.cpp Menu.cpp
OUT_FILE_NAME := main
EXE_EXPANSION := exe
I_EXPANSION := i

all: build run

build:
	cd ${SRC_PATH}; \
	g++ ${INP_FILE_LIST} -o ${OUT_FILE_NAME}.${EXE_EXPANSION}

run:
	${SRC_PATH}\${OUT_FILE_NAME}

i_file:
	cd ${SRC_PATH}; \
	g++ -E ${INP_FILE_LIST} -o ${OUT_FILE_NAME}.${I_EXPANSION}