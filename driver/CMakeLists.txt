cmake_minimum_required(VERSION 3.5)
project(driver)

# Indiquez que c'est un package ROS 2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)

# Indiquez les dépendances du package
set(
    DEPENDENCIES
    rclcpp
    geometry_msgs
    std_msgs
)
find_package(ament_cmake REQUIRED)
foreach(dep ${dependencies})
    find_package(${dep} REQUIRED)
endforeach()

include_directories(include)

# Compilez le code dans le répertoire src
add_executable(driver src/MotorDriverNode.cpp)
ament_target_dependencies(driver ${dependencies})

    # Installez les exécutables dans le répertoire 'lib/motor_controller'
install(TARGETS
    driver
    DESTINATION lib/${PROJECT_NAME}
)

# Installez le fichier package.xml
ament_package()
                    
