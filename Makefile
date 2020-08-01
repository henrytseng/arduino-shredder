FQBN=arduino:avr:uno
PROGRAM=PaperShredder
PORT=/dev/ttyACM0

compile:
	arduino-cli compile --fqbn ${FQBN} ${PROGRAM}

show_boards:
	arduino-cli board list

upload:
	arduino-cli upload -p ${PORT} --fqbn ${FQBN} ${PROGRAM}

monitor:
	stty -F ${PORT} 9600 raw -clocal -echo
	cat ${PORT}

clean:
	rm -rf PaperShredder/build
