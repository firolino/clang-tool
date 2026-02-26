set(CLANG_TOOL_SRC
    main.cc
    actions/frontendaction.cc
    consumer/consumer.cc
    transformer/transformer.cc
    transformer/functioncalltransformer.cc
    finder/finder.cc
    finder/integervariablefinder.cc
)

add_executable(clang-tool ${CLANG_TOOL_SRC})
target_link_libraries(clang-tool PRIVATE clang-cpp LLVM)
target_compile_definitions(clang-tool PRIVATE
    CLANG_RESOURCE_DIR="${LLVM_LIBRARY_DIR}/clang/${LLVM_VERSION_MAJOR}"
)
