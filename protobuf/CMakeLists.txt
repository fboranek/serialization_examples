
# Set variables:
# PROTOBUF_FOUND - Found the Google Protocol Buffers library (libprotobuf & header files)
# PROTOBUF_INCLUDE_DIRS - Include directories for Google Protocol Buffers
# PROTOBUF_LIBRARIES - The protobuf libraries
# PROTOBUF_LIBRARY - The protobuf library
# PROTOBUF_PROTOC_LIBRARY   - The protoc library
# PROTOBUF_INCLUDE_DIR - The include directory for protocol buffers
# PROTOBUF_PROTOC_EXECUTABLE - The protoc compiler
find_package(Protobuf)

set(PROTO_DEFINITION_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)

if (PROTOBUF_FOUND)
    source_group(src REGULAR_EXPRESSION src/.*)

    set(proto_GENERATED_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/proto")
    file(MAKE_DIRECTORY ${proto_GENERATED_OUT_DIR})

    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.pb.h
            ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.pb.cc
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}" "--proto_path=${PROTO_DEFINITION_DIR}" "${PROTO_DEFINITION_DIR}/Person.v1.proto"
        DEPENDS "${PROTO_DEFINITION_DIR}/Person.v1.proto"
    )

    add_custom_command(
        OUTPUT
            ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.pb.h
            ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.pb.cc
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} "--cpp_out=${CMAKE_CURRENT_BINARY_DIR}" "--proto_path=${PROTO_DEFINITION_DIR}" "${PROTO_DEFINITION_DIR}/Person.v2.proto"
        DEPENDS "${PROTO_DEFINITION_DIR}/Person.v2.proto"
    )

    set(proto_GENERATED_SOURCES
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.pb.h
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v1.pb.cc
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.pb.h
        ${CMAKE_CURRENT_BINARY_DIR}/Person.v2.pb.cc
    )


    add_executable(proto_simple src/simple.cc ${proto_GENERATED_SOURCES})
    target_include_directories(proto_simple PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${PROTOBUF_INCLUDE_DIRS})
    target_link_libraries(proto_simple ${PROTOBUF_LIBRARIES})

    add_executable(proto_upgrade_producer src/upgrade_producer.cc ${proto_GENERATED_SOURCES})
    target_include_directories(proto_upgrade_producer PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${PROTOBUF_INCLUDE_DIRS})
    target_link_libraries(proto_upgrade_producer ${PROTOBUF_LIBRARIES})

    install(TARGETS proto_simple proto_upgrade_producer
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
    )

    add_test(run_example_proto_simple proto_simple)
    add_test(run_example_proto_upgrade_producer proto_upgrade_producer)
    
else()
    message(STATUS "Project examle Protobuf is disabled. Missing tool ${PROTO_GEN}.")
endif()
