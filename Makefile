main: src/main.cpp
	sudo g++ src/main.cpp -o asa src/objects.cpp src/AsaInteger.cpp src/AsaFloat.cpp src/AsaDouble.cpp src/AsaString.cpp src/AsaBigInteger.cpp src/AsaBigDouble.cpp
	sudo cp asa /bin/asa
	sudo mkdir -p /lib/asa
	sudo cp -r src/stdlib/* /lib/asa/
