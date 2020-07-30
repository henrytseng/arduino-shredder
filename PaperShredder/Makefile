FQBN=arduino:avr:uno
PROGRAM=shredder
PORT=/dev/ttyACM0

compile:
	arduino-cli compile --fqbn ${FQBN} ${PROGRAM}

show_boards:
	arduino-cli board list

upload:
	arduino-cli upload -p ${PORT} --fqbn ${FQBN} ${PROGRAM}

