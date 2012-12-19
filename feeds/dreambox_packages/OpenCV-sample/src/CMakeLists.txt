PROJECT(opencv_example)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FIND_PACKAGE( OpenCV REQUIRED )

# Declare the target (an executable)
ADD_EXECUTABLE(opencv_facedetect  facedetect.cpp)
ADD_EXECUTABLE(opencv_minarea  minarea.cpp)
ADD_EXECUTABLE(opencv_drawing  drawing.cpp)


TARGET_LINK_LIBRARIES(opencv_facedetect  ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(opencv_minarea  ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(opencv_drawing  ${OpenCV_LIBS})

INSTALL(FILES opencv_facedetect DESTINATION /usr/bin)
INSTALL(FILES opencv_minarea DESTINATION /usr/bin) 
INSTALL(FILES opencv_drawing DESTINATION /usr/bin)  
INSTALL(FILES haarcascade_frontalface_alt.xml DESTINATION /usr/bin)
INSTALL(FILES haarcascade_eye.xml DESTINATION /usr/bin)
INSTALL(FILES catty.jpg DESTINATION /usr/bin)   
INSTALL(FILES catty-left.jpg DESTINATION /usr/bin)

#MESSAGE(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")



