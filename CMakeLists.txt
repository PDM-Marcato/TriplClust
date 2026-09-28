cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(triplclust)

set (CMAKE_CXX_FLAGS "-O2")

# with MS Visual C++ we must explicity switch on proper exception handling
if (MSVC)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif (MSVC)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# all source files
#set(SRC src/cluster.cpp src/triplet.cpp src/main.cpp src/dnn.cpp src/hclust/fastcluster.cpp src/kdtree/kdtree.cpp src/pointcloud.cpp src/output.cpp src/option.cpp src/util.cpp src/graph.cpp src/run_clustering.cpp)
set(SRC src/cluster.cpp src/triplet.cpp src/dnn.cpp src/hclust/fastcluster.cpp src/kdtree/kdtree.cpp src/pointcloud.cpp src/output.cpp src/option.cpp src/util.cpp src/graph.cpp src/run_clustering.cpp)


# default target (created with "make")
#add_executable (triplclust ${SRC})

##create a library
add_library (triplclust SHARED ${SRC})

# webdemo target (created with "make demo")
#add_executable (triplclust-demo ${SRC})
#set_target_properties(triplclust-demo PROPERTIES EXCLUDE_FROM_ALL TRUE COMPILE_FLAGS "-DWEBDEMO")
#add_custom_target(demo DEPENDS triplclust-demo)



# --------------------------------
# Add pybind11 locally
# --------------------------------
add_subdirectory(pybind11)  # Assuming pybind11/ is in your project root

# --------------------------------
# Python bindings target
# --------------------------------
# This will be a separate .cpp file just for Python bindings
set(PYTHON_BINDINGS ${PROJECT_SOURCE_DIR}/src/python_bindings.cpp)

# Build the Python module linking against your existing Trackinglib
pybind11_add_module(pyTriplClust ${PYTHON_BINDINGS})

# Link it to your existing library 
target_link_libraries(pyTriplClust PRIVATE triplclust )

# Output the compiled .so into your project source directory for easy import
set_target_properties(pyTriplClust PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

