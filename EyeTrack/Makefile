CCX=g++
OPENFACE_DIR=/home/seniordesign/eye-track/OpenFace/
OPENCV=`pkg-config --libs --cflags opencv4`
OPENBLAS=`pkg-config --libs --cflags openblas`

INCLUDEDIR=-I$(OPENFACE_DIR)lib/local/
INC_UTIL=$(INCLUDEDIR)Utilities/include/
INC_LAND=$(INCLUDEDIR)LandmarkDetector/include/
INC_GAZE=$(INCLUDEDIR)GazeAnalyser/include/
INC_FACE=$(INCLUDEDIR)FaceAnalyser/include/
INC_CPP=$(INCLUDEDIR)CppInerop/include/

CFLAGS=$(INC_UTIL) $(INC_LAND) $(INC_GAZE) $(INC_FACE) $(INC_CPP)

BUILDDIR=$(OPENFACE_DIR)build/lib/local
BUILDLIB=-L$(BUILDDIR)
BUILD_UTIL=$(BUILDLIB)/Utilities/ -l Utilities
BUILD_LAND=$(BUILDLIB)/LandmarkDetector/ -l LandmarkDetector
BUILD_GAZE=$(BUILDLIB)/GazeAnalyser/ -l GazeAnalyser
BUILD_FACE=$(BUILDLIB)/FaceAnalyser/ -l FaceAnalyser

LIBS=$(BUILD_UTIL) $(BUILD_LAND) $(BUILD_GAZE) $(BUILD_FACE) -lz -pthread

DLIBDIR=/usr/local/lib/
DLIBLIB=-L$(DLIBDIR)

INCBOOST=-I/usr/include/boost/
BOOSTLIBS=-L/usr/lib/x86_64-linux-gnu/ -lboost_atomic -lboost_chrono -lboost_container -lboost_context -lboost_coroutine -lboost_date_time -lboost_exception -lboost_fiber -lboost_filesystem -lboost_graph -lboost_graph_parallel -lboost_iostreams -lboost_locale -lboost_log -lboost_log_setup -lboost_math_c99 -lboost_math_c99f -lboost_math_c99l -lboost_math_tr1 -lboost_math_tr1f -lboost_math_tr1l -lboost_system


all: 
	$(CCX) -o test eye_tracking.cpp $(CFLAGS) $(LIBS) $(OPENCV) $(OPENBLAS) $(DLIBLIB) -ldlib $(INCBOOST) $(BOOSTLIBS)
	$(CCX) -o client client.cpp $(CFLAGS) $(LIBS) $(OPENCV) $(OPENBLAS) $(DLIBLIB) -ldlib $(INCBOOST) $(BOOSTLIBS) 

debug:
	$(CCX) -o test eye_tracking.cpp $(CFLAGS) $(LIBS) $(OPENCV) $(OPENBLAS) $(DLIBLIB) -ldlib $(INCBOOST) $(BOOSTLIBS) -g	

clean:
	rm test
