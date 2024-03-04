cmake_minimum_required(VERSION 3.5)
project(driver)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# Indiquez que c'est un package ROS 2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)  
find_package(sensor_msgs REQUIRED)  

include_directories(include)

add_executable(driver_node src/MotorDriverNode.cpp)

ament_target_dependencies(driver_node
rclcpp
geometry_msgs
std_msgs
)

add_executable(calcul_node src/calculNode.cpp)

ament_target_dependencies(calcul_node
rclcpp
geometry_msgs
std_msgs
)



# add_executable(driver_6_node src/driver_6_Node.cpp)
# ament_target_dependencies(driver_6_node
# rclcpp
# geometry_msgs
# std_msgs
# )
# Indiquez les dépendances du package
# set(
#     dependencies
#     rclcpp
#     geometry_msgs
#     std_msgs
# )
# find_package(ament_cmake REQUIRED)
# foreach(dep ${dependencies})
#     find_package(${dep} REQUIRED)
# endforeach()


# Compilez le code dans le répertoire src
# add_executable(driver src/driver_node)
# ament_target_dependencies(driver_node ${dependencies})

    # Installez les exécutables dans le répertoire 'lib/motor_controller'
install(TARGETS
    driver_node
    calcul_node
    # driver_6_node
    #pixx_driver
    #pixx_odometry
    #pixx_fakedriver
    DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)

# Installez le fichier package.xml
ament_package()
                    
