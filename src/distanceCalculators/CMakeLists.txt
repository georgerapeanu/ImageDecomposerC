set(HEADER_LIST 
"${ImageDecomposer_SOURCE_DIR}/include/distanceCalculators/EuclidianDistance.hpp"
"${ImageDecomposer_SOURCE_DIR}/include/distanceCalculators/ManhattanDistance.hpp"
)
set(CPP_LIST
EuclidianDistance.cpp
ManhattanDistance.cpp
)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library(distance_library ${CPP_LIST} ${HEADER_LIST})
target_include_directories(distance_library PUBLIC ${ImageDecomposer_SOURCE_DIR}/include)
target_compile_features(distance_library PUBLIC cxx_std_11)