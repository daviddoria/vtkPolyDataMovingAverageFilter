cmake_minimum_required(VERSION 2.6)

PROJECT(vtkPolyDataMovingAverageFilter)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(vtkPolyDataMovingAverageFilterExample vtkPolyDataMovingAverageFilter.cxx
vtkPolyDataMovingAverageFilterExample.cxx)

TARGET_LINK_LIBRARIES(vtkPolyDataMovingAverageFilterExample vtkHybrid )

