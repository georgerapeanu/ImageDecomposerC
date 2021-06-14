set(HEADER_LIST 
"${ImageDecomposer_SOURCE_DIR}/include/drawers/EllipseDrawer.hpp"
"${ImageDecomposer_SOURCE_DIR}/include/drawers/TriangleDrawer.hpp"
"${ImageDecomposer_SOURCE_DIR}/include/drawers/CircleDrawer.hpp"
"${ImageDecomposer_SOURCE_DIR}/include/drawers/SquareDrawer.hpp"
"${ImageDecomposer_SOURCE_DIR}/include/drawers/RectangleDrawer.hpp"
)
set(CPP_LIST
EllipseDrawer.cpp
TriangleDrawer.cpp
CircleDrawer.cpp
SquareDrawer.cpp
RectangleDrawer.cpp
)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library(drawer_library ${CPP_LIST} ${HEADER_LIST})
target_include_directories(drawer_library PUBLIC ${ImageDecomposer_SOURCE_DIR}/include)
target_compile_features(drawer_library PUBLIC cxx_std_11)