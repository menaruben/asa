main: src/main.cpp
	sudo g++ src/main.cpp -o asa src/AsaInteger.cpp src/AsaFloat.cpp src/AsaDouble.cpp
	sudo cp asa /bin/asa
	sudo mkdir -p /lib/asa
	sudo cp -r src/stdlib/* /lib/asa/
