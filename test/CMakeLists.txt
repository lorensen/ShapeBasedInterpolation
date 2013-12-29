
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../filters )


ADD_EXECUTABLE( ShapeBasedInterpolationImageDemo ShapeBasedInterpolationImageDemo.cxx )
TARGET_LINK_LIBRARIES( ShapeBasedInterpolationImageDemo ${ITK_LIBRARIES} BinaryShapeBasedInterpolationImageFilters )


