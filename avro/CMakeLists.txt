find_program(AVRO_GENERATOR avrogencpp)
find_library(AVROCPP_LIB avrocpp)
find_package(Boost)

set(AVRO_SCHEMA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/schema)

# Cpp Avro is depends on Boost
if (AVRO_GENERATOR AND AVROCPP_LIB AND Boost_INCLUDE_DIR)

    source_group(src REGULAR_EXPRESSION src/.*)

    add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.hpp
        COMMAND "${AVRO_GENERATOR}" -i "${AVRO_SCHEMA_DIR}/Person.v1.avsc" -o ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.hpp -n avro_v1
        DEPENDS "${AVRO_SCHEMA_DIR}/Person.v1.avsc"
    )

    add_custom_command(
        OUTPUT  ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.hpp
        COMMAND "${AVRO_GENERATOR}" -i "${AVRO_SCHEMA_DIR}/Person.v2.avsc" -o ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.hpp -n avro_v2
        DEPENDS "${AVRO_SCHEMA_DIR}/Person.v2.avsc"
    )

    set(avro_GENERATED_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.hpp
    )

    add_executable(avro_simple src/simple.cc src/utils.cc ${avro_GENERATED_SOURCES})
    target_include_directories(avro_simple PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIR})
    target_link_libraries(avro_simple ${AVROCPP_LIB})

    add_executable(avro_upgrade_producer src/upgrade_producer.cc src/utils.cc ${avro_GENERATED_SOURCES})
    target_include_directories(avro_upgrade_producer PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIR})
    target_link_libraries(avro_upgrade_producer ${AVROCPP_LIB})

    add_executable(avro_upgrade_consumer src/upgrade_consumer.cc src/utils.cc ${avro_GENERATED_SOURCES})
    target_include_directories(avro_upgrade_consumer PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIR})
    target_link_libraries(avro_upgrade_consumer ${AVROCPP_LIB})

    install(TARGETS avro_simple avro_upgrade_producer avro_upgrade_consumer
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
    )

    add_test(run_example_avro_simple avro_simple)
    add_test(run_example_avro_producer avro_upgrade_producer "${AVRO_SCHEMA_DIR}")
    add_test(run_example_avro_consumer avro_upgrade_consumer "${AVRO_SCHEMA_DIR}")

else()
    if(NOT AVRO_GENERATOR OR NOT AVROCPP_LIB)
        message(STATUS "Project examle Avro is disabled. Missing ${AVRO_GENERATOR} or library avrocpp.")
    else()
        message(STATUS "Project examle Avro is disabled. Missing Boost library.")
    endif()
    
endif()
