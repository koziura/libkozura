TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

# Debug configuration
CONFIG(debug, debug|release) {
	# Configuration name
	OUTPUT_DIR = debug
	TARGET_POSTFIX = d
	DEFINES += _DEBUG
	unix:QMAKE_CXXFLAGS = -g
}else{
	# Configuration name
	OUTPUT_DIR = release
	DEFINES += NDEBUG
}
#
win32:DEFINES += _CRT_SECURE_NO_WARNINGS _WIN32_WINDOWS WIN_OS _WIN32
DEFINES += __STDC_CONSTANT_MACROS __STDC_FORMAT_MACROS
#
DESTDIR = bin
#
# Temp objects output directory
OBJECTS_DIR = obj/$$OUTPUT_DIR
#
KOZURA_LIB = '$${PWD}/../'
# Check if the kstring file exists
! include($${KOZURA_LIB}/kstring.pri) {
	error("Couldn't find the kstring.pri file!")
}
#
! include($${KOZURA_LIB}/karray.pri) {
	error("Couldn't find the karray.pri file!")
}
#
! include($${KOZURA_LIB}/kvector.pri) {
	error("Couldn't find the kvector.pri file!")
}
#
! include($${KOZURA_LIB}/kbytearray.pri) {
	error("Couldn't find the kbytearray.pri file!")
}
#
SOURCES += \
	main.cpp
